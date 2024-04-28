#pragma once
#include "Player.h"

// 構造体定義 -------------------------------------------------------------------------------------

typedef struct _Stage
{
	int ModelHandle;
	int SkyDomeModelHandle;

}Stage;

// 関数プロトタイプ宣言 ---------------------------------------------------------------------------

// 生成・破棄
Stage* StageInit();
void StageClean(Stage* stage);
// 処理・描画
void StageUpdate(Stage* stage, Player* player);
void DrawStage(Stage* stage);