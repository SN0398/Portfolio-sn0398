#include "AI.h"
#include <queue>

using namespace MyLib;
using namespace Astar;
using namespace std;

// A*アルゴリズムによる経路探索
std::vector<Astar::Node*> MyLib::AStarAlgorithm(Position2D start, Position2D goal, MapChip& CostTable)
{
    // スタートノードとゴールノードの作成
    Node* startNode = new Node(start);
    Node* goalNode = new Node(goal);
    // スタートノードの初期化
    UpdateNodeParam(startNode, goalNode);   // ノードの初期化関数

    // オープンリストとクローズドリストの初期化
    vector<Node*> openList;
    vector<Node*> closedList;

    // スタートノードをオープンリストに追加
    openList.push_back(startNode);

    while (!openList.empty())
    {
        // 先頭のノードを取り出す
        // 先頭のノードは最小のコストを持つノードに並び替えられている
        sort(openList.begin(), openList.end(), CompareNodeCost);
        Node* currentNode = openList.front();
        openList.erase(openList.begin()); // ノードを削除する

        // ゴールノードに到達した場合経路を返して終了
        if (CompareNode(currentNode, goalNode)) // ノードの比較関数
        {
            // リザルト用の配列
            vector<Node*> path;
            // 走査用ノード
            Node* node = currentNode;
            // 最短経路の親をリザルト配列に追加する
            while (node->Parent != nullptr)
            {
                path.push_back(node);
                node = node->Parent;
            }
            // 配列の順番を反転
            reverse(path.begin(), path.end());

            return path;
        }

        // カレントノードをクローズドリストに追加
        closedList.push_back(currentNode);

        // カレントノードの周囲のノードを探索
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                // 斜め移動は無効
                if (dx != 0 && dy != 0)
                {
                    continue;
                }

                int searchX = currentNode->pos.x + dx;
                int searchY = currentNode->pos.y + dy;

                // マップの範囲外の場合は無視
                if (searchX < 0 || searchX >= CostTable.width || searchY < 0 || searchY >= CostTable.height)
                {
                    continue;
                }

                // ウォーク可能な場合のみ探索
                if (CostTable.Chip[searchY][searchX] >= 0)
                {
                    // 移動コストを計算
                    // スタートからの移動コスト+移動コスト
                    int cost = currentNode->Cost + CostTable.Chip[searchY][searchX];

                    // 移動先のノード
                    Node* nextNode = new Node({ searchX, searchY });
                    // ノードの更新
                    UpdateNodeParam(nextNode, goalNode, cost, currentNode);

                    // ここに処理を追加
                    bool skip = true;

                    // オープンリストとクローズドリストに追加するノードがない場合
                    auto openIt = find_if(openList.begin(), openList.end(), [nextNode](Node* node) { return CompareNode(node, nextNode); });
                    auto closedIt = find_if(closedList.begin(), closedList.end(), [nextNode](Node* node) { return CompareNode(node, nextNode); });
                    if (openIt == openList.end() && closedIt == closedList.end())
                    {
                        skip = false;
                    }
                    // オープンリストに追加するノードがあるかつ、新しいノードの方がトータルコストが低い場合
                    if (openIt != openList.end() && (*openIt)->TotalCost > nextNode->TotalCost)
                    {
                        openList.erase(openIt);
                        skip = false;
                    }
                    // クローズドリストに追加するノードがあるかつ、新しいノードの方がトータルコストが低い場合
                    if (closedIt != closedList.end() && (*closedIt)->TotalCost > nextNode->TotalCost)
                    {
                        closedList.erase(closedIt);
                        skip = false;
                    }

                    if (skip)
                    {
                        delete nextNode;
                        continue; // すでに探索済みの場合はスキップ
                    }
                    // オープンリストに追加
                    openList.push_back(nextNode);
                    sort(openList.begin(), openList.end(), CompareNodeCost);
                }
            }
        }
    }
    for (Node* node : closedList)
    {
        delete node;
    }

    // 経路が見つからなかった
    return {};
}

// ノードのコスト比較関数
bool Astar::CompareNodeCost(Node* a, Node* b)
{
    return a->TotalCost < b->TotalCost; 
}

// ノードの座標比較関数
bool Astar::CompareNode(Node* a, Node* b)
{ 
    return a->pos.x == b->pos.x && a->pos.y == b->pos.y; 
}

// ヒューリスティック関数
float Astar::Heuristic(Position2D a, Position2D b) 
{ 
    return ManhattanDistance(a, b);
}

// ユークリッド距離
float Astar::EuclidDistance(Position2D a, Position2D b)
{
    float x = a.x - b.x;
    float y = a.y - b.y;
    return sqrt(x * x + y * y);
}

// マンハッタン距離
int Astar::ManhattanDistance(Position2D a, Position2D b)
{
    return abs(a.x - b.x) + abs(a.y - b.y); 
}

// ノードのパラメータ設定
void Astar::UpdateNodeParam(Node* UpdateNode, Node* goalNode, int cost, Node* parent)
{
    // コストを設定
    UpdateNode->Cost = cost;
    // ノードの推定移動コストを計算
    UpdateNode->HeuristicCost = Heuristic(UpdateNode->pos, goalNode->pos);
    // 合計コスト算出
    UpdateNode->TotalCost = UpdateNode->HeuristicCost + UpdateNode->Cost;
    // 親を現在のノードに設定
    UpdateNode->Parent = parent;
    return;
}