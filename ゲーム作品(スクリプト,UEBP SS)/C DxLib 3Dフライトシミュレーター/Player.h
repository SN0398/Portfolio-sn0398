#pragma once
#include "DxLib.h"
#include "Utility.h"
#include "Bullet.h"

// 定数定義 ---------------------------------------------------------------------------------------

#define DIRECTIONROTATIONSPEED	0.02f	// 回転量
#define ROTATIONATTENUATION		0.5f	// 回転速度減速量
#define SPEEDATTENUATION		0.1f	// 自然減測量
#define MAXSPEED				50.0f	// 最大速度
#define SPEEDACCELERATION		0.5f	// 加速量
#define SPEEDDECELERATION		0.3f	// 減速量
#define MAXFALLSPEED			30.0f	// 最大落下速度
#define FALLSPEEDACCELERATION	0.1f	// 落下速度加速量
#define LRSPEED					5.0f	// 左右のスピード

// 構造体定義 -------------------------------------------------------------------------------------

typedef struct _Player
{
	int ModelHandle;
	VECTOR position, move;
	float Speed;
	BulletData* bdata;

}Player;

// 関数プロトタイプ宣言 ---------------------------------------------------------------------------

// 生成・破棄
Player* PlayerInit();
void PlayerClean(Player* player);
// プレイヤー処理・描画
void PlayerUpdate(Player* player);
void PlayerPositionUpdate(Player* player);
void PlayerMoveProcess(Player* player);
void PlayerRotationProcess(Player* player);
void DrawPlayer(Player* player);