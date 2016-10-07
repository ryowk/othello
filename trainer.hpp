#pragma once

#include <array>
#include <fstream>
#include "learner.hpp"

class Trainer {
    int black;
    int turn;
    int color;
    int round_number;
    std::array<Stone, SIZE2> board;
    Learner *learner;
    std::string dirname;

public:
    // public member functions
    Trainer(int rn, std::string &dirn);
    ~Trainer();
    void play();
    void oneplay(Stone mycolor);
};
