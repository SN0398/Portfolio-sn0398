#include "../MyLib.h"

#pragma warning(disable:4996)

#define MAXSTRINGNUM	32	// 最大文字数

// 構造体定義
static struct StringData
{
	char string[2];
	int x;
	float y;
	float moveY;
	int startpoint;
	int Width;
};

static int SetTime = -1;

static char* pstring;	// 前の文字列のポインタ
static StringData str[MAXSTRINGNUM];	// 構造体実体
static float JumpPower;	// 跳ね返りの力
static float Gravity;	// 重力
static int GroundY;	// 地面のY座標

static int WindowState = WINDOW_STYLE_DEFAULT;

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
	// 右上の×ボタンが押されたら1を返す
	if (GetWindowUserCloseFlag(TRUE))
	{
		return 1;
	}
	// 終了キーが押されたら終了する
	if (Keyboard_Get(LeaveKey) == 1)
	{
		if (MyMessageBoxYN("終了しますか？", "終了確認") == 1)
		{
			return 1;
		}
	}
	return 0;
}

// ウィンドウ設定のセット
void SetWindowProperty(int WindowStyle)
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

		SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

		int currentWindowStyle = GetWindowLong(windowHandle, GWL_STYLE);
		SetWindowLong(windowHandle, GWL_STYLE, currentWindowStyle | WS_MAXIMIZEBOX);

		break;
	}
	case 1:
	{
		// ウィンドウモードの変更
		ChangeWindowMode(TRUE);
		// ウィンドウの見た目を変更する
		SetWindowStyleMode(2);
		// 画面のサイズを変更できるようにするかどうか
		SetWindowSizeChangeEnableFlag(FALSE);

		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		SetWindowSize(screenWidth, screenHeight);

		break;
	}
	}

	return;
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

// 文字のｼﾞｬﾝﾌﾟｱﾆﾒｰｼｮﾝ
void StringAnimation
(
	const char string[],
	const int stringnum,
	int x,
	int y,
	int Font,
	int Color,
	float StringJumpPower,
	float StringGravity,
	int StartInterval,
	int width
)
{
	// 初回呼び出し
	if (pstring != string)
	{
		JumpPower = StringJumpPower;	// 跳ね返りの力
		Gravity = StringGravity;	// 重力
		GroundY = y;	// 地面のY座標
		// ヌル文字か最大文字数になるまで回す
		for (int i = 0; string[i] != '\0' && i < stringnum; i++)
		{
			// 文字をコピー
			str[i].string[0] = string[i];
			// 文字の幅
			str[i].Width = GetDrawStringWidthToHandle(str[i].string, GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, str[i].string), Font);
			if (i != 0)	// X座標
			{
				// ひとつ前の文字の X + 文字の幅
				str[i].x = str[i - 1].x + str[i - 1].Width + width;
			}
			else
			{
				str[i].x = x;
			}
			str[i].y = y;	// Y座標
			str[i].moveY = 0;	// 移動ベクトル
			str[i].startpoint = i * StartInterval;	// 開始位置
		}
		pstring = (char*)string;
	}
	//clsDx();
	for (int i = 0; i < stringnum && str[i].string[0] != '\0'; i++)
	{
		// 開始位置になるまでデクリメント
		if (str[i].startpoint != 0)
		{
			str[i].startpoint--;
		}
		else
		{
			if (str[i].y + str[i].moveY >= GroundY)
			{
				str[i].moveY = -JumpPower;
			}
			str[i].moveY += Gravity;
			str[i].y += str[i].moveY;
		}
		if (Font != NULL)
		{
			DrawStringToHandle(str[i].x, str[i].y, str[i].string, Color, Font);
		}
		else
		{
			DrawString(str[i].x, str[i].y, str[i].string, Color);
		}
	}

	return;
}

// 時間取得
int GetNowTime()
{
	// 時間を取得
	return GetNowCount();
}

// 時間経過取得
bool GetTimer(int _SetTime, int _Timer)
{
	if (_SetTime == NULL) { return false; }

	if (GetNowCount() - _SetTime > _Timer)
	{
		return true;
	}

	return false;
}

// 分割画像ハンドルの削除
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

std::string FormatNumber(int num) 
{
	const char* units[] = { "", "K", "M", "B", "T" };
	int unit = 0;
	int value = num;

	while (value >= 1000)
	{
		value /= 1000;
		unit++;
	}

	std::string result = std::to_string(value) + units[unit];
	return result;
}

// バイナリファイルに書き込み
bool SaveData(void* _buffer, size_t _ElementSize, const char* _FileName)
{
	// ファイルのロード
	FILE* fp = fopen(_FileName, "wb");
	// 開けなかったらエラーを返す
	if (fp == NULL) { return false; }
	// 構造体から書き込み
	fwrite(_buffer, _ElementSize, 1, fp);
	// ファイルを閉じる
	fclose(fp);

	return true;
}

// バイナリファイルからデータの受け取り
bool LoadData(void* _buffer, size_t _ElementSize, const char* _FileName)
{
	// ファイルのロード
	FILE* fp = fopen(_FileName, "rb");
	// 開けなかったらエラーを返す
	if (fp == NULL) { return false; }
	// バイナリファイルから読み込み
	fread(_buffer, _ElementSize, 1, fp);
	// ファイルを閉じる
	fclose(fp);

	return true;
}