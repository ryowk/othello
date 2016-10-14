#include "network.hpp"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

Network::Network(const std::vector<int> &n, double lam, double alp, double lam2,
                 bool drop)
    : L(n.size()),
      N(n),
      lambda(lam),
      alpha(alp),
      lambda_2(lam2),
      dropout(drop) {
    // w, b は層数よりも一つ少ないので、0番目は使わない
    w.resize(L);
    b.resize(L);
    ew.resize(L);
    eb.resize(L);
    // AdaDelta 用の変数たち
    rw_ada.resize(L);
    rb_ada.resize(L);
    sw_ada.resize(L);
    sb_ada.resize(L);
    rho_ada = 0.95;
    epsilon_ada = 1e-8;
    for (int i = 1; i < L; i++) {
        w[i].resize(N[i], N[i - 1]);
        b[i].resize(N[i]);
        ew[i].resize(N[i], N[i - 1]);
        eb[i].resize(N[i]);
        rw_ada[i].resize(N[i], N[i - 1]);
        rb_ada[i].resize(N[i]);
        sw_ada[i].resize(N[i], N[i - 1]);
        sb_ada[i].resize(N[i]);
    }
}

void Network::unset_et() {
    for (int i = 1; i < L; i++) {
        ew[i].clear();
        eb[i].clear();
    }
}

//// ReLU
// inline double Network::ReLU(double x) const { return x * (x > 0.0); }
// inline double Network::dReLU(double x) const { return 1.0 * (x > 0.0); }
//// sigmoid
// inline double Network::sigmoid(double x) const { return 1.0 / (1.0 +
// exp(-x)); }
// inline double Network::dsigmoid(double x) const {
//    return (1.0 - sigmoid(x)) * sigmoid(x);
//}
//// tanh
// inline double Network::tanh(double x) const { return std::tanh(x); }
// inline double Network::dtanh(double x) const { return 1.0 - tanh(x) *
// tanh(x); }

// activation functoin for the hidden units
inline double Network::act_func_hidden(double x) const {
    return x / (1.0 + fabs(x));
}
inline double Network::dact_func_hidden(double x) const {
    return (1.0 + 2.0 * fabs(x)) / ((1.0 + fabs(x)) * (1.0 + fabs(x)));
}

// x が大きくなると導関数が 0 になると、更新されなくなってしまうので注意
// return は [-1:1] の中にあるが、勾配が消えないように 2 倍している
// activation function for the output unit
inline double Network::act_func_output(double x) const {
    return 2.0 * x / (1.0 + fabs(x));
}
inline double Network::dact_func_output(double x) const {
    return 2.0 * (1.0 + 2.0 * fabs(x)) / ((1.0 + fabs(x)) * (1.0 + fabs(x)));
}

