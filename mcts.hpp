#pragma once

#include <vector>
#include "player.hpp"

struct Node {
    double w;         // 〜勝利数 (win: 1, draw: 0.5, lose: 0)
    int n;         // 実行回数
    int playerID;  // ノードにおけるplayerID
    int board[64];
    int pos;  // 親から pos に石を置いた
    Node* parent;
    std::vector<Node*> children;
    Node() : w(0), n(0), parent(nullptr) {}
    // 親を元にしたコンストラクタ
    Node(Node* par) : w(0), n(0), parent(par) {
        for (int i = 0; i < 64; i++) board[i] = par->board[i];
        par->children.push_back(this);
    }
};

class MCTS : public Player {
    const double time_limit;
    const double c;  // 大きければ大きいほど広く探索するようになる
    int playout(const Node* node) const;
    void backpropagation(Node* node, int winner) const;
    Node* getOptChild(Node* node, int t, double cc) const;
    void expand(Node* par) const;
    void erase(Node* node) const;
public:
    MCTS(int b[64], int pID, double tl, double cc);
    ~MCTS();
    bool isMan() const;
    int getPos() const;
};
