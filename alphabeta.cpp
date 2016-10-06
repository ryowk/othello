#include "alphabeta.hpp"
#include <ctime>
#include "functions.hpp"

AlphaBeta::AlphaBeta(double tl)
    : Player(), time_limit(tl), heur_corner(100), heur_win(1000000) {}
AlphaBeta::~AlphaBeta() {}

bool AlphaBeta::isMan() const { return false; }

int AlphaBeta::getPos(const std::array<Stone, SIZE2> &board, int color) const {
    clock_t ct1 = clock();
    double time;

    int pos_opt;

    int depth = 0;
    int eval_max;
    // 反復深化
    do {
        eval_max = -1000000000;
        depth++;
        std::vector<int> vpos;
        getAllValidPos(board, color, vpos);
        for (size_t i = 0; i < vpos.size(); i++) {
            int pos = vpos[i];
            std::array<Stone, SIZE2> board_cpy = board;
            putStone(board_cpy, color, pos);
            int val = dfs(board_cpy, color, getOpponentColor(color), depth - 1,
                          -1000000000, 1000000000);
            if (eval_max < val) {
                eval_max = val;
                pos_opt = pos;
            }
        }
        clock_t ct2 = clock();
        time = static_cast<double>(ct2 - ct1) / CLOCKS_PER_SEC;
//        // 深さを1増やすと2倍以上時間がかかると考えられるので早めに切り上げる
//    } while (time < time_limit / 2.0 && eval_max < heur_win);
    } while (time < time_limit && eval_max < heur_win);
    return pos_opt;
}

int AlphaBeta::dfs(const std::array<Stone, SIZE2> &board, int root_color,
                   int color, int depth, int alpha, int beta) const {
    // 設定した深さまで探索したなら評価値を返す
    if (depth == 0) return eval(board, root_color);
    // 投了なら無限大の重みをつけた評価値を返す
    // color = +-1 であることを仮定している
    if (isEnd(board)) return heur_win * getWinner(board) * root_color;

    // その時のプレイヤーが置けないならターンを変える
    if (!isPuttableBoard(board, color))
        return dfs(board, root_color, getOpponentColor(color), depth, alpha,
                   beta);

    std::vector<int> vpos;
    getAllValidPos(board, color, vpos);

    if (color == root_color) {
        for (size_t i = 0; i < vpos.size(); i++) {
            int pos = vpos[i];
            std::array<Stone, SIZE2> board_cpy = board;
            putStone(board_cpy, color, pos);
            alpha = std::max(alpha,
                             dfs(board_cpy, root_color, getOpponentColor(color),
                                 depth - 1, alpha, beta));
            if (alpha >= beta) return beta;
        }
        return alpha;
    } else {
        for (size_t i = 0; i < vpos.size(); i++) {
            int pos = vpos[i];
            std::array<Stone, SIZE2> board_cpy = board;
            putStone(board_cpy, color, pos);
            beta = std::min(beta,
                            dfs(board_cpy, root_color, getOpponentColor(color),
                                depth - 1, alpha, beta));
            if (alpha >= beta) return alpha;
        }
        return beta;
    }
}

// 評価関数（石の差＆角の重み）
int AlphaBeta::eval(const std::array<Stone, SIZE2> &board, int color) const {
    int stones[2];
    countStones(board, stones);
    // Heuristic
    int heur = 0;
    const int corner[4] = {0, SIZE1 - 1, SIZE1 * (SIZE1 - 1), SIZE2 - 1};
    for (int i = 0; i < 4; i++) {
        if (board[corner[i]] == BLACK)
            heur++;
        else if (board[corner[i]] == WHITE)
            heur--;
    }
    heur *= heur_corner;
    int black_white = stones[0] - stones[1] + heur;
    return black_white * color;
}
