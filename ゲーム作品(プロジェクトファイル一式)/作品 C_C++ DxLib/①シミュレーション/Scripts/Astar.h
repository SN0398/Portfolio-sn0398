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
    // �m�[�h�̒�`
    struct Node
    {
        Position pos;       // �m�[�h�̍��W
        float Cost;           // �X�^�[�g�m�[�h����̈ړ��R�X�g
        float HeuristicCost;  // �S�[���m�[�h�ւ̐���ړ��R�X�g
        float TotalCost;      // ���v�R�X�g
        Node* Parent;       // �e�m�[�h�̃|�C���^
        Node(Position pos) : pos(pos) {}
        bool operator<(const Node& obj) const
        {
            //�����o�ϐ��ł���num1�Ŕ�r�������ʂ�
            //���̍\���̂̔�r�Ƃ���
            return TotalCost < obj.TotalCost;
        }
    };
    // �R�X�g�̔�r�p�\����
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
    // A*�A���S���Y���ɂ��o�H�T��
    vector<Node*> AStarAlgorithm(Position start, Position goal);
    
}