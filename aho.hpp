#pragma once
#include <array>
#include "player.hpp"
#include "constants.hpp"
#include <random>

class Aho : public Player{
public:
    Aho();
    ~Aho();
    bool isMan() const;
    int getPos(const std::array<Stone, SIZE2> &board, int color) const;
};
