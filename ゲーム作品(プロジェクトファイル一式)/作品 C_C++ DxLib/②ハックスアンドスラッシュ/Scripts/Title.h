#pragma once

#include "ResourceMgr.h"

// 定数定義 ---------------------------------------------------------------------------------------

#define MENUNUM	4
#define SETTINGMENUNUM	5

// 構造体定義 -------------------------------------------------------------------------------------

typedef struct _TitleMenu
{
	char ID[32];
	int BoxX, BoxY, Width, Height, stringX, stringY;
	bool IsCursor;

}TitleMenu;

typedef enum _TitleState
{
	TS_LOADING = 0,
	TS_MAIN,
	TS_TUTORIAL,
	TS_MENU,
	TS_EXIT,

}TitleState;

// 関数プロトタイプ宣言 ---------------------------------------------------------------------------

int Title(bool* PlayMusic);

bool TitleLoadingUpdate(TitleMenu menu[][5], Resource* resource, int* TITLESTATE, int* RETURNVALUE, bool* PlayMusic);
bool TitleMainUpdate(TitleMenu menu[][5], Resource* resourc, int* TITLESTATE, int* RETURNVALUE, bool* PlayMusic);
bool TitleTutorialUpdate(TitleMenu menu[][5], Resource* resource, int* TITLESTATE, int* RETURNVALUE, bool* PlayMusic);
bool TitleMenuUpdate(TitleMenu menu[][5], Resource* resource, int* TITLESTATE, int* RETURNVALUE, bool* PlayMusic);
bool TitleExitUpdate(TitleMenu menu[][5], Resource* resource, int* TITLESTATE, int* RETURNVALUE, bool* PlayMusic);
void TitleDrawTemplate(TitleMenu menu[][5], Resource* resource);

static bool (*TitleStateFunction[])(TitleMenu menu[][5], Resource* resource, int* TITLESTATE, int* RETURNVALUE, bool* PlayMusic) =
{
	TitleLoadingUpdate,
	TitleMainUpdate,
	TitleTutorialUpdate,
	TitleMenuUpdate,
	TitleExitUpdate
};

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
);