/// DXライブラリ ゲームプログラミングの雛型
/// Ver.1.8	最終更新日 2022/10/14

#include "DxLib.h"
#include "Utility.h"
#include "Define.h"
#include "Game.h"
#include "Title.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Init ---------------------------------------------------------------------------------------
	
	if (Game_Init() != 0)
	{
		return 1;
	}

	// 変数定義 -----------------------------------------------------------------------------------

#ifdef _DEBUG
	int  SceneNum = GAMESCENE_TITLE;
#else
	int  SceneNum = GAMESCENE_TITLE;
#endif

	bool InGame = true;
	bool PlayeMusic = true;

	// ゲームループ -------------------------------------------------------------------------------

	while (InGame)
	{
		switch (SceneNum)
		{
		case GAMESCENE_LEAVE:
		{
			InGame = false;
			break;
		}
		case GAMESCENE_TITLE:
		{
			SceneNum = Title(&PlayeMusic);
			break;
		}
		case GAMESCENE_GAME:
		{
			SceneNum = Game(&PlayeMusic);
			break;
		}
		}
	}

	// 終了処理 -----------------------------------------------------------------------------------

	if (Game_End() != 0)
	{
		return 1;
	}

	return 0;
}