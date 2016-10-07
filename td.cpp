#include "td.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include "constants.hpp"
#include "functions.hpp"

TD::TD(std::string dn, bool isB)
    : Learner(isB), dirname(dn), training_count(0) {
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
    if (L < 3){
        std::cout << "ERROR: L < 3\n";
        std::exit(0);
    }
    if (N.front() != SIZE2){
        std::cout << "ERROR: N != SIZE2\n";
        std::exit(0);
    }
    if(N.back() != 1){
        std::cout << "ERROR: N != 1\n";
        std::exit(0);
    }

    double lambda, alpha, lambda2;
    bool dropout;
    file_para >> epsilon >> lambda >> alpha >> lambda2 >> dropout;

    network = new Network(N, lambda, alpha, lambda2, dropout);

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
    File << "Training Count: " << training_count << std::endl;
}

bool TD::isMan() const { return false; }

int TD::getPos(const std::array<Stone, SIZE2> &board, int color) const {
    static std::random_device seed_gen;
    static std::mt19937 mt(seed_gen());
    static std::uniform_real_distribution<> drand(0.0, 1.0);

    // 取りうる全ての action を得る
    std::vector<int> v;
    getAllValidPos(board, color, v);

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
            std::array<Stone, SIZE2> board_cpy = board;
            putStone(board_cpy, color, pos);
            double val = getValue(board_cpy, color);
            if (val > val_max) {
                val_max = val;
                pos_opt = pos;
            }
        }
    }
    return pos_opt;
}

void TD::train(const std::array<Stone, SIZE2> &board, int step, Stone mycolor,
               int color) {
    // mycolor 視点の value を求めたいので、arr2vec は全て mycolor に基づく
    // ゲーム終了なら勝敗に応じた reward を return とする
    if (isEnd(board)) {
        vector<int> vboard(SIZE2), vboard_old(SIZE2);
        arr2vec(board, vboard, mycolor);
        arr2vec(board_old, vboard_old, mycolor);

        int winner = getWinner(board);
        double reward;
        if (winner == mycolor)
            reward = 1.0;
        else if (winner == getOpponentColor(mycolor))
            reward = -1.0;
        else
            reward = 0.0;
        network->train(vboard_old, reward);
        network->train(vboard, reward);
        training_count++;
        return;
    }

    // afterstate なので、自分の番では更新しない
    if (mycolor == color) return;

    // 初手なら更新しない
    if (step == 0 || step == 1) {
        board_old = board;
        network->unset_et();
        return;
    }

    // TD(lambda)
    vector<int> vboard_old(SIZE2);
    arr2vec(board_old, vboard_old, mycolor);
    double value = getValue(board, mycolor);
    network->train(vboard_old, value);

    board_old = board;
}

double TD::getValue(const std::array<Stone, SIZE2> &board, int color) const {
    vector<int> vboard(SIZE2);
    arr2vec(board, vboard, color);
    return network->getValue(vboard);
}

double TD::getValue(const vector<int> &vboard) const{
    return network->getValue(vboard);
}

// 自分の石なら+1、相手の石なら-1、空きなら0と表現する
void TD::arr2vec(const std::array<Stone, SIZE2> &board, vector<int> &vboard,
                 int color) const {
    vboard.clear();
    // Stone が -1, 0, 1 であることを仮定している
    for (int i = 0; i < SIZE2; i++) vboard(i) = board[i] * color;
}
