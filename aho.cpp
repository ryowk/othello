#include "aho.hpp"

Aho::Aho() : Player(){}

Aho::~Aho(){}

bool Aho::isMan() const {
    return false;
}

int Aho::getPos(const std::array<Stone, SIZE2> &board, int color) const {
    static std::random_device seed_gen;
    static std::mt19937 mt(seed_gen());
    static std::uniform_int_distribution<int> rand64(0, SIZE2-1);
    return rand64(mt);
}
