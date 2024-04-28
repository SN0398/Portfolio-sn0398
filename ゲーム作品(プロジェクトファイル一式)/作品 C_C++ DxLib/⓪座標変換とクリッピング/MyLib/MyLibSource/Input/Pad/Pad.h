#pragma once

namespace MyLib
{
	// �p�b�h���͒�`
	const int  MYPAD_INPUTNUM = 14;

	// �p�b�h���͏�Ԃ̍\����
	typedef struct _PadInput
	{
		int P_Code[MYPAD_INPUTNUM];	// �p�b�h�̓��͏�Ԋi�[�p�ϐ�

	}PadInput;

	//�p�b�h���͊֘A
	void PadInput_Update();	// �p�b�h�̓��͏�ԍX�V
	int PadInput_Get(int PadCode);	// �p�b�h�̓��͏�Ԃ��擾����
	void PadInput_Update_Multiple(PadInput Pad[], int Num);	// �p�b�h�z��̓��͏�ԍX�V
	int PadInput_Get_Multiple(PadInput Pad, int PadCode);	// �w��p�b�h�̓��͏�Ԃ��擾����
}
