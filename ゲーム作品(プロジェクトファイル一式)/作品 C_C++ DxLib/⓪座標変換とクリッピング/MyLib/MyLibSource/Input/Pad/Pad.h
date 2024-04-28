#pragma once

namespace MyLib
{
	// パッド入力定義
	const int  MYPAD_INPUTNUM = 14;

	// パッド入力状態の構造体
	typedef struct _PadInput
	{
		int P_Code[MYPAD_INPUTNUM];	// パッドの入力状態格納用変数

	}PadInput;

	//パッド入力関連
	void PadInput_Update();	// パッドの入力状態更新
	int PadInput_Get(int PadCode);	// パッドの入力状態を取得する
	void PadInput_Update_Multiple(PadInput Pad[], int Num);	// パッド配列の入力状態更新
	int PadInput_Get_Multiple(PadInput Pad, int PadCode);	// 指定パッドの入力状態を取得する
}
