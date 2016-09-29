#include "trainer.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <ctime>

int main(int argc, char *argv[]) {
    clock_t ct1 = clock();

    if (argc != 3){
        std::cout << "Input round_number & dirname.\n";
        return 0;
    }
    int round_number = atoi(argv[1]);
    std::string dirname = std::string(argv[2]);

    Trainer *trainer = new Trainer(round_number, dirname);
    trainer->play();
    delete trainer;

    clock_t ct2 = clock();
    std::cout << "TIME:" << (ct2-ct1) / CLOCKS_PER_SEC << "sec\n";
}
