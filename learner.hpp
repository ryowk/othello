#pragma once

#include "player.hpp"
#include <array>

class Learner : public Player {
public:
    Learner();
    virtual ~Learner();
    virtual void train(const std::array<Stone, SIZE2> &board, int step, Stone mycolor, int color) = 0;
    virtual void read() = 0;
    virtual void write() const = 0;
};
