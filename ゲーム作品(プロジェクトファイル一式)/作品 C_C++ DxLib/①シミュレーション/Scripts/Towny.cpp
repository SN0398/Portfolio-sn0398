#include "Building.h"
#include "BuildingManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

void Towny::DrawBuildingInfo(const int PosX, const int PosY)
{
	Resource& instance = Resource::GetInstance();

	// 建物名
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"【%s】", DisplayName
	);
	// 生産アイテム
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 40,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"町民 ： %d", GetResidents()
	);

	// 人数
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 80,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"食糧消費量 ： %d", GetResidents() * FOOD_CONSUME_PER
	);
	// 生産数
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 120,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"人口増加量 ： %d", IncreaseRate
	);

	return;
}

void Towny::IncreaseResidentsProcess()
{
	if (WorldManager::GetInstance().IsHour)
	{
		Building* obj;
		// 増加人数は10分割されてランダムな建物に所属する
		for (int i = 0; i < 10; i++)
		{
			obj = BuildingManager::GetInstance().GetRandomBuilding();
			if (obj == nullptr) { continue; }
			obj->AddResidents(IncreaseRate / 10);
		}
	}
	return;
}