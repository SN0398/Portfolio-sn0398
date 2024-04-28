#include "GameProcess.h"

// ゲームのメインループ
int Game_MainLoop(int LeaveKey)
{
	Keyboard_Update();					// キーボード入力状態の更新
	MouseInput_Update();				// マウス入力状態の更新
	PadInput_Update();					// パッド入力状態の更新
	return (
		ScreenFlip() == 0 &&			// 裏画面描画
		ClearDrawScreen() == 0 &&		// 画面を消す
		ProcessMessage() == 0 &&		// ｳｨﾝﾄﾞｳﾒｯｾｰｼﾞの処理
		LeaveProcess(LeaveKey) == 0);	// 終了値の受け取り
}

// 終了リクエスト
int LeaveProcess(int LeaveKey)
{
	// 右上の×ボタンが押された
	if (GetWindowUserCloseFlag(TRUE))
	{
		return 1;
	}
	// 終了キーが押された
	if (Keyboard_Get(LeaveKey) == 1)
	{
		if (MyMessageBoxYN("終了しますか？", "終了確認") == 1)
		{
			return 1;
		}
	}
	return 0;
}