#pragma once

#include <array>
#include <boost/numeric/ublas/matrix.hpp>
#include <string>
#include "learner.hpp"
#include "network.hpp"
using namespace boost::numeric::ublas;
using namespace boost::numeric;

// TD(lambda) & neural network
class TD : public Learner {
    std::string dirname;
    double epsilon;

    std::array<Stone, SIZE2> board_old;
    Network *network;
    // private member functions
    // 自分が color のときのインプットの表現を得る
    void arr2vec(const std::array<Stone, SIZE2> &board, vector<int> &vboard, int color) const;
public:
    TD(std::string dn, bool isB);
    ~TD();
    bool isMan() const;
    int getPos(const std::array<Stone, SIZE2> &board, int color) const;
    void train(const std::array<Stone, SIZE2> &board, int step, Stone mycolor, int color);
    void read();
    void write() const;
    double getValue(const std::array<Stone, SIZE2> &board, int color) const;
    double getValue(const vector<int> &vboard) const;
};
