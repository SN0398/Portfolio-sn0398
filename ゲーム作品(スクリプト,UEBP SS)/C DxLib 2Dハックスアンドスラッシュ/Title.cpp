#include "Title.h"
#include "DxLib.h"
#include "Game.h"
#include "Utility.h"
#include "Define.h"
#include "ResourceMgr.h"
#include "MapMgr.h"

static const int LoadingTime = 150;
static int count = 0;

int Title(bool* PlayMusic)
{
	TitleMenu menu[2][5] =
	{
		{
			{"Play",200,200,200,50,220,210,false},
			{"Tutorial",200,300,200,50,220,310,false},
			{"Setting",200,400,200,50,220,410,false},
			{"Exit",200,500,200,50,220,510,false},
		},
		{
			{"Music:ON",650,200,200,50,660,210,false},
			{"Music:OFF",650,300,200,50,660,310,false},
			{"FullScreen",650,400,200,50,660,410,false},
			{"WindowMode",650,500,200,50,660,510,false},
			{"Close",650,600,200,50,660,610,false},
		},

	};

	Resource* resource = CreateResource();

	int RETURNVALUE = GAMESCENE_LEAVE;
	int TITLESTATE = TS_LOADING;
	bool IsLoop = true;

	if (*PlayMusic)
	{
		PlaySoundMem(resource->MusicHandle[2], DX_PLAYTYPE_LOOP);
	}

	while (Game_MainLoop() && IsLoop)
	{
		FPSUpdate();

		if (!GetWindowActiveFlag())
		{
			if (TITLESTATE != TS_LOADING)
			{
				StopSoundMem(resource->MusicHandle[1]);
				if (*PlayMusic)
				{
					PlaySoundMem(resource->MusicHandle[2], DX_PLAYTYPE_LOOP);
				}
			}
			TITLESTATE = TS_LOADING;
			count = 0;
		}

		IsLoop = TitleStateFunction[TITLESTATE](menu, resource, &TITLESTATE, &RETURNVALUE, PlayMusic);

		FPSWait();
	}

	StopSoundMem(resource->MusicHandle[1]);

	ReleaseResource(resource);

	return RETURNVALUE;
}

bool TitleLoadingUpdate(TitleMenu menu[][5], Resource* resource, int* TITLESTATE, int* RETURNVALUE, bool* PlayMusic)
{
	// �߂�l
	bool IsLoop = true;

	if (GetWindowActiveFlag())
	{
		if (++count > LoadingTime)
		{
			StopSoundMem(resource->MusicHandle[2]);
			if (*PlayMusic)
			{
				PlaySoundMem(resource->MusicHandle[1], DX_PLAYTYPE_LOOP);
			}
			*TITLESTATE = TS_MAIN;
			count = 0;
			return IsLoop;
		}
	}
	for (int j = 0; j + 1 * MAPCHIPSIZE < SCREEN_HEIGHT; j++)
	{
		for (int i = 0; i + 1 * MAPCHIPSIZE < SCREEN_WIDTH; i++)
		{
			DrawExtendGraph(i * MAPCHIPSIZE, j * MAPCHIPSIZE, i * MAPCHIPSIZE + MAPCHIPSIZE, j * MAPCHIPSIZE + MAPCHIPSIZE, resource->WoodHandle, FALSE);
		}
	}
	StringAnimation((char*)"Now Loading...", 14, 470, 400, 4.0, 0.2, 5, 10, resource->FontHandle[0], resource->SubColorSchemeHandle[2]);
	DrawLine(0 + 100, 435, SCREEN_WIDTH - 100, 435, resource->SubColorSchemeHandle[2]);

	return IsLoop;
}

