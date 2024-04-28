#include "DxLib.h"
#include <math.h>
#include "Utility.h"
#include "Define.h"

static int mStartTime;
static int mCount;
static float mFps;
static const int N = 60;
static const int FPS = 60;

static int m_Key[256];  // �L�[�̓��͏�Ԋi�[�p�ϐ�
static int m_Code[256];	// �}�E�X�̓��͏�Ԋi�[�p�ϐ�

// �Q�[���̏���������
int Game_Init()
{
	// �E�B���h�E���[�h�̕ύX
	ChangeWindowMode(TRUE);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	// �E�B���h�E�̌����ڂ�ύX����
	SetWindowStyleMode(0);
	// �o�b�N�O���E���h�����̕ύX
	SetAlwaysRunFlag(TRUE);
	// �E�B���h�E�̃^�C�g����ݒ肷��
	SetMainWindowText("DxLib");
	// ��ʂ̃T�C�Y��ύX�ł���悤�ɂ��邩�ǂ���
	SetWindowSizeChangeEnableFlag(TRUE);
	// �E�B���h�E�̉𑜓x���ێ������܂܃T�C�Y��ύX����
	SetWindowSizeExtendRate(1.0);
	// �E�B���h�E�̃A�C�R����ύX
	SetWindowIconID(2284930);
	// Log.txt���o�͂��邩��ύX
	SetOutApplicationLogValidFlag(FALSE);
	// �ő剻�{�^����K�p
	//SetUseASyncChangeWindowModeFunction(TRUE, NULL, NULL);
	// ���[�U�[������{�^���������Ă������I�����Ȃ��悤�ɂ���
	SetWindowUserCloseEnableFlag(FALSE);
	// DX���C�u����������
	if (DxLib_Init() == -1)
	{
		//�������Ɏ��s
		return -1;
	}
	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	return 0;
}

// �Q�[���̃��C�����[�v
int Game_MainLoop()
{
	Keyboard_Update();
	MouseInput_Update();
	return (ScreenFlip() == 0 && ClearDrawScreen() == 0 && ProcessMessage() == 0 && LeaveProcess() == 0);
}

// �Q�[���̏I������
int Game_End()
{
	DxLib_End();

	return 0;
}

// �I�����N�G�X�g
int LeaveProcess()
{
	// �I�����N�G�X�g������ꂽ��false��Ԃ�
	if (GetWindowUserCloseFlag(TRUE))
	{
		return 1;
	}
	return 0;
}

// �E�B���h�E�X�^�C���̕ύX
int ChangeWindowStyleMode(int style)
{
	int ChangedFlag = 0;

	switch (style)
	{
	case WINDOW_STYLE_DEFAULT:
	{
		// �E�B���h�E�̌����ڂ�ύX����
		SetWindowStyleMode(0);
		// �E�B���h�E�̑傫����ύX����
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

// FPS�̍X�V
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

// FPS�̕`��
void DrawFPSRate(int x, int y, unsigned int _font_color)
{
	DrawFormatString(x, y, _font_color, "%.1f", mFps);
}

// FPS�̑ҋ@
void FPSWait()
{
	int tookTime = GetNowCount() - mStartTime;
	int waitTime = mCount * 1000 / FPS - tookTime;
	if (waitTime > 0)
	{
		Sleep(waitTime);
	}
}

// �L�[�̓��͏�ԍX�V
void Keyboard_Update()
{
	char tmpKey[256];             // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey);  // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++)
	{
		if (tmpKey[i] != 0)
		{ // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			m_Key[i]++;   // ���Z
		}
		else
		{              // ������Ă��Ȃ����
			m_Key[i] = 0; // 0�ɂ���
		}
	}
	return;
}

// KeyCode�̃L�[�̓��͏�Ԃ��擾����
int Keyboard_Get(int KeyCode)
{
	return m_Key[KeyCode]; // KeyCode�̓��͏�Ԃ�Ԃ�
}

// �}�E�X�̓��͏�ԍX�V
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

// �}�E�X�̓��͏�Ԃ��擾����
int MouseInput_Get(int InputCode)
{
	return m_Code[InputCode];
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

// �摜�̈ʒu���l�������T�C�Y���擾����
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

// ��`���m�̓����蔻��
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

// ��`�Ɠ_�Ƃ̓����蔻��
int Check_Hit_Box_To_Point_2D(MYGRAPHINFO graph, int pointX, int pointY)
{
	if (pointY >= graph.y_up && pointY <= graph.y_down &&
		pointX >= graph.x_left && pointX <= graph.x_right)
	{
		return 1;
	}
	return 0;
}

// 2D�x�N�g���̐��K��
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

// 2�_�Ԃ̋������擾����
float GetDistance_2D(float x1, float y1, float x2, float y2)
{
	float x = x1 - x2;
	float y = y1 - y2;
	return sqrt(x * x + y * y);
}

// �\���L�[�ł�2D�ړ��x�N�g������
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