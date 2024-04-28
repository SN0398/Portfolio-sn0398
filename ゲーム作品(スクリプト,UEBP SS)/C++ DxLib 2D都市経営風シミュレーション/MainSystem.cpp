#include "MainSystem.h"
#include "DxLib.h"
#include "MyLib.h"
#include "SceneManager.h"
#include "ResourceManager.h"

bool MainSystem::Init()
{
	// ウィンドウモードの変更
	ChangeWindowMode(TRUE);
	// 画面サイズの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	// ウィンドウの見た目を変更する
	SetWindowStyleMode(0);
	// バックグラウンド処理の変更
	SetAlwaysRunFlag(TRUE);
	// ウィンドウのタイトルを設定する
	SetMainWindowText("Override");
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
	SetWindowProperty(0);
	// 拡大縮小の方法を設定する
	SetDrawMode(DX_DRAWMODE_ANISOTROPIC);

	return true;
}

void MainSystem::End()
{
	// Dxライブラリの終了処理
	DxLib_End();
	return;
}

// 処理
void MainSystem::Process()
{
	// 初期シーンの設定
	SceneManager::GetInstance().ChangeScene(Define::CS_CallType::Push, Define::SceneType::Title);
	// リソースの生成
	Resource::GetInstance().Load();

	// 終了リクエストが送られるまで回す
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
	// リソースの解放
	Resource::GetInstance().Delete();

	return;
}

bool MainSystem::Loop()
{
	return Game_MainLoop(NULL);
}