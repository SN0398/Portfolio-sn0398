// �g�p���C�u�����FDX���C�u����
// �z�[���y�[�W : https://dxlib.xsrv.jp/
// �֐����X�g   : https://dxlib.xsrv.jp/dxfunc.html

#include "DxLib.h"
#include "Utility.h"
#include "Define.h"
#include "SceneMgr.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Init ---------------------------------------------------------------------------------------
	
	if (Game_Init() != 0)
	{
		return 1;
	}

	// �ϐ���` -----------------------------------------------------------------------------------

	int  SceneNum;

#ifdef _DEBUG
	SceneNum = GS_GAME;
#else
	SceneNum = GS_GAME;
#endif

	bool InGame = true;

	// �Q�[�����[�v -------------------------------------------------------------------------------

	while (InGame)
	{
		SceneNum = SceneManager[SceneNum]();
		InGame = (SceneNum != GS_LEAVE);
	}

	// �I������ -----------------------------------------------------------------------------------

	if (Game_End() != 0)
	{
		return 1;
	}

	return 0;
}

// �Q�[���̏���������
int Game_Init()
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
	SetWindowSizeChangeEnableFlag(FALSE);
	// �E�B���h�E�̉𑜓x���ێ������܂܃T�C�Y��ύX����
	SetWindowSizeExtendRate(1.0);
	// �E�B���h�E�̃A�C�R����ύX
	SetWindowIconID(2284930);
	// Log.txt���o�͂��邩��ύX
	SetOutApplicationLogValidFlag(FALSE);
	// DX���C�u����������
	if (DxLib_Init() == -1)
	{
		//�������Ɏ��s
		return -1;
	}
	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);
	// 3D��Ԃ̔w�i�F�ύX
	SetBackgroundColor(30, 128, 255);
	// �g�p����DirectX�̃o�[�W������ς���
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	return 0;
}

// �Q�[���̃��C�����[�v
int Game_MainLoop(int LeaveKey)
{
	Keyboard_Update();					// �L�[�{�[�h���͏�ԍX�V
	MouseInput_Update();				// �}�E�X���͏�ԍX�V
	PadInput_Update();					// �p�b�h���͏�ԍX�V
	return (
			ScreenFlip() == 0 &&		// 
			ClearDrawScreen() == 0 &&	// ���
			ProcessMessage() == 0 &&	// 
			LeaveProcess(LeaveKey) == 0	// �Q�[����ԍX�V
			);
}

// �Q�[���̏I������
int Game_End()
{
	DxLib_End();

	return 0;
}