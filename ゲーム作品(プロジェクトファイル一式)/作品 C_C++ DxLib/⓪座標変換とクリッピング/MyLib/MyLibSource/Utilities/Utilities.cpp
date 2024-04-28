#include "Utilities.h"
#include "MyLibSource/Input/Keyboard/Keyboard.h"
#include "DxLib.h"

#pragma warning(disable:4996)

#define MAXSTRINGNUM	32	// �ő啶����

using namespace MyLib;

// ���b�Z�[�W�{�b�N�X���� Yes �� No ��Ԃ�
int MyLib::MyMessageBoxYN(const char Text[], const char Title[])
{
	if (MessageBox(NULL, TEXT(Text), TEXT(Title), MB_YESNO | MB_ICONQUESTION) != IDNO) { return 1; }
	else { return 0; }
}

// �����摜�n���h���̍폜
int MyLib::DeleteDivGraph(int HandleArray[], int AllNum)
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

std::string MyLib::FormatNumber(int num)
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

int MyLib::GetStringCenter(std::string str, int font, int leftX, int rightX)
{
	// �����l�擾
	int center = (leftX + rightX) / 2;
	// �����̕�
	int width = GetDrawStringWidthToHandle(str.c_str(),
		strlen(str.c_str()), font);
	// �ԋp
	return center - width / 2;
}