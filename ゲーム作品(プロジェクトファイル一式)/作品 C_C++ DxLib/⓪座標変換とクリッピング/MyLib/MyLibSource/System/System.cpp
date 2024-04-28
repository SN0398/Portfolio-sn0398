#include "System.h"

using namespace MyLib;

// ウィンドウ設定のセット
void MyLib::SetWindowProperty(int WindowWidth, int WindowHeight, int WindowStyle)
{
	HWND windowHandle = GetMainWindowHandle();
	int taskBarHeight = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYSIZEFRAME);

	switch (WindowStyle)
	{
	case 0:
	{
		// ウィンドウモードの変更
		ChangeWindowMode(TRUE);
		// ウィンドウの見た目を変更する
		SetWindowStyleMode(0);
		// 画面のサイズを変更できるようにするかどうか
		SetWindowSizeChangeEnableFlag(TRUE);

		SetWindowSize(WindowWidth, WindowHeight);

		int currentWindowStyle = GetWindowLong(windowHandle, GWL_STYLE);
		SetWindowLong(windowHandle, GWL_STYLE, currentWindowStyle | WS_MAXIMIZEBOX);

		//SetWindowStyleMode(7);

		break;
	}
	case 1:
	{
		//// ウィンドウモードの変更
		//ChangeWindowMode(TRUE);
		//// ウィンドウの見た目を変更する
		//SetWindowStyleMode(2);
		//// 画面のサイズを変更できるようにするかどうか
		//SetWindowSizeChangeEnableFlag(FALSE);

		//int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		//int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		//SetWindowSize(screenWidth, screenHeight);

		// ウィンドウモードの変更
		ChangeWindowMode(TRUE);
		// ウィンドウの見た目を変更する
		SetWindowStyleMode(2);
		// 画面のサイズを変更できるようにするかどうか
		SetWindowSizeChangeEnableFlag(FALSE);

		ShowWindow(GetMainWindowHandle(), SW_MAXIMIZE);

		break;
	}
	}

	return;
}