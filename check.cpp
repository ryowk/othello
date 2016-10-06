#include <fstream>
#include <iostream>
#include <random>
#include "td.hpp"

void identity_trans(vector<int> &vboard){};

void x_mirror(vector<int> &vboard) {
    for (int y = 0; y < SIZE1; y++) {
        for (int x = 0; x < SIZE1 / 2; x++) {
            int pos1 = SIZE1 * y + x;
            int pos2 = SIZE1 * y + (SIZE1 - 1 - x);
            std::swap(vboard[pos1], vboard[pos2]);
        }
    }
}

void y_mirror(vector<int> &vboard) {
    for (int y = 0; y < SIZE1 / 2; y++) {
        for (int x = 0; x < SIZE1; x++) {
            int pos1 = SIZE1 * y + x;
            int pos2 = SIZE1 * (SIZE1 - 1 - y) + x;
            std::swap(vboard[pos1], vboard[pos2]);
        }
    }
}

void player_trans(vector<int> &vboard) {
    for (int i = 0; i < SIZE2; i++) vboard[i] = -vboard[i];
}

int main(int argc, char *argv[]) {
    std::random_device seed_gen;
    std::mt19937 mt(seed_gen());
    std::uniform_int_distribution<> rand3(0, 2);

    if (argc != 2) {
        std::cout << "Input dirname.\n";
        return 0;
    }

    std::string str = std::string(argv[1]);

    TD *td = new TD(str, false);

    vector<int> vboard(SIZE2);
    str = str + "check";
    std::ofstream output(str);

    // 場所ごとのスコア
    double score_pos[SIZE2] = {0.0};
    // 石の差に対するスコア(-SIZE2 ~ SIZE2)
    double score_num[2 * SIZE2 + 1] = {0.0};
    // 石の差の出現数
    int stones_num[2 * SIZE2 + 1] = {0};

    const int samples = 10000;

    void (*trans[8])(vector<int> &) = {identity_trans, x_mirror,     y_mirror,
                                       x_mirror,       player_trans, x_mirror,
                                       y_mirror,       x_mirror};

    for (int i = 0; i < samples; i++) {
        for (int j = 0; j < SIZE2; j++) vboard[j] = rand3(mt) - 1;

        for (int k = 0; k < 8; k++) {
            trans[k](vboard);
            double value = td->getValue(vboard);
            // s=自分の石-相手の石
            int s = 0;
            for (int j = 0; j < SIZE2; j++) {
                if (vboard[j] != 0) {
                    score_pos[j] += value * vboard[j];
                    s += vboard[j];
                }
            }
            score_num[s + SIZE2] += value;
            stones_num[s + SIZE2]++;
        }
    }

    for (int y = 0; y < SIZE1; y++) {
        for (int x = 0; x < SIZE1; x++) {
            output << x << " " << y << " "
                   << score_pos[SIZE1 * y + x]
                   << std::endl;
        }
        output << std::endl;
    }
    output << std::endl;

    for (int i = 0; i <= 2 * SIZE2; i++) {
        if (stones_num[i] != 0)
            output << i - SIZE2 << " " << score_num[i] / stones_num[i]
                   << std::endl;
    }
    delete td;
}
