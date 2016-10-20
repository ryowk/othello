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

int main(){
    std::ifstream File("apgame_menu", std::ios::in);
    Player *player;

    double time_limit;
    File >> time_limit;
    std::string player_name;
    File >> player_name;
    if (player_name == "Aho") {
        player = new Aho();
        player_name = "Aho";
    } else if (player_name == "AlphaBeta") {
        player = new AlphaBeta(time_limit);
        player_name = "AlphaBeta";
    } else if (player_name == "PrimitiveMC") {
        player = new PrimitiveMC(time_limit);
        player_name = "PrimitiveMC";
    } else if (player_name == "MCTS") {
        double c;
        File >> c;
        player = new MCTS(time_limit, c);
        player_name = "MCTS";
    } else if (player_name == "TD") {
        std::string dirname;
        File >> dirname;
        player = new TD(dirname, true);
        player_name = "TD";
    } else if (player_name == "Man") {
        player = new Man();
        player_name = "Man";
    } else {
        std::cout << "PLAYER NAME ERROR" << std::endl;
        player = new Aho();
        player_name = "Aho";
    }
    std::cout << player_name << " is used." << std::endl;

    int color;
    std::string status;
    std::string result;
    std::string board_str;
    std::array<Stone, SIZE2> board;

    std::cout << "GET_COLOR" << std::endl;
    std::cin >> color;
    while(true){
        std::cout << "GET_BOARD" << std::endl;
        std::cin >> board_str;
        for(int i=0; i<64; i++){
            if(board_str[i]=='B') board[i] = BLACK;
            else if(board_str[i]=='W') board[i] = WHITE;
            else board[i] = EMPTY;
        }
        int pos = player->getPos(board, color);
        int x = pos % SIZE1;
        int y = pos / SIZE1;

        std::cout << "PUT_STONE" << x << " " << y << std::endl;
        std::cin >> result;
        if (result == "TRUE"){
            continue;
        }else{
            std::cout << "OKENAI" << std::endl;
        }
    }
    delete player;
}
