#pragma once

#include "MyLibSource/2D/2D.h"

#include <vector>

namespace MyLib
{
    // A*経路探索
    namespace Astar
    {
        // ノードの定義
        struct Node
        {
            Position2D pos;       // ノードの座標
            float Cost;           // スタートノードからの移動コスト
            float HeuristicCost;  // ゴールノードへの推定移動コスト
            float TotalCost;      // 合計コスト
            Node* Parent;       // 親ノードのポインタ
            Node(Position2D pos) : pos(pos) {}
            bool operator()(const Node& a, const Node& b) { return a.Cost < b.Cost; }
        };
        bool    CompareNodeCost(Node* a, Node* b);
        bool    CompareNode(Node* a, Node* b);                      // ノードの座標比較関数
        float   Heuristic(Position2D a, Position2D b);              // ヒューリスティック関数
        float   EuclidDistance(Position2D a, Position2D b);         // ユークリッド距離
        int     ManhattanDistance(Position2D a, Position2D b);      // マンハッタン距離
        void    UpdateNodeParam(Node* UpdateNode, Node* goalNode, int cost = 0, Node* parent = nullptr);
    }
    // A*アルゴリズムによる経路探索
    std::vector<Astar::Node*> AStarAlgorithm(Position2D start, Position2D goal, MapChip& CostTable);
}