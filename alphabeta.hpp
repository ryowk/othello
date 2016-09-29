#pragma once
#include "player.hpp"

class AlphaBeta : public Player{
    const double time_limit;
    const int h_corner;
    const int h_win;
    int dfs(const int b[64], int pID, int d, int alpha, int beta) const;
    int eval(const int b[64]) const;
public:
    AlphaBeta(int b[64], int pID, double tl);
    ~AlphaBeta();
    bool isMan() const;
    int getPos() const;
};
