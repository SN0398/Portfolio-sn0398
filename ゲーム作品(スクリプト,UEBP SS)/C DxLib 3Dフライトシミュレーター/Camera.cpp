#include "Camera.h"
#include "DxLib.h"
#include <math.h>
#include "Utility.h"

void CameraUpdate(Player* player)
{
	//VECTOR target = player->position;
	//target.y += 100;
	//VECTOR position = player->position;
	//position.z += 500;

	//SetCameraPositionAndTarget_UpVecY(position, target);

	// 注視点、 位置、 カメラ上座標
	VECTOR target, position, up;
	// モデルが持つ回転行列を取得
	MATRIX rotmat = MV1GetRotationMatrix(player->ModelHandle);
	// 注視点
	{
		target = player->position;	// 常にプレイヤーを見る
	}
	// 位置
	{
		position = player->position;					// プレイヤー座標
		VECTOR rotation;
		if (!Keyboard_Get(KEY_INPUT_C))					// 機体のz500手前(Cｷｰが押されていたら500奥)
		{
			rotation = VGet(0.0f, 0.0f, 500.0f);
		}
		else
		{
			rotation = VGet(0.0f, 0.0f, -500.0f);
		}
		rotation = VTransform(rotation, rotmat);		// プレイヤーの回転行列で回転させる
		position = VAdd(position, rotation);			// 位置に回転した座標を加算
	}
	// カメラ上座標
	{
		// カメラの上方向は機体が水平に見えるように
		up = VGet(0.0f, 1.0f, 0.0f);
		// カメラの上方向を機体の傾きに合わせて変更する
		up = VTransform(up, rotmat);
	}
	// カメラ設定適用
	SetCameraPositionAndTargetAndUpVec(position, target, up);

	return;
}