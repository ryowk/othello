#pragma once

#include <array>
#include <fstream>
#include "learner.hpp"

class Trainer {
    int black;
    int color;
    std::array<Stone, SIZE2> board;
    Learner *learner;
    std::string dirname;
    int write_interval;
    int battle_interval;

public:
    // public member functions
    Trainer(std::string &dirn, int wi, int bi);
    ~Trainer();
    void play();
    void oneplay(Stone mycolor);
};
