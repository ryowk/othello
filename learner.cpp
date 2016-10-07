#include "learner.hpp"

Learner::Learner(bool isB) : Player(), isBattle(isB){}
Learner::~Learner(){}
void Learner::setIsBattle(bool isB){isBattle = isB;}
