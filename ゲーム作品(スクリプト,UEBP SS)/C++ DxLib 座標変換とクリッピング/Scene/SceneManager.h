#pragma once
#include <iostream>
#include <stack>

#include "Base/ManagerAbstract.h"
#include "Base/Singleton.h"
#include "BaseScene.h"
#include "Config/Define.h"

using namespace std;

class SceneManager final :
    public ManagerAbstract<Scene>,
    public Singleton<SceneManager>
{
public:
    friend class MainSystem;

    // �f�t�H���g�R���X�g���N�^
    SceneManager() = default;
    // �f�X�g���N�^
    ~SceneManager() = default;

public:
    // �X�^�b�N�̈�ԏ�̃C���X�^���X(�擪)�̏���
    // �X�V
    void Update() { Instance.top()->Update(); }
    // �`��
    void Draw() { Instance.top()->Draw(); }
    // ���b�p�[
    void Process() { Instance.top()->Process(); }

};