#pragma once
#include "DxLib.h"
#include "Utility.h"
#include "Bullet.h"

// 定数定義 ---------------------------------------------------------------------------------------

#define ENEMYMAXNUM		1		// 敵の最大数
#define DAMAGERADIUS	200.0f	// ダメージを受ける範囲

// 構造体定義 -------------------------------------------------------------------------------------

// 敵の状態の連番
typedef enum _EnemyState
{
	ES_OK = 0,		// 平常(アクティブ)
	ES_NOTOK,		// 被弾
	ES_DEAD,		// 非アクティブ

}EnemyState;

// 敵のパラメータをまとめた構造体
typedef struct _Enemy
{
	int ModelHandle;	// モデル
	int State;			// 状態
	VECTOR position, move, rotation, direction;
	float Speed;	// 移動速度
	VECTOR target;	// 目標の位置

}Enemy;

// すべての敵の情報をまとめた構造体
typedef struct _EnemyList
{
	Enemy* enemy[ENEMYMAXNUM];	// 敵の構造体配列

}EnemyList;

// 関数プロトタイプ宣言 ---------------------------------------------------------------------------

/// 生成・破棄 ///

// データ生成
EnemyList* EnemyInit();
// データ破棄
void EnemyClean(EnemyList* list);
// データ確保
Enemy* CreateEnemy(VECTOR position);
// データ解放
void ReleaseEnemy(Enemy* enemy);

/// 処理・描画 ///

// 敵の情報をまとめた構造体を更新
void EnemyListUpdate(EnemyList* list, VECTOR TargetPosition, BulletData* bulletdata);
// 敵の更新
void EnemyUpdate(Enemy* enemy, VECTOR TargetPosition, BulletData* bulletdata);
// 弾と敵の当たり判定
void CheckHitUpdate(Enemy* enemy, BulletData* bulletdata);
// 敵の描画
void DrawEnemy(EnemyList* list);