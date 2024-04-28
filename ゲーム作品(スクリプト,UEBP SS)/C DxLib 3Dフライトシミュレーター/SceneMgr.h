#pragma once
#include "Define.h"
#include "Title.h"
#include "Game.h"

int (*SceneManager[GS_LEAVE])() =
{
	Title,
	Game,
};