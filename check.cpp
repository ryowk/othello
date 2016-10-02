#include <fstream>
#include <iostream>
#include <random>
#include "td.hpp"

void identity_trans(int board[64]){};

void x_mirror(int board[64]){
	for(int y=0; y<8; y++){
		for(int x=0; x<8; x++){
            int pos1 = 8 * y + x;
            int pos2 = 8 * y + (7 - x);
            for (int i = 0; i < 2; i++) {
                std::swap(board[pos1], board[pos2]);
            }
        }
    }
}

void y_mirror(int board[64]){
	for(int y=0; y<8; y++){
		for(int x=0; x<8; x++){
            int pos1 = 8 * y + x;
            int pos2 = 8 * (7-y) + x;
            for (int i = 0; i < 2; i++) {
                std::swap(board[pos1], board[pos2]);
            }
        }
    }
}

void player_trans(int board[64]){
	for(int i=0; i<64; i++){
		if(board[i] != -1) board[i] = 1 - board[i];
	}
}


int main(int argc, char *argv[]){
    std::random_device seed_gen;
    std::mt19937 mt(seed_gen());
    std::uniform_int_distribution<> rand3(0, 2);

    if (argc != 2){
        std::cout << "Input dirname.\n";
        return 0;
    }

    std::string str = std::string(argv[1]);

    int board[64];

    TD *td = new TD(board, 0, str, false);

    vector<int> bd(192);
    str = str + "check";
    std::ofstream output(str);

    // 場所ごとのスコア
    double score_pos[64] = {0.0};
    // 石の差に対するスコア(-64 ~ 64)
    double score_num[129] = {0.0};
    // 石の差の出現数
    int stones_num[129] = {0};

    const int samples = 10000;

		void (*trans[8])(int*) = {
			identity_trans, x_mirror, y_mirror, x_mirror,
			player_trans, x_mirror, y_mirror, x_mirror};

    for (int i = 0; i < samples; i++) {
        for (int j = 0; j < 64; j++)
            board[j] = rand3(mt) - 1;

				for(int k=0; k<8; k++){
					trans[k](board);
					double value = 2.0*td->getValue(board) - 1.0;
        	int s = 0;
        	for(int j=0; j<64; j++){
        	    if(board[j] != -1){
        	        score_pos[j] += value * (1-2*board[j]);
        	        s += (1-2*board[j]);
        	    }
        	}
        	score_num[s+64] += value;
        	stones_num[s+64]++;
				}
    }

    for(int y=0; y<8; y++){
        for(int x=0; x<8; x++){
            output << x << " " << y << " " << score_pos[8*y+x] << std::endl;
        }
        output << std::endl;
    }
    output << std::endl;

    for(int i=0; i<=128; i++){
        if(stones_num[i]==0) stones_num[i] = 1;
        output << i-64 << " " << score_num[i] / stones_num[i] << std::endl;;
    }
    delete td;
}
