#pragma once

#include "player.hpp"
#include <fstream>

class Game {
    int board[64];
    int playerID;
    int round_number;
    double time_limit;
    Player *player[2];
public:
    Game(std::ifstream &File);
    ~Game();
    void play();
    void oneplay();
};