bool TitleMainUpdate(TitleMenu menu[][5], Resource* resource, int* TITLESTATE, int* RETURNVALUE, bool* PlayMusic)
{
	// �߂�l
	bool IsLoop = true;
	int mouseX, mouseY;

	// �}�E�X�����֌W
	{
		// �}�E�X���W�擾
		GetMousePoint(&mouseX, &mouseY);
		// �X�V
		for (int i = 0; i < MENUNUM; i++)
		{
			// �}�E�X���W�ƃ��j���[�{�b�N�X�̓����蔻��
			if (mouseY >= menu[0][i].BoxY && mouseY <= menu[0][i].BoxY + menu[0][i].Height &&
				mouseX >= menu[0][i].BoxX && mouseX <= menu[0][i].BoxX + menu[0][i].Width)
			{
				// �œ_�t���O�𗧂Ă�
				menu[0][i].IsCursor = true;
			}
			else
			{
				// �œ_�t���O��|��
				menu[0][i].IsCursor = false;
			}
			// �œ_�t���O�������Ă����Ԃō��N���b�N
			if (menu[0][i].IsCursor && MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
			{
				// �t���O�������Ă��郁�j���[�̔ԍ�
				switch (i)
				{
				case 0:	// Play
				{
					StopSoundMem(resource->MusicHandle[1]);
					// �Q�[����ʂɑJ��
					*RETURNVALUE = GAMESCENE_GAME;
					// �Q�[�����[�v����O���
					IsLoop = false;
					break;
				}
				case 1:	// �`���[�g���A��
				{
					*TITLESTATE = TS_TUTORIAL;
					break;
				}
				case 2:	// ���j���[
				{
					*TITLESTATE = TS_MENU;
					break;
				}
				case 3:	// �I��
				{
					*TITLESTATE = TS_EXIT;
					break;
				}
				}
			}
		}
		// �`��

		// ��{�`��
		TitleDrawTemplate(menu, resource);
	}

	return IsLoop;
}

bool TitleTutorialUpdate(TitleMenu menu[][5], Resource* resource, int* TITLESTATE, int* RETURNVALUE, bool* PlayMusic)
{
	// �߂�l
	bool IsLoop = true;

	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	{
		*TITLESTATE = TS_MAIN;
	}

	// ��{�`��
	TitleDrawTemplate(menu, resource);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);		//�u�����h���[�h����(128/255)�ɐݒ�
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, resource->CHandle[6], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t
	DrawExtendGraph(600, 0 + 100, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 50, resource->BoxUIHandle, TRUE);

	DrawFormatStringToHandle(660, 150, resource->SubColorSchemeHandle[0], resource->FontHandle[1], "�T�v");
	DrawFormatStringToHandle(670, 200, resource->SubColorSchemeHandle[0], resource->FontHandle[2], "�G��|���ĕ󔠂���ɓ���悤");
	DrawFormatStringToHandle(660, 400, resource->SubColorSchemeHandle[0], resource->FontHandle[1], "����");
	DrawFormatStringToHandle(680, 450, resource->SubColorSchemeHandle[0], resource->FontHandle[2], "WASD ... �ړ�\n\nEsc ...  �|�[�Y/����\n\nLClick ... ����/����");

	return IsLoop;
}

bool TitleMenuUpdate(TitleMenu menu[][5], Resource* resource, int* TITLESTATE, int* RETURNVALUE, bool* PlayMusic)
{
	// �߂�l
	bool IsLoop = true;
	int mouseX, mouseY;

	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	{
		*TITLESTATE = TS_MAIN;
	}

	// �}�E�X�����֌W
	{
		// �}�E�X���W�擾
		GetMousePoint(&mouseX, &mouseY);
		// �X�V
		for (int i = 0; i < SETTINGMENUNUM; i++)
		{
			// �}�E�X���W�ƃ��j���[�{�b�N�X�̓����蔻��
			if (mouseY >= menu[1][i].BoxY && mouseY <= menu[1][i].BoxY + menu[1][i].Height &&
				mouseX >= menu[1][i].BoxX && mouseX <= menu[1][i].BoxX + menu[1][i].Width)
			{
				// �œ_�t���O�𗧂Ă�
				menu[1][i].IsCursor = true;
			}
			else
			{
				// �œ_�t���O��|��
				menu[1][i].IsCursor = false;
			}
			// �œ_�t���O�������Ă����Ԃō��N���b�N
			if (menu[1][i].IsCursor && MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
			{
				// �t���O�������Ă��郁�j���[�̔ԍ�
				switch (i)
				{
				case 0:	// MusicOn
				{
					*PlayMusic = true;
					PlaySoundMem(resource->MusicHandle[1], DX_PLAYTYPE_LOOP, FALSE);
					break;
				}
				case 1:	// MusicOff
				{
					*PlayMusic = false;
					StopSoundMem(resource->MusicHandle[1]);
					break;
				}
				case 2:	// FullScreen
				{
					// �E�B���h�E���[�h�̕ύX
					ChangeWindowMode(FALSE);
					// �_�u���o�b�t�@���[�h
					SetDrawScreen(DX_SCREEN_BACK);
					// �J��
					*RETURNVALUE = GAMESCENE_TITLE;
					// �Q�[�����[�v����O���
					IsLoop = false;
					break;

				}
				case 3:	// Windowmode
				{
					// �E�B���h�E���[�h�̕ύX
					ChangeWindowMode(TRUE);
					// �_�u���o�b�t�@���[�h
					SetDrawScreen(DX_SCREEN_BACK);
					// �J��
					*RETURNVALUE = GAMESCENE_TITLE;
					// �Q�[�����[�v����O���
					IsLoop = false;
					break;
				}
				case 4:	// Close
				{
					*TITLESTATE = TS_MAIN;
				}
				}
			}
		}
	}
	// �`��

	// ��{�`��
	TitleDrawTemplate(menu, resource);
	// ���w�i�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);		//�u�����h���[�h����(128/255)�ɐݒ�
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, resource->CHandle[6], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t
	// ���j���[�{�b�N�X�`��
	DrawExtendGraph(600, 0 + 100, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 50, resource->BoxUIHandle, TRUE);
	// ���j���[�o�[�`��
	for (int i = 0; i < SETTINGMENUNUM; i++)
	{
		DrawExtendGraph(menu[1][i].BoxX, menu[1][i].BoxY, menu[1][i].BoxX + menu[1][i].Width, menu[1][i].BoxY + menu[1][i].Height, resource->MenuUIHandle, TRUE);
		if (menu[1][i].IsCursor)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);		//�u�����h���[�h����(128/255)�ɐݒ�
			DrawBox(menu[1][i].BoxX, menu[1][i].BoxY, menu[1][i].BoxX + menu[1][i].Width, menu[1][i].BoxY + menu[1][i].Height, resource->CHandle[6], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t
		}
		DrawFormatStringToHandle(menu[1][i].stringX, menu[1][i].stringY, resource->SubColorSchemeHandle[(!menu[1][i].IsCursor) ? 2 : 1], resource->FontHandle[1], "%s", menu[1][i].ID);
	}

	return IsLoop;
}

