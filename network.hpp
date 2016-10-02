#pragma once

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <fstream>
#include <random>
#include <vector>
using namespace boost::numeric::ublas;
using namespace boost::numeric;

struct ET {
    // eligibility trace
    std::vector< matrix<double> > ew;
    std::vector< vector<double> > eb;
};

class Network {
    // number of the layers
    int L;
    // number of units in each layer
    std::vector<int> N;

    // variational parameters
    std::vector< matrix<double> > w;
    std::vector< vector<double> > b;
    // Eligibility Trace 用
    // 対称性の数だけ用意すると良い
    std::vector< ET > et;

    // AdaDelta 用
    std::vector< matrix<double> > rw_ad;
    std::vector< vector<double> > rb_ad;
    std::vector< matrix<double> > sw_ad;
    std::vector< vector<double> > sb_ad;
    double rho, epsilon;

    // TD(lambda)
    double lambda;
    // degree of L2 regularization
    double lambda_2;

    bool dropout;

    // private member functions
    double ReLU(double x) const;
    double dReLU(double x) const;
    double sigmoid(double x) const;
    double dsigmoid(double x) const;
public:
    Network(const std::vector<int> &n, double lam, double lam2, bool drop = true);
    void unset_et();
    double getValue(const vector<int> &x) const;
    void train(const vector<int> &x, double y, int et_id);
    void read(std::ifstream &File);
    void write(std::ofstream &File) const;
    void init();
};
