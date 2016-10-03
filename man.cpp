#include <iostream>
#include "man.hpp"
#include "functions.hpp"

Man::Man(int b[64], int pID) : Player(b, pID){}
Man::~Man(){}

bool Man::isMan() const {
    return true;
}

int Man::getPos() const {
    print(board);
    std::cout << "Input x and y." << std::endl;
    int x, y;
    std::cin >> x >> y;
    return 8 * y + x;
}
