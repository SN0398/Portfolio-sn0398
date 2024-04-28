#include "Camp.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "BuildingManager.h"

Camp::Camp(int PosX, int PosY) :
	Towny(PosX, PosY)
{
	// 画像ハンドルのポインタ
	Graph[0] = &Resource::GetInstance().Camp[0];
	Graph[1] = &Resource::GetInstance().Camp[1];

	// 基底クラス変数の初期化
	DisplayName = "キャンプ";

	// 派生クラス変数の初期化
	IncreaseRate = 0;

	return;
}

void Camp::Update()
{
	// 拠点に何も存在しなくなったらキャンプを削除
	if (!GetHasContents())
	{
		BuildingManager::GetInstance().EraseRequest(this);
		return;
	}
	// 食糧消費処理
	ConsumeFoodProcess();

	// 人口増加処理
	//IncreaseResidentsProcess();

	return;
}

void Camp::Draw()
{
	DrawBuilding();

	return;
}