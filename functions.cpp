#include "functions.hpp"
#include <iostream>
#include "constants.hpp"

void init(int board[64]) {
    for (int i = 0; i < 64; i++) board[i] = NOONE;
    board[8 * 3 + 3] = PLAYER1;
    board[8 * 3 + 4] = PLAYER2;
    board[8 * 4 + 4] = PLAYER1;
    board[8 * 4 + 3] = PLAYER2;
}

void print(const int board[64]) {
    char cboard[64];
    for (int i = 0; i < 64; i++) {
        if (board[i] == NOONE)
            cboard[i] = '*';
        else if (board[i] == PLAYER1)
            cboard[i] = 'o';
        else
            cboard[i] = 'x';
    }

    std::cout << " ";
    for (int x = 0; x < 8; x++) std::cout << x;
    std::cout << std::endl;

    for (int y = 0; y < 8; y++) {
        std::cout << y;
        for (int x = 0; x < 8; x++) {
            std::cout << cboard[8 * y + x];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void getPuttablePos(const int board[64], int playerID, std::vector<int> &v) {
    for (int pos = 0; pos < 64; pos++) {
        if (isPuttable(board, playerID, pos)) v.push_back(pos);
    }
}

// プレイヤーがposに石を置けるか
bool isPuttable(const int board[64], int playerID, int pos) {
    static const int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    static const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    // 既に石があるならfalse
    if (board[pos] != NOONE) return false;

    int x = pos % 8;
    int y = pos / 8;
    for (int dir = 0; dir < 8; dir++) {
        bool flag = false;
        for (int i = 1; i < 8; i++) {
            int x1 = x + dx[dir] * i;
            int y1 = y + dy[dir] * i;
            int pos1 = 8 * y1 + x1;
            if (x1 < 0 || x1 >= 8 || y1 < 0 || y1 >= 8) break;
            if (board[pos1] == NOONE)
                break;
            else if (board[pos1] == playerID) {
                if (flag)
                    return true;
                else
                    break;
            } else
                flag = true;
        }
    }
    return false;
}

// プレイヤーが盤に石を置けるか
bool isPuttableBoard(const int board[64], int playerID) {
    for (int pos = 0; pos < 64; pos++) {
        if (isPuttable(board, playerID, pos)) return true;
    }
    return false;
}

// 盤上の石を数える
void countStones(const int board[64], int stones[2]) {
    stones[0] = stones[1] = 0;
    for (int i = 0; i < 64; i++) {
        if (board[i] == PLAYER1)
            stones[0]++;
        else if (board[i] == PLAYER2)
            stones[1]++;
    }
}

int getWinner(const int board[64]) {
    int stones[2];
    countStones(board, stones);
    if (stones[0] > stones[1])
        return PLAYER1;
    else if (stones[0] < stones[1])
        return PLAYER2;
    return NOONE;
}

// どちらのプレイヤーも石を置けなくなったら終了
// 石の合計が64個の場合、どちらかのプレイヤーの石がなくなった場合
// の他にも石が置けなくなる場合があることに注意
bool isEnd(const int board[64]) {
    for (int i = 0; i < 2; i++) {
        for (int pos = 0; pos < 64; pos++) {
            if (isPuttable(board, i, pos)) return false;
        }
    }
    return true;
}

// プレイヤーが石をposに置こうとする
// 置けるか置けないかをboolで返す
bool putStone(int board[64], int playerID, int pos) {
    static const int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    static const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    // 置けなければfalse
    if (!isPuttable(board, playerID, pos)) return false;

    int x = pos % 8;
    int y = pos / 8;
    board[pos] = playerID;
    for (int dir = 0; dir < 8; dir++) {
        bool flag = false;
        for (int i = 1; i < 8; i++) {
            int x1 = x + dx[dir] * i;
            int y1 = y + dy[dir] * i;
            int pos1 = 8 * y1 + x1;
            if (x1 < 0 || x1 >= 8 || y1 < 0 || y1 >= 8) break;
            if (board[pos1] == NOONE)
                break;
            else if (board[pos1] == playerID) {
                if (flag) {
                    for (int j = 1; j < i; j++) {
                        int x1 = x + dx[dir] * j;
                        int y1 = y + dy[dir] * j;
                        int pos1 = 8 * y1 + x1;
                        board[pos1] = playerID;
                    }
                }
                break;
            } else
                flag = true;
        }
    }
    return true;
}
