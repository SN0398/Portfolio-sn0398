#pragma once
#include <iostream>
#include <vector>
#include <queue>

#include "MyLib.h"

using namespace std;

namespace Astar
{
    struct Position
    {
        int x, y;
    };
    // ノードの定義
    struct Node
    {
        Position pos;       // ノードの座標
        float Cost;           // スタートノードからの移動コスト
        float HeuristicCost;  // ゴールノードへの推定移動コスト
        float TotalCost;      // 合計コスト
        Node* Parent;       // 親ノードのポインタ
        Node(Position pos) : pos(pos) {}
        bool operator<(const Node& obj) const
        {
            //メンバ変数であるnum1で比較した結果を
            //この構造体の比較とする
            return TotalCost < obj.TotalCost;
        }
    };
    // コストの比較用構造体
    struct CompareCost
    {
        bool operator()(const Node* a, const Node* b)
        {
            return a->TotalCost > b->TotalCost;
        }
    };
    bool CompareNodeCost(Node* a, Node* b);
    bool CompareNode(Node* a, Node* b);
    float EuclidDistance(Position a, Position b);
    int ManhattanDistance(Position a, Position b);
    float Heuristic(Position a, Position b);
    void UpdateNodeParam(Node* UpdateNode, Node* goalNode, int cost = 0, Node* parent = nullptr);
    // A*アルゴリズムによる経路探索
    vector<Node*> AStarAlgorithm(Position start, Position goal);
    
}