#pragma once

#include "player.hpp"

class Man : public Player{
public:
    Man(int b[64], int pID);
    ~Man();
    bool isMan() const;
    int getPos() const;
};
