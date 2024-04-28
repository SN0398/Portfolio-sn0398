#include "Building.h"

#include "WorldManager.h"
#include "ResourceManager.h"

void Industries::DrawBuildingInfo(const int PosX, const int PosY)
{
	Resource& instance = Resource::GetInstance();

	// Œš•¨–¼
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"y%sz", DisplayName
	);
	// ¶ŽYƒAƒCƒeƒ€
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 40,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"¶ŽY F %s", ProductItemTitle
	);

	// l”
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 80,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"’¬–¯ F %d", GetResidents()
	);
	// ¶ŽY”
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 120,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"Œ©ž¶ŽY” F %d",	GetProductValue()
	);
	// H—ÆÁ”ï—Ê
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 160,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"H—ÆÁ”ï—Ê F %d", GetResidents() * FOOD_CONSUME_PER
	);
	// ’À‹à‚ÌŽx•¥ó‹µ
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 200,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"’À‹à F %d", PayRate * Resident
	);
	// ¶ŽY—¦
	DrawExtendFormatStringToHandle
	(
		PosX,
		PosY + 240,
		1.0f, 1.0f,
		instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
		"Œš•¨‚Ì¶ŽYŒø—¦ F %d", EarningRate
	);

	return;
}

void Industries::ItemProduceProcess()
{
	// Œš•¨‚ªƒAƒNƒeƒBƒuŽž‚Ìˆ—
	if (!IsOverride)
	{
		if (WorldManager::GetInstance().IsHour)
		{
			// ¶ŽY•¨‚ð“¾‚é
			Items->ChangeItemAmount(ProduceItem, GetProductValue());
			//// ’À‹à‚ðŽx•¥‚¤
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