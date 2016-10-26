#pragma once

#include "player.hpp"
#include <array>

class Learner : public Player {
protected:
    bool isBattle;
    int training_count;
public:
    Learner(bool isB);
    virtual ~Learner();
    virtual void train(const std::array<Stone, SIZE2> &board, int step, Stone mycolor, int color) = 0;
    virtual void read() = 0;
    virtual void write() const = 0;
    void setIsBattle(bool isB);
    int getTrainingCount();
};
