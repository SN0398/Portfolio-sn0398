// 使用ライブラリ：DXライブラリ
// ホームページ : https://dxlib.xsrv.jp/
// 関数リスト   : https://dxlib.xsrv.jp/dxfunc.html

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

	// 変数定義 -----------------------------------------------------------------------------------

	int  SceneNum;

#ifdef _DEBUG
	SceneNum = GS_GAME;
#else
	SceneNum = GS_GAME;
#endif

	bool InGame = true;

	// ゲームループ -------------------------------------------------------------------------------

	while (InGame)
	{
		SceneNum = SceneManager[SceneNum]();
		InGame = (SceneNum != GS_LEAVE);
	}

	// 終了処理 -----------------------------------------------------------------------------------

	if (Game_End() != 0)
	{
		return 1;
	}

	return 0;
}

// ゲームの初期化処理
int Game_Init()
{
	// ウィンドウモードの変更
	ChangeWindowMode(TRUE);
	// 画面サイズの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	// ウィンドウの見た目を変更する
	SetWindowStyleMode(0);
	// バックグラウンド処理の変更
	SetAlwaysRunFlag(FALSE);
	// ウィンドウのタイトルを設定する
	SetMainWindowText("DxLib");
	// 画面のサイズを変更できるようにするかどうか
	SetWindowSizeChangeEnableFlag(FALSE);
	// ウィンドウの解像度を維持したままサイズを変更する
	SetWindowSizeExtendRate(1.0);
	// ウィンドウのアイコンを変更
	SetWindowIconID(2284930);
	// Log.txtを出力するかを変更
	SetOutApplicationLogValidFlag(FALSE);
	// DXライブラリ初期化
	if (DxLib_Init() == -1)
	{
		//初期化に失敗
		return -1;
	}
	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);
	// 3D空間の背景色変更
	SetBackgroundColor(30, 128, 255);
	// 使用するDirectXのバージョンを変える
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	return 0;
}

// ゲームのメインループ
int Game_MainLoop(int LeaveKey)
{
	Keyboard_Update();					// キーボード入力状態更新
	MouseInput_Update();				// マウス入力状態更新
	PadInput_Update();					// パッド入力状態更新
	return (
			ScreenFlip() == 0 &&		// 
			ClearDrawScreen() == 0 &&	// 画面
			ProcessMessage() == 0 &&	// 
			LeaveProcess(LeaveKey) == 0	// ゲーム状態更新
			);
}

// ゲームの終了処理
int Game_End()
{
	DxLib_End();

	return 0;
}