#include "../MyLib.h"

static int m_Code[256];	// マウスの入力状態格納用変数

// マウスの入力状態更新
void MouseInput_Update()
{
	int tmpCode[256];	// このフレームの入力状態保存用変数
	int input_Code = GetMouseInput();	// 入力状態を得る
	memset(tmpCode, 0, sizeof(tmpCode));	// 
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

	int MCode = GetMouseInput();	// 入力状態を得る

	return;
}

// マウスの入力状態を取得する
int MouseInput_Get(int InputCode)
{
	return m_Code[InputCode];
}