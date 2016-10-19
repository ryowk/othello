#pragma once

typedef unsigned long long BitBoard;
struct Board{
    BitBoard black;
    BitBoard white;
};

BitBoard xy2bitboard(int x, int y);
void printboard(const Board &board);
void initBoard(Board &board);
BitBoard getValidMove(const Board &board, int playerID);
BitBoard getReverse(const Board &board, int playerID, BitBoard pos);
void putStone(Board &board, int playerID, BitBoard pos);
int countStones(const BitBoard bb);
