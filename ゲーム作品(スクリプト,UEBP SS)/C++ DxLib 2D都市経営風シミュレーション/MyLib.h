#pragma once
#include <DxLib.h>
#include "Define.h"
#include <string>

// �萔��` ---------------------------------------------------------------------------------------

// �~����
#define PI 3.14159265358979323846

// ���Z�}�N��
#define ADD(num1,num2)	(num1+num2)
#define SUB(num1,num2)	(num1-num2)

// �E�B���h�E�̃X�^�C��
#define WINDOW_STYLE_DEFAULT					0		// �ő剻�؂�ւ��\�ȃE�B���h�E
#define WINDOW_STYLE_VIRTUAL_FULLSCREEN			1		// ���z�t���X�N���[��

// �p�b�h���͒�`
#define MYPAD_INPUTNUM		14

// �\���̒�` -------------------------------------------------------------------------------------

// 2D�̃x�N�g���\����
typedef struct _Vector2D
{
	double x;
	double y;

}Vector2D;

// 2D�̍��W�\����
typedef struct _Position2D
{
	int x;
	int y;

}Position2D;

// 3D�̃x�N�g���\����
typedef struct _Vector3D
{
	double x;
	double y;
	double z;

}Vector3D;

// �p�b�h���͏�Ԃ̍\����
typedef struct _PadInput
{
	int P_Code[MYPAD_INPUTNUM];	// �p�b�h�̓��͏�Ԋi�[�p�ϐ�

}PadInput;

// �֐��v���g�^�C�v�錾 ---------------------------------------------------------------------------

// �Q�[����{�����֌W
int Game_MainLoop(int LeaveKeyCode = KEY_INPUT_ESCAPE);	// �Q�[�����[�v�ɕK�v�Ȋ֐��̃��b�p�[
int LeaveProcess(int LeaveKeyCode);	// �I���Ɉڂ�l���󂯎��

// �t���[�����[�g�֌W:https://dixq.net/g/03_14.html
bool FPSUpdate();
void DrawFPSRate(int x, int y, unsigned int _font_color = 0xffffff);
void FPSWait();

// �L�[�{�[�h���͊֘A:https://dixq.net/g/02_09.html
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
void SetWindowProperty(int WindowStyle = WINDOW_STYLE_DEFAULT);	// �E�B���h�E�̃Z�b�g�A�b�v
int GetMyName(char name[]);	// ���������͂���(���{���Ή�)
void StringAnimation(const char string[], const int stringnum, int x, int y, int Font = NULL, int Color = 0xffffff, float StringJumpPower = 5.0, float StringGravity = 0.2, int StartInterval = 5, int width = 10);	// ���������˂�悤�ȱ�Ұ���
int GetNowTime();	// ���Ԏ擾
bool GetTimer(int _SetTime, int _Timer);	// ���Ԍo�ߎ擾
int DeleteDivGraph(int HandleArray[], int AllNum);	// �����摜�n���h���̍폜
std::string FormatNumber(int num);		// SI�ړ���
bool SaveData(void* _buffer, size_t _ElementSize, const char* _FileName); // �t�@�C����������
bool LoadData(void* _buffer, size_t _ElementSize, const char* _FileName); // �t�@�C����������

// ���b�Z�[�W�{�b�N�X�֌W
int MyMessageBoxYN(const char Text[], const char Title[]);	// Yes || No �̒l���󂯎��

// 2D�����֌W
Vector2D GetVec2D(float X, float Y);	// �w�肵��2D�x�N�g���𓾂�
Vector2D AddVec2D(Vector2D VecA, Vector2D VecB);	// ���2D�x�N�g������������2D�x�N�g���𓾂�
Vector2D SubVec2D(Vector2D VecA, Vector2D VecB);	// ���2D�x�N�g�������Z����2D�x�N�g���𓾂�
Vector2D MulVec2D(Vector2D Vec, float Multiplier);	// 2D�x�N�g������Z�����x�N�g���𓾂�
int CheckHitBoxToBox2D(Vector2D StartPosA, Vector2D EndPosA, Vector2D StartPosB, Vector2D EndPosB);	// ��`���m�̓����蔻��
int CheckHitBoxToPoint2D(Vector2D StartPos, Vector2D EndPos, Vector2D Point);	// ��`�Ɠ_�Ƃ̓����蔻��
Vector2D Normalize_2D(Vector2D pos);	// 2D�x�N�g���̐��K��
Vector2D GetDirection(Vector2D pos, Vector2D target);	// �����x�N�g���𓾂�
float GetDistance_2D(Vector2D VecA, Vector2D VecB);	// 2�_�Ԃ̋������擾����
float GetMagniture2D(float x, float y);	// �x�N�g���̑傫���𓾂�
void MoveProcess(Vector2D* pos, double MoveSpeed);	//�ėp�ړ�����

// 3D�����֌W
float GetMagnitude3D(Vector3D pos);						// �x�N�g���̑傫���𓾂�
Vector3D Normalize_3D(Vector3D pos);					// 3D�x�N�g���̐��K��