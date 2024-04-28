#pragma once

#include "ResourceMgr.h"

// �萔��` ---------------------------------------------------------------------------------------

#define MAPCHIPSIZE		64
#define CHIPTYPE		9
#define MAPCHIPWIDTH	64
#define MAPCHIPHEIGHT	64

// �\���̒�` -------------------------------------------------------------------------------------

typedef struct _Map
{
	int stage[MAPCHIPHEIGHT][MAPCHIPWIDTH];

}Map;

// �֐��v���g�^�C�v�錾 ---------------------------------------------------------------------------

Map* CreateMap();
void DrawMap(Map* map, Resource* resource, int PlayerX, int PlayerY);
void ReleaseMap(Map* map);