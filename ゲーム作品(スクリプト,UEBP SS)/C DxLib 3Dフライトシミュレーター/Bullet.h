#pragma once
#include "DxLib.h"
#include "Utility.h"

// 定数定義 ---------------------------------------------------------------------------------------

#define BULLETSPEED				200.0f	// 弾のスピード
#define BULLETMAXNUM			30		// 銃弾の最大数
#define SHOTINTERVAL			5		// 射出間隔
#define SHOTDELETETIME			100		// 銃弾が出されてから消えるまでの時間

// 構造体定義 -------------------------------------------------------------------------------------

typedef struct _Bullet
{
	int ModelHandle;
	VECTOR position, move, direction;
	bool Flag;
	int DeleteCount;

}Bullet;

typedef struct _BulletData
{
	int ShootCount;
	Bullet* bullet[BULLETMAXNUM];

}BulletData;

// 関数プロトタイプ宣言 ---------------------------------------------------------------------------

/// 生成・破棄 ///

// 親構造体のデータ生成
BulletData* BulletDataInit();
// 親構造体のデータ破棄
void BulletDataClean(BulletData* bulletdata);
// 子構造体のデータ生成
Bullet* CreateBullet();
// 子構造体のデータ破棄
void ReleaseBullet(Bullet* bullet);

/// 弾の処理・描画 ///

// 弾の処理関数ラッパー
void BulletUpdate(BulletData* bulletdata, int ModelHandle, VECTOR position);		
// 弾の初期化・アクティブ化
void GenerateBulletProcess(BulletData* bulletdata, int ModelHandle, VECTOR position);
// 弾の描画
void DrawBullet(BulletData* bulletdata);