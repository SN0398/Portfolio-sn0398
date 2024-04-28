#include "../Utility.h"
#include <math.h>

static int m_Pad[MYPAD_INPUTNUM];	// �p�b�h�̓��͏�Ԋi�[�p�ϐ�

// �p�b�h�̓��͏�ԍX�V
void PadInput_Update()
{
	int Code = 1;
	int NowInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	for (int i = 1; i < MYPAD_INPUTNUM; i++)
	{
		if (NowInput & Code)
		{
			m_Pad[i]++;
		}
		else
		{
			m_Pad[i] = 0;
		}
		Code = (int)pow((double)1 * 2, (double)i);
	}
	return;
}

// �p�b�h�̓��͏�Ԃ��擾����
int PadInput_Get(int PadCode)
{
	int Code = 1;
	for (int i = 1; i < PadCode; i *= 2)
	{
		Code++;
	}
	return m_Pad[Code];
}

// �w��p�b�h�̓��͏�ԍX�V
void PadInput_Update_Multiple(PadInput Pad[], int Num)
{
	for (int j = 0; j < Num; j++)
	{
		int Code = 1;
		int NowInput = GetJoypadInputState(j + 1);
		for (int i = 1; i < MYPAD_INPUTNUM; i++)
		{
			if (NowInput & Code)
			{
				Pad[j].P_Code[i]++;
			}
			else
			{
				Pad[j].P_Code[i] = 0;
			}
			Code = (int)pow((double)1 * 2, (double)i);
		}
	}
	return;
}

// �w��p�b�h�̓��͏�Ԃ��擾����
int PadInput_Get_Multiple(PadInput Pad, int PadCode)
{
	int Code = 1;
	for (int i = 1; i < PadCode; i *= 2)
	{
		Code++;
	}
	return Pad.P_Code[Code];

}