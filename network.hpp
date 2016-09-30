#pragma once

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <fstream>
#include <random>
#include <vector>
using namespace boost::numeric::ublas;
using namespace boost::numeric;

class Network {
    // number of the layers
    int L;
    // number of units in each layer
    std::vector<int> N;

    // variational parameters
    std::vector< matrix<double> > w;
    std::vector< vector<double> > b;
    // eligibility trace
    std::vector< matrix<double> > ew;
    std::vector< vector<double> > eb;
    // AdaGrad 用
    std::vector< matrix<double> > gw;
    std::vector< vector<double> > gb;

    // TD(lambda)
    double lambda;
    // speed of gradient descent
    double alpha;
    // degree of L2 regularization
    double lambda_2;

    bool dropout;

    // private member functions
    double ReLU(double x) const;
    double dReLU(double x) const;
    double sigmoid(double x) const;
    double dsigmoid(double x) const;
public:
    Network(const std::vector<int> &n, double lam, double alp, double lam2, bool drop = true);
    void unset_et();
    double getValue(const vector<int> &x) const;
    void train(const vector<int> &x, double y);
    void read(std::ifstream &File);
    void write(std::ofstream &File) const;
    void init();
};
