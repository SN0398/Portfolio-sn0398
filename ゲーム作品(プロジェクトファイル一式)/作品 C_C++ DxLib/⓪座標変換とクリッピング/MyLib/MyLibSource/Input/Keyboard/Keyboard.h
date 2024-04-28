#pragma once

namespace MyLib
{
	// キーボード入力関連:https://dixq.net/g/02_09.html
	void Keyboard_Update();	// キーの入力状態を更新する
	int Keyboard_Get(int KeyCode);	// 引数のキーコードのキーの入力状態を返す
}