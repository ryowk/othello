#include "primitivemc.hpp"
#include "constants.hpp"
#include "functions.hpp"

#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <algorithm>
#include <cstring>

PrimitiveMC::PrimitiveMC(int b[64], int pID, double tl)
    : Player(b, pID), time_limit(tl) {}
PrimitiveMC::~PrimitiveMC(){}

bool PrimitiveMC::isMan() const { return false; }

int PrimitiveMC::getPos() const {
    clock_t ct1 = clock();

    std::vector<int> v;
    getPuttablePos(board, playerID, v);
    std::vector<int> rate(v.size());
    std::fill(rate.begin(), rate.end(), 0);

    // time_limit になるまでサンプリングする
    double time;
    do {
        for(size_t i=0; i<v.size(); i++){
            int pos = v[i];
            int winner = playout(pos);
            if(winner == playerID) rate[i]++;
            else if(winner == 1 - playerID) rate[i]--;
        }
        clock_t ct2 = clock();
        time = static_cast<double>(ct2-ct1) / CLOCKS_PER_SEC;
    } while (time < time_limit);

    auto rate_max = std::max_element(rate.begin(), rate.end());
    return v[rate_max - rate.begin()];
}

// board に pos を置いてからプレイアウトして勝ち負け分けを返す
int PrimitiveMC::playout(int pos) const {
    static std::random_device seed_gen;
    static std::mt19937 mt(seed_gen());
    static std::uniform_int_distribution<> rand64(0, 63);
    // 最初に pos に石を置き、それを元にプレイアウトする
    int b[64];
    memcpy(b, board, sizeof(b));
    putStone(b, playerID, pos);
    int pID = 1 - playerID;

    while(1){
        if(!isPuttableBoard(b, pID)){
            pID = 1 - pID;
            if(!isPuttableBoard(b, pID)) break;
        }

        while (1) {
            int pos = rand64(mt);
            if (putStone(b, pID, pos)) break;
        }

        pID = 1 - pID;
    }
    return getWinner(b);
}
