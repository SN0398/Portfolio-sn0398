#include "UserInterface.h"

void UserInterface::UpdateProcess()
{
	WorldManager::GetInstance().Update();
	MapManager::GetInstance().Update();
	BuildingManager::GetInstance().Update();
	UnitMovement::GetInstance().Update();
	LogManager::GetInstance().Update();

	return;
}

void UserInterface::DrawProcess()
{
	MapManager::GetInstance().Draw();
	BuildingManager::GetInstance().Draw();
	UnitMovement::GetInstance().Draw();
	LogManager::GetInstance().Draw();
	DrawWindow();
	DrawWorldInfo();

	return;
}

void UserInterface::GetSelectChipInfo()
{
	SelectBuilding = BuildingManager::GetInstance().GetBuildingInfo(SelectChip);
	// クリックした座標に建物があれば建物の情報を表示するフラグを立てる
	ShowBuildingInfo = (SelectBuilding);

	return;
}

void UserInterface::DrawSelectChip()
{
	// 描画位置と描画幅取得
	Vector2D SelectPos = MapManager::GetInstance().GetDrawPos({ (float)SelectChip[0],(float)SelectChip[1] });
	int size = MapManager::GetInstance().GetChipSize();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	// 描画
	DrawBox
	(
		SelectPos.x,
		SelectPos.y,
		SelectPos.x + size,
		SelectPos.y + size,
		Resource::GetInstance().Color[Color_ID::Green], TRUE
	);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	return;
}

void UserInterface::DrawWindow()
{
	DrawExtendGraph
	(
		336,
		902,
		1346 + 1,
		1079 + 1,
		Resource::GetInstance().DialogueWindow, FALSE);
	DrawExtendGraph
	(
		0,
		591,
		335 + 1,
		1079 + 1,
		Resource::GetInstance().InfoWindow, FALSE);
	DrawExtendGraph
	(
		1347,
		757,
		1567 + 1,
		1079 + 1,
		Resource::GetInstance().InfoWindow, FALSE);
	DrawExtendGraph
	(
		1568,
		587,
		1919 + 1,
		1079 + 1,
		Resource::GetInstance().MenuWindow, FALSE);
	DrawExtendGraph
	(
		336,
		814,
		629 + 1,
		901 + 1,
		Resource::GetInstance().DialogueWindow, FALSE);


	return;
}

void UserInterface::DrawWorldInfo()
{
	DrawFormatStringToHandle
	(
		1180,
		927,
		Resource::GetInstance().Color[Color_ID::White], Resource::GetInstance().Font[Font_ID::Yumincho],
		"日時 : %d日目",
		WorldManager::GetInstance().Day
	);
	DrawFormatStringToHandle
	(
		1232,
		953,
		Resource::GetInstance().Color[Color_ID::White], Resource::GetInstance().Font[Font_ID::Yumincho],
		"%02d : %02d",
		WorldManager::GetInstance().Hour,
		WorldManager::GetInstance().Minute
	);
	//DrawFormatStringToHandle
	//(
	//	400,
	//	953,
	//	Resource::GetInstance().Color[Color_ID::White], Resource::GetInstance().Font[Font_ID::Yumincho],
	//	"所持金 : "
	//);
	//DrawExtendFormatStringToHandle
	//(
	//	485,
	//	953,
	//	1.0f, 1.0f,
	//	Resource::GetInstance().Color[Color_ID::White], Resource::GetInstance().Font[Font_ID::Yumincho],
	//	"%d", WorldManager::GetInstance().Money
	//);
	//DrawFormatStringToHandle
	//(
	//	400,
	//	990,
	//	Resource::GetInstance().Color[Color_ID::White], Resource::GetInstance().Font[Font_ID::Yumincho],
	//	"飢　餓 : %d", WorldManager::GetInstance().HungerRate
	//);
	//DrawFormatStringToHandle
	//(
	//	400,
	//	1010,
	//	Resource::GetInstance().Color[Color_ID::White], Resource::GetInstance().Font[Font_ID::Yumincho],
	//	"食　糧 : %d", WorldManager::GetInstance().GetFoodValue()
	//);
	//DrawFormatStringToHandle
	//(
	//	400,
	//	1030,
	//	Resource::GetInstance().Color[Color_ID::White], Resource::GetInstance().Font[Font_ID::Yumincho],
	//	"半日の食糧消費量 : %d", WorldManager::GetInstance().FoodConsumption
	//);
	//DrawFormatStringToHandle
	//(
	//	400,
	//	927,
	//	Resource::GetInstance().Color[Color_ID::White], Resource::GetInstance().Font[Font_ID::Yumincho],
	//	"人数 : %d", WorldManager::GetInstance().AllResidents
	//);

	return;
}

void UserInterface::DrawBuildingInfo()
{
	if (UserInterface::SelectBuilding == nullptr) { return; }
	UserInterface::SelectBuilding->DrawBuildingInfoWindow(70, 600);

	return;
}

void UserInterface::DrawItemInfo()
{
	//DrawFormatStringToHandle
	//(
	//	1390,
	//	815,
	//	Resource::GetInstance().Color[Color_ID::White], Resource::GetInstance().Font[Font_ID::Yumincho],
	//	"アイテム一覧"
	//);
	//DrawFormatStringToHandle
	//(
	//	1380,
	//	900,
	//	Resource::GetInstance().Color[Color_ID::White], Resource::GetInstance().Font[Font_ID::Yumincho],
	//	"食料 : %d", WorldManager::GetInstance().Item->GetItemAmount(ItemList::Item_ID::Bread)
	//);
	//DrawFormatStringToHandle
	//(
	//	1380,
	//	930,
	//	Resource::GetInstance().Color[Color_ID::White], Resource::GetInstance().Font[Font_ID::Yumincho],
	//	"資材 : %d", WorldManager::GetInstance().Item->GetItemAmount(ItemList::Item_ID::Material)
	//);
	return;
}