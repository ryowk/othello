#pragma once

#include "player.hpp"

class PrimitiveMC : public Player{
    const double time_limit;
    int playout(int pos) const;
public:
    // 制限時間を指定
    PrimitiveMC(int b[64], int pID, double tl);
    ~PrimitiveMC();
    bool isMan() const;
    int getPos() const;
};
