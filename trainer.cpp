#include "trainer.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include "functions.hpp"
#include "td.hpp"

#include "game.hpp"

Trainer::Trainer(int rn, std::string &dirname) : round_number(rn){
    learner = new TD(dirname, false);
}

Trainer::~Trainer() { delete learner; }

void Trainer::oneplay(Stone mycolor) {
    initBoard(board);
    int step = 0;
    while (1) {
        // 学習
        learner->train(board, step, mycolor, color);

        // 石を置けないならパス
        if (!isPuttableBoard(board, color)) {
            color = getOpponentColor(color);
            turn = 1 - turn;
            // 交代した人も置けないならゲーム終了
            if (!isPuttableBoard(board, color)) break;
        }

        putStone(board, color, learner->getPos(board, color));

        // ターンを変更
        color = getOpponentColor(color);
        turn = 1 - turn;
        step++;
    }
}

void Trainer::play() {
    std::ifstream File("battle_menu", std::ios::in);
    std::ofstream Log("rate");

    ///////////////////////////////int win1 = 0;
    ///////////////////////////////int win2 = 0;
    for (int irn = 1; irn <= round_number; irn++) {
        black = irn % 2;
        Stone mycolor = (black == 0) ? BLACK : WHITE;
        turn = black;
        color = BLACK;

        // 一回プレイしてmycolorの場合を育てる
        oneplay(mycolor);

        //////////////////////////////////// 勝敗判定 (ややこしい)
        /////////////////////////////int winner = getWinner(board);
        /////////////////////////////if ( (winner == BLACK && black == 0) || (winner == WHITE && black == 1) )
        /////////////////////////////    win1++;
        /////////////////////////////else if ( (winner == WHITE && black == 0) || (winner == BLACK && black == 1) )
        /////////////////////////////    win2++;

        /////////////////////////////// 結果を出力
        /////////////////////////////printBoard(board);
        /////////////////////////////std::cout << "Current Status: " << win1 << " VS " << win2;
        /////////////////////////////std::cout << " (" << std::fixed << std::setw(8)
        /////////////////////////////          << static_cast<double>(100 * win1) / (win1 + win2) << "%)\n";

        std::cout << irn << "/" << round_number << std::endl;

        if (irn % 1000 == 0) {
            learner->write();
            static Game *game = new Game(File);
            learner->setIsBattle(true);
            game->setPlayer(learner, 0);
            double ratio;
            game->play(ratio);
            Log << irn << " " << ratio << std::endl;
            learner->setIsBattle(false);
        }
    }
    learner->write();
}
