#pragma once
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template <class T>
class ManagerAbstract abstract
{
public:
    enum Approach_Calltype
    {
        AC_PopTop,     // �擪�������Ă���擪�ɒǉ�����
        AC_PopAll,     // �S�ď����Ă���擪�ɒǉ�����
        AC_Push,       // �擪�ɒǉ����邾��
        AC_Back,       // �擪����������
    };

public:
    // �f�t�H���g�R���X�g���N�^
    ManagerAbstract() = default;
    // �f�X�g���N�^
    virtual ~ManagerAbstract()
    {
        PopAll();
        while (!ChangeList.empty())
        {
            ChangeList.pop();
        }
    }

public:
    // �X�^�b�N�̃T�C�Y�𓾂�
    int GetSize() { return Instance.size(); }

    // �擪�̕ύX���N�G�X�g�𑗂�
    template <class U>
    void Change(Approach_Calltype type = AC_Push) { ChangeList.push({ type,make_unique<U>() }); }

    // �擪���폜���郊�N�G�X�g�𑗂�
    void Back() { ChangeList.push({ AC_Back, nullptr }); }    

protected:
    // �擪�C���X�^���X�폜
    void Pop() { Instance.pop(); }

    // ���ׂẴC���X�^���X�폜
    void PopAll() { while (!Instance.empty()) { Pop(); } }

    // �V�[���ύX���N�G�X�g������
    void ChangeProcess()
    {
        // ����������܂Ń��[�v
        while (!ChangeList.empty())
        {
            auto& request = ChangeList.front(); // �擪�C���X�^���X�擾
            unique_ptr<T> temp;

            // �V�[���̃|�C���^������Ȓl�̏ꍇ�ɏ��L�����ړ�
            if (request.second) { temp = move(request.second); }
            // �|�C���^���s���Ȓl�̏ꍇ�͐擪�V�[�����폜���邾���ɂ���
            else { request.first = AC_Back; }

            // �{����
            switch (request.first)
            {
            case AC_PopTop:    // �擪�������Ă���擪�ɒǉ�����
            {
                Pop();
                Instance.push(move(temp));
            }break;
            case AC_PopAll:    // �S�ď����Ă���擪�ɒǉ�����
            {
                PopAll();
                Instance.push(move(temp));
            }break;
            case AC_Push:      // �擪�ɒǉ����邾��
            {
                Instance.push(move(temp));
            }break;
            case AC_Back:      // �擪����������
            {
                Pop();
            }break;
            default: {}break;
            }
            ChangeList.pop();   // �C���X�^���X������
        }
    }

protected:
    stack<unique_ptr<T>> Instance;   // �X�^�b�N
    queue<pair<Approach_Calltype, unique_ptr<T>>> ChangeList;    // �����҂��̕ύX���N�G�X�g���X�g

};