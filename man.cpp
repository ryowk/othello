#include <iostream>
#include "man.hpp"
#include "functions.hpp"

Man::Man() : Player(){}
Man::~Man(){}

bool Man::isMan() const {
    return true;
}

int Man::getPos(const std::array<Stone, SIZE2> &board, int color) const {
    printBoard(board);
    std::cout << "You are " << (color == BLACK ? "BLACK" : "WHITE") << std::endl;
    std::cout << "Input x and y." << std::endl;
    int x, y;
    std::cin >> x >> y;
    return SIZE1 * y + x;
}
