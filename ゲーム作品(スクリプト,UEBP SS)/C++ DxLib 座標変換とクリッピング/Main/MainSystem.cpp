#include "MyLib.h"
#include "Main/MainSystem.h"
#include "Config/Define.h"
#include "Config/Console.h"
#include "Resource/ResourceManager.h"
#include "Scene/SceneManager.h"
#include "Scene/Game/Game.h"
#include "System/GameProcess.h"

bool MainSystem::Init()
{
	// �E�B���h�E���[�h�̕ύX
	ChangeWindowMode(TRUE);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	// �E�B���h�E�̌����ڂ�ύX����
	SetWindowStyleMode(0);
	// �o�b�N�O���E���h�����̕ύX
	SetAlwaysRunFlag(FALSE);
	// �E�B���h�E�̃^�C�g����ݒ肷��
	SetMainWindowText("DxLib");
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
	SetWindowProperty(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_STYLE_DEFAULT);
#ifdef _DEBUG
	// �f�o�b�O�p�̃R���\�[���̏�������
	initDebugConsole();

#endif
	// �g��k���̕��@��ݒ肷��
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	return true;
}

void MainSystem::End()
{
#ifdef _DEBUG
	// �f�o�b�O�p�̃R���\�[���̏I������
	endDebugConsole();
#endif
	// Dx���C�u�����̏I������
	DxLib_End();
	return;
}

// ����
void MainSystem::Process()
{
	auto& Smgr = SceneManager::GetInstance();
	// �����V�[���̐ݒ�
	Smgr.Change<Game>(SceneManager::AC_Push);
	Smgr.ChangeProcess();	// �V�[���ύX����
	// ���\�[�X�̐���
	Resource::GetInstance().Load();

	// �I�����N�G�X�g��������܂ŉ�
	while (Loop() && Smgr.GetSize() > 0)
	{
		FPSUpdate();
		Smgr.Process();	// ����->�`��
		Smgr.ChangeProcess();	// �V�[���ύX����
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