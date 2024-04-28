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
	SetWindowSizeChangeEnableFlag(TRUE);
	// ウィンドウの解像度を維持したままサイズを変更する
	SetWindowSizeExtendRate(1.0);
	// ウィンドウのアイコンを変更
	SetWindowIconID(2284930);
	// Log.txtを出力するかを変更
#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);
#else
	SetOutApplicationLogValidFlag(FALSE);
#endif
	// ユーザーが閉じるボタンを押しても強制終了しないようにする
	SetWindowUserCloseEnableFlag(FALSE);
	// DXライブラリ初期化
	if (DxLib_Init() == -1)
	{
		//初期化に失敗
		return false;
	}
	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);
	// ウィンドウ設定のセットアップ
	SetWindowProperty(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_STYLE_DEFAULT);
#ifdef _DEBUG
	// デバッグ用のコンソールの初期処理
	initDebugConsole();

#endif
	// 拡大縮小の方法を設定する
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	return true;
}

void MainSystem::End()
{
#ifdef _DEBUG
	// デバッグ用のコンソールの終了処理
	endDebugConsole();
#endif
	// Dxライブラリの終了処理
	DxLib_End();
	return;
}

// 処理
void MainSystem::Process()
{
	auto& Smgr = SceneManager::GetInstance();
	// 初期シーンの設定
	Smgr.Change<Game>(SceneManager::AC_Push);
	Smgr.ChangeProcess();	// シーン変更処理
	// リソースの生成
	Resource::GetInstance().Load();

	// 終了リクエストが送られるまで回す
	while (Loop() && Smgr.GetSize() > 0)
	{
		FPSUpdate();
		Smgr.Process();	// 処理->描画
		Smgr.ChangeProcess();	// シーン変更処理
		FPSWait();
	}
	// リソースの解放
	Resource::GetInstance().Delete();

	return;
}

bool MainSystem::Loop()
{
	return Game_MainLoop(NULL);
}