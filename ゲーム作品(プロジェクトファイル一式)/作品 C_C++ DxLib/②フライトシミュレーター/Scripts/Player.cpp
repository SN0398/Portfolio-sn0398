#include "Player.h"
#include <malloc.h>
#include "DxLib.h"
#include "Utility.h"
#include <math.h>

Player* PlayerInit()
{
	// メモリ確保
	Player* player = (Player*)malloc(sizeof(Player));
	// モデル読込
	player->ModelHandle = MV1LoadModel("Data/Models/Player/A6M5_Model_52/A6M5_Model_52.mv1");

	// 初期化
	player->Speed = MAXSPEED;
	player->position = VGet(700.0f, 0.0f, 0.0f);
	player->move = VGet(0.0f, 0.0f, 0.0f);
	
	// 弾の初期化
	player->bdata = BulletDataInit();

	return player;
}

void PlayerClean(Player* player)
{
	// モデル削除
	MV1DeleteModel(player->ModelHandle);
	// メモリ破棄
	BulletDataClean(player->bdata);	// 弾のメモリ破棄
	free(player);
	player = NULL;
	return;
}

void PlayerUpdate(Player* player)
{
	// 方向処理
	PlayerRotationProcess(player);

	// 座標処理
	PlayerPositionUpdate(player);

	// 弾の処理
	BulletUpdate(player->bdata, player->ModelHandle, player->position);

	return;
}

void PlayerPositionUpdate(Player* player)
{
	// 移動処理
	PlayerMoveProcess(player);
	// 座標管理
	{
		// 海面に接触したら位置を戻す
		if (player->position.y <= -5500.0f)
		{
			player->position = VGet(700.0f, 0.0f, 0.0f);
		}
		// 座標が再端になったらスピードを０にする
		if (player->position.x > 100000 || player->position.x < -100000 ||
			player->position.z > 100000 || player->position.z < -100000)
		{
			player->Speed = 0;
		}
	}

	return;
}

void PlayerMoveProcess(Player* player)
{
	// 移動処理
	{
		// 移動ベクトル初期化
		player->move.x = 0;
		player->move.y = 0;
		// 加速・減速処理
		{
			// スピードは毎フレーム減算(０以上)
			player->Speed = (player->Speed - SPEEDATTENUATION >= 0) ? player->Speed - SPEEDATTENUATION : 0;
			// Wキーで加速
			if (Keyboard_Get(KEY_INPUT_W) >= 1)
			{
				// MAXSPEED以下に収まるようにする
				player->Speed += (player->Speed + SPEEDACCELERATION <= MAXSPEED) ? SPEEDACCELERATION : 0;
			}
			// Sキーで減速
			if (Keyboard_Get(KEY_INPUT_S) >= 1)
			{
				// 0以上に収まるようにする
				player->Speed -= (player->Speed - SPEEDDECELERATION >= 0) ? SPEEDDECELERATION : 0;
			}
			// ADキーで左右
			if (Keyboard_Get(KEY_INPUT_A) >= 1)
			{
				player->move.x += LRSPEED;
			}
			if (Keyboard_Get(KEY_INPUT_D) >= 1)
			{
				player->move.x -= LRSPEED;
			}
		}
		player->move.z = -player->Speed;
		// 移動ベクトル = 移動ベクトル * モデルの回転行列
		player->move = VTransform(player->move, MV1GetRotationMatrix(player->ModelHandle));
		// 落下速度算出
		float FallSpeed = MAXFALLSPEED - player->Speed;
		FallSpeed = (FallSpeed < 0) ? 0 : -FallSpeed;
		// 移動ベクトル正規化
		player->move = Normalize_3D(player->move);
		// スピード乗算
		player->move.x *= player->Speed;
		player->move.y *= player->Speed;
		player->move.z *= player->Speed;
		// 移動ベクトル合成
		player->position.x += player->move.x;
		player->position.y += player->move.y + FallSpeed;
		player->position.z += player->move.z;
		// 座標設定
		MV1SetPosition(player->ModelHandle, player->position);
	}

	return;
}
;
void PlayerRotationProcess(Player* player)
{
	// 方向処理
	{
		// 回転率初期化
		float rotX = 0.0f;
		float rotZ = 0.0f;
		// 方向キー入力
		if (Keyboard_Get(KEY_INPUT_NUMPAD8) >= 1)	// NUM8キー
		{
			rotX -= DIRECTIONROTATIONSPEED;
		}
		if (Keyboard_Get(KEY_INPUT_NUMPAD5) >= 1)	// NUM5キー
		{
			rotX += DIRECTIONROTATIONSPEED;
		}
		if (Keyboard_Get(KEY_INPUT_NUMPAD4) >= 1)	// NUM4キー
		{
			rotZ -= DIRECTIONROTATIONSPEED;
		}
		if (Keyboard_Get(KEY_INPUT_NUMPAD6) >= 1)	// NUM6キー
		{
			rotZ += DIRECTIONROTATIONSPEED;
		}
		// 回転行列取得
		MATRIX rx = MGetRotX(rotX);	// X軸回転
		MATRIX rz = MGetRotZ(rotZ);	// Z軸回転
		// 回転行列(x * z)
		MATRIX rot = MMult(rx, rz);
		// 回転行列 = 回転行列 * ワールド変換行列
		rot = MMult(rot, MV1GetMatrix(player->ModelHandle));
		// 回転行列セット
		MV1SetRotationMatrix(player->ModelHandle, rot);
	}

	return;
}

void DrawPlayer(Player* player)
{
	// プレイヤーモデルの描画
	MV1DrawModel(player->ModelHandle);
	//弾の描画
	DrawBullet(player->bdata);

	return;
}