bool TitleExitUpdate(TitleMenu menu[][5], Resource* resource, int* TITLESTATE, int* RETURNVALUE, bool* PlayMusic)
{
	// �߂�l
	bool IsLoop = true;

	if (MyMessageBoxYN("�I�����܂����H", "�I���m�F") == 1)
	{
		IsLoop = false;
	}
	else
	{
		*TITLESTATE = TS_MAIN;
	}

	// �`��

	TitleDrawTemplate(menu, resource);	// ��{�`��

	return IsLoop;
}
void TitleDrawTemplate(TitleMenu menu[][5], Resource* resource)
{
	for (int j = 0; j + 1 * MAPCHIPSIZE < SCREEN_HEIGHT; j++)
	{
		for (int i = 0; i + 1 * MAPCHIPSIZE < SCREEN_WIDTH; i++)
		{
			DrawExtendGraph(i * MAPCHIPSIZE, j * MAPCHIPSIZE, i * MAPCHIPSIZE + MAPCHIPSIZE, j * MAPCHIPSIZE + MAPCHIPSIZE, resource->WallHandle, FALSE);
		}
	}
	for (int i = 0; i < MENUNUM; i++)
	{
		DrawExtendGraph(menu[0][i].BoxX, menu[0][i].BoxY, menu[0][i].BoxX + menu[0][i].Width, menu[0][i].BoxY + menu[0][i].Height, resource->MenuUIHandle, TRUE);
		if (menu[0][i].IsCursor)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);		//�u�����h���[�h����(128/255)�ɐݒ�
			DrawBox(menu[0][i].BoxX, menu[0][i].BoxY, menu[0][i].BoxX + menu[0][i].Width, menu[0][i].BoxY + menu[0][i].Height, resource->CHandle[6], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t
		}
		DrawFormatStringToHandle(menu[0][i].stringX, menu[0][i].stringY, resource->SubColorSchemeHandle[(!menu[0][i].IsCursor) ? 2 : 1], resource->FontHandle[0], "%s", menu[0][i].ID);
	}

	return;
}

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

static char* pstring;	// �O�̕�����̃|�C���^
static const int maxstringnum = 32;	// �ő啶����
static StringData str[maxstringnum];	// �\���̎���
static float JumpPower;	// ���˕Ԃ�̗�
static float Gravity;	// �d��
static int GroundY;	// �n�ʂ�Y���W

void StringAnimation
(
	char string[],
	const int stringnum,
	int x,
	int y,
	float StringJumpPower,
	float StringGravity,
	int StartInterval,
	int width,
	int Font,
	int Color
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
		pstring = string;
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
				str[i].moveY = -StringJumpPower;
			}
			str[i].moveY += Gravity;
			str[i].y += str[i].moveY;
		}
		DrawStringToHandle(str[i].x, str[i].y, str[i].string, Color, Font);
	}

	return;
}
