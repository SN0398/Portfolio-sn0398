#include "../MyLib.h"

#pragma warning(disable:4996)

#define MAXSTRINGNUM	32	// �ő啶����

// �\���̒�`
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

static char* pstring;	// �O�̕�����̃|�C���^
static StringData str[MAXSTRINGNUM];	// �\���̎���
static float JumpPower;	// ���˕Ԃ�̗�
static float Gravity;	// �d��
static int GroundY;	// �n�ʂ�Y���W

static int WindowState = WINDOW_STYLE_DEFAULT;

// �Q�[���̃��C�����[�v
int Game_MainLoop(int LeaveKey)
{
	Keyboard_Update();					// �L�[�{�[�h���͏�Ԃ̍X�V
	MouseInput_Update();				// �}�E�X���͏�Ԃ̍X�V
	PadInput_Update();					// �p�b�h���͏�Ԃ̍X�V
	return (
		ScreenFlip() == 0 &&			// ����ʕ`��
		ClearDrawScreen() == 0 &&		// ��ʂ�����
		ProcessMessage() == 0 &&		// ����޳ү���ނ̏���
		LeaveProcess(LeaveKey) == 0);	// �I���l�̎󂯎��
}

// �I�����N�G�X�g
int LeaveProcess(int LeaveKey)
{
	// �E��́~�{�^���������ꂽ��1��Ԃ�
	if (GetWindowUserCloseFlag(TRUE))
	{
		return 1;
	}
	// �I���L�[�������ꂽ��I������
	if (Keyboard_Get(LeaveKey) == 1)
	{
		if (MyMessageBoxYN("�I�����܂����H", "�I���m�F") == 1)
		{
			return 1;
		}
	}
	return 0;
}

// �E�B���h�E�ݒ�̃Z�b�g
void SetWindowProperty(int WindowStyle)
{
	HWND windowHandle = GetMainWindowHandle();
	int taskBarHeight = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYSIZEFRAME);

	switch (WindowStyle)
	{
	case 0:
	{
		// �E�B���h�E���[�h�̕ύX
		ChangeWindowMode(TRUE);
		// �E�B���h�E�̌����ڂ�ύX����
		SetWindowStyleMode(0);
		// ��ʂ̃T�C�Y��ύX�ł���悤�ɂ��邩�ǂ���
		SetWindowSizeChangeEnableFlag(TRUE);

		SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

		int currentWindowStyle = GetWindowLong(windowHandle, GWL_STYLE);
		SetWindowLong(windowHandle, GWL_STYLE, currentWindowStyle | WS_MAXIMIZEBOX);

		break;
	}
	case 1:
	{
		// �E�B���h�E���[�h�̕ύX
		ChangeWindowMode(TRUE);
		// �E�B���h�E�̌����ڂ�ύX����
		SetWindowStyleMode(2);
		// ��ʂ̃T�C�Y��ύX�ł���悤�ɂ��邩�ǂ���
		SetWindowSizeChangeEnableFlag(FALSE);

		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		SetWindowSize(screenWidth, screenHeight);

		break;
	}
	}

	return;
}

// ������̓��͏���
int GetMyName(char name[])
{
	int  stringnum = 0;	// �����̈ʒu
	char InputChar[2];	// ���ݓ��͂��Ă��镶���ƃk������

	// �������łP��Ԃ�
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1)
	{
		return 1;
	}
	// �ޯ���߰����ň�O�̕������폜����
	if (Keyboard_Get(KEY_INPUT_BACK) == 1)
	{
		// char�z�񂩂�k����������������
		while (name[0] != '\0' && name[stringnum] != '\0')
		{
			stringnum++;
		}
		// ��O�̕������폜����
		name[stringnum - 1] = '\0';
	}

	// �������擾����
	InputChar[0] = GetInputChar(TRUE);
	InputChar[1] = '\0';
	// ���������͂���Ă����char�z��ɓ��͂���������ǉ�����
	if (InputChar[0] != 0 && InputChar[0] >= CTRL_CODE_CMP)
	{
		while (name[0] != '\0' && name[stringnum] != '\0')
		{
			stringnum++;
		}
		name[stringnum] = InputChar[0];
	}

	// �ʏ�̖߂�l
	return 0;
}

// ���b�Z�[�W�{�b�N�X���� Yes �� No ��Ԃ�
int MyMessageBoxYN(const char Text[], const char Title[])
{
	if (MessageBox(NULL, TEXT(Text), TEXT(Title), MB_YESNO | MB_ICONQUESTION) != IDNO) { return 1; }
	else { return 0; }
}

// �����̼ެ��߱�Ұ���
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
	// ����Ăяo��
	if (pstring != string)
	{
		JumpPower = StringJumpPower;	// ���˕Ԃ�̗�
		Gravity = StringGravity;	// �d��
		GroundY = y;	// �n�ʂ�Y���W
		// �k���������ő啶�����ɂȂ�܂ŉ�
		for (int i = 0; string[i] != '\0' && i < stringnum; i++)
		{
			// �������R�s�[
			str[i].string[0] = string[i];
			// �����̕�
			str[i].Width = GetDrawStringWidthToHandle(str[i].string, GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, str[i].string), Font);
			if (i != 0)	// X���W
			{
				// �ЂƂO�̕����� X + �����̕�
				str[i].x = str[i - 1].x + str[i - 1].Width + width;
			}
			else
			{
				str[i].x = x;
			}
			str[i].y = y;	// Y���W
			str[i].moveY = 0;	// �ړ��x�N�g��
			str[i].startpoint = i * StartInterval;	// �J�n�ʒu
		}
		pstring = (char*)string;
	}
	//clsDx();
	for (int i = 0; i < stringnum && str[i].string[0] != '\0'; i++)
	{
		// �J�n�ʒu�ɂȂ�܂Ńf�N�������g
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

// ���Ԏ擾
int GetNowTime()
{
	// ���Ԃ��擾
	return GetNowCount();
}

// ���Ԍo�ߎ擾
bool GetTimer(int _SetTime, int _Timer)
{
	if (_SetTime == NULL) { return false; }

	if (GetNowCount() - _SetTime > _Timer)
	{
		return true;
	}

	return false;
}

// �����摜�n���h���̍폜
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

// �o�C�i���t�@�C���ɏ�������
bool SaveData(void* _buffer, size_t _ElementSize, const char* _FileName)
{
	// �t�@�C���̃��[�h
	FILE* fp = fopen(_FileName, "wb");
	// �J���Ȃ�������G���[��Ԃ�
	if (fp == NULL) { return false; }
	// �\���̂��珑������
	fwrite(_buffer, _ElementSize, 1, fp);
	// �t�@�C�������
	fclose(fp);

	return true;
}

// �o�C�i���t�@�C������f�[�^�̎󂯎��
bool LoadData(void* _buffer, size_t _ElementSize, const char* _FileName)
{
	// �t�@�C���̃��[�h
	FILE* fp = fopen(_FileName, "rb");
	// �J���Ȃ�������G���[��Ԃ�
	if (fp == NULL) { return false; }
	// �o�C�i���t�@�C������ǂݍ���
	fread(_buffer, _ElementSize, 1, fp);
	// �t�@�C�������
	fclose(fp);

	return true;
}