#pragma once
#include <DxLib.h>
#include "Define.h"

// �萔��` ---------------------------------------------------------------------------------------

// �~����
#define PI 3.14159265358979323846

// ���Z�}�N��
#define ADD(num1,num2)	(num1+num2)
#define SUB(num1,num2)	(num1-num2)

// �p�b�h���͒�`
#define MYPAD_INPUTNUM		14

// �\���̒�` -------------------------------------------------------------------------------------

typedef struct _PadInput
{
	int P_Code[MYPAD_INPUTNUM];	// �p�b�h�̓��͏�Ԋi�[�p�ϐ�

}PadInput;

// �֐��v���g�^�C�v�錾 ---------------------------------------------------------------------------

// �Q�[����{�����֌W
int Game_Init();
int Game_MainLoop(int LeaveKeyCode = KEY_INPUT_ESCAPE);
int Game_End();
int LeaveProcess(int LeaveKeyCode);

// �t���[�����[�g�֌W
bool FPSUpdate();
void DrawFPSRate(int x, int y, unsigned int _font_color = 0xffffff);
void FPSWait();

// �L�[�{�[�h���͊֘A
void Keyboard_Update();	// �L�[�̓��͏�Ԃ��X�V����
int Keyboard_Get(int KeyCode);	// �����̃L�[�R�[�h�̃L�[�̓��͏�Ԃ�Ԃ�

// �}�E�X���͊֌W
void MouseInput_Update();	// �}�E�X�̓��͏�ԍX�V
int MouseInput_Get(int InputCode);	// �}�E�X�̓��͏�Ԃ��擾����

//�p�b�h���͊֘A
void PadInput_Update();	// �p�b�h�̓��͏�ԍX�V
int PadInput_Get(int PadCode);	// �p�b�h�̓��͏�Ԃ��擾����
void PadInput_Update_Multiple(PadInput Pad[], int Num);	// �p�b�h�z��̓��͏�ԍX�V
int PadInput_Get_Multiple(PadInput Pad, int PadCode);	// �w��p�b�h�̓��͏�Ԃ��擾����

// �ėp�֐�
int GetMyName(char name[]);	// ���������͂���
int MyMessageBoxYN(const char Text[], const char Title[]);	// ���b�Z�[�W�{�b�N�X�֌W
int DeleteDivGraph(int HandleArray[], int AllNum);	// �����摜�n���h���̍폜

// 3D�����֌W
float GetMagnitude(VECTOR pos);	// �x�N�g���̑傫���𓾂�
VECTOR Normalize_3D(VECTOR pos);	// 3D�x�N�g���̐��K��