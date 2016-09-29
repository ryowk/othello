#pragma once

class Player{
protected:
    const int *board;
    const int playerID;
public:
    Player(int b[64], int pID);
    virtual ~Player();
    virtual bool isMan() const = 0;
    virtual int getPos() const = 0;
};
