#pragma once
#include <vector>
#include <memory>
#include "GameObject/GameObject.h"

// �e�V�[���̊��N���X
class Scene abstract
{
public:
    Scene() = default;
    virtual ~Scene() = default;

public:
    virtual void Initialize() = 0;  // ������
    virtual void Clean() = 0;       // ��n��
    virtual void Update() = 0;      // ����
    virtual void Draw() = 0;        // �`��

    void Process()                  // �����`��
    {
        Update();
        Draw();
    }
    // �Q�[���I�u�W�F�N�g�X�V
    void UpdateGameObjects()
    {
        for (auto& cmp : gameobjects)
        {
            cmp->Update();
        }
    }
    // �Q�[���I�u�W�F�N�g�`��
    void DrawGameObjects()
    {
        for (auto& cmp : gameobjects)
        {
            cmp->Draw();
        }
    }

public:
    std::vector<std::shared_ptr<GameObject>> gameobjects;

};