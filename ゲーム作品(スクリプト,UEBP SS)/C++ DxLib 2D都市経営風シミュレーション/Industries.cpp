#include "Building.h"

#include "WorldManager.h"
#include "ResourceManager.h"

void Industries::DrawBuildingInfo(const int PosX, const int PosY)
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
		"���Y �F %s", ProductItemTitle
	);

	// �l��
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 80,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"���� �F %d", GetResidents()
	);
	// ���Y��
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 120,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"�������Y�� �F %d",	GetProductValue()
	);
	// �H�Ə����
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 160,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"�H�Ə���� �F %d", GetResidents() * FOOD_CONSUME_PER
	);
	// �����̎x����
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 200,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"���� �F %d", PayRate * Resident
	);
	// ���Y��
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 240,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"�����̐��Y���� �F %d", EarningRate
	);

	return;
}

void Industries::ItemProduceProcess()
{
	// �������A�N�e�B�u���̏���
	if (!IsOverride)
	{
		if (WorldManager::GetInstance().IsHour)
		{
			// ���Y���𓾂�
			Items->ChangeItemAmount(ProduceItem, GetProductValue());
			//// �������x����
			//WorldManager::GetInstance().PayProcess(PayRate * Resident);
		}
	}
	return;
}

int Industries::GetProductValue()
{
	float value = (static_cast<float>(PayRate) / 100) * (static_cast<float>(EarningRate) / 10) * (1 - static_cast<float>(HungerRate) / HUNGERRATE_MAX) * Residents->GetAllResident();
	return static_cast<int>(value);
}