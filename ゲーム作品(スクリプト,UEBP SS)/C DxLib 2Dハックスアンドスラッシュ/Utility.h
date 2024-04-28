#pragma once

// �萔��` ---------------------------------------------------------------------------------------

// �~����
#define PI 3.14159265358979323846

// ���Z�}�N��
#define ADD(num1,num2)	(num1+num2)
#define SUB(num1,num2)	(num1-num2)

// �E�B���h�E�̃X�^�C��
#define WINDOW_STYLE_DEFAULT				0
#define WINDOW_STYLE_FULLSCREEN				1
#define WINDOW_STYLE_VIRTUAL_FULLSCREEN		2

// �\���̒�` -------------------------------------------------------------------------------------

typedef struct _MY_GRAPH_INFO
{
	int x_left;
	int y_up;
	int x_right;
	int y_down;

}MYGRAPHINFO;

typedef struct _Vector2D
{
	float x;
	float y;

}Vector2D;

// �֐��v���g�^�C�v�錾 ---------------------------------------------------------------------------

// �Q�[����{�����֌W
int Game_Init();
int Game_MainLoop();
int Game_End();
int LeaveProcess();

// �E�B���h�E�֌W
int ChangeWindowStyleMode(int style = WINDOW_STYLE_DEFAULT);

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

// �ėp�֐�
int GetMyName(char name[]);	// ���������͂���
int MyMessageBoxYN(const char Text[], const char Title[]);	// ���b�Z�[�W�{�b�N�X�֌W

// 2D�����֌W
MYGRAPHINFO GetGraphInfo(int GraphHandle, int x, int y);	// �摜�̑傫����MYGRAPHINFO�^�ŕԂ�
int Check_Hit_Box_To_Box_2D(MYGRAPHINFO graph1, MYGRAPHINFO graph2);	// ��`���m�̓����蔻��
int Check_Hit_Box_To_Point_2D(MYGRAPHINFO graph, int pointX, int pointY);	// ��`�Ɠ_�Ƃ̓����蔻��
void Normalize_2D(float* x, float* y);	// 2D�x�N�g���̐��K��
float GetDistance_2D(float x1, float y1, float x2, float y2);	// 2�_�Ԃ̋������擾����
void MoveProcess(float* x, float* y, float MoveSpeed);	//�ړ��x�N�g������

/// �摜�����֌W
int DeleteDivGraph(int HandleArray[], int AllNum);	// �z��ɕۑ�����Ă���摜�n���h�����폜