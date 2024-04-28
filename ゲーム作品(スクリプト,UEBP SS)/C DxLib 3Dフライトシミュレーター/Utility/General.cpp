#include "../Utility.h"

// 終了リクエスト
int LeaveProcess(int LeaveKey)
{
	// 終了リクエストが送られたらfalseを返す
	if (GetWindowUserCloseFlag(TRUE))
	{
		return 1;
	}
	// キーが押されたら終了する
	if (Keyboard_Get(LeaveKey) == 1)
	{
		if (MyMessageBoxYN("終了しますか？", "終了確認") == 1)
		{
			return 1;
		}
	}
	return 0;
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