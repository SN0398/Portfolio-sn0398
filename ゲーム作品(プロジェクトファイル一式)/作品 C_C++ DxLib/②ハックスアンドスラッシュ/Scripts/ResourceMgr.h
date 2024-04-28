#pragma once

// �\���̒�` -------------------------------------------------------------------------------------

typedef struct _Resource
{
	int DxLogoHandle;
	int CHandle[10];
	int ColorSchemeHandle[5];
	int SubColorSchemeHandle[5];
	int FHandle[5];
	int DungeonChipHandle;
	int WallHandle;
	int BrickHandle;
	int WoodHandle;
	int TreasureBoxHandle;
	int TutorialHandle;
	int MenuUIHandle;
	int BoxUIHandle;
	int BulletHandle;
	int EnemyHandle;
	int PlayerHandle;
	int FontHandle[3];
	int MusicHandle[3];
	int ExplosionHandle[7];

}Resource;

// �֐��v���g�^�C�v�錾 ---------------------------------------------------------------------------

Resource* CreateResource();
void ReleaseResource(Resource* resource);