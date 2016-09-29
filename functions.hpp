#pragma once
#include <vector>

void init(int board[64]);
void print(const int board[64]);
void getPuttablePos(const int board[64], int playerID, std::vector<int> &v);
bool isPuttable(const int board[64], int playerID, int pos);
bool isPuttableBoard(const int board[64], int playerID);
void countStones(const int board[64], int stones[2]);
int getWinner(const int board[64]);
bool isEnd(const int board[64]);
bool putStone(int board[64], int playerID, int pos);
