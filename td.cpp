#include "td.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include "constants.hpp"
#include "functions.hpp"

TD::TD(int b[64], int pID, std::string dn, bool isB)
    : Learner(b, pID), dirname(dn), isBattle(isB) {
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
    if (L < 3 || N.front() !=128 || N.back() != 1) {
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
}

bool TD::isMan() const { return false; }

int TD::getPos() const {
    static std::random_device seed_gen;
    static std::mt19937 mt(seed_gen());
    static std::uniform_real_distribution<> drand(0.0, 1.0);

    // 取りうる全ての action を得る
    std::vector<int> v;
    getPuttablePos(board, playerID, v);

    int pos;
    // epsilon の確率でランダムな場所に置く
    if (drand(mt) < epsilon && !isBattle) {
        pos = v[static_cast<int>(drand(mt) * v.size())];
    } else {
        // 貪欲には、取りうる全ての action に対して state value を最大にする pos
        // を選ぶ
        int pos_opt;
        double val_max = -1.0e128;
        for (size_t i = 0; i < v.size(); i++) {
            pos = v[i];
            int b[64];
            for (int i = 0; i < 64; i++) b[i] = board[i];
            putStone(b, playerID, pos);
            vector<int> vec(128);
            arr2vec(b, vec);
            double val = network->getValue(vec);
            if (val > val_max) {
                val_max = val;
                pos_opt = pos;
            }
        }
        pos = pos_opt;
    }
    return pos;
}

int TD::getOpponentPos() const {
    static std::random_device seed_gen;
    static std::mt19937 mt(seed_gen());
    static std::uniform_real_distribution<> drand(0.0, 1.0);

    std::vector<int> v;
    getPuttablePos(board, 1 - playerID, v);

    int pos;
    if (drand(mt) < epsilon) {
        pos = v[static_cast<int>(drand(mt) * v.size())];
    } else {
        int pos_opt;
        double val_min = 1.0e128;
        for (size_t i = 0; i < v.size(); i++) {
            pos = v[i];
            int b[64];
            for (int i = 0; i < 64; i++) b[i] = board[i];
            putStone(b, 1 - playerID, pos);
            vector<int> vec(128);
            arr2vec(b, vec);
            double val = network->getValue(vec);
            if (val < val_min) {
                val_min = val;
                pos_opt = pos;
            }
        }
        pos = pos_opt;
    }
    return pos;
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

void TD::train(int t, int pID) {
    vector<int> bd(128), bd_old(128);
    arr2vec(board, bd);
    arr2vec(board_old, bd_old);

    // ゲーム終了なら勝敗に応じた reward を return とする
    if (isEnd(board)) {
        int winner = getWinner(board);
        double reward;
        if (winner == playerID)
            reward = 1.0;
        else if (winner == 1 - playerID)
            reward = 0.0;
        else
            reward = 0.5;
        network->train(bd_old, reward);
        network->train(bd, reward);
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
    double val = network->getValue(bd);
    network->train(bd_old, val);

    for (int i = 0; i < 64; i++) board_old[i] = board[i];
}

double TD::getValue(const int b[64]) const {
    vector<int> bd(128);
    arr2vec(b, bd);
    return network->getValue(bd);
}
