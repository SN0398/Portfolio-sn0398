#include "ResourceMgr.h"
#include "DxLib.h"

Resource* CreateResource()
{
	Resource* resource = (Resource*)malloc(sizeof(Resource));

	resource->DxLogoHandle = LoadGraph("Data/Images/DxLogo.jpg");
	resource->WallHandle = LoadGraph("Data/Images/Wall.png");
	resource->BrickHandle = LoadGraph("Data/Images/Brick.png");
	resource->TreasureBoxHandle = LoadGraph("Data/Images/TreasureBox.png");
	resource->WoodHandle = LoadGraph("Data/Images/Wood.png");
	resource->MenuUIHandle = LoadGraph("Data/Images/MenuUIBar.png");
	resource->BoxUIHandle = LoadGraph("Data/Images/MenuBoard.png");
	resource->BulletHandle = LoadGraph("Data/Images/Bullet.png");
	resource->EnemyHandle = LoadGraph("Data/Images/Enemy.png");
	resource->PlayerHandle = LoadGraph("Data/Images/Player.png");

	// カラースキーム
	resource->ColorSchemeHandle[0] = GetColor(0, 99, 30);
	resource->ColorSchemeHandle[1] = GetColor(13, 58, 27);
	resource->ColorSchemeHandle[2] = GetColor(43, 128, 69);
	resource->ColorSchemeHandle[3] = GetColor(87, 198, 120);
	resource->ColorSchemeHandle[4] = GetColor(130, 183, 146);
	// サブカラースキーム
	resource->SubColorSchemeHandle[0] = GetColor(157, 157, 0);
	resource->SubColorSchemeHandle[1] = GetColor(175, 175, 0);
	resource->SubColorSchemeHandle[2] = GetColor(226, 226, 40);
	resource->SubColorSchemeHandle[3] = GetColor(239, 239, 179);
	resource->SubColorSchemeHandle[4] = GetColor(255, 255, 197);

	resource->CHandle[1] = GetColor(255, 0, 0);		// 赤
	resource->CHandle[2] = GetColor(0, 255, 0);		// 緑
	resource->CHandle[3] = GetColor(0, 0, 255);		// 青
	resource->CHandle[4] = GetColor(128, 128, 128);	// 灰
	resource->CHandle[5] = GetColor(255, 255, 255);	// 白
	resource->CHandle[6] = GetColor(0, 0, 0);		// 黒
	resource->CHandle[7] = GetColor(0, 255, 255);	// 水
	resource->CHandle[8] = GetColor(255, 0, 255);	// 紫
	resource->CHandle[9] = GetColor(255, 255, 0);	// 黄

	resource->MusicHandle[0] = LoadSoundMem("Data/Musics/audiostock_1694.mp3");
	resource->MusicHandle[1] = LoadSoundMem("Data/Musics/audiostock_1246380.mp3");
	resource->MusicHandle[2] = LoadSoundMem("Data/Musics/audiostock_1230087.mp3");

	resource->FontHandle[0] = CreateFontToHandle("Elephant", 30, 10);
	resource->FontHandle[1] = CreateFontToHandle("ＭＳ 明朝", 30, 10, DX_FONTTYPE_ANTIALIASING_EDGE);
	resource->FontHandle[2] = CreateFontToHandle("ＭＳ 明朝", 21, 7, DX_FONTTYPE_ANTIALIASING_EDGE);

	LoadDivGraph("Data/Images/Explosion.png", 7, 7, 1, 128, 128, resource->ExplosionHandle);

	return resource;
}

void ReleaseResource(Resource* resource)
{
	DeleteGraph(resource->DxLogoHandle);
	DeleteGraph(resource->WallHandle);
	DeleteGraph(resource->BrickHandle);
	DeleteGraph(resource->TreasureBoxHandle);
	DeleteGraph(resource->WoodHandle);
	DeleteGraph(resource->MenuUIHandle);
	DeleteGraph(resource->BoxUIHandle);
	DeleteGraph(resource->BulletHandle);
	DeleteGraph(resource->EnemyHandle);
	DeleteGraph(resource->PlayerHandle);

	DeleteGraph(resource->ColorSchemeHandle[0]);
	DeleteGraph(resource->ColorSchemeHandle[1]);
	DeleteGraph(resource->ColorSchemeHandle[2]);
	DeleteGraph(resource->ColorSchemeHandle[3]);
	DeleteGraph(resource->ColorSchemeHandle[4]);

	DeleteGraph(resource->SubColorSchemeHandle[0]);
	DeleteGraph(resource->SubColorSchemeHandle[1]);
	DeleteGraph(resource->SubColorSchemeHandle[2]);
	DeleteGraph(resource->SubColorSchemeHandle[3]);
	DeleteGraph(resource->SubColorSchemeHandle[4]);

	DeleteGraph(resource->CHandle[0]);
	DeleteGraph(resource->CHandle[1]);
	DeleteGraph(resource->CHandle[2]);
	DeleteGraph(resource->CHandle[3]);
	DeleteGraph(resource->CHandle[4]);
	DeleteGraph(resource->CHandle[5]);
	DeleteGraph(resource->CHandle[6]);
	DeleteGraph(resource->CHandle[7]);
	DeleteGraph(resource->CHandle[8]);
	DeleteGraph(resource->CHandle[9]);

	DeleteFontToHandle(resource->FontHandle[0]);
	DeleteFontToHandle(resource->FontHandle[1]);
	DeleteFontToHandle(resource->FontHandle[2]);

	DeleteGraph(resource->ExplosionHandle[0]);
	DeleteGraph(resource->ExplosionHandle[1]);
	DeleteGraph(resource->ExplosionHandle[2]);
	DeleteGraph(resource->ExplosionHandle[3]);
	DeleteGraph(resource->ExplosionHandle[4]);
	DeleteGraph(resource->ExplosionHandle[5]);
	DeleteGraph(resource->ExplosionHandle[6]);

	free(resource);
	resource = NULL;
	return;
}