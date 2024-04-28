#include "Factory.h"
#include "ResourceManager.h"

Factory::Factory(int PosX, int PosY)
{
	// 画像ハンドルのポインタ
	Graph[0] = &Resource::GetInstance().Factory[0];
	Graph[1] = &Resource::GetInstance().Factory[1];

	// 基底クラス変数の初期化
	IsOverride = false;
	Pos[0] = PosX;
	Pos[1] = PosY;

	// 派生クラス変数の初期化
	EarningRate = FACTORY_LOW_EARNRATE;
	ProduceItem = ItemList::Item_ID::Material;
	Resident = 0;
	PayRate = 100;
	ProductItemTitle = "建築資材";
	DisplayName = "工場";

	return;
}

void Factory::Update()
{
	ConsumeFoodProcess();
	ItemProduceProcess();

	return;
}

void Factory::Draw()
{
	DrawBuilding();

	return;
}