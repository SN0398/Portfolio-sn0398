#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <DxLib.h>

// https://kage3.cocolog-nifty.com/blog/2014/03/post-c1b7.html

#ifdef _DEBUG

//*******************************************************
// �f�o�b�O�p�̃R���\�[���̏�������(���C�����[�v�O�ɌĂ�)
//*******************************************************
void initDebugConsole() 
{
    //�f�o�b�O�p�ɃR���\�[�����Ăяo��
    AllocConsole();
    // �W�����o�͂Ɋ��蓖�Ă�
    FILE* fp = NULL;
    // �̂̃R�[�h
    //freopen("CONOUT$", "w", stdout);
    //freopen("CONIN$", "r", stdin);
    // ���݂̃R�[�h
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONIN$", "r", stdin);
    // �f�o�b�O�R���\�[�����A�N�e�B�u�E�B���h�E�ɂȂ�̂�
    // �Q�[���{�̂̃E�B���h�E���A�N�e�B�u�ɂ���
    SetForegroundWindow(GetMainWindowHandle());
    return;
}
//*******************************************************
// �f�o�b�O�p�̃R���\�[���̃N���A����
//*******************************************************
void clearDebugConsole() 
{
    system("cls");
    return;
}
//*******************************************************
// �f�o�b�O�p�̃R���\�[���̏I������(���C�����[�v��ɌĂ�)
//*******************************************************
void endDebugConsole()
{
    //�R���\�[�����
    FreeConsole();
    return;
}

#endif // _DEBUG
