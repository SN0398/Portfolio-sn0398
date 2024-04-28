#pragma once
#include <iostream>
#include <stack>

#include "Singleton.h"
#include "BaseScene.h"
#include "Define.h"

using namespace std;

class SceneManager final :  public Singleton<SceneManager>
{
public:
    // �f�t�H���g�R���X�g���N�^
    SceneManager();
    // �f�X�g���N�^
    ~SceneManager();

public:

    // �擪�̃V�[���폜
    void PopScene();
    // �V�[���ǉ�
    bool PushScene(Define::SceneType Stype);
    // ���ׂẴV�[���폜
    void PopAllScene();
    // �V�[���ύX
    bool ChangeScene(Define::CS_CallType CStype, Define::SceneType Stype = Define::SceneType::None);
    // �擪�V�[����Update���s
    bool Update() { return s_stack.top()->Update(); }   // �X�V�@�X�^�b�N�̈�ԏ�̃C���X�^���X��Update()�����s
    // �擪�V�[����Draw���s
    void Draw() { return s_stack.top()->Draw(); }   // �`��@�X�^�b�N�̈�ԏ�̃C���X�^���X��Draw()�����s
    // �V�[�������݂��Ȃ������擾
    bool GetEmpty() { return s_stack.empty(); }

private:
    stack<unique_ptr<Scene>> s_stack;    // �V�[���N���X�̏��L�������X�}�[�g�|�C���^�����R���e�i�A�_�v�^:�X�^�b�N

};
