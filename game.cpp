#include <fstream>
#include <iostream>
#include <iomanip>
#include "game.hpp"
#include "functions.hpp"
#include "aho.hpp"
#include "alphabeta.hpp"
#include "primitivemc.hpp"
#include "mcts.hpp"
#include "td.hpp"
#include "man.hpp"

Game::Game(std::ifstream &File) {
    File >> round_number >> time_limit;

    // プレイヤー読み込み
    for (int i = 0; i < 2; i++) {
        std::string str;
        File >> str;
        if (str == "Aho") {
            player[i] = new Aho(board, i);
        } else if (str == "AlphaBeta") {
            player[i] = new AlphaBeta(board, i, time_limit);
        } else if (str == "PrimitiveMC") {
            player[i] = new PrimitiveMC(board, i, time_limit);
        } else if (str == "MCTS") {
            double c;
            File >> c;
            player[i] = new MCTS(board, i, time_limit, c);
        } else if (str == "TD") {
            std::string dirname;
            File >> dirname;
            player[i] = new TD(board, i, dirname, true);
        } else if (str == "Man") {
            player[i] = new Man(board, i);
        } else {
            std::cout << "PLAYER NAME ERROR" << std::endl;
            std::cout << "Aho is used." << std::endl;
            player[i] = new Aho(board, i);
        }
    }
}

Game::~Game() {
    delete player[0];
    delete player[1];
}

void Game::oneplay() {
    init(board);
    int turn = 0;
    while (1) {
        // 石を置けないならパス
        if (!isPuttableBoard(board, playerID)) {
            playerID = 1 - playerID;
            // 交代した人も置けないならゲーム終了
            if (!isPuttableBoard(board, playerID)) break;
        }


        // プレイヤーplayerID が石を置く
        while (1) {
            int pos = player[playerID]->getPos();
            if (putStone(board, playerID, pos)) break;
        }

        // ターンを変更
        playerID = 1 - playerID;
        turn++;
    }
}

void Game::play() {
    int win1 = 0;
    int win2 = 0;
    for (int irn = 0; irn < round_number; irn++) {
        playerID = irn % 2;
        // 一回プレイ
        oneplay();

        // 勝敗判定
        int winner = getWinner(board);
        if (winner == 0) win1++;
        else if(winner == 1) win2++;

        // 結果を出力
        print(board);
        std::cout << "Current Status: " << win1 << " VS " << win2;
        std::cout << " (" << std::fixed << std::setw(8) << static_cast<double>(100*win1) / std::max(1, (win1+win2)) << "%)\n\n";
    }
    std::cout << "Final Result: ";
    std::cout << win1 << " VS " << win2 << " (" << static_cast<double>(100*win1) / (win1 + win2) << "%)\n";
}
