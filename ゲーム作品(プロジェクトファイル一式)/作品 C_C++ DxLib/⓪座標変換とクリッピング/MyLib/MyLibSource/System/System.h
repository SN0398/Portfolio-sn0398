#pragma once
#include "DxLib.h"

namespace MyLib
{
	// ウィンドウのスタイル
	const int WINDOW_STYLE_DEFAULT			  = 0;		// 最大化切り替え可能なウィンドウ
	const int WINDOW_STYLE_VIRTUAL_FULLSCREEN = 1;		// 仮想フルスクリーン

	void SetWindowProperty(int WindowWidth, int WindowHeight, int WindowStyle = WINDOW_STYLE_DEFAULT);	// ウィンドウのセットアップ
}