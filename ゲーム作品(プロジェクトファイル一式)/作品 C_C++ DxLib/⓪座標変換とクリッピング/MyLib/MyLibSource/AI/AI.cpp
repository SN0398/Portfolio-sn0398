#include "AI.h"
#include <queue>

using namespace MyLib;
using namespace Astar;
using namespace std;

// A*�A���S���Y���ɂ��o�H�T��
std::vector<Astar::Node*> MyLib::AStarAlgorithm(Position2D start, Position2D goal, MapChip& CostTable)
{
    // �X�^�[�g�m�[�h�ƃS�[���m�[�h�̍쐬
    Node* startNode = new Node(start);
    Node* goalNode = new Node(goal);
    // �X�^�[�g�m�[�h�̏�����
    UpdateNodeParam(startNode, goalNode);   // �m�[�h�̏������֐�

    // �I�[�v�����X�g�ƃN���[�Y�h���X�g�̏�����
    vector<Node*> openList;
    vector<Node*> closedList;

    // �X�^�[�g�m�[�h���I�[�v�����X�g�ɒǉ�
    openList.push_back(startNode);

    while (!openList.empty())
    {
        // �擪�̃m�[�h�����o��
        // �擪�̃m�[�h�͍ŏ��̃R�X�g�����m�[�h�ɕ��ёւ����Ă���
        sort(openList.begin(), openList.end(), CompareNodeCost);
        Node* currentNode = openList.front();
        openList.erase(openList.begin()); // �m�[�h���폜����

        // �S�[���m�[�h�ɓ��B�����ꍇ�o�H��Ԃ��ďI��
        if (CompareNode(currentNode, goalNode)) // �m�[�h�̔�r�֐�
        {
            // ���U���g�p�̔z��
            vector<Node*> path;
            // �����p�m�[�h
            Node* node = currentNode;
            // �ŒZ�o�H�̐e�����U���g�z��ɒǉ�����
            while (node->Parent != nullptr)
            {
                path.push_back(node);
                node = node->Parent;
            }
            // �z��̏��Ԃ𔽓]
            reverse(path.begin(), path.end());

            return path;
        }

        // �J�����g�m�[�h���N���[�Y�h���X�g�ɒǉ�
        closedList.push_back(currentNode);

        // �J�����g�m�[�h�̎��͂̃m�[�h��T��
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                // �΂߈ړ��͖���
                if (dx != 0 && dy != 0)
                {
                    continue;
                }

                int searchX = currentNode->pos.x + dx;
                int searchY = currentNode->pos.y + dy;

                // �}�b�v�͈̔͊O�̏ꍇ�͖���
                if (searchX < 0 || searchX >= CostTable.width || searchY < 0 || searchY >= CostTable.height)
                {
                    continue;
                }

                // �E�H�[�N�\�ȏꍇ�̂ݒT��
                if (CostTable.Chip[searchY][searchX] >= 0)
                {
                    // �ړ��R�X�g���v�Z
                    // �X�^�[�g����̈ړ��R�X�g+�ړ��R�X�g
                    int cost = currentNode->Cost + CostTable.Chip[searchY][searchX];

                    // �ړ���̃m�[�h
                    Node* nextNode = new Node({ searchX, searchY });
                    // �m�[�h�̍X�V
                    UpdateNodeParam(nextNode, goalNode, cost, currentNode);

                    // �����ɏ�����ǉ�
                    bool skip = true;

                    // �I�[�v�����X�g�ƃN���[�Y�h���X�g�ɒǉ�����m�[�h���Ȃ��ꍇ
                    auto openIt = find_if(openList.begin(), openList.end(), [nextNode](Node* node) { return CompareNode(node, nextNode); });
                    auto closedIt = find_if(closedList.begin(), closedList.end(), [nextNode](Node* node) { return CompareNode(node, nextNode); });
                    if (openIt == openList.end() && closedIt == closedList.end())
                    {
                        skip = false;
                    }
                    // �I�[�v�����X�g�ɒǉ�����m�[�h�����邩�A�V�����m�[�h�̕����g�[�^���R�X�g���Ⴂ�ꍇ
                    if (openIt != openList.end() && (*openIt)->TotalCost > nextNode->TotalCost)
                    {
                        openList.erase(openIt);
                        skip = false;
                    }
                    // �N���[�Y�h���X�g�ɒǉ�����m�[�h�����邩�A�V�����m�[�h�̕����g�[�^���R�X�g���Ⴂ�ꍇ
                    if (closedIt != closedList.end() && (*closedIt)->TotalCost > nextNode->TotalCost)
                    {
                        closedList.erase(closedIt);
                        skip = false;
                    }

                    if (skip)
                    {
                        delete nextNode;
                        continue; // ���łɒT���ς݂̏ꍇ�̓X�L�b�v
                    }
                    // �I�[�v�����X�g�ɒǉ�
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

    // �o�H��������Ȃ�����
    return {};
}

// �m�[�h�̃R�X�g��r�֐�
bool Astar::CompareNodeCost(Node* a, Node* b)
{
    return a->TotalCost < b->TotalCost; 
}

// �m�[�h�̍��W��r�֐�
bool Astar::CompareNode(Node* a, Node* b)
{ 
    return a->pos.x == b->pos.x && a->pos.y == b->pos.y; 
}

// �q���[���X�e�B�b�N�֐�
float Astar::Heuristic(Position2D a, Position2D b) 
{ 
    return ManhattanDistance(a, b);
}

// ���[�N���b�h����
float Astar::EuclidDistance(Position2D a, Position2D b)
{
    float x = a.x - b.x;
    float y = a.y - b.y;
    return sqrt(x * x + y * y);
}

// �}���n�b�^������
int Astar::ManhattanDistance(Position2D a, Position2D b)
{
    return abs(a.x - b.x) + abs(a.y - b.y); 
}

// �m�[�h�̃p�����[�^�ݒ�
void Astar::UpdateNodeParam(Node* UpdateNode, Node* goalNode, int cost, Node* parent)
{
    // �R�X�g��ݒ�
    UpdateNode->Cost = cost;
    // �m�[�h�̐���ړ��R�X�g���v�Z
    UpdateNode->HeuristicCost = Heuristic(UpdateNode->pos, goalNode->pos);
    // ���v�R�X�g�Z�o
    UpdateNode->TotalCost = UpdateNode->HeuristicCost + UpdateNode->Cost;
    // �e�����݂̃m�[�h�ɐݒ�
    UpdateNode->Parent = parent;
    return;
}