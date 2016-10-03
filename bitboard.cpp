#include "bitboard.hpp"
#include <iostream>

BitBoard xy2bitboard(int x, int y) {
    return static_cast<BitBoard>(1) << (8 * y + x);
}

void printBoard(const Board &board) {
    int rank = 1;
    BitBoard pos = static_cast<BitBoard>(1) << 63;
    std::cout << " abcdefgh\n";
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) std::cout << rank++;
        if ((board.black & pos) != 0)
            std::cout << "o";
        else if ((board.white & pos) != 0)
            std::cout << "x";
        else
            std::cout << "-";
        if (i % 8 == 7) std::cout << std::endl;
        pos >>= 1;
    }
}

void initBoard(Board &board) {
    board.black =
        (static_cast<BitBoard>(1) << 28) + (static_cast<BitBoard>(1) << 35);
    board.white =
        (static_cast<BitBoard>(1) << 27) + (static_cast<BitBoard>(1) << 36);
}

BitBoard getValidMove(const Board &board, int playerID) {
    BitBoard me, enemy, masked_enemy, t, valid = 0, blank;
    if (playerID == 0) {
        me = board.black;
        enemy = board.white;
    } else {
        me = board.white;
        enemy = board.black;
    }

    // EMPTY のビットボード
    blank = ~(board.black | board.white);

    // 右方向
    masked_enemy = enemy & 0x7e7e7e7e7e7e7e;
    t = masked_enemy & (me << 1);
    for (int i = 0; i < 5; i++) {
        t |= masked_enemy & (t << 1);
    }
    valid |= blank & (t << 1);

    // 左方向
    masked_enemy = enemy & 0x7e7e7e7e7e7e7e;
    t = masked_enemy & (me >> 1);
    for (int i = 0; i < 5; i++) {
        t |= masked_enemy & (t >> 1);
    }
    valid |= blank & (t >> 1);

    // 上方向
    masked_enemy = enemy & 0x00ffffffffff00;
    t = masked_enemy & (me << 8);
    for (int i = 0; i < 5; i++) {
        t |= masked_enemy & (t << 8);
    }
    valid |= blank & (t << 8);

    // 下方向
    masked_enemy = enemy & 0x00ffffffffff00;
    t = masked_enemy & (me >> 8);
    for (int i = 0; i < 5; i++) {
        t |= masked_enemy & (t >> 8);
    }
    valid |= blank & (t >> 8);

    // 右上方向
    masked_enemy = enemy & 0x007e7e7e7e7e7e00;
    t = masked_enemy & (me << 7);
    for (int i = 0; i < 5; i++) {
        t |= masked_enemy & (t << 7);
    }
    valid |= blank & (t << 7);

    // 左上方向
    masked_enemy = enemy & 0x007e7e7e7e7e7e00;
    t = masked_enemy & (me << 9);
    for (int i = 0; i < 5; i++) {
        t |= masked_enemy & (t << 9);
    }
    valid |= blank & (t << 9);

    // 右下方向
    masked_enemy = enemy & 0x007e7e7e7e7e7e00;
    t = masked_enemy & (me >> 9);
    for (int i = 0; i < 5; i++) {
        t |= masked_enemy & (t >> 9);
    }
    valid |= blank & (t >> 9);

    // 左下方向
    masked_enemy = enemy & 0x007e7e7e7e7e7e00;
    t = masked_enemy & (me >> 7);
    for (int i = 0; i < 5; i++) {
        t |= masked_enemy & (t >> 7);
    }
    valid |= blank & (t >> 7);

    return valid;
}

