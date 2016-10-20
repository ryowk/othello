#include "game.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include "aho.hpp"
#include "alphabeta.hpp"
#include "functions.hpp"
#include "man.hpp"
#include "mcts.hpp"
#include "primitivemc.hpp"
#include "td.hpp"

Game::Game(std::ifstream &File) {
    File >> round_number >> time_limit;

    // プレイヤー読み込み
    for (int i = 0; i < 2; i++) {
        std::string str;
        File >> str;
        if (str == "Aho") {
            player[i] = new Aho();
            player_name[i] = "Aho";
        } else if (str == "AlphaBeta") {
            player[i] = new AlphaBeta(time_limit);
            player_name[i] = "AlphaBeta";
      } else if (str == "PrimitiveMC") {
          player[i] = new PrimitiveMC(time_limit);
            player_name[i] = "PrimitiveMC";
      } else if (str == "MCTS") {
          double c;
          File >> c;
          player[i] = new MCTS(time_limit, c);
            player_name[i] = "MCTS";
      } else if (str == "TD") {
          std::string dirname;
          File >> dirname;
          player[i] = new TD(dirname, true);
            player_name[i] = "TD";
      } else if (str == "Man") {
          player[i] = new Man();
            player_name[i] = "Man";
      } else {
          std::cout << "PLAYER NAME ERROR" << std::endl;
          std::cout << "Aho is used." << std::endl;
          player[i] = new Aho();
            player_name[i] = "Aho";
        }
    }
}

Game::~Game() {
    delete player[0];
    delete player[1];
}

void Game::oneplay() {
    initBoard(board);
    while (1) {
        // 石を置けないならパス
        if (!isPuttableBoard(board, color)) {
            color = getOpponentColor(color);
            turn = 1 - turn;
            // 交代した人も置けないならゲーム終了
            if (!isPuttableBoard(board, color)) break;
        }

        // color が石を置く
        while (1) {
            int pos = player[turn]->getPos(board, color);
            if (putStone(board, color, pos)) break;
        }

        // ターンを変更
        color = getOpponentColor(color);
        turn = 1 - turn;
    }
}

void Game::play() {
    int win1 = 0;
    int win2 = 0;
    for (int irn = 0; irn < round_number; irn++) {
        black = irn % 2;  // 先行は交互
        turn = black;
        color = BLACK;  // 最初は黒が先行
        // 一回プレイ
        oneplay();

        // 勝敗判定 (ややこしい)
        int winner = getWinner(board);
        if ((winner == BLACK && black == 0) || (winner == WHITE && black == 1))
            win1++;
        else if ((winner == WHITE && black == 0) ||
                 (winner == BLACK && black == 1))
            win2++;

        // 結果を出力
        printBoard(board);
        std::cout << "Player 1 (" << (black == 0 ? "O" : "X") << ") :" << player_name[0] <<  std::endl;
        std::cout << "Player 2 (" << (black == 1 ? "O" : "X") << ") :" << player_name[1] <<  std::endl;
        std::cout << "Current Status: " << win1 << " VS " << win2;
        std::cout << " (" << std::fixed << std::setw(8)
                  << static_cast<double>(100 * win1) / (win1 + win2) << "%)\n";
    }
    std::cout << player_name[0] << " VS " << player_name[1] << std::endl;
    std::cout << "Final Result: ";
    std::cout << win1 << " VS " << win2 << " ("
              << static_cast<double>(100 * win1) / (win1 + win2) << "%)\n";
}

// Player 1 の勝率を得る
void Game::play(double &ratio){
    int win1 = 0;
    int win2 = 0;
    for (int irn = 0; irn < round_number; irn++) {
        black = irn % 2;  // 先行は交互
        turn = black;
        color = BLACK;  // 最初は黒が先行
        // 一回プレイ
        oneplay();

        // 勝敗判定 (ややこしい)
        int winner = getWinner(board);
        if ((winner == BLACK && black == 0) || (winner == WHITE && black == 1))
            win1++;
        else if ((winner == WHITE && black == 0) ||
                 (winner == BLACK && black == 1))
            win2++;
    }
    ratio = static_cast<double>(win1) / (win1 + win2);
}

void Game::setPlayer(Player *p, int id){
    if(id != 0 && id != 1){
        std::cout << "ERROR: Invalid id in setPlayer" << std::endl;
        std::exit(0);
    }
    if(player[id] != nullptr && player[id] != p) delete player[id];
    player[id] = p;
}
