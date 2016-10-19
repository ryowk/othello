#pragma once

#include <array>
#include <vector>
#include "player.hpp"

struct Node {
    double w;   // 〜勝利数 (win: 1, draw: 0.5, lose: 0)
    int n;      // 実行回数
    int color;  // パスも考慮して、このノードでの手番色
    std::array<Stone, SIZE2> board;  // ノードにおける board
    int pos;                         // 親から pos に石を置いた
    Node* parent;
    std::vector<Node*> children;
    Node() : w(0), n(0), parent(nullptr) {}
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
    MCTS(double tl, double cc);
    ~MCTS();
    bool isMan() const;
    int getPos(const std::array<Stone, SIZE2>& board, int color) const;
};
