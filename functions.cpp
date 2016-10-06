#include "functions.hpp"
#include <iostream>
#include "constants.hpp"

void initBoard(std::array<Stone, SIZE2> &board) {
    board.fill(EMPTY);
    board[SIZE1 * (SIZE1 / 2 - 1) + (SIZE1 / 2 - 1)] = WHITE;
    board[SIZE1 * (SIZE1 / 2 - 1) + SIZE1 / 2] = BLACK;
    board[SIZE1 * SIZE1 / 2 + (SIZE1 / 2 - 1)] = BLACK;
    board[SIZE1 * SIZE1 / 2 + SIZE1 / 2] = WHITE;
}

void printBoard(const std::array<Stone, SIZE2> &board) {
    std::cout << " ";
    for (int x = 0; x < SIZE1; x++) std::cout << x;
    std::cout << std::endl;
    for (int y = 0; y < SIZE1; y++) {
        std::cout << y;
        for (int x = 0; x < SIZE1; x++) {
            switch (board[SIZE1 * y + x]) {
                case (EMPTY):
                    std::cout << "-";
                    break;
                case (BLACK):
                    std::cout << "O";
                    break;
                case (WHITE):
                    std::cout << "X";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

void getAllValidPos(const std::array<Stone, SIZE2> &board, int color,
                    std::vector<int> &v) {
    v.clear();
    for (int pos = 0; pos < SIZE2; pos++) {
        if (isValidPos(board, color, pos)) v.push_back(pos);
    }
}

bool isValidPos(const std::array<Stone, SIZE2> &board, int color, int pos) {
    static const int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    static const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    // 既に石があるならfalse
    if (board[pos] != EMPTY) return false;

    for (int dir = 0; dir < 8; dir++) {
        int x = pos % SIZE1 + dx[dir];
        int y = pos / SIZE1 + dy[dir];
        if (board[SIZE1 * y + x] != getOpponentColor(color)) continue;
        while (1) {
            x += dx[dir];
            y += dy[dir];
            if (x < 0 || x >= SIZE1 || y < 0 || y >= SIZE1) break;
            if (board[SIZE1 * y + x] == EMPTY)
                break;
            else if (board[SIZE1 * y + x] == Stone(color)) {
                return true;
            }
        }
    }
    return false;
}

// プレイヤーが盤に石を置けるか
bool isPuttableBoard(const std::array<Stone, SIZE2> &board, int color) {
    for (int pos = 0; pos < SIZE2; pos++) {
        if (isValidPos(board, color, pos)) return true;
    }
    return false;
}

// 盤上の石を数える
void countStones(const std::array<Stone, SIZE2> &board, int stones[2]) {
    stones[0] = stones[1] = 0;
    for (int i = 0; i < SIZE2; i++) {
        if (board[i] == BLACK)
            stones[0]++;
        else if (board[i] == WHITE)
            stones[1]++;
    }
}

int getWinner(const std::array<Stone, SIZE2> &board) {
    int stones[2];
    countStones(board, stones);
    if (stones[0] > stones[1])
        return BLACK;
    else if (stones[0] < stones[1])
        return WHITE;
    return EMPTY;
}

// どちらのプレイヤーも石を置けなくなったら終了
// 石の合計がSIZE2個の場合、どちらかのプレイヤーの石がなくなった場合
// の他にも石が置けなくなる場合があることに注意
bool isEnd(const std::array<Stone, SIZE2> &board) {
    if (isPuttableBoard(board, BLACK)) return false;
    if (isPuttableBoard(board, WHITE)) return false;
    return true;
}

// プレイヤーが石をposに置こうとする
// 置けるか置けないかをboolで返す
bool putStone(std::array<Stone, SIZE2> &board, int color, int pos) {
    static const int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    static const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    // 置けなければfalse
    if (!isValidPos(board, color, pos)) return false;

    board[pos] = Stone(color);

    for (int dir = 0; dir < 8; dir++) {
        int x = pos % SIZE1 + dx[dir];
        int y = pos / SIZE1 + dy[dir];
        int j = 1;
        while (1) {
            if (x < 0 || x >= SIZE1 || y < 0 || y >= SIZE1) break;
            if (board[SIZE1 * y + x] == EMPTY)
                break;
            else if (board[SIZE1 * y + x] == getOpponentColor(color))
                j++;
            else {
                for (int i = 1; i < j; i++) {
                    x -= dx[dir];
                    y -= dy[dir];
                    board[SIZE1 * y + x] = Stone(color);
                }
                break;
            }
            x += dx[dir];
            y += dy[dir];
        }
    }
    return true;
}
