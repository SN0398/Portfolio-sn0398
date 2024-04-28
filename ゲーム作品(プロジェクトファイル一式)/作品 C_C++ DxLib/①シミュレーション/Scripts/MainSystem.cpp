#include "MainSystem.h"
#include "DxLib.h"
#include "MyLib.h"
#include "SceneManager.h"
#include "ResourceManager.h"

bool MainSystem::Init()
{
	// �E�B���h�E���[�h�̕ύX
	ChangeWindowMode(TRUE);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	// �E�B���h�E�̌����ڂ�ύX����
	SetWindowStyleMode(0);
	// �o�b�N�O���E���h�����̕ύX
	SetAlwaysRunFlag(TRUE);
	// �E�B���h�E�̃^�C�g����ݒ肷��
	SetMainWindowText("Override");
	// ��ʂ̃T�C�Y��ύX�ł���悤�ɂ��邩�ǂ���
	SetWindowSizeChangeEnableFlag(TRUE);
	// �E�B���h�E�̉𑜓x���ێ������܂܃T�C�Y��ύX����
	SetWindowSizeExtendRate(1.0);
	// �E�B���h�E�̃A�C�R����ύX
	SetWindowIconID(2284930);
	// Log.txt���o�͂��邩��ύX
#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);
#else
	SetOutApplicationLogValidFlag(FALSE);
#endif
	// ���[�U�[������{�^���������Ă������I�����Ȃ��悤�ɂ���
	SetWindowUserCloseEnableFlag(FALSE);
	// DX���C�u����������
	if (DxLib_Init() == -1)
	{
		//�������Ɏ��s
		return false;
	}
	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);
	// �E�B���h�E�ݒ�̃Z�b�g�A�b�v
	SetWindowProperty(0);
	// �g��k���̕��@��ݒ肷��
	SetDrawMode(DX_DRAWMODE_ANISOTROPIC);

	return true;
}

void MainSystem::End()
{
	// Dx���C�u�����̏I������
	DxLib_End();
	return;
}

// ����
void MainSystem::Process()
{
	// �����V�[���̐ݒ�
	SceneManager::GetInstance().ChangeScene(Define::CS_CallType::Push, Define::SceneType::Title);
	// ���\�[�X�̐���
	Resource::GetInstance().Load();

	// �I�����N�G�X�g��������܂ŉ�
	while (Loop())
	{
		FPSUpdate();
		if (!SceneManager::GetInstance().Update())
		{
			break;
		}
		if (SceneManager::GetInstance().GetEmpty()) { break; }
		SceneManager::GetInstance().Draw();
		FPSWait();
	}
	// ���\�[�X�̉��
	Resource::GetInstance().Delete();

	return;
}

bool MainSystem::Loop()
{
	return Game_MainLoop(NULL);
}