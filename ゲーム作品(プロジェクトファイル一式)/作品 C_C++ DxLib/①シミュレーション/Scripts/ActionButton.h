#pragma once
#include "MyLib.h"
#include "UserInterface.h"
#include <string>

class ActionButton
{
private:	
	// ファクトリーを介さないコンストラクタは禁止
	ActionButton() = default;
	ActionButton(std::string text) :
		DiaplayName(text) {}

public:
	~ActionButton() = default;

public:
	// インスタンス生成メソッド
	static ActionButton* Create(Vector2D Pos1, Vector2D Pos2, std::string text, int* graph, int index = 0);
	// GUI描画
	void Draw();
	// 当たり判定更新
	void HitStateUpdate(const Vector2D PointPos);
	// 当たり判定取得
	bool GetHitState() { return HitFlag; }

public:
	int* Icon_ptr;				// 画像のポインタ
	std::string DiaplayName;	// 文字
	Vector2D Pos1, Pos2;		// 矩形の始点終点
	int HitFlag;				// 点と矩形の当たり判定フラグ	true = 当たっている
	int Index;					// インデックス

};