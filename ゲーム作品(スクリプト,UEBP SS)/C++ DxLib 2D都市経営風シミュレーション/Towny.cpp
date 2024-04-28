#include "Building.h"
#include "BuildingManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

void Towny::DrawBuildingInfo(const int PosX, const int PosY)
{
	Resource& instance = Resource::GetInstance();

	// ������
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"�y%s�z", DisplayName
	);
	// ���Y�A�C�e��
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 40,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"���� �F %d", GetResidents()
	);

	// �l��
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 80,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"�H�Ə���� �F %d", GetResidents() * FOOD_CONSUME_PER
	);
	// ���Y��
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 120,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"�l�������� �F %d", IncreaseRate
	);

	return;
}

void Towny::IncreaseResidentsProcess()
{
	if (WorldManager::GetInstance().IsHour)
	{
		Building* obj;
		// �����l����10��������ă����_���Ȍ����ɏ�������
		for (int i = 0; i < 10; i++)
		{
			obj = BuildingManager::GetInstance().GetRandomBuilding();
			if (obj == nullptr) { continue; }
			obj->AddResidents(IncreaseRate / 10);
		}
	}
	return;
}