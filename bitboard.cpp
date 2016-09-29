#include "bitboard.hpp"
#include <iostream>

BitBoard xy2bitboard(int x, int y){
    return static_cast<BitBoard>(1) << (8*y+x);
}

void print_board(Board &board){
    int rank = 1;
    BitBoard pos = static_cast<BitBoard>(1) << 63;
    std::cout << " abcdefgh\n";
    for(int i=0; i<64; i++){
        if(i % 8 == 0) std::cout << rank++;
        if((board.black & pos)!=0) std::cout << "o";
        else if((board.white & pos)!=0) std::cout << "x";
        else std::cout << "-";
        if(i % 8 == 7) std::cout << std::endl;
        pos >>= 1;
    }
}

void init_board(Board &board){
    board.black = static_cast<BitBoard>(1) << 28 + static_cast<BitBoard>(1) << 35;
    board.white = static_cast<BitBoard>(1) << 27 + static_cast<BitBoard>(1) << 36;
}

int main(){
    Board board;
    for(int y=0; y<8; y++){
        for(int x=0; x<8; x++){
            board.black = xy2bitboard(x, y);
            print_board(board);
            std::cout << std::endl;
        }
    }
}

