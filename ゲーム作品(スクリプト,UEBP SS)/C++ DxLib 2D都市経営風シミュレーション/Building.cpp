#include "Building.h"

#include "MyLib.h"
#include "MapManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"

Building::Building()
{
	Items = new ItemList();
	Residents = new ResidentList();

}

Building::Building(int PosX, int PosY)
{
	Items = new ItemList();
	Residents = new ResidentList();

	// 変数の初期化
	IsOverride = false;
	Pos[0] = PosX;
	Pos[1] = PosY;

	Tax = 0;
	HungerRate = 0;
	FoodConsumption = 0;
	Graph[0] = nullptr;
	Graph[1] = nullptr;
	Resident = 0;
	FoodRate = 0; 
}

Building::~Building()
{
	delete Items;
	delete Residents;
}

void Building::DrawBuilding()
{
	// 建物の描画座標
	Vector2D DrawPos = MapManager::GetInstance().GetDrawPos({ (float)Pos[0],(float)Pos[1] });
	// 描画サイズ
	int size = MapManager::GetInstance().GetChipSize();

	// 描画
	DrawExtendGraph
	(
		DrawPos.x,
		DrawPos.y,
		DrawPos.x + size,
		DrawPos.y + size,
		GetGraphHandle(),
		TRUE
	);

	return;
}

void Building::DrawBuildingInfoWindow(const int PosX, const int PosY)
{
	DrawBuildingIcon(PosX, PosY);	// アイコン描画
	DrawResidentInfo(PosX, PosY);	// キャラクター別の人数表示
	//DrawBuildingInfo(PosX, PosY + 175);	// 情報描画

	return;
}

void Building::DrawBuildingIcon(const int PosX, const int PosY)
{
	// アイコン
	DrawExtendGraph(PosX + 10, PosY, PosX + 160, PosY + 150, GetGraphHandle(), TRUE);

	return;
}

void Building::DrawResidentInfo(const int PosX, const int PosY)
{
	auto& resource = Resource::GetInstance();

	int X = PosX - 20;
	int Y = PosY + 180;
	int stringX = X + 32 + 5;
	int stringY = 13;
	DrawExtendGraph(X, Y, X + 32, Y + 32, resource.CharacterIcon[0], TRUE);
	DrawFormatStringToHandle(stringX, Y + stringY, resource.Color[Color_ID::Black],
		resource.Font[Font_ID::Yumincho_medium], "%s", FormatNumber(Residents->GetAllResident()).c_str());
	Y += 32 + 16;
	DrawExtendGraph(X, Y, X + 32, Y + 32, resource.Items[0], TRUE);
	DrawFormatStringToHandle(stringX, Y + stringY, resource.Color[Color_ID::Black],
		resource.Font[Font_ID::Yumincho_medium], "%s", FormatNumber(Items->GetItemAmount(ItemList::Item_ID::Bread)).c_str());
	Y += 32 + 16;
	DrawExtendGraph(X, Y, X + 32, Y + 32, resource.Items[1], TRUE);
	DrawFormatStringToHandle(stringX, Y + stringY, resource.Color[Color_ID::Black],
		resource.Font[Font_ID::Yumincho_medium], "%s", FormatNumber(Items->GetItemAmount(ItemList::Item_ID::Material)).c_str());
	Y += 32 + 16;
	DrawExtendGraph(X, Y, X + 32, Y + 32, resource.Starving, TRUE);
	DrawFormatStringToHandle(stringX, Y + stringY, resource.Color[Color_ID::Black],
		resource.Font[Font_ID::Yumincho_medium], "%d%%", HungerRate);
	Y += 32 + 16;
	DrawExtendGraph(X, Y, X + 32, Y + 32, resource.Anger, TRUE);
	DrawFormatStringToHandle(stringX, Y + stringY, resource.Color[Color_ID::Black],
		resource.Font[Font_ID::Yumincho_medium], "%d%%", Anger);
	//Y += 32 + 16;
	//DrawExtendGraph(X, Y, X + 32, Y + 32, resource.Starving, TRUE);
	//DrawFormatStringToHandle(stringX, Y, resource.Color[Color_ID::Black],
	//	resource.Font[Font_ID::Yumincho_mini], "%d％", HungerRate);


	return;
}

int Building::FoodConsumptionUpdate()
{
	return FoodConsumption = FOOD_CONSUME_PER * Residents->GetAllResident();
}

void Building::ConsumeFoodProcess()
{
	// 半日経過
	if (WorldManager::GetInstance().IsHalfDay)
	{
		FoodConsumptionUpdate();
		ConsumeFoods();
	}

	return;
}

void Building::ConsumeFoods()
{
	// 食糧総量が減算量より少ない場合
	if (Items->GetItemAmount(ItemList::Item_ID::Bread) < FoodConsumption)
	{
		// 飢餓率を引ききれなかった数値に応じて加算 ( 食糧消費量 - 食糧所持数 / 500 )
		HungerRate += (FoodConsumption - Items->GetItemAmount(ItemList::Item_ID::Bread)) / 500;
		//	食糧を下限値に減算
		Items->SetItemAmount(ItemList::Item_ID::Bread, 0);
		// 飢餓率が上限値より大きくなった場合、飢餓率を上限値に設定
		if (HungerRate > HUNGERRATE_MAX) { HungerRate = HUNGERRATE_MAX; }
	}
	// 多い場合
	else
	{
		// 食糧を減算
		Items->ChangeItemAmount(ItemList::Item_ID::Bread, -FoodConsumption);
		// 飢餓率を回復する
		HungerRate -= HUNGERRATE_RECOVERYSPEED;
		// 飢餓率が下限値より小さくなった場合、飢餓率を下限値に設定
		if (HungerRate < HUNGERRATE_MIN) { HungerRate = HUNGERRATE_MIN; }
	}

	return;
}