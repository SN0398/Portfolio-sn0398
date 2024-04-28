#include "Keyboard.h"
#include "DxLib.h"

namespace MyLib
{
	static int m_Key[256];  // �L�[�̓��͏�Ԋi�[�p�ϐ�
}

using namespace MyLib;

// �L�[�̓��͏�ԍX�V
void MyLib::Keyboard_Update()
{
	char tmpKey[256];             // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey);  // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++)
	{
		if (tmpKey[i] != 0)
		{ // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			m_Key[i]++;   // ���Z
		}
		else
		{              // ������Ă��Ȃ����
			m_Key[i] = 0; // 0�ɂ���
		}
	}
	return;
}

// KeyCode�̃L�[�̓��͏�Ԃ��擾����
int MyLib::Keyboard_Get(int KeyCode)
{
	return m_Key[KeyCode]; // KeyCode�̓��͏�Ԃ�Ԃ�
}