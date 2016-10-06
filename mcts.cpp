#include "mcts.hpp"
#include "constants.hpp"
#include "functions.hpp"

#include <cmath>
#include <ctime>
#include <random>

#include <iostream>

MCTS::MCTS(double tl, double cc = 1.0) : Player(), time_limit(tl), c(cc) {}
MCTS::~MCTS() {}

bool MCTS::isMan() const { return false; }

// [前のターンの情報を記憶しておくともっと良くなりそうだが、結構大変そう]
int MCTS::getPos(const std::array<Stone, SIZE2>& board, int color) const {
    clock_t ct1 = clock();

    // 現在の board から root を作成
    Node* root = new Node();
    root->board = board;
    root->color = color;
    expand(root);

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

        // node を初めて訪れたのではなく、かつnode が終端状態でないなら展開する
        if (node->n != 0 && !isEnd(node->board)) {
            expand(node);
            // 新しい葉のうちの一つに移動する
            node = node->children[0];
        }
        // プレイアウトして返ってきた結果を root までバックプロパゲーション
        backpropagation(node, playout(node));

        ct2 = clock();
        time = static_cast<double>(ct2 - ct1) / CLOCKS_PER_SEC;
    } while (time < time_limit);

    // 勝率を表示
    //std::cout << "Percentage:" << 100.0 * root->w / root->n << "%" << std::endl;

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

        // 勝率
        double weight = (*itr)->w / (*itr)->n;
        // 分散の寄与を足す
        weight +=
            cc * std::sqrt(2.0 * std::log(static_cast<double>(t) / (*itr)->n));

        if (weight_max < weight) {
            weight_max = weight;
            child_opt = *itr;
        }
    }
    return child_opt;
}

void MCTS::expand(Node* par) const {
    // 全てのマスを探索して、置けるなら子を作成
    for (int pos = 0; pos < SIZE2; pos++) {
        if (isValidPos(par->board, par->color, pos)) {
            // Valid な pos なら子を作成
            Node* chil = new Node();
            // 親board を子boardにコピー
            chil->board = par->board;
            // 子の親ポインタを設定
            chil->parent = par;
            // 親の子ポインタを設定
            par->children.push_back(chil);
            // 親ボードのどこに置いたのかを覚えておく
            chil->pos = pos;
            // 子のボードに実際に石を置く
            putStone(chil->board, par->color, pos);
            // expand した直後に子の手番を判定しておく
            int color = getOpponentColor(par->color);
            if (isPuttableBoard(chil->board, color)) chil->color = color;
            else chil->color = par->color;
        }
    }
}

// node からプレイアウトして、勝ち負け分けを返す
int MCTS::playout(const Node* node) const {
    static std::random_device seed_gen;
    static std::mt19937 mt(seed_gen());
    static std::uniform_int_distribution<> rand64(0, SIZE2-1);

    std::array<Stone, SIZE2> board = node->board;
    int color = node->color;

    while (1) {
        if (!isPuttableBoard(board, color)) {
            color = getOpponentColor(color);
            if (!isPuttableBoard(board, color)) break;
        }

        while (1) {
            if (putStone(board, color, rand64(mt))) break;
        }
        color = getOpponentColor(color);
    }
    return getWinner(board);
}

// node から親へ向かって winner をバックプロパゲーションする
void MCTS::backpropagation(Node* node, int winner) const {
    // 今の UCB を使うとき、return は [0, 1] 内にないといけない
    // after state を見ているので、親の color と winner を比較すべし
    while (node->parent != nullptr){
        if (winner == node->parent->color)
            node->w += 1.0;
        else if (winner == EMPTY)
            node->w += 0.5;
        node->n++;
        node = node->parent;
    }
    // この時点で node は root を指している
    // root には親がいないので結局の勝率を計算しておく
    if (winner == node->color)
        node->w += 1.0;
    else if (winner == EMPTY)
        node->w += 0.5;
    node->n++;
}
