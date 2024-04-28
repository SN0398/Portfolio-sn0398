#include "Bullet.h"

BulletData* BulletDataInit()
{
	// メモリ確保
	BulletData* bulletdata = (BulletData*)malloc(sizeof(BulletData));

	// 子構造体を生成
	for (int i = 0;i < BULLETMAXNUM;i++)
	{
		bulletdata->bullet[i] = CreateBullet();
	}

	// 初期化
	bulletdata->ShootCount = 0;

	return bulletdata;
}

void BulletDataClean(BulletData* bulletdata)
{
	// 子構造体の破棄
	for (int i = 0;i < BULLETMAXNUM;i++)
	{
		ReleaseBullet(bulletdata->bullet[i]);
	}

	// 親構造体の破棄
	free(bulletdata);
	bulletdata = NULL;

	return;
}

Bullet* CreateBullet()
{
	// メモリ確保
	Bullet* bullet = (Bullet*)malloc(sizeof(Bullet));
	// モデル読込
	bullet->ModelHandle = MV1LoadModel("Data/Models/Bullet/Bullet.mv1");
	// スケール変更
	MV1SetScale(bullet->ModelHandle, VScale(VGet(1.0f, 1.0f, 1.0f), 0.1f));
	// 初期化
	bullet->position = VECTOR{ 0.0f,0.0f,0.0f };
	bullet->direction = VECTOR{ 0.0f,0.0f,0.0f };
	bullet->Flag = false;
	bullet->DeleteCount = 0;

	return bullet;
}

void ReleaseBullet(Bullet* bullet)
{
	// モデル削除
	MV1DeleteModel(bullet->ModelHandle);
	// メモリ破棄
	free(bullet);
	bullet = NULL;

	return;
}
static float scalebuf = 0.1f;
void BulletUpdate(BulletData* bdata, int MHandle, VECTOR position)
{
	// スペースキーを押し続けている間等間隔で弾をアクティブにする関数
	GenerateBulletProcess(bdata, MHandle, position);

	Bullet* bullet;
	for (int i = 0; i < BULLETMAXNUM; i++)
	{
		// 操作データの更新
		bullet = bdata->bullet[i];

		// 座標の更新
		bullet->position = VAdd(bullet->position, bullet->direction);
		// 座標アタッチ
		MV1SetPosition(bullet->ModelHandle, bullet->position);

		// アクティブな弾は一定時間で非アクティブにする
		if (++bullet->DeleteCount > SHOTDELETETIME)
		{
			// アクティブフラグを折る
			bullet->Flag = false;
		}
	}


	return;
}

void GenerateBulletProcess(BulletData* bdata, int MHandle, VECTOR position)
{
	Bullet* bullet;
	// スペースキーを押し続けている間
	if (Keyboard_Get(KEY_INPUT_SPACE) >= 1)
	{
		// 一定の間隔で銃弾を飛ばす
		if (++bdata->ShootCount >= SHOTINTERVAL)
		{
			//clsDx();
			//printfDx("%0.1f,%0.1f,%0.1f\n\n", MV1GetPosition(MHandle).x, MV1GetPosition(MHandle).y, MV1GetPosition(MHandle).z);
			// 射出中ではないデータを探す
			for (int i = 0; i < BULLETMAXNUM; i++)
			{
				// 操作データの更新
				bullet = bdata->bullet[i];

				// 一フレームにつき一回弾をアクティブにする
				if (!bullet->Flag)
				{
					// アクティブフラグを立てる
					bullet->Flag = true;
					// 消滅までのカウンタをセット
					bullet->DeleteCount = 0;
					// 座標 = 座標補正 * プレイヤー回転行列 + プレイヤー座標
					bullet->position = 
						VAdd(VTransform(VGet(0.0f, -30.0f, 0.0f), 
							MV1GetRotationMatrix(MHandle)), MV1GetPosition(MHandle));					
					// 移動ベクトル初期化
					{
						bullet->direction = { 0.0f,0.0f,-0.1f };
						// 移動ベクトル = 移動ベクトル * プレイヤーの回転行列
						bullet->direction = VTransform(bullet->direction, MV1GetRotationMatrix(MHandle));
						// 移動ベクトル正規化
						bullet->direction = Normalize_3D(bullet->direction);
						// スピード乗算
						bullet->direction = VScale(bullet->direction, BULLETSPEED);
					}
					// 方向初期化
					{
						// 回転行列セット
						MV1SetRotationMatrix(bullet->ModelHandle, MV1GetRotationMatrix(MHandle));
					}
					// カウンタを初期化
					bdata->ShootCount = 0;
					
					return;
				}
			}
		}
	}

	return;
}

void DrawBullet(BulletData* bdata)
{
	for (int i = 0; i < BULLETMAXNUM; i++)
	{
		// アクティブな弾のみ描画
		if (!bdata->bullet[i]->Flag) { continue; }
		MV1DrawModel(bdata->bullet[i]->ModelHandle);
	}

	return;
}