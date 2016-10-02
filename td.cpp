#include "td.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include "constants.hpp"
#include "functions.hpp"

TD::TD(int b[64], int pID, std::string dn, bool isB)
    : Learner(b, pID), dirname(dn), isBattle(isB), training_count(0) {
    read();
}

TD::~TD() { delete network; }

void TD::read() {
    std::string fname_para = dirname + "param";
    std::ifstream file_para(fname_para, std::ios::in);
    if (file_para.fail()) {
        std::cout << "No " << fname_para << std::endl;
        std::exit(0);
    }
    int L;
    std::vector<int> N;
    file_para >> L;
    for (int i = 0; i < L; i++) {
        int temp;
        file_para >> temp;
        N.push_back(temp);
    }
    if (L < 3 || N.front() != 128 || N.back() != 1) {
        std::cout << "N should be 128 *,..., *, 1.\n";
        std::exit(0);
    }

    double lambda, lambda2;
    bool dropout;
    file_para >> epsilon >> lambda >> lambda2 >> dropout;

    network = new Network(N, lambda, lambda2, dropout);

    // 学習済みデータを読み込み
    std::string fname_data = dirname + "coeff";
    std::ifstream file_data(fname_data, std::ios::in);
    if (!file_data.fail()) {
        network->read(file_data);
    } else {
        std::cout << fname_data << " is created." << std::endl;
        network->init();
    }
}

void TD::write() const {
    // std::ios::out : ファイルが有ってもなくても新しく作りなおす
    std::string fname_data = dirname + "coeff";
    std::ofstream File(fname_data, std::ios::out);
    network->write(File);
    File << "Training Count: " << training_count;
}

bool TD::isMan() const { return false; }

int TD::getPos() const {
    static std::random_device seed_gen;
    static std::mt19937 mt(seed_gen());
    static std::uniform_real_distribution<> drand(0.0, 1.0);

    // 取りうる全ての action を得る
    std::vector<int> v;
    getPuttablePos(board, playerID, v);

    int pos_opt;
    // epsilon の確率でランダムな場所に置く
    if (drand(mt) < epsilon && !isBattle) {
        pos_opt = v[static_cast<int>(drand(mt) * v.size())];
    } else {
        // 貪欲には、取りうる全ての action に対して state value を最大にする pos
        // を選ぶ
        double val_max = -1.0e128;
        for (size_t i = 0; i < v.size(); i++) {
            int pos = v[i];
            int b[64];
            for (int i = 0; i < 64; i++) b[i] = board[i];
            putStone(b, playerID, pos);
            double val = getValue(b);
            if (val > val_max) {
                val_max = val;
                pos_opt = pos;
            }
        }
    }
    return pos_opt;
}

int TD::getOpponentPos() const {
    static std::random_device seed_gen;
    static std::mt19937 mt(seed_gen());
    static std::uniform_real_distribution<> drand(0.0, 1.0);

    std::vector<int> v;
    getPuttablePos(board, 1 - playerID, v);

    int pos_opt;
    if (drand(mt) < epsilon && !isBattle) {
        pos_opt = v[static_cast<int>(drand(mt) * v.size())];
    } else {
        double val_min = 1.0e128;
        for (size_t i = 0; i < v.size(); i++) {
            int pos = v[i];
            int b[64];
            for (int i = 0; i < 64; i++) b[i] = board[i];
            putStone(b, 1 - playerID, pos);
            double val = getValue(b);
            if (val < val_min) {
                val_min = val;
                pos_opt = pos;
            }
        }
    }
    return pos_opt;
}

void TD::train(int t, int pID) {
    // ゲーム終了なら勝敗に応じた reward を return とする

    // 対称操作
    // 逐次的に対称操作を施すので、全ての状態を得るため
    // 1, x, y, x, opponent, x, y, x の順に変換を行う
    static int (*symm_trans[8])(vector<int> &) = {
        identity_trans, x_mirror, y_mirror, x_mirror,
        player_trans,   x_mirror, y_mirror, x_mirror};

    if (isEnd(board)) {
        vector<int> bd(128), bd_old(128);
        arr2vec(board, bd);
        arr2vec(board_old, bd_old);

        int winner = getWinner(board);
        double reward;
        if (winner == playerID)
            reward = 1.0;
        else if (winner == 1 - playerID)
            reward = 0.0;
        else
            reward = 0.5;
        for(int i=0; i<8; i++){
            int parity = symm_trans[i](bd_old);
            symm_trans[i](bd);
            if(parity) reward = 1.0 - reward;
            network->train(bd_old, reward, i);
            network->train(bd, reward, i);
        }
        training_count++;
        return;
    }

    // afterstate なので、自分の番では更新しない
    if (pID == playerID) return;

    // 初手なら更新しない
    if (t == 0 || t == 1) {
        for (int i = 0; i < 64; i++) board_old[i] = board[i];
        network->unset_et();
        return;
    }

    // TD(lambda)
    vector<int> bd_old(128);
    arr2vec(board_old, bd_old);
    double value = getValue(board);
    for (int i = 0; i < 8; i++) {
        int parity = symm_trans[i](bd_old);
        if(parity) value = 1.0 - value;
        network->train(bd_old, value, i);
    }

    for (int i = 0; i < 64; i++) board_old[i] = board[i];
}

double TD::getValue(const int b[64]) const {
    vector<int> bd(128);
    arr2vec(b, bd);
    return network->getValue(bd);
}

// 配列から boost のベクトルに変換する
void TD::arr2vec(const int b[64], vector<int> &v) const {
    v.clear();
    for (int i = 0; i < 64; i++) {
        if (b[i] == playerID)
            v(2 * i) = 1;
        else if (b[i] == 1 - playerID)
            v(2 * i + 1) = 1;
    }
}

// 対称操作たち
// 自分なら0を返し、相手なら1を返す
int TD::identity_trans(vector<int> &v) {return 0;}

int TD::x_mirror(vector<int> &v) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            int pos1 = 8 * y + x;
            int pos2 = 8 * y + (7 - x);
            for (int i = 0; i < 2; i++) {
                std::swap(v(2 * pos1 + i), v(2 * pos2 + i));
            }
        }
    }
    return 0;
}

int TD::y_mirror(vector<int> &v) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            int pos1 = 8 * y + x;
            int pos2 = 8 * (7 - y) + x;
            for (int i = 0; i < 2; i++) {
                std::swap(v(2 * pos1 + i), v(2 * pos2 + i));
            }
        }
    }
    return 0;
}

int TD::player_trans(vector<int> &v) {
    for (int i = 0; i < 64; i++) {
        std::swap(v(2 * i), v(2 * i + 1));
    }
    return 1;
}
