#include "trainer.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include "functions.hpp"
#include "td.hpp"

Trainer::Trainer(int rn, std::string &dirname) {
    std::fill(board, board + 64, 0);

    round_number = rn;
    learner = new TD(board, 0, dirname, false);
}

Trainer::~Trainer() { delete learner; }

void Trainer::oneplay() {
    init(board);
    int turn = 0;

    while (1) {
        // 学習
        learner->train(turn, playerID);

        // 石を置けないならパス
        if (!isPuttableBoard(board, playerID)) {
            playerID = 1 - playerID;
            // 交代した人も置けないならゲーム終了
            if (!isPuttableBoard(board, playerID)) break;
        }

        if (playerID == 0) {
            putStone(board, 0, learner->getPos());
        } else {
            putStone(board, 1, learner->getOpponentPos());
        }

        // ターンを変更
        playerID = 1 - playerID;
        turn++;
    }
}

void Trainer::play() {
//    int win1 = 0;
//    int win2 = 0;
    for (int irn = 1; irn <= round_number; irn++) {
        playerID = irn % 2;
        // 一回プレイ
        oneplay();

        ///////////////////////////////
        //        // 勝敗判定
        // int stones[2];
        // countStones(board, stones);
        // if (stones[0] > stones[1])
        //    win1++;
        // else if (stones[0] < stones[1])
        //    win2++;
        //
        //        // 結果を出力
        //        print(board);
        // std::cout << "Round" << irn + 1 << "'s result: " << stones[0] << " VS "
        //          << stones[1] << std::endl;
        // std::cout << "Current Status: " << win1 << " VS " << win2 << " ("
        //          << std::fixed << std::setw(8)
        //          << static_cast<double>(100 * win1) / (win1 + win2) <<
        //          "%)"
        //          << std::endl;
        // std::cout << std::endl;
        ///////////////////////////////

        std::cout << irn << "/" << round_number << std::endl;

        if (irn % 100 == 0) learner->write();
    }
    learner->write();
}
