#pragma once

#include "learner.hpp"
#include <fstream>

class Trainer {
public:
    int board[64];
    int round_number;
    int playerID;
    Learner *learner;

    // public member functions
    Trainer(int rn, std::string &dirname);
    ~Trainer();
    void play();
    void oneplay();
};
