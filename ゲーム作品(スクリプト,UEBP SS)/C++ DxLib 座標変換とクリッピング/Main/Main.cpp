#include "DxLib.h"
#include "MainSystem.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MainSystem system;	// 全体の管理クラス
	if (system.Init())	// 初期化成功
	{
		system.Process();	// 本処理
	}
	system.End();	// 終了処理

	return 0;
}