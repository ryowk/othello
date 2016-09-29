#include "game.hpp"
#include <fstream>
#include <iostream>
#include <ctime>

int main() {
    clock_t ct1 = clock();

    std::ifstream File("battle_menu", std::ios::in);
    if(File.fail()){
        std::cout << "No battle_menu" << std::endl;
        return 0;
    }
    Game *game = new Game(File);
    game->play();
    delete game;

    clock_t ct2 = clock();
    std::cout << "TIME:" << (ct2-ct1) / CLOCKS_PER_SEC << "sec\n";
}
