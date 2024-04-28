#include "Enemy.h"
#include <math.h>

EnemyList* EnemyInit()
{
	// メモリ確保
	EnemyList* list = (EnemyList*)malloc(sizeof(EnemyList));

	// 敵の数だけ初期化
	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		list->enemy[i] = CreateEnemy(VGet(-1000.0f + i * 200.0f, 0.0f, 1000.0f));
	}

	return list;
}

void EnemyClean(EnemyList* list)
{
	// メモリ破棄
	free(list);
	list = NULL;
	return;
}

Enemy* CreateEnemy(VECTOR position)
{
	// メモリ確保
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));

	// 初期化
	enemy->ModelHandle = MV1LoadModel("Data/Models/Player/ROKN ngear/F-35E ROKN.mv1");	// モデルのハンドル
	enemy->position = position;	// 初期位置
	enemy->Speed = 15.0f;	// 移動速度
	enemy->direction = { 0.0f,0.0f,1.0f };	// 進行方向

	// 大きさ変更
	MV1SetScale(enemy->ModelHandle, VScale(VGet(1.0f, 1.0f, 1.0f), 0.5f));
	// モデル全体のコリジョン情報を構築
	MV1SetupCollInfo(enemy->ModelHandle, -1, 8, 8, 8);

	return enemy;
}

void ReleaseEnemy(Enemy* enemy)
{
	// メモリ破棄
	free(enemy);
	enemy = NULL;
	return;
}

void EnemyListUpdate(EnemyList* list, VECTOR target, BulletData* bdata)
{
	// 敵の数だけ処理
	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		EnemyUpdate(list->enemy[i], target, bdata);
	}
	return;
}

void EnemyUpdate(Enemy* enemy, VECTOR target, BulletData* bdata)
{
	// 目標の位置を更新する
	enemy->target = target;
	
	// 移動処理
	{
		// 移動ベクトル初期化
		enemy->move = VGet(0.0f, 0.0f, 0.0f);
		// 移動ベクトルは進行方向*移動速度
		enemy->move = VScale(enemy->direction, enemy->Speed);
		// 移動ベクトル加算
		enemy->position = VAdd(enemy->position, enemy->move);
		// モデルに座標を設定
		MV1SetPosition(enemy->ModelHandle, enemy->position);
	}
	// 方向処理
	{
		// 進行方向の更新 ホーミング
		VECTOR addDir = VScale(VNorm(VSub(target, enemy->position)), 0.01f);
		enemy->direction = VNorm(VAdd(enemy->direction, addDir));

		enemy->rotation = VSub(enemy->position, VAdd(enemy->position, enemy->move));
		// モデルの向きをセット(進行方向)
		MV1SetRotationZYAxis(enemy->ModelHandle, enemy->rotation, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	}
	// 海面に接触したら非アクティブにする
	if (enemy->position.y <= -5500.0f)
	{
		enemy->State = ES_NOTOK;
	}
	if (enemy->State == ES_NOTOK)
	{
		enemy->State = ES_DEAD;
	}
	if (enemy->State == ES_DEAD)
	{
		enemy->position = { 0.0f,0.0f,0.0f };
		enemy->State = ES_OK;
	}

	// 弾と敵の当たり判定（範囲で判定）
	CheckHitUpdate(enemy, bdata);

	return;
}

void CheckHitUpdate(Enemy* enemy, BulletData* bdata)
{
	Bullet* bullet;
	float X, Y, Z;

	for (int i = 0; i < BULLETMAXNUM; i++)
	{
		// 操作データ
		bullet = bdata->bullet[i];

		// 弾が非アクティブなら飛ばす
		if (!bullet->Flag) { continue; }

		// 方向取得
		X = enemy->position.x - bullet->position.x;
		Y = enemy->position.y - bullet->position.y;
		Z = enemy->position.z - bullet->position.z;

		// 敵と弾の距離
		if (sqrt(X * X + Y * Y + Z * Z) <= DAMAGERADIUS)
		{
			// 当たった弾を非アクティブにする
			bullet->Flag = false;
			// 敵を被弾状態にする
			enemy->State = ES_DEAD;
		}
	}

	return;
}

void DrawEnemy(EnemyList* list)
{
	// 敵の数だけ描画
	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		// 状態が死亡中の敵は描画しない
		if (list->enemy[i]->State == ES_DEAD) { continue; }
		// モデル描画
		MV1DrawModel(list->enemy[i]->ModelHandle);
	}

	return;
}