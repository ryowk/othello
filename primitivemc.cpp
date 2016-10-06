#include "primitivemc.hpp"
#include "constants.hpp"
#include "functions.hpp"

#include <algorithm>
#include <ctime>
#include <random>
#include <vector>

PrimitiveMC::PrimitiveMC(double tl) : Player(), time_limit(tl) {}
PrimitiveMC::~PrimitiveMC() {}

bool PrimitiveMC::isMan() const { return false; }

int PrimitiveMC::getPos(const std::array<Stone, SIZE2> &board, int color) const {
    clock_t ct1 = clock();

    std::vector<int> v;
    getAllValidPos(board, color, v);
    std::vector<int> rate(v.size());
    std::fill(rate.begin(), rate.end(), 0);

    // time_limit になるまでサンプリングする
    double time;
    do {
        for (size_t i = 0; i < v.size(); i++) {
            int pos = v[i];
            // pos に置いてプレイアウトした時の勝敗を取得する
            int winner = playout(board, color, pos);
            if (winner == color)
                rate[i]++;
            else if (winner == getOpponentColor(color))
                rate[i]--;
        }
        clock_t ct2 = clock();
        time = static_cast<double>(ct2 - ct1) / CLOCKS_PER_SEC;
    } while (time < time_limit);

    auto rate_max = std::max_element(rate.begin(), rate.end());
    return v[rate_max - rate.begin()];
}

// board に pos を置いてからプレイアウトして勝ち負け分けを返す
int PrimitiveMC::playout(const std::array<Stone, SIZE2> &board, int color, int pos) const {
    static std::random_device seed_gen;
    static std::mt19937 mt(seed_gen());
    static std::uniform_int_distribution<> rand64(0, SIZE2-1);
    // 最初に pos に石を置き、それを元にプレイアウトする
    std::array<Stone, SIZE2> board_cpy = board;
    putStone(board_cpy, color, pos);
    color = getOpponentColor(color);

    while (1) {
        if (!isPuttableBoard(board_cpy, color)) {
            color = getOpponentColor(color);
            if (!isPuttableBoard(board_cpy, color)) break;
        }

        while (1) {
            if (putStone(board_cpy, color, rand64(mt))) break;
        }
        color = getOpponentColor(color);
    }
    return getWinner(board_cpy);
}
