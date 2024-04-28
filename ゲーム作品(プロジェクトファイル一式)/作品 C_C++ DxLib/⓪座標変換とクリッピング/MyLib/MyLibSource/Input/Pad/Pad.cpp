#include "Pad.h"
#include "DxLib.h"
#include <math.h>

// �p�b�h�n�֐�
// ���l:DxLib�K���PAD_INPUT�萔��2��ő����Ă���	DxLib.h/794�s~
//		MyLib�ł͔z��ɕۑ����邽�ߘA�Ԏ�

// 1P�݂̂̃p�b�h���͊֐� -------------------------------------------------------------------------
// 2P�ȏ�̓��͔͂�Ή��@2P�ȏ�̏ꍇ��Multiple�֐����g��

using namespace MyLib;

// �p�b�h�̓��͏�Ԋi�[�p�ϐ�
static int m_Pad[MYPAD_INPUTNUM];

// �p�b�h�̓��͏�ԍX�V
void MyLib::PadInput_Update()
{
	// [�p�b�h�̓��͏�ԍX�V]
	// �����F�Ȃ�
	// �ߒl�F�Ȃ�

	int Code = 1;	//  ������Ԃ͂P
	// ���݂̃t���[���̓��͏�Ԃ��擾����(�p�b�h�P�̓���)
	int NowInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	// ���͏�Ԋi�[�p�ϐ��̒��g���X�V����
	for (int i = 1; i < MYPAD_INPUTNUM; i++)
	{
		// ���݂̃t���[���œ��͂���Ă�������Z��������
		if (NowInput & Code)
		{
			m_Pad[i]++;
		}
		// ���͂���Ă��Ȃ���΂O�ɂ���
		else
		{
			m_Pad[i] = 0;
		}
		// 2��i����擾
		Code = (int)pow((double)1 * 2, (double)i);
	}
	return;
}

// �p�b�h�̓��͏�Ԃ��擾����
int MyLib::PadInput_Get(int PadCode)
{
	// [�p�b�h�̓��͏�Ԃ��擾����]
	// �������F�w��R�[�h�ԍ�
	// �� �� �l�F�w��R�[�h�̓��͏��
	int Code = 1;
	// PadCode��������܂œ�悷��
	for (int i = 1; i < PadCode; i *= 2)
	{
		// �z��̗v�f���C���N�������g
		Code++;
	}
	// �w��z��̗v�f��Ԃ�
	return m_Pad[Code];
}

// 2P�ȏ�Ή��̃p�b�h���͌n�֐� -------------------------------------------------------------------

// �w��p�b�h�̓��͏�ԍX�V
void MyLib::PadInput_Update_Multiple(PadInput Pad[], int Num)
{
	// [�w��p�b�h�̓��͏�ԍX�V]
	// �������FPadInput�\���̔z��
	// �������F���͏�Ԃ��X�V����z��̐�
	// �� �� �l�F�Ȃ�

	for (int j = 0; j < Num; j++)
	{
		// Pad�z���j�Ԗڂ�NULL�Ȃ�I������
		if (&Pad[j] == NULL) { return; }
		int Code = 1;	//  ������Ԃ͂P
		// ���݂̃t���[���̓��͏�Ԃ��擾����(�p�b�h�P�̓���)
		int NowInput = GetJoypadInputState(j + 1);
		// ���͏�Ԋi�[�p�ϐ��̒��g���X�V����
		for (int i = 1; i < MYPAD_INPUTNUM; i++)
		{
			// ���݂̃t���[���œ��͂���Ă�������Z��������
			if (NowInput & Code)
			{
				Pad[j].P_Code[i]++;
			}
			// ���͂���Ă��Ȃ���΂O�ɂ���
			else
			{
				Pad[j].P_Code[i] = 0;
			}
			// 2��i����擾
			Code = (int)pow((double)1 * 2, (double)i);
		}

	}
	return;
}

// �w�肵��PadInput�\���̂̎w��v�f�̒l���擾����
int MyLib::PadInput_Get_Multiple(PadInput Pad, int PadCode)
{
	// [�w��p�b�h�̓��͏�ԍX�V]
	// �������FPadInput�\����
	// �������F�w��R�[�h�ԍ�
	// �� �� �l�F�w�肵��PadInput�\���̂̎w��R�[�h�̓��͏��
	int Code = 1;	// �z��̗v�f
	// PadCode��������܂œ�悷��
	for (int i = 1; i < PadCode; i *= 2)
	{
		// �z��̗v�f���C���N�������g
		Code++;
	}
	// �w��z��̗v�f��Ԃ�
	return Pad.P_Code[Code];
}