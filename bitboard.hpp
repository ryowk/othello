#pragma once

typedef unsigned long long BitBoard;
struct Board{
    BitBoard black;
    BitBoard white;
};

BitBoard xy2bitboard(int x, int y);
void print_board(Board &board);
void init_board(Board &board);
