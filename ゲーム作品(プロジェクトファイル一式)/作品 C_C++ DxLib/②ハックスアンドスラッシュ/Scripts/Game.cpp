#include "Game.h"
#include "DxLib.h"
#include "Utility.h"
#include "Define.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "MapMgr.h"
#include "Object.h"

typedef enum _WindowState
{
	WS_NORMAL = 0,
	WS_GAMEOVER,
	WS_POSE,

}WindowState;

// ゲームメイン
int Game(bool* PlayMusic)
{
	int RETURNVALUE = GAMESCENE_LEAVE;
	int WindowState = WS_NORMAL;

	Resource* resource = CreateResource();
	Map* map = CreateMap();
	Player* player = CreatePlayer();
	Data* data = CreateData();

	if (*PlayMusic)
	{
		PlaySoundMem(resource->MusicHandle[0], DX_PLAYTYPE_LOOP);
	}

	while (Game_MainLoop())
	{
		FPSUpdate();

		if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
		{
			if (WindowState == WS_POSE || WindowState == WS_GAMEOVER)
			{
				RETURNVALUE = GAMESCENE_TITLE;
				StopSoundMem(resource->MusicHandle[0]);
				break;
			}
			WindowState = WS_POSE;
			StopSoundMem(resource->MusicHandle[0]);
		}
		if (Keyboard_Get(KEY_INPUT_SPACE) == 1)
		{
			if (WindowState == WS_POSE)
			{
				WindowState = WS_NORMAL;
				if (*PlayMusic)
				{
					PlaySoundMem(resource->MusicHandle[0], DX_PLAYTYPE_LOOP, FALSE);
				}
			}
		}

		switch (WindowState)
		{
		case WS_NORMAL:	// メイン処理
		{
			// バックグラウンドになったらポーズ画面に遷移
			if (!GetWindowActiveFlag()) { WindowState = WS_POSE; }
			ObjectUpdate(data, player->x, player->y, &player->Health);	// オブジェクト処理
			// プレイヤー処理の戻り値からｹﾞｰﾑｵｰﾊﾞｰが返されたらｹﾞｰﾑｵｰﾊﾞｰ画面に遷移
			if (PlayerUpdate(player, map->stage, data) == WS_GAMEOVER)
			{
				WindowState = WS_GAMEOVER;
				StopSoundMem(resource->MusicHandle[0]);	// 音楽再生停止
			}

			DrawMap(map, resource, player->x, player->y);	// マップ描画
			DrawObject(data, resource, player->x, player->y);	// オブジェクト描画
			DrawPlayer(player, resource);	//  プレイヤー描画

			break;
		}
		case WS_GAMEOVER:	// ｹﾞｰﾑｵｰﾊﾞｰ画面
		{
			DrawMap(map, resource, player->x, player->y);
			DrawObject(data, resource, player->x, player->y);
			DrawPlayer(player, resource);

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);		//ブレンドモードをα(128/255)に設定
			DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, resource->CHandle[6], TRUE); //画像の描画
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ

			DrawFormatString(580, 375, resource->CHandle[5], "ゲームオーバー");

			break;
		}
		case WS_POSE:	// ﾎﾟｰｽﾞ画面
		{
			DrawMap(map, resource, player->x, player->y);
			DrawObject(data, resource, player->x, player->y);
			DrawPlayer(player, resource);

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);		//ブレンドモードをα(128/255)に設定
			DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, resource->CHandle[6], TRUE); //画像の描画
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ

			DrawFormatString(610, 375, resource->CHandle[5], "ポーズ中");
			break;
		}
		}
		
		FPSWait();
	}

	ReleaseResource(resource);
	ReleaseData(data);
	ReleasePlayer(player);

	return RETURNVALUE;
}