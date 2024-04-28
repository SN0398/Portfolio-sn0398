#pragma once
#include <DxLib.h>
#include "Define.h"
#include <string>

// 定数定義 ---------------------------------------------------------------------------------------

// 円周率
#define PI 3.14159265358979323846

// 演算マクロ
#define ADD(num1,num2)	(num1+num2)
#define SUB(num1,num2)	(num1-num2)

// ウィンドウのスタイル
#define WINDOW_STYLE_DEFAULT					0		// 最大化切り替え可能なウィンドウ
#define WINDOW_STYLE_VIRTUAL_FULLSCREEN			1		// 仮想フルスクリーン

// パッド入力定義
#define MYPAD_INPUTNUM		14

// 構造体定義 -------------------------------------------------------------------------------------

// 2Dのベクトル構造体
typedef struct _Vector2D
{
	double x;
	double y;

}Vector2D;

// 2Dの座標構造体
typedef struct _Position2D
{
	int x;
	int y;

}Position2D;

// 3Dのベクトル構造体
typedef struct _Vector3D
{
	double x;
	double y;
	double z;

}Vector3D;

// パッド入力状態の構造体
typedef struct _PadInput
{
	int P_Code[MYPAD_INPUTNUM];	// パッドの入力状態格納用変数

}PadInput;

// 関数プロトタイプ宣言 ---------------------------------------------------------------------------

// ゲーム基本処理関係
int Game_MainLoop(int LeaveKeyCode = KEY_INPUT_ESCAPE);	// ゲームループに必要な関数のラッパー
int LeaveProcess(int LeaveKeyCode);	// 終了に移る値を受け取る

// フレームレート関係:https://dixq.net/g/03_14.html
bool FPSUpdate();
void DrawFPSRate(int x, int y, unsigned int _font_color = 0xffffff);
void FPSWait();

// キーボード入力関連:https://dixq.net/g/02_09.html
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
void SetWindowProperty(int WindowStyle = WINDOW_STYLE_DEFAULT);	// ウィンドウのセットアップ
int GetMyName(char name[]);	// 文字列を入力する(日本語非対応)
void StringAnimation(const char string[], const int stringnum, int x, int y, int Font = NULL, int Color = 0xffffff, float StringJumpPower = 5.0, float StringGravity = 0.2, int StartInterval = 5, int width = 10);	// 文字が跳ねるようなｱﾆﾒｰｼｮﾝ
int GetNowTime();	// 時間取得
bool GetTimer(int _SetTime, int _Timer);	// 時間経過取得
int DeleteDivGraph(int HandleArray[], int AllNum);	// 分割画像ハンドルの削除
std::string FormatNumber(int num);		// SI接頭辞
bool SaveData(void* _buffer, size_t _ElementSize, const char* _FileName); // ファイル書き込み
bool LoadData(void* _buffer, size_t _ElementSize, const char* _FileName); // ファイル書き込み

// メッセージボックス関係
int MyMessageBoxYN(const char Text[], const char Title[]);	// Yes || No の値を受け取る

// 2D処理関係
Vector2D GetVec2D(float X, float Y);	// 指定した2Dベクトルを得る
Vector2D AddVec2D(Vector2D VecA, Vector2D VecB);	// 二つの2Dベクトルを合成した2Dベクトルを得る
Vector2D SubVec2D(Vector2D VecA, Vector2D VecB);	// 二つの2Dベクトルを減算した2Dベクトルを得る
Vector2D MulVec2D(Vector2D Vec, float Multiplier);	// 2Dベクトルを乗算したベクトルを得る
int CheckHitBoxToBox2D(Vector2D StartPosA, Vector2D EndPosA, Vector2D StartPosB, Vector2D EndPosB);	// 矩形同士の当たり判定
int CheckHitBoxToPoint2D(Vector2D StartPos, Vector2D EndPos, Vector2D Point);	// 矩形と点との当たり判定
Vector2D Normalize_2D(Vector2D pos);	// 2Dベクトルの正規化
Vector2D GetDirection(Vector2D pos, Vector2D target);	// 方向ベクトルを得る
float GetDistance_2D(Vector2D VecA, Vector2D VecB);	// 2点間の距離を取得する
float GetMagniture2D(float x, float y);	// ベクトルの大きさを得る
void MoveProcess(Vector2D* pos, double MoveSpeed);	//汎用移動処理

// 3D処理関係
float GetMagnitude3D(Vector3D pos);						// ベクトルの大きさを得る
Vector3D Normalize_3D(Vector3D pos);					// 3Dベクトルの正規化