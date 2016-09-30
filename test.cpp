#include <iostream>

int main(){

    unsigned long long j = 1;
    for(int i=0; i<64; i++){
        std::cout << j << std::endl;
        j <<= 1;
    }
}
