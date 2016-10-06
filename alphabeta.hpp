#pragma once
#include "player.hpp"
#include <array>

class AlphaBeta : public Player{
    const double time_limit;
    const int heur_corner;
    const int heur_win;
    int dfs(const std::array<Stone, SIZE2> &board, int root_color, int color, int depth, int alpha, int beta) const;
    int eval(const std::array<Stone, SIZE2> &board, int color) const;
public:
    AlphaBeta(double tl);
    ~AlphaBeta();
    bool isMan() const;
    int getPos(const std::array<Stone, SIZE2> &board, int color) const;
};
