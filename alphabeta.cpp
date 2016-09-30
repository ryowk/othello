#include "alphabeta.hpp"
#include <ctime>
#include "functions.hpp"
#include <cstring>

AlphaBeta::AlphaBeta(int b[64], int pID, double tl)
    : Player(b, pID), time_limit(tl), h_corner(100), h_win(10000) {}
AlphaBeta::~AlphaBeta() {}

bool AlphaBeta::isMan() const { return false; }

int AlphaBeta::getPos() const {
    clock_t ct1 = clock();
    double time;

    int pos_opt;

    int depth = 1;
    int eval_max;
    // 反復深化
    do {
        eval_max = -1000000000;
        depth++;
        std::vector<int> vpos;
        getPuttablePos(board, playerID, vpos);
        for (size_t i = 0; i < vpos.size(); i++) {
            int pos = vpos[i];
            int b2[64];
            memcpy(b2, board, sizeof(b2));
            putStone(b2, playerID, pos);
            int eval_t =
                dfs(b2, 1 - playerID, depth - 1, -1000000000, 1000000000);
            if (eval_max < eval_t) {
                eval_max = eval_t;
                pos_opt = pos;
            }
        }
        clock_t ct2 = clock();
        time = static_cast<double>(ct2 - ct1) / CLOCKS_PER_SEC;
        // 深さを1増やすと2倍以上時間がかかると考えられるので早めに切り上げる
    } while (time < time_limit / 2.0 && eval_max < h_win);
    return pos_opt;
}

// pID == playerID のとき、evalが最大となるものを返す
// pID != playerID のとき、evalが最小となるものを返す
int AlphaBeta::dfs(const int b[64], int pID, int d, int alpha, int beta) const {
    // 設定した深さまで探索したなら評価値を返す
    if (d == 0) return eval(b);
    // 投了なら無限大の重みをつけた評価値を返す
    if (isEnd(b)) return h_win * eval(b);

    // その時のプレイヤーが置けないならターンを変える
    if (!isPuttableBoard(b, pID)) return dfs(b, 1 - pID, d, alpha, beta);

    if (pID == playerID) {
        std::vector<int> vpos;
        getPuttablePos(b, pID, vpos);
        for (size_t i = 0; i < vpos.size(); i++) {
            int pos = vpos[i];
            int b2[64];
            memcpy(b2, b, sizeof(b2));
            putStone(b2, pID, pos);
            alpha = std::max(alpha, dfs(b2, 1 - pID, d - 1, alpha, beta));
            if (alpha >= beta) return beta;
        }
        return alpha;
    } else {
        std::vector<int> vpos;
        getPuttablePos(b, pID, vpos);
        for (size_t i = 0; i < vpos.size(); i++) {
            int pos = vpos[i];
            int b2[64];
            memcpy(b2, b, sizeof(b2));
            putStone(b2, pID, pos);
            beta = std::min(beta, dfs(b2, 1 - pID, d - 1, alpha, beta));
            if (alpha >= beta) return alpha;
        }
        return beta;
    }
}

// 評価関数（石の差＆角の重み）
int AlphaBeta::eval(const int b[64]) const {
    int stones[2];
    countStones(b, stones);
    // Heuristic
    int h = 0;
    int corner[4] = {0, 7, 8 * 7, 8 * 7 + 7};
    for (int i = 0; i < 4; i++) {
        if (b[corner[i]] == playerID)
            h++;
        else if (b[corner[i]] == 1 - playerID)
            h--;
    }
    h *= h_corner;
    return stones[playerID] - stones[1 - playerID] + h;
}
