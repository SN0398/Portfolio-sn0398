#include "Game.h"
#include "DxLib.h"
#include "Utility.h"
#include "Define.h"
#include "ResourceMgr.h"
#include "Stage.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"

// ゲームメイン
int Game()
{
	// 戻り値（シーン番号）デフォルトは終了処理シーン
	int RETURNVALUE = GS_LEAVE;

	// データ生成
	Resource* resource = CreateResource();
	Stage* stage = StageInit();
	Player* player = PlayerInit();
	EnemyList* enemylist = EnemyInit();

	// メインループ(Escでループを抜けない)
	while (Game_MainLoop(NULL))
	{
		// FPS更新
		FPSUpdate();

		// 処理
		PlayerUpdate(player);		// プレイヤー
		StageUpdate(stage, player);	// ステージ
		CameraUpdate(player);		// カメラ
		EnemyListUpdate(enemylist, player->position, player->bdata);	// 敵

		// 描画
		DrawStage(stage);	// ステージ
		DrawEnemy(enemylist);	// 敵
		DrawPlayer(player); // プレイヤー

		// FPS調整
		FPSWait();
	}

	// データ破棄
	ReleaseResource(resource);
	StageClean(stage); 
	PlayerClean(player);

	return RETURNVALUE;
}