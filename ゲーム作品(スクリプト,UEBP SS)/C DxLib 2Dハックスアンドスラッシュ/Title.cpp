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
	// 戻り値
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
	// 戻り値
	bool IsLoop = true;
	int mouseX, mouseY;

	// マウス処理関係
	{
		// マウス座標取得
		GetMousePoint(&mouseX, &mouseY);
		// 更新
		for (int i = 0; i < MENUNUM; i++)
		{
			// マウス座標とメニューボックスの当たり判定
			if (mouseY >= menu[0][i].BoxY && mouseY <= menu[0][i].BoxY + menu[0][i].Height &&
				mouseX >= menu[0][i].BoxX && mouseX <= menu[0][i].BoxX + menu[0][i].Width)
			{
				// 焦点フラグを立てる
				menu[0][i].IsCursor = true;
			}
			else
			{
				// 焦点フラグを倒す
				menu[0][i].IsCursor = false;
			}
			// 焦点フラグが立っている状態で左クリック
			if (menu[0][i].IsCursor && MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
			{
				// フラグが立っているメニューの番号
				switch (i)
				{
				case 0:	// Play
				{
					StopSoundMem(resource->MusicHandle[1]);
					// ゲーム画面に遷移
					*RETURNVALUE = GAMESCENE_GAME;
					// ゲームループから外れる
					IsLoop = false;
					break;
				}
				case 1:	// チュートリアル
				{
					*TITLESTATE = TS_TUTORIAL;
					break;
				}
				case 2:	// メニュー
				{
					*TITLESTATE = TS_MENU;
					break;
				}
				case 3:	// 終了
				{
					*TITLESTATE = TS_EXIT;
					break;
				}
				}
			}
		}
		// 描画

		// 基本描画
		TitleDrawTemplate(menu, resource);
	}

	return IsLoop;
}

bool TitleTutorialUpdate(TitleMenu menu[][5], Resource* resource, int* TITLESTATE, int* RETURNVALUE, bool* PlayMusic)
{
	// 戻り値
	bool IsLoop = true;

	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	{
		*TITLESTATE = TS_MAIN;
	}

	// 基本描画
	TitleDrawTemplate(menu, resource);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);		//ブレンドモードをα(128/255)に設定
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, resource->CHandle[6], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
	DrawExtendGraph(600, 0 + 100, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 50, resource->BoxUIHandle, TRUE);

	DrawFormatStringToHandle(660, 150, resource->SubColorSchemeHandle[0], resource->FontHandle[1], "概要");
	DrawFormatStringToHandle(670, 200, resource->SubColorSchemeHandle[0], resource->FontHandle[2], "敵を倒して宝箱を手に入れよう");
	DrawFormatStringToHandle(660, 400, resource->SubColorSchemeHandle[0], resource->FontHandle[1], "操作");
	DrawFormatStringToHandle(680, 450, resource->SubColorSchemeHandle[0], resource->FontHandle[2], "WASD ... 移動\n\nEsc ...  ポーズ/閉じる\n\nLClick ... 発射/決定");

	return IsLoop;
}

bool TitleMenuUpdate(TitleMenu menu[][5], Resource* resource, int* TITLESTATE, int* RETURNVALUE, bool* PlayMusic)
{
	// 戻り値
	bool IsLoop = true;
	int mouseX, mouseY;

	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	{
		*TITLESTATE = TS_MAIN;
	}

	// マウス処理関係
	{
		// マウス座標取得
		GetMousePoint(&mouseX, &mouseY);
		// 更新
		for (int i = 0; i < SETTINGMENUNUM; i++)
		{
			// マウス座標とメニューボックスの当たり判定
			if (mouseY >= menu[1][i].BoxY && mouseY <= menu[1][i].BoxY + menu[1][i].Height &&
				mouseX >= menu[1][i].BoxX && mouseX <= menu[1][i].BoxX + menu[1][i].Width)
			{
				// 焦点フラグを立てる
				menu[1][i].IsCursor = true;
			}
			else
			{
				// 焦点フラグを倒す
				menu[1][i].IsCursor = false;
			}
			// 焦点フラグが立っている状態で左クリック
			if (menu[1][i].IsCursor && MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
			{
				// フラグが立っているメニューの番号
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
					// ウィンドウモードの変更
					ChangeWindowMode(FALSE);
					// ダブルバッファモード
					SetDrawScreen(DX_SCREEN_BACK);
					// 遷移
					*RETURNVALUE = GAMESCENE_TITLE;
					// ゲームループから外れる
					IsLoop = false;
					break;

				}
				case 3:	// Windowmode
				{
					// ウィンドウモードの変更
					ChangeWindowMode(TRUE);
					// ダブルバッファモード
					SetDrawScreen(DX_SCREEN_BACK);
					// 遷移
					*RETURNVALUE = GAMESCENE_TITLE;
					// ゲームループから外れる
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
	// 描画

	// 基本描画
	TitleDrawTemplate(menu, resource);
	// 黒背景描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);		//ブレンドモードをα(128/255)に設定
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, resource->CHandle[6], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
	// メニューボックス描画
	DrawExtendGraph(600, 0 + 100, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 50, resource->BoxUIHandle, TRUE);
	// メニューバー描画
	for (int i = 0; i < SETTINGMENUNUM; i++)
	{
		DrawExtendGraph(menu[1][i].BoxX, menu[1][i].BoxY, menu[1][i].BoxX + menu[1][i].Width, menu[1][i].BoxY + menu[1][i].Height, resource->MenuUIHandle, TRUE);
		if (menu[1][i].IsCursor)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);		//ブレンドモードをα(128/255)に設定
			DrawBox(menu[1][i].BoxX, menu[1][i].BoxY, menu[1][i].BoxX + menu[1][i].Width, menu[1][i].BoxY + menu[1][i].Height, resource->CHandle[6], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
		}
		DrawFormatStringToHandle(menu[1][i].stringX, menu[1][i].stringY, resource->SubColorSchemeHandle[(!menu[1][i].IsCursor) ? 2 : 1], resource->FontHandle[1], "%s", menu[1][i].ID);
	}

	return IsLoop;
}

bool TitleExitUpdate(TitleMenu menu[][5], Resource* resource, int* TITLESTATE, int* RETURNVALUE, bool* PlayMusic)
{
	// 戻り値
	bool IsLoop = true;

	if (MyMessageBoxYN("終了しますか？", "終了確認") == 1)
	{
		IsLoop = false;
	}
	else
	{
		*TITLESTATE = TS_MAIN;
	}

	// 描画

	TitleDrawTemplate(menu, resource);	// 基本描画

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
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);		//ブレンドモードをα(128/255)に設定
			DrawBox(menu[0][i].BoxX, menu[0][i].BoxY, menu[0][i].BoxX + menu[0][i].Width, menu[0][i].BoxY + menu[0][i].Height, resource->CHandle[6], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
		}
		DrawFormatStringToHandle(menu[0][i].stringX, menu[0][i].stringY, resource->SubColorSchemeHandle[(!menu[0][i].IsCursor) ? 2 : 1], resource->FontHandle[0], "%s", menu[0][i].ID);
	}

	return;
}

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

static char* pstring;	// 前の文字列のポインタ
static const int maxstringnum = 32;	// 最大文字数
static StringData str[maxstringnum];	// 構造体実体
static float JumpPower;	// 跳ね返りの力
static float Gravity;	// 重力
static int GroundY;	// 地面のY座標

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
		pstring = string;
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
				str[i].moveY = -StringJumpPower;
			}
			str[i].moveY += Gravity;
			str[i].y += str[i].moveY;
		}
		DrawStringToHandle(str[i].x, str[i].y, str[i].string, Color, Font);
	}

	return;
}
