#include "Pad.h"
#include "DxLib.h"
#include <math.h>

// パッド系関数
// 備考:DxLib規定のPAD_INPUT定数は2乗で増えていく	DxLib.h/794行~
//		MyLibでは配列に保存するため連番式

// 1Pのみのパッド入力関数 -------------------------------------------------------------------------
// 2P以上の入力は非対応　2P以上の場合はMultiple関数を使う

using namespace MyLib;

// パッドの入力状態格納用変数
static int m_Pad[MYPAD_INPUTNUM];

// パッドの入力状態更新
void MyLib::PadInput_Update()
{
	// [パッドの入力状態更新]
	// 引数：なし
	// 戻値：なし

	int Code = 1;	//  初期状態は１
	// 現在のフレームの入力状態を取得する(パッド１の入力)
	int NowInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	// 入力状態格納用変数の中身を更新する
	for (int i = 1; i < MYPAD_INPUTNUM; i++)
	{
		// 現在のフレームで入力されていたら加算し続ける
		if (NowInput & Code)
		{
			m_Pad[i]++;
		}
		// 入力されていなければ０にする
		else
		{
			m_Pad[i] = 0;
		}
		// 2のi乗を取得
		Code = (int)pow((double)1 * 2, (double)i);
	}
	return;
}

// パッドの入力状態を取得する
int MyLib::PadInput_Get(int PadCode)
{
	// [パッドの入力状態を取得する]
	// 第一引数：指定コード番号
	// 戻 り 値：指定コードの入力状態
	int Code = 1;
	// PadCodeが見つかるまで二乗する
	for (int i = 1; i < PadCode; i *= 2)
	{
		// 配列の要素数インクリメント
		Code++;
	}
	// 指定配列の要素を返す
	return m_Pad[Code];
}

// 2P以上対応のパッド入力系関数 -------------------------------------------------------------------

// 指定パッドの入力状態更新
void MyLib::PadInput_Update_Multiple(PadInput Pad[], int Num)
{
	// [指定パッドの入力状態更新]
	// 第一引数：PadInput構造体配列
	// 第二引数：入力状態を更新する配列の数
	// 戻 り 値：なし

	for (int j = 0; j < Num; j++)
	{
		// Pad配列のj番目がNULLなら終了する
		if (&Pad[j] == NULL) { return; }
		int Code = 1;	//  初期状態は１
		// 現在のフレームの入力状態を取得する(パッド１の入力)
		int NowInput = GetJoypadInputState(j + 1);
		// 入力状態格納用変数の中身を更新する
		for (int i = 1; i < MYPAD_INPUTNUM; i++)
		{
			// 現在のフレームで入力されていたら加算し続ける
			if (NowInput & Code)
			{
				Pad[j].P_Code[i]++;
			}
			// 入力されていなければ０にする
			else
			{
				Pad[j].P_Code[i] = 0;
			}
			// 2のi乗を取得
			Code = (int)pow((double)1 * 2, (double)i);
		}

	}
	return;
}

// 指定したPadInput構造体の指定要素の値を取得する
int MyLib::PadInput_Get_Multiple(PadInput Pad, int PadCode)
{
	// [指定パッドの入力状態更新]
	// 第一引数：PadInput構造体
	// 第二引数：指定コード番号
	// 戻 り 値：指定したPadInput構造体の指定コードの入力状態
	int Code = 1;	// 配列の要素
	// PadCodeが見つかるまで二乗する
	for (int i = 1; i < PadCode; i *= 2)
	{
		// 配列の要素数インクリメント
		Code++;
	}
	// 指定配列の要素を返す
	return Pad.P_Code[Code];
}