#pragma once

#include "MyLibSource/2D/2D.h"

#include <vector>

namespace MyLib
{
    // A*�o�H�T��
    namespace Astar
    {
        // �m�[�h�̒�`
        struct Node
        {
            Position2D pos;       // �m�[�h�̍��W
            float Cost;           // �X�^�[�g�m�[�h����̈ړ��R�X�g
            float HeuristicCost;  // �S�[���m�[�h�ւ̐���ړ��R�X�g
            float TotalCost;      // ���v�R�X�g
            Node* Parent;       // �e�m�[�h�̃|�C���^
            Node(Position2D pos) : pos(pos) {}
            bool operator()(const Node& a, const Node& b) { return a.Cost < b.Cost; }
        };
        bool    CompareNodeCost(Node* a, Node* b);
        bool    CompareNode(Node* a, Node* b);                      // �m�[�h�̍��W��r�֐�
        float   Heuristic(Position2D a, Position2D b);              // �q���[���X�e�B�b�N�֐�
        float   EuclidDistance(Position2D a, Position2D b);         // ���[�N���b�h����
        int     ManhattanDistance(Position2D a, Position2D b);      // �}���n�b�^������
        void    UpdateNodeParam(Node* UpdateNode, Node* goalNode, int cost = 0, Node* parent = nullptr);
    }
    // A*�A���S���Y���ɂ��o�H�T��
    std::vector<Astar::Node*> AStarAlgorithm(Position2D start, Position2D goal, MapChip& CostTable);
}