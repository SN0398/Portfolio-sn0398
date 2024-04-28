#include "ActionButton.h"

#include "ResourceManager.h"
#include "InterfaceManager.h"

ActionButton* ActionButton::Create(Vector2D Pos1, Vector2D Pos2, std::string text, int* graph, int index)
{
	// 例外
	if (text.empty()) { return nullptr; }
	if (graph == nullptr) { return nullptr; }
	// インスタンス生成
	ActionButton* tmp = new ActionButton(text);
	// 初期化
	tmp->Icon_ptr = graph;
	tmp->HitFlag = false;
	tmp->Pos1 = Pos1;
	tmp->Pos2 = Pos2;
	tmp->Index = index;

	// 返却
	return tmp;
}

void ActionButton::Draw()
{
	auto& instance = Resource::GetInstance();
	// ボックス描画
	DrawExtendGraph(Pos1.x, Pos1.y, Pos2.x, Pos2.y, instance.BoxUI, FALSE);
	// アイコン描画
	DrawExtendGraph(Pos1.x, Pos1.y, Pos2.x, Pos2.y, *Icon_ptr, TRUE);
	// カーソルが当たっていたら半透明の黒色を描画
	if (HitFlag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawBox(Pos1.x, Pos1.y, Pos2.x, Pos2.y, instance.Color[Color_ID::Black], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	// 文字描画
	DrawExtendFormatStringToHandle
	(
		Pos1.x, Pos1.y, 
		1.0f, 1.0f, 
		instance.Color[Color_ID::White],
		instance.Font[Font_ID::Yumincho], 
		DiaplayName.c_str()
	);
	return;
}

void ActionButton::HitStateUpdate(const Vector2D PointPos)
{
	// 矩形と点を当たり判定
	HitFlag = CheckHitBoxToPoint2D(Pos1, Pos2, PointPos);
	return;
}