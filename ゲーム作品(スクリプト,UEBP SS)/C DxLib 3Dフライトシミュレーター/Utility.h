#pragma once
#include <DxLib.h>
#include "Define.h"

// 定数定義 ---------------------------------------------------------------------------------------

// 円周率
#define PI 3.14159265358979323846

// 演算マクロ
#define ADD(num1,num2)	(num1+num2)
#define SUB(num1,num2)	(num1-num2)

// パッド入力定義
#define MYPAD_INPUTNUM		14

// 構造体定義 -------------------------------------------------------------------------------------

typedef struct _PadInput
{
	int P_Code[MYPAD_INPUTNUM];	// パッドの入力状態格納用変数

}PadInput;

// 関数プロトタイプ宣言 ---------------------------------------------------------------------------

// ゲーム基本処理関係
int Game_Init();
int Game_MainLoop(int LeaveKeyCode = KEY_INPUT_ESCAPE);
int Game_End();
int LeaveProcess(int LeaveKeyCode);

// フレームレート関係
bool FPSUpdate();
void DrawFPSRate(int x, int y, unsigned int _font_color = 0xffffff);
void FPSWait();

// キーボード入力関連
void Keyboard_Update();	// キーの入力状態を更新する
int Keyboard_Get(int KeyCode);	// 引数のキーコードのキーの入力状態を返す

// マウス入力関係
void MouseInput_Update();	// マウスの入力状態更新
int MouseInput_Get(int InputCode);	// マウスの入力状態を取得する

//パッド入力関連
void PadInput_Update();	// パッドの入力状態更新
int PadInput_Get(int PadCode);	// パッドの入力状態を取得する
void PadInput_Update_Multiple(PadInput Pad[], int Num);	// パッド配列の入力状態更新
int PadInput_Get_Multiple(PadInput Pad, int PadCode);	// 指定パッドの入力状態を取得する

// 汎用関数
int GetMyName(char name[]);	// 文字列を入力する
int MyMessageBoxYN(const char Text[], const char Title[]);	// メッセージボックス関係
int DeleteDivGraph(int HandleArray[], int AllNum);	// 分割画像ハンドルの削除

// 3D処理関係
float GetMagnitude(VECTOR pos);	// ベクトルの大きさを得る
VECTOR Normalize_3D(VECTOR pos);	// 3Dベクトルの正規化