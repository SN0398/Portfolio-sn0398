#include "../Utility.h"

// �I�����N�G�X�g
int LeaveProcess(int LeaveKey)
{
	// �I�����N�G�X�g������ꂽ��false��Ԃ�
	if (GetWindowUserCloseFlag(TRUE))
	{
		return 1;
	}
	// �L�[�������ꂽ��I������
	if (Keyboard_Get(LeaveKey) == 1)
	{
		if (MyMessageBoxYN("�I�����܂����H", "�I���m�F") == 1)
		{
			return 1;
		}
	}
	return 0;
}

// ������̓��͏���
int GetMyName(char name[])
{
	int  stringnum = 0;	// �����̈ʒu
	char InputChar[2];	// ���ݓ��͂��Ă��镶���ƃk������

	// �������łP��Ԃ�
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1)
	{
		return 1;
	}
	// �ޯ���߰����ň�O�̕������폜����
	if (Keyboard_Get(KEY_INPUT_BACK) == 1)
	{
		// char�z�񂩂�k����������������
		while (name[0] != '\0' && name[stringnum] != '\0')
		{
			stringnum++;
		}
		// ��O�̕������폜����
		name[stringnum - 1] = '\0';
	}

	// �������擾����
	InputChar[0] = GetInputChar(TRUE);
	InputChar[1] = '\0';
	// ���������͂���Ă����char�z��ɓ��͂���������ǉ�����
	if (InputChar[0] != 0 && InputChar[0] >= CTRL_CODE_CMP)
	{
		while (name[0] != '\0' && name[stringnum] != '\0')
		{
			stringnum++;
		}
		name[stringnum] = InputChar[0];
	}

	// �ʏ�̖߂�l
	return 0;
}

// ���b�Z�[�W�{�b�N�X���� Yes �� No ��Ԃ�
int MyMessageBoxYN(const char Text[], const char Title[])
{
	if (MessageBox(NULL, TEXT(Text), TEXT(Title), MB_YESNO | MB_ICONQUESTION) != IDNO) { return 1; }
	else { return 0; }
}

// �����摜�n���h���̍폜
int DeleteDivGraph(int HandleArray[], int AllNum)
{
	for (int i = 0; i < AllNum; i++)
	{
		DeleteGraph(HandleArray[i]);
	}
	for (int i = 0; i < AllNum; i++)
	{
		if (HandleArray[i] != -1)
		{
			return 0;
		}
	}
	return 1;
}