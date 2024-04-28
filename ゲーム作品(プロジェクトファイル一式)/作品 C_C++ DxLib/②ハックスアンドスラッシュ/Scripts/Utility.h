#pragma once

// 定数定義 ---------------------------------------------------------------------------------------

// 円周率
#define PI 3.14159265358979323846

// 演算マクロ
#define ADD(num1,num2)	(num1+num2)
#define SUB(num1,num2)	(num1-num2)

// ウィンドウのスタイル
#define WINDOW_STYLE_DEFAULT				0
#define WINDOW_STYLE_FULLSCREEN				1
#define WINDOW_STYLE_VIRTUAL_FULLSCREEN		2

// 構造体定義 -------------------------------------------------------------------------------------

typedef struct _MY_GRAPH_INFO
{
	int x_left;
	int y_up;
	int x_right;
	int y_down;

}MYGRAPHINFO;

typedef struct _Vector2D
{
	float x;
	float y;

}Vector2D;

// 関数プロトタイプ宣言 ---------------------------------------------------------------------------

// ゲーム基本処理関係
int Game_Init();
int Game_MainLoop();
int Game_End();
int LeaveProcess();

// ウィンドウ関係
int ChangeWindowStyleMode(int style = WINDOW_STYLE_DEFAULT);

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

// 汎用関数
int GetMyName(char name[]);	// 文字列を入力する
int MyMessageBoxYN(const char Text[], const char Title[]);	// メッセージボックス関係

// 2D処理関係
MYGRAPHINFO GetGraphInfo(int GraphHandle, int x, int y);	// 画像の大きさをMYGRAPHINFO型で返す
int Check_Hit_Box_To_Box_2D(MYGRAPHINFO graph1, MYGRAPHINFO graph2);	// 矩形同士の当たり判定
int Check_Hit_Box_To_Point_2D(MYGRAPHINFO graph, int pointX, int pointY);	// 矩形と点との当たり判定
void Normalize_2D(float* x, float* y);	// 2Dベクトルの正規化
float GetDistance_2D(float x1, float y1, float x2, float y2);	// 2点間の距離を取得する
void MoveProcess(float* x, float* y, float MoveSpeed);	//移動ベクトル処理

/// 画像処理関係
int DeleteDivGraph(int HandleArray[], int AllNum);	// 配列に保存されている画像ハンドルを削除