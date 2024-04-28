#include "Stage.h"
#include "DxLib.h"

// 生成・破棄
Stage* StageInit()
{
	// メモリ確保
	Stage* stage = (Stage*)malloc(sizeof(Stage));
	// モデルの読み込み
	stage->ModelHandle = 
		MV1LoadModel("Data/Models/Stage/Stage.mv1");	// 海
	stage->SkyDomeModelHandle = 
		MV1LoadModel("Data/Models/Stage/Skydome_TN8/Dome_TN802.mv1");	// スカイドーム
	// モデルのスケール変更
	MV1SetScale(stage->ModelHandle, VScale(VGet(1, 1, 1), 10));
	MV1SetScale(stage->SkyDomeModelHandle, VScale(VGet(1, 1, 1), 20));
	// モデルの位置変更
	MV1SetPosition(stage->ModelHandle, VGet(0, -5500, 0));

	return stage;
}

void StageClean(Stage* stage)
{
	// モデル削除
	MV1DeleteModel(stage->ModelHandle);
	MV1DeleteModel(stage->SkyDomeModelHandle);
	// メモリ解放
	free(stage);
	stage = NULL;
	return;
}

// 処理・描画
void StageUpdate(Stage* stage, Player* player)
{
	// スカイドーム座標は常にプレイヤーの座標が中心になるようにする
	MV1SetPosition(stage->SkyDomeModelHandle, player->position);

	return;
}

void DrawStage(Stage* stage)
{
	// モデルの描画
	MV1DrawModel(stage->SkyDomeModelHandle);
	MV1DrawModel(stage->ModelHandle);
	return;
}