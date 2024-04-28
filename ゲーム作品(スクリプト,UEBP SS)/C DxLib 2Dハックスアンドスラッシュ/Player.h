#pragma once

#include "ResourceMgr.h"
#include "MapMgr.h"
#include "Object.h"

#define PLAYERGRAPHSIZEX	64
#define PLAYERGRAPHSIZEY	64
#define BULLETRADIUS		5
#define DEFAULTMAXHEALTH	200

// 構造体定義 -------------------------------------------------------------------------------------

struct Bullet
{
	float x;
	float y;
	float vecX;
	float vecY;
	float Speed;
	int State;

	Bullet* NextNode;
	Bullet* PrevNode;

};

typedef struct _Player
{
	float x;
	float y;
	float vecx;
	float vecy;
	float MoveSpeed;
	int DirectionX;
	int DirectionY;
	int Health;
	int Gold;

	Bullet* Head;

}Player;

// 関数プロトタイプ宣言 ---------------------------------------------------------------------------

// プレイヤー構造体管理系関数
Player* CreatePlayer();	// プレイヤー構造体作成
int PlayerUpdate(Player* player,int CollData[][MAPCHIPWIDTH], Data* data);	// 本処理
void PlayerMoveProcess(Player* player, int CollData[][MAPCHIPWIDTH]);	// 移動処理
void DrawPlayer(Player* player, Resource* resource);	// プレイヤー描画
void DrawHealth(Player* player, Resource* resource);	// 体力描画
void ReleasePlayer(Player* player);	// プレイヤー構造体解放

// Bullet構造体リスト管理系関数
Bullet* CreateBullet(Bullet* Head);	// ノード作成
void InsertBullet(Bullet* Head, Bullet* Node);	// ノード挿入
Bullet* DetachBullet(Bullet* Node);	// 指定したノードを切り離す
void ReleaseBullet(Bullet* Head);	// ノード全開放

// Bullet構造体基本処理系関数
void BulletUpdate(Bullet* Head, Player* player, Data* data);	// メイン関数
Bullet* BulletMoveProcess(Bullet* Node, Player* player);	// 移動処理
void GenerateBulletProcess(Bullet* Head, Player* player);	// 生成処理
void HitProcessBulletToEnemy(Player* player, Bullet* Node, Data* data);
void HitProcessPlayerToTreasureBox(Player* player, Data* data);
void DrawBullet(Bullet* Head, Player* player, Resource* resource);	// 描画処理