#pragma once
#include "player.hpp"

class Aho : public Player{
public:
    Aho(int b[64], int pID);
    ~Aho();
    bool isMan() const;
    int getPos() const;
};