BitBoard getReverse(const Board &board, int playerID, BitBoard pos) {
    int i;
    BitBoard me, enemy, mask, rev = 0, rev_cand;
    if (playerID == 0) {
        me = board.black;
        enemy = board.white;
    } else {
        me = board.white;
        enemy = board.black;
    }

    // 右方向
    rev_cand = 0;
    mask = 0x7e7e7e7e7e7e7e7e;
    for (i = 1; ((pos >> i) & mask & enemy) != 0; i++) {
        rev_cand |= (pos >> i);
    }
    if (((pos >> i) & me) != 0) rev |= rev_cand;

    /* 他の方向の処理 */

    // 左方向
    rev_cand = 0;
    mask = 0x7e7e7e7e7e7e7e7e;
    for (i = 1; ((pos << i) & mask & enemy) != 0; i++) {
        rev_cand |= (pos << i);
    }
    if (((pos << i) & me) != 0) rev |= rev_cand;

    // 上方向
    rev_cand = 0;
    mask = 0x00ffffffffffff00;
    for (i = 1; ((pos << 8 * i) & mask & enemy) != 0; i++) {
        rev_cand |= (pos << 8 * i);
    }
    if (((pos << 8 * i) & me) != 0) rev |= rev_cand;

    // 下方向
    rev_cand = 0;
    mask = 0x00ffffffffffff00;
    for (i = 1; ((pos >> 8 * i) & mask & enemy) != 0; i++) {
        rev_cand |= (pos >> 8 * i);
    }
    if (((pos >> 8 * i) & me) != 0) rev |= rev_cand;

    // 右上方向
    rev_cand = 0;
    mask = 0x007e7e7e7e7e7e00;
    for (i = 1; ((pos << 7 * i) & mask & enemy) != 0; i++) {
        rev_cand |= (pos << 7 * i);
    }
    if (((pos << 7 * i) & me) != 0) rev |= rev_cand;

    // 左上方向
    rev_cand = 0;
    mask = 0x007e7e7e7e7e7e00;
    for (i = 1; ((pos << 9 * i) & mask & enemy) != 0; i++) {
        rev_cand |= (pos << 9 * i);
    }
    if (((pos << 9 * i) & me) != 0) rev |= rev_cand;

    // 右下方向
    rev_cand = 0;
    mask = 0x007e7e7e7e7e7e00;
    for (i = 1; ((pos >> 9 * i) & mask & enemy) != 0; i++) {
        rev_cand |= (pos >> 9 * i);
    }
    if (((pos >> 9 * i) & me) != 0) rev |= rev_cand;

    // 左下方向
    rev_cand = 0;
    mask = 0x007e7e7e7e7e7e00;
    for (i = 1; ((pos >> 7 * i) & mask & enemy) != 0; i++) {
        rev_cand |= (pos >> 7 * i);
    }
    if (((pos >> 7 * i) & me) != 0) rev |= rev_cand;

    return rev;
}

void putStone(Board &board, int playerID, BitBoard pos) {
    BitBoard rev;

    // 反転パターン取得
    rev = getReverse(board, playerID, pos);

    if (playerID == 0) {
        board.black ^= pos | rev;
        board.white ^= rev;
    } else {
        board.white ^= pos | rev;
        board.black ^= rev;
    }
}

int countStones(const BitBoard bb) {
    bb = bb - (bb >> 1 & 0x5555555555555555);  // 2bitごと
    bb = (bb & 0x3333333333333333) + (bb >> 2 & 0x3333333333333333);   // 4bit
    bb = (bb & 0x0f0f0f0f0f0f0f0f) + (bb >> 4 & 0x0f0f0f0f0f0f0f0f);   // 8bit
    bb = (bb & 0x00ff00ff00ff00ff) + (bb >> 8 & 0x00ff00ff00ff00ff);   // 16bit
    bb = (bb & 0x0000ffff0000ffff) + (bb >> 16 & 0x0000ffff0000ffff);  // 32bit
    return (bb + (bb >> 32)) & 0x000000000000007f;                     // 64bit
}

int main() {
    Board board;
    initBoard(board);
    printBoard(board);
    BitBoard pos = xy2bitboard(3, 2);
    putStone(board, 0, pos);
    printBoard(board);
}
