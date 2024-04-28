#include "GameProcess.h"

// �Q�[���̃��C�����[�v
int Game_MainLoop(int LeaveKey)
{
	Keyboard_Update();					// �L�[�{�[�h���͏�Ԃ̍X�V
	MouseInput_Update();				// �}�E�X���͏�Ԃ̍X�V
	PadInput_Update();					// �p�b�h���͏�Ԃ̍X�V
	return (
		ScreenFlip() == 0 &&			// ����ʕ`��
		ClearDrawScreen() == 0 &&		// ��ʂ�����
		ProcessMessage() == 0 &&		// ����޳ү���ނ̏���
		LeaveProcess(LeaveKey) == 0);	// �I���l�̎󂯎��
}

// �I�����N�G�X�g
int LeaveProcess(int LeaveKey)
{
	// �E��́~�{�^���������ꂽ
	if (GetWindowUserCloseFlag(TRUE))
	{
		return 1;
	}
	// �I���L�[�������ꂽ
	if (Keyboard_Get(LeaveKey) == 1)
	{
		if (MyMessageBoxYN("�I�����܂����H", "�I���m�F") == 1)
		{
			return 1;
		}
	}
	return 0;
}