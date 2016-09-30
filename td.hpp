#pragma once

#include "learner.hpp"
#include <string>
#include "network.hpp"
#include <boost/numeric/ublas/matrix.hpp>
using namespace boost::numeric::ublas;
using namespace boost::numeric;

// TD(lambda) & neural network
class TD : public Learner {
    std::string dirname;;
    bool isBattle;
    double epsilon;
		int training_count;

    int board_old[64];
    Network *network;
    // private member functions
    void arr2vec(const int b[64], vector<int> &v) const;
public:
    TD(int b[64], int pID, std::string dn, bool isB);
    ~TD();
    bool isMan() const;
    int getPos() const;
    int getOpponentPos() const;
    void train(int t, int pID);
    void read();
    void write() const;
    double getValue(const int b[64]) const;
};
