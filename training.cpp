#include "trainer.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <ctime>

int main(int argc, char *argv[]) {
    clock_t ct1 = clock();

    if (argc != 4){
        std::cout << "dirname, write_interval, and battle_interval.\n";
        return 0;
    }
    std::string dirname = std::string(argv[1]);
    int write_interval = atoi(argv[2]);
    int battle_interval = atoi(argv[3]);

    Trainer *trainer = new Trainer(dirname, write_interval, battle_interval);
    trainer->play();
    delete trainer;

    clock_t ct2 = clock();
    std::cout << "TIME:" << (ct2-ct1) / CLOCKS_PER_SEC << "sec\n";
}
