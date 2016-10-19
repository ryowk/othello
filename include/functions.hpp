#pragma once
#include <vector>
#include <array>
#include "constants.hpp"

// インライン関数
inline int getOpponentColor(int color) { return -color; }


void initBoard(std::array<Stone, SIZE2> &board);
void printBoard(const std::array<Stone, SIZE2> &board);
void getAllValidPos(const std::array<Stone, SIZE2> &board, int color, std::vector<int> &v);
bool isValidPos(const std::array<Stone, SIZE2> &board, int color, int pos);
bool isPuttableBoard(const std::array<Stone, SIZE2> &board, int color);
void countStones(const std::array<Stone, SIZE2> &board, int stones[2]);
int getWinner(const std::array<Stone, SIZE2> &board);
bool isEnd(const std::array<Stone, SIZE2> &board);
bool putStone(std::array<Stone, SIZE2> &board, int color, int pos);
