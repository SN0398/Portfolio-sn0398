#include "DxLib.h"
#include <math.h>
#include "Utility.h"
#include "Define.h"

static int mStartTime;
static int mCount;
static float mFps;
static const int N = 60;
static const int FPS = 60;

static int m_Key[256];  // キーの入力状態格納用変数
static int m_Code[256];	// マウスの入力状態格納用変数

// ゲームの初期化処理
int Game_Init()
{
	// ウィンドウモードの変更
	ChangeWindowMode(TRUE);
	// 画面サイズの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	// ウィンドウの見た目を変更する
	SetWindowStyleMode(0);
	// バックグラウンド処理の変更
	SetAlwaysRunFlag(TRUE);
	// ウィンドウのタイトルを設定する
	SetMainWindowText("DxLib");
	// 画面のサイズを変更できるようにするかどうか
	SetWindowSizeChangeEnableFlag(TRUE);
	// ウィンドウの解像度を維持したままサイズを変更する
	SetWindowSizeExtendRate(1.0);
	// ウィンドウのアイコンを変更
	SetWindowIconID(2284930);
	// Log.txtを出力するかを変更
	SetOutApplicationLogValidFlag(FALSE);
	// 最大化ボタンを適用
	//SetUseASyncChangeWindowModeFunction(TRUE, NULL, NULL);
	// ユーザーが閉じるボタンを押しても強制終了しないようにする
	SetWindowUserCloseEnableFlag(FALSE);
	// DXライブラリ初期化
	if (DxLib_Init() == -1)
	{
		//初期化に失敗
		return -1;
	}
	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	return 0;
}

// ゲームのメインループ
int Game_MainLoop()
{
	Keyboard_Update();
	MouseInput_Update();
	return (ScreenFlip() == 0 && ClearDrawScreen() == 0 && ProcessMessage() == 0 && LeaveProcess() == 0);
}

// ゲームの終了処理
int Game_End()
{
	DxLib_End();

	return 0;
}

// 終了リクエスト
int LeaveProcess()
{
	// 終了リクエストが送られたらfalseを返す
	if (GetWindowUserCloseFlag(TRUE))
	{
		return 1;
	}
	return 0;
}

// ウィンドウスタイルの変更
int ChangeWindowStyleMode(int style)
{
	int ChangedFlag = 0;

	switch (style)
	{
	case WINDOW_STYLE_DEFAULT:
	{
		// ウィンドウの見た目を変更する
		SetWindowStyleMode(0);
		// ウィンドウの大きさを変更する
		SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

		ChangedFlag = 1;
		break;
	}
	case WINDOW_STYLE_FULLSCREEN:
	{
		ChangedFlag = 1;
		break;
	}
	case WINDOW_STYLE_VIRTUAL_FULLSCREEN:
	{
		ChangedFlag = 1;
		break;
	}
	}

	return ChangedFlag;
}

