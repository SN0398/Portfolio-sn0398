#pragma once

#include "ResourceMgr.h"

// 定数定義 ---------------------------------------------------------------------------------------

#define MAPCHIPSIZE		64
#define CHIPTYPE		9
#define MAPCHIPWIDTH	64
#define MAPCHIPHEIGHT	64

// 構造体定義 -------------------------------------------------------------------------------------

typedef struct _Map
{
	int stage[MAPCHIPHEIGHT][MAPCHIPWIDTH];

}Map;

// 関数プロトタイプ宣言 ---------------------------------------------------------------------------

Map* CreateMap();
void DrawMap(Map* map, Resource* resource, int PlayerX, int PlayerY);
void ReleaseMap(Map* map);