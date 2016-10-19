#pragma once

#include "player.hpp"
#include <array>

class Man : public Player{
public:
    Man();
    ~Man();
    bool isMan() const;
    int getPos(const std::array<Stone, SIZE2> &board, int color) const;
};