void Network::train(const vector<int> &x, double y) {
    // Dropout mask
    static std::random_device seed_gen;
    static std::mt19937 mt(seed_gen());
    static std::uniform_int_distribution<> nd(0, 1);
    static std::vector<vector<int> > mask(L);
    if (dropout) {
        for (int i = 0; i < L; i++) {
            mask[i].resize(N[i]);
        }
        for (int i = 1; i < L - 1; i++) {
            for (size_t j = 0; j < mask[i].size(); j++) {
                mask[i](j) = nd(mt);
            }
        }
    }

    std::vector<vector<double> > z(L);
    std::vector<vector<double> > u(L);
    std::vector<vector<double> > d(L);
    for (int i = 0; i < L; i++) {
        z[i].resize(N[i]);
        u[i].resize(N[i]);
        d[i].resize(N[i]);
    }
    // z[0] に x をコピー
    z[0] = x;
    // forward calculation
    // u[i] = w[i].z[i-1] + b[i]
    // z[i] = f(u[i])
    for (int i = 1; i < L - 1; i++) {
        u[i] = prod(w[i], z[i - 1]) + b[i];
        for (size_t j = 0; j < z[i].size(); j++)
            z[i](j) = act_func_hidden(u[i](j));
        // Dropout mask
        if (dropout) {
            for (size_t j = 0; j < z[i].size(); j++) z[i](j) *= mask[i](j);
        }
    }
    // 出力層の活性化関数は変える
    u[L - 1] = prod(w[L - 1], z[L - 2]) + b[L - 1];
    z[L - 1](0) = act_func_output(u[L - 1](0));
    double est = z[L - 1](0);

    double delta = y - est;

    // backward calculation
    // d[L-1] = y_data - y_pred
    // d[i] = df(u[i])*(trans(w[i+1]).d[i+1])
    // dW[i] = d[i].trans(z[i-1])
    // db[i] = d[i]
    // TD(lambda)では∇vのみを計算するので、y_data - y_pred はない
    d[L - 1](0) = dact_func_output(u[L - 1](0));
    for (int i = L - 2; i > 0; i--) {
        vector<double> v(N[i]);
        v = prod(trans(w[i + 1]), d[i + 1]);
        for (size_t j = 0; j < d[i].size(); j++)
            d[i](j) = dact_func_hidden(u[i](j)) * v(j);
        // Dropout mask
        if (dropout) {
            for (size_t j = 0; j < d[i].size(); j++) d[i](j) *= mask[i](j);
        }
    }

    // これに delta をかければ TD(λ) での更新量（lambda = 0
    // とすれば通常のニューラルネットワーク）
    for (int i = 1; i < L; i++) {
        ew[i] = lambda * ew[i] + outer_prod(d[i], z[i - 1]);
        eb[i] = lambda * eb[i] + d[i];
    }

#if DEBUG
    // Gradient checking
    const double eps = 1.0e-4;
    for (int i = 1; i < L; i++) {
        for (size_t j = 0; j < w[i].size1(); j++) {
            for (size_t k = 0; k < w[i].size2(); k++) {
                w[i](j, k) += eps;
                double val1 = (getValue(x) - est) / eps;
                double val2 = ew[i](j, k);
                double err = val1 - val2;
                std::cout << val1 << " " << val2 << std::endl;
                if (fabs(err) > 1.0e-4) std::cout << "WARNING:";
                std::cout << "ERROR: " << err << std::endl;
                w[i](j, k) -= eps;
            }
        }
        for (size_t j = 0; j < b[i].size(); j++) {
            b[i](j) += eps;
            double val1 = (getValue(x) - est) / eps;
            double val2 = eb[i](j);
            double err = val1 - val2;
            std::cout << val1 << " " << val2 << std::endl;
            if (fabs(err) > 1.0e-4) std::cout << "WARNING:";
            std::cout << "ERROR: " << err << std::endl;
            b[i](j) -= eps;
        }
    }
#endif

    // AdaDelta
    // この書き方は遅いかもしれない
    for (int i = 1; i < L; i++) {
        for (size_t j = 0; j < w[i].size1(); j++) {
            for (size_t k = 0; k < w[i].size2(); k++) {
                double grad = -(delta * ew[i](j, k) - lambda_2 * w[i](j, k));
                rw_ada[i](j, k) =
                    rho_ada * rw_ada[i](j, k) + (1.0 - rho_ada) * grad * grad;
                double v = -sqrt(sw_ada[i](j, k) + epsilon_ada) /
                           sqrt(rw_ada[i](j, k) + epsilon_ada) * grad;
                sw_ada[i](j, k) =
                    rho_ada * sw_ada[i](j, k) + (1.0 - rho_ada) * v * v;
                w[i](j, k) += alpha * v;
            }
        }

        // バイアス項は正則化しない
        for (size_t j = 0; j < b[i].size(); j++) {
            double grad = -(delta * eb[i](j));
            rb_ada[i](j) =
                rho_ada * rb_ada[i](j) + (1.0 - rho_ada) * grad * grad;
            double v = -sqrt(sb_ada[i](j) + epsilon_ada) /
                       sqrt(rb_ada[i](j) + epsilon_ada) * grad;
            sb_ada[i](j) = rho_ada * sb_ada[i](j) + (1.0 - rho_ada) * v * v;
            b[i](j) += alpha * v;
        }
    }
}

double Network::getValue(const vector<int> &x) const {
    std::vector<vector<double> > z(L);
    std::vector<vector<double> > u(L);
    for (int i = 0; i < L; i++) {
        z[i].resize(N[i]);
        u[i].resize(N[i]);
    }

    z[0] = x;
    for (int i = 1; i < L - 1; i++) {
        u[i] = prod(w[i], z[i - 1]) + b[i];
        for (size_t j = 0; j < z[i].size(); j++)
            z[i](j) = act_func_hidden(u[i](j));
        // Factor due to Dropout
        if (dropout) {
            z[i] *= 0.5;
        }
    }
    u[L - 1] = prod(w[L - 1], z[L - 2]) + b[L - 1];
    z[L - 1](0) = act_func_output(u[L - 1](0));

    return z[L - 1](0);
}

void Network::read(std::ifstream &File) {
    int l;
    File >> l;
    if (L != l) {
        std::cout << "ERROR: param and coeff are contradictory.\n";
        std::exit(0);
    }
    for (int i = 0; i < L; i++) {
        int n;
        File >> n;
        if (N[i] != n) {
            std::cout << "ERROR: param and coeff are contradictory.\n";
            std::exit(0);
        }
    }

    for (int i = 0; i < L; i++) {
        for (size_t j = 0; j < w[i].size1(); j++) {
            for (size_t k = 0; k < w[i].size2(); k++) {
                File >> w[i](j, k);
            }
        }
        for (size_t j = 0; j < b[i].size(); j++) {
            File >> b[i](j);
        }
    }
}

void Network::write(std::ofstream &File) const {
    File << L << std::endl;
    for (int i = 0; i < L; i++) File << N[i] << " ";
    File << std::endl;

    for (int i = 0; i < L; i++) {
        for (size_t j = 0; j < w[i].size1(); j++) {
            for (size_t k = 0; k < w[i].size2(); k++) {
                File << w[i](j, k) << " ";
            }
            File << std::endl;
        }
        for (size_t j = 0; j < b[i].size(); j++) {
            File << b[i](j) << " ";
        }
        File << std::endl;
    }
}

void Network::init() {
    // w は標準正規分布で初期化
    std::random_device seed_gen;
    std::mt19937 mt(seed_gen());
    std::normal_distribution<> nd(0.0, 1.0);
    for (int i = 1; i < L; i++) {
        for (size_t j = 0; j < w[i].size1(); j++) {
            for (size_t k = 0; k < w[i].size2(); k++) {
                w[i](j, k) = nd(mt);
            }
        }
    }
}
