#include "Title.h"
#include "DxLib.h"
#include "Game.h"
#include "Utility.h"
#include "Define.h"

int Title()
{
	int RETURNVALUE = GS_LEAVE;

	while (Game_MainLoop())
	{
		FPSUpdate();

		if (Keyboard_Get(KEY_INPUT_SPACE) == 1)
		{
			RETURNVALUE = GS_GAME;
			break;
		}

		DrawFormatString(0, 0, GetColor(255, 255, 255), "TITLE MODE");

		FPSWait();
	}

	return RETURNVALUE;
}