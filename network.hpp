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
    std::vector<matrix<double> > w;
    std::vector<vector<double> > b;

//    // AdaDelta 用
//    std::vector<matrix<double> > rw_ada;
//    std::vector<vector<double> > rb_ada;
//    std::vector<matrix<double> > sw_ada;
//    std::vector<vector<double> > sb_ada;
//    double rho_ada, epsilon_ada;

    // eligibility trace
    std::vector<matrix<double> > ew;
    std::vector<vector<double> > eb;

    // TD(lambda)
    double lambda;
    // Learning rate
    double alpha;
    // degree of L2 regularization
    double lambda_2;

    bool dropout;

    // private member functions
    double act_func_hidden(double x) const;
    double dact_func_hidden(double x) const;
    double act_func_output(double x) const;
    double dact_func_output(double x) const;

public:
    Network(const std::vector<int> &n, double lam, double alp, double lam2,
            bool drop = false);
    void unset_et();
    double getValue(const vector<int> &x) const;
    void train(const vector<int> &x, double y);
    void read(std::ifstream &File);
    void write(std::ofstream &File) const;
    void init();
};