// FPSの更新
bool FPSUpdate()
{
	if (mCount == 0)
	{
		mStartTime = GetNowCount();
	}
	if (mCount == N)
	{
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

// FPSの描画
void DrawFPSRate(int x, int y, unsigned int _font_color)
{
	DrawFormatString(x, y, _font_color, "%.1f", mFps);
}

// FPSの待機
void FPSWait()
{
	int tookTime = GetNowCount() - mStartTime;
	int waitTime = mCount * 1000 / FPS - tookTime;
	if (waitTime > 0)
	{
		Sleep(waitTime);
	}
}

// キーの入力状態更新
void Keyboard_Update()
{
	char tmpKey[256];             // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey);  // 全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++)
	{
		if (tmpKey[i] != 0)
		{ // i番のキーコードに対応するキーが押されていたら
			m_Key[i]++;   // 加算
		}
		else
		{              // 押されていなければ
			m_Key[i] = 0; // 0にする
		}
	}
	return;
}

// KeyCodeのキーの入力状態を取得する
int Keyboard_Get(int KeyCode)
{
	return m_Key[KeyCode]; // KeyCodeの入力状態を返す
}

// マウスの入力状態更新
void MouseInput_Update()
{
	int tmpCode[256];
	int input_Code = GetMouseInput();
	memset(tmpCode, 0, sizeof(tmpCode));
	tmpCode[input_Code] = (input_Code != 0) ? 1 : 0;

	for (int i = 0; i < 256; i++)
	{
		if (tmpCode[i] != 0)
		{
			m_Code[i]++;
		}
		else
		{
			m_Code[i] = 0;
		}
	}
	return;
}

// マウスの入力状態を取得する
int MouseInput_Get(int InputCode)
{
	return m_Code[InputCode];
}

// 文字列の入力処理
int GetMyName(char name[])
{
	int  stringnum = 0;	// 文字の位置
	char InputChar[2];	// 現在入力している文字とヌル文字

	// ｴﾝﾀｰｷｰで１を返す
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1)
	{
		return 1;
	}
	// ﾊﾞｯｸｽﾍﾟｰｽｷｰで一つ前の文字を削除する
	if (Keyboard_Get(KEY_INPUT_BACK) == 1)
	{
		// char配列からヌル文字を検索する
		while (name[0] != '\0' && name[stringnum] != '\0')
		{
			stringnum++;
		}
		// 一つ前の文字を削除する
		name[stringnum - 1] = '\0';
	}

	// 文字を取得する
	InputChar[0] = GetInputChar(TRUE);
	InputChar[1] = '\0';
	// 文字が入力されていればchar配列に入力した文字を追加する
	if (InputChar[0] != 0 && InputChar[0] >= CTRL_CODE_CMP)
	{
		while (name[0] != '\0' && name[stringnum] != '\0')
		{
			stringnum++;
		}
		name[stringnum] = InputChar[0];
	}

	// 通常の戻り値
	return 0;
}

// メッセージボックスから Yes か No を返す
int MyMessageBoxYN(const char Text[], const char Title[])
{
	if (MessageBox(NULL, TEXT(Text), TEXT(Title), MB_YESNO | MB_ICONQUESTION) != IDNO) { return 1; }
	else { return 0; }
}

// 画像の位置を考慮したサイズを取得する
MYGRAPHINFO GetGraphInfo(int GraphHandle, int x, int y)
{
	MYGRAPHINFO graph;
	GetGraphSize(GraphHandle, &graph.x_right, &graph.y_down);
	graph.x_left = x;
	graph.y_up = y;
	graph.x_right += x;
	graph.y_down += y;
	return graph;
}

// 矩形同士の当たり判定
int Check_Hit_Box_To_Box_2D(MYGRAPHINFO graph1, MYGRAPHINFO graph2)
{
	if (((graph1.x_left > graph2.x_left && graph1.x_left < graph2.x_left + graph2.x_right) ||
		(graph2.x_left > graph1.x_left && graph2.x_left < graph1.x_left + graph1.x_right)) &&
		((graph1.y_up > graph2.y_up && graph1.y_up < graph2.y_up + graph2.y_down) ||
			(graph2.y_up > graph1.y_up && graph2.y_up < graph1.y_up + graph1.y_down)))
	{
		return 1;
	}

	return 0;
}

// 矩形と点との当たり判定
int Check_Hit_Box_To_Point_2D(MYGRAPHINFO graph, int pointX, int pointY)
{
	if (pointY >= graph.y_up && pointY <= graph.y_down &&
		pointX >= graph.x_left && pointX <= graph.x_right)
	{
		return 1;
	}
	return 0;
}

// 2Dベクトルの正規化
void Normalize_2D(float* x, float* y)
{
	float X = *x;
	float Y = *y;
	float C = sqrt(X * X + Y * Y);

	X /= C;
	Y /= C;

	*x = X;
	*y = Y;

	return;
}

// 2点間の距離を取得する
float GetDistance_2D(float x1, float y1, float x2, float y2)
{
	float x = x1 - x2;
	float y = y1 - y2;
	return sqrt(x * x + y * y);
}

// 十字キーでの2D移動ベクトル処理
void MoveProcess(float* x, float* y, float MoveSpeed)
{
	float VecX = 0;
	float VecY = 0;

	if (Keyboard_Get(KEY_INPUT_RIGHT) >= 1 || Keyboard_Get(KEY_INPUT_D) >= 1)
	{
		VecX += 1;
	}
	if (Keyboard_Get(KEY_INPUT_LEFT) >= 1 || Keyboard_Get(KEY_INPUT_A) >= 1)
	{
		VecX -= 1;
	}
	if (Keyboard_Get(KEY_INPUT_DOWN) >= 1 || Keyboard_Get(KEY_INPUT_S) >= 1)
	{
		VecY += 1;
	}
	if (Keyboard_Get(KEY_INPUT_UP) >= 1 || Keyboard_Get(KEY_INPUT_W) >= 1)
	{
		VecY -= 1;
	}
	if ((int)VecX != 0 && (int)VecY != 0)
	{
		Normalize_2D(&VecX, &VecY);
	}
	*x += VecX * MoveSpeed;
	*y += VecY * MoveSpeed;

	return;
}

int DeleteDivGraph(int HandleArray[], int AllNum)
{
	for (int i = 0; i < AllNum; i++)
	{
		DeleteGraph(HandleArray[i]);
	}
	for (int i = 0; i < AllNum; i++)
	{
		if (HandleArray[i] != -1)
		{
			return 0;
		}
	}
	return 1;
}