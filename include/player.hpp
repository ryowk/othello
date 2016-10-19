#pragma once

#include <array>
#include "constants.hpp"

class Player{
public:
    Player();
    virtual ~Player();
    virtual bool isMan() const = 0;
    virtual int getPos(const std::array<Stone, SIZE2> &board, int color) const = 0;
};
