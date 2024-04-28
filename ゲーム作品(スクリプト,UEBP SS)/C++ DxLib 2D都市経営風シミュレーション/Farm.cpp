#include "Farm.h"
#include "MapManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Item.h"

Farm::Farm(int OverrideFlag, int PosX, int PosY)
{
	// 画像ハンドルのポインタ
	Graph[0] = &Resource::GetInstance().Farm[0];
	Graph[1] = &Resource::GetInstance().Farm[1];

	// 基底クラス変数の初期化
	IsOverride = OverrideFlag;
	Pos[0] = PosX;
	Pos[1] = PosY;

	// 派生クラス変数の初期化
	EarningRate = FARM_LOW_EARNRATE;
	ProduceItem = ItemList::Item_ID::Bread;
	Resident = 1000;
	PayRate = 100;
	ProductItemTitle = "食糧";
	DisplayName = "農村";

	return;
}

Farm::Farm(int PosX, int PosY)
{
	// 画像ハンドルのポインタ
	Graph[0] = &Resource::GetInstance().Farm[0];
	Graph[1] = &Resource::GetInstance().Farm[1];

	// 基底クラス変数の初期化
	IsOverride = false;
	Pos[0] = PosX;
	Pos[1] = PosY;

	// 派生クラス変数の初期化
	EarningRate = FARM_LOW_EARNRATE;
	ProduceItem = ItemList::Item_ID::Bread;
	Resident = 0;
	PayRate = 100;
	ProductItemTitle = "食糧";
	DisplayName = "農村";

	return;
}

void Farm::Update()
{
	ConsumeFoodProcess();
	ItemProduceProcess();

	return;
}

void Farm::Draw()
{
	DrawBuilding();

	return;
}