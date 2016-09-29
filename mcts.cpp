#include "mcts.hpp"
#include "constants.hpp"
#include "functions.hpp"

#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <cstring>

// node 以下のノードを全て表示するヘルパ関数
void printnode(Node* node) {
    std::cout << "w:" << node->w << " n:" << node->n
              << " pID:" << node->playerID << std::endl;
    print(node->board);
    if (!node->children.empty()) {
        for (auto itr = node->children.begin(); itr != node->children.end();
             itr++) {
            printnode(*itr);
        }
    }
    std::cout << "\n\n";
}

MCTS::MCTS(int b[64], int pID, double tl, double cc = 1.0)
    : Player(b, pID), time_limit(tl), c(cc) {}
MCTS::~MCTS(){}

bool MCTS::isMan() const { return false; }

// [前のターンの情報を記憶しておくともっと良くなりそうだが、実際にどうやるのかはわからない]
int MCTS::getPos() const {
    clock_t ct1 = clock();

    // 現在の board から root を作成
    Node* root = new Node();
    // root の状態は MCTS の状態
    root->playerID = playerID;
    for (int i = 0; i < 64; i++) root->board[i] = board[i];

    // time_limit に達するまでサンプリングする
    int loop = 0;
    clock_t ct2;
    double time;
    do {
        loop++;
        // 毎回 root から出発
        Node* node = root;
        // 木（≠ゲーム木）の葉まで、重みが大きい子を辿る
        while (!node->children.empty()) {
            node = getOptChild(node, loop, c);
        }

        // node が終端状態でなければ展開する
        if (!isEnd(node->board)) {
            expand(node);
            // 新しい葉に移動する
            node = node->children[0];
        }

        // プレイアウトして返ってきた結果を root までバックプロパゲーション
        backpropagation(node, playout(node));

        ct2 = clock();
        time = static_cast<double>(ct2 - ct1) / CLOCKS_PER_SEC;
    } while (time < time_limit);

    // 手を決めるときには分散の寄与をなくす
    Node* child_opt = getOptChild(root, loop, 0.0);
    int pos_opt = child_opt->pos;

    // root から辿って全ての node を削除
    erase(root);
    return pos_opt;
}

// node 以下の node を全消去
void MCTS::erase(Node* node) const {
    if (!node->children.empty()) {
        for (auto itr = node->children.begin(); itr != node->children.end();
             itr++) {
            erase(*itr);
        }
    }
    delete node;
}

// 重みが最も大きい子 child_opt を計算
Node* MCTS::getOptChild(Node* node, int t, double cc) const {
    double weight_max = -1.0e8;
    Node* child_opt;
    for (auto itr = node->children.begin(); itr != node->children.end();
         itr++) {
        // まだ一回も訪問していない時は優先する
        if ((*itr)->n == 0) return *itr;

        double weight = (*itr)->w / (*itr)->n;
        weight +=
            cc * std::sqrt(2.0 * std::log(static_cast<double>(t) / (*itr)->n));

//        // ヒューリスティックス
//        double h = 0.0;
//        const int corner[4] = {0, 7, 8*7, 8*7+7};
//        for(int i=0; i<4; i++){
//            if(node->board[corner[i]] == NOONE){
//                if((*itr)->board[corner[i]] == node->playerID) h++;
//                else if((*itr)->board[corner[i]] == 1 - node->playerID) h--;
//            }
//        }
//        h *= 10;

        if (weight_max < weight) {
            weight_max = weight;
            child_opt = *itr;
        }
    }
    return child_opt;
}

void MCTS::expand(Node* par) const {
    int pID;
    // par のプレイヤーが石を置けるならそのままで、置けないならターン交代
    if (isPuttableBoard(par->board, par->playerID))
        pID = par->playerID;
    else
        pID = 1 - par->playerID;

    // 全てのマスを探索して、置けるなら子を作成
    for (int pos = 0; pos < 64; pos++) {
        if (isPuttable(par->board, pID, pos)) {
            Node* chil = new Node(par);
            putStone(chil->board, pID, pos);
            chil->playerID = 1 - pID;
            chil->pos = pos;
        }
    }
}

// node からプレイアウトして、勝ち負け分けを返す
int MCTS::playout(const Node* node) const {
    static std::random_device seed_gen;
    static std::mt19937 mt(seed_gen());
    static std::uniform_int_distribution<> rand64(0, 63);

    int b[64];
    memcpy(b, node->board, sizeof(b));
    int pID = node->playerID;

    while(1){
        if(!isPuttableBoard(b, pID)){
            pID = 1 - pID;
            if(!isPuttableBoard(b, pID)) break;
        }

        while (1) {
            int pos = rand64(mt);
            if (putStone(b, pID, pos)) break;
        }

        pID = 1 - pID;
    }
    return getWinner(b);
}

void MCTS::backpropagation(Node* node, int winner) const {
    // 今の UCB を使うとき、return は [0, 1] 内にないといけない
    // after state を見ているので、親の playerID と winner を比較すべし
    do {
        if(winner == node->parent->playerID) node->w += 1.0;
        else if(winner == NOONE) node->w += 0.5;
        node->n++;
        node = node->parent;
    } while (node->parent != nullptr);

    // root には親がいないので場合分け
    if(winner == node->playerID) node->w += 1.0;
    else if(winner == NOONE) node->w += 0.5;
    node->n++;
}
