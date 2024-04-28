#pragma once
#include "MyLibSource/2D/2D.h"

namespace MyLib
{
	class Button
	{
	public:
		Button() = delete;
		Button(Position2D Pos1, Position2D Pos2);

	public:
		// 更新 ボタン押下状態返却
		bool Update();
		// 既定の描画関数
		void Draw();

	private:
		// 当たり判定更新
		void HitStateUpdate();
		// ヒット状態更新
		void HitFrameUpdate();
		// ボタン入力状態取得
		int Get() { return ClickFrame; }

	public:
		Position2D Pos1, Pos2;		// 矩形の始点終点

	private:
		bool HitFlag;				// 点と矩形の当たり判定フラグ	true = 当たっている
		int  ClickFrame;			// ボタン入力状態格納用変数

	};
}