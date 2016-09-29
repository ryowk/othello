#pragma once

#include "player.hpp"

class Learner : public Player {
public:
    Learner(int b[64], int pID);
    virtual ~Learner();
    virtual void train(int t, int pID) = 0;
    virtual int getOpponentPos() const = 0;
    virtual void read() = 0;
    virtual void write() const = 0;
};
