#include "Village.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "BuildingManager.h"

Village::Village(int PosX, int PosY) :
	Towny(PosX, PosY)
{
	// 画像ハンドルのポインタ
	Graph[0] = &Resource::GetInstance().Village[0];
	Graph[1] = &Resource::GetInstance().Village[1];

	// 基底クラス変数の初期化
	DisplayName = "村";
	//IsOverride = false;
	//Pos[0] = PosX;
	//Pos[1] = PosY;
	//Resident = 0;

	// 派生クラス変数の初期化
	IncreaseRate = VILLAGE_LOW_INCREASE_RATE;

	return;
}

void Village::Update()
{
	// 食糧消費処理
	ConsumeFoodProcess();

	// 人口増加処理
	//IncreaseResidentsProcess();

	return;
}

void Village::Draw()
{
	DrawBuilding();

	return;
}