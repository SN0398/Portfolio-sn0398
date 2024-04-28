#include "../MyLib.h"

static int m_Code[256];	// �}�E�X�̓��͏�Ԋi�[�p�ϐ�

// �}�E�X�̓��͏�ԍX�V
void MouseInput_Update()
{
	int tmpCode[256];	// ���̃t���[���̓��͏�ԕۑ��p�ϐ�
	int input_Code = GetMouseInput();	// ���͏�Ԃ𓾂�
	memset(tmpCode, 0, sizeof(tmpCode));	// 
	tmpCode[input_Code] = (input_Code != 0) ? 1 : 0;

	for (int i = 0; i < 256; i++)
	{
		if (tmpCode[i] != 0)
		{
			m_Code[i]++;
		}
		else
		{
			m_Code[i] = 0;
		}
	}

	int MCode = GetMouseInput();	// ���͏�Ԃ𓾂�

	return;
}

// �}�E�X�̓��͏�Ԃ��擾����
int MouseInput_Get(int InputCode)
{
	return m_Code[InputCode];
}