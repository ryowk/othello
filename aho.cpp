#include "aho.hpp"
#include <random>

Aho::Aho(int b[64], int pID) : Player(b, pID){}
Aho::~Aho(){}

bool Aho::isMan() const {
    return false;
}

int Aho::getPos() const {
    static std::random_device seed_gen;
    static std::mt19937 mt(seed_gen());
    static std::uniform_int_distribution<> rand64(0, 63);
    return rand64(mt);
}
