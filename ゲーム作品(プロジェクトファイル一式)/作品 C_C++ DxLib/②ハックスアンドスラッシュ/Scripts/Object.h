#pragma once

#include "ResourceMgr.h"
#include "MapMgr.h"

#define ENEMYMAXNUM	20
#define ENEMYGRAPHSIZEX	64
#define ENEMYGRAPHSIZEY	64
#define ENEMYMAXTYPENUM	2
#define ENEMYRESPAWNINTERVAL	700

#define TREASUREGRAPHSIZEX	64
#define TREASUREGRAPHSIZEY	64

typedef enum _ObjectType
{
	OT_NONE = 0,
	OT_GOLD,
	OT_ENEMY,
	OT_TREASURE,

}ObjectType;

typedef enum _EnemyState
{
	ES_IDLE = 0,
	ES_CHASE,
	ES_ATTACK,
	ES_INDEATH,
	ES_DEAD,
	ES_NUMSTATE,

}EnemyState;

typedef enum _ObjectState
{
	OS_IDLE = 0,
	OS_INOPEN,
	OS_OPEN,
	OS_OPENED,

}ObjectState;

typedef struct _Object
{
	// 初期座標
	int SpawnPointX;
	int SpawnPointY;
	// 現在の座標
	float X;			
	float Y;
	// 移動方向
	float vecX;
	float vecY;
	// 移動速度
	float MoveSpeed;
	// オブジェクト種類のインデックス
	int objecttype;
	// 攻撃力
	int Attack;
	// 攻撃の間隔
	int AttackDelay;
	// 攻撃のカウンタ
	int CoolDownCount;
	// リスポーンまでの時間
	int RespawnInterval;
	// 状態
	int state;
	// アニメーション系
	int AnimIndex;
	int AnimCount;
	int AnimSpeed;

	// 連結構造
	_Object* NextNode;
	_Object* PrevNode;

}Object;

// オブジェクト管理構造体
typedef struct _Data
{
	Object* enemy[ENEMYMAXNUM];
	Object* head;

}Data;

/// 関数 ///

// 作製・破棄
Data* CreateData();
void ReleaseData(Data* data);

// オブジェクト
// 作製・破棄
Object* CreateObject();	// オブジェクトの確保
void ReleaseObject(Object* object);	// オブジェクトの解放
void GenerateEnemy(Object* object);	// 敵の生成
void GenerateTreasureBox(Object* head, int ObjectX, int ObjectY, int objecttype);

// 双方向循環リストのオブジェクト管理系関数
Object* CreateObjectNode();	// ノード作成
void InsertObject(Object* Head, Object* Node);	// ノード挿入
Object* DetachObject(Object* Node);	// 指定したノードを切り離す
void ReleaseObjectList(Object* Head);	// ノード全開放

// 基本処理系
void ObjectUpdate(Data* data, int PlayerX, int PlayerY, int* PlayerHealth);	// メイン関数
void AnimationInitialize(int* AnimIndex, int* AnimCount, int* AnimSpeed, const int AnimDelay);	// アニメーション初期化
int AnimationUpdate(int* AnimIndex, int* AnimCount, const int AnimSpeed, const int AnimNum);	// アニメーション処理
void DrawObject(Data* data, Resource* resource, int PlayerX, int PlayerY);	// 総合描画
void DrawEnemy(Data* data, Resource* resource, int PlayerX, int PlayerY);	// 敵の描画
void DrawObjectList(Data* data, Resource* resource, int PlayerX, int PlayerY);	// オブジェクト描画

// 状態別処理関数
void EnemyIdleProcess(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth);
void EnemyChaseProcess(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth);
void EnemyAttackProcess(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth);
void EnemyInDeathProcess(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth);
void EnemyDeadProcess(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth);

// 状態別処理の関数ポインタ
static void (*StateFunction[ES_NUMSTATE])(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth) =
{
	EnemyIdleProcess,
	EnemyChaseProcess,
	EnemyAttackProcess,
	EnemyInDeathProcess,
	EnemyDeadProcess,
};