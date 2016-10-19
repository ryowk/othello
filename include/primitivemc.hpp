#pragma once

#include "player.hpp"
#include <array>

class PrimitiveMC : public Player{
    const double time_limit;
    int playout(const std::array<Stone, SIZE2> &board, int color, int pos) const;
public:
    // 制限時間を指定
    PrimitiveMC(double tl);
    ~PrimitiveMC();
    bool isMan() const;
    int getPos(const std::array<Stone, SIZE2> &board, int color) const;
};
