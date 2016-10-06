#pragma once

#include "player.hpp"
#include <fstream>
#include <array>

class Game {
    std::array<Stone, SIZE2> board;
    int black; // 先行のplayerID
    int color; // 現在のターン色
    int turn;  // 現在のターンID
    int round_number;
    double time_limit;
    Player *player[2];
public:
    Game(std::ifstream &File);
    ~Game();
    void play();
    void oneplay();
};
