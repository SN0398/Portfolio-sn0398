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

	// �ϐ��̏�����
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
	// �����̕`����W
	Vector2D DrawPos = MapManager::GetInstance().GetDrawPos({ (float)Pos[0],(float)Pos[1] });
	// �`��T�C�Y
	int size = MapManager::GetInstance().GetChipSize();

	// �`��
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
	DrawBuildingIcon(PosX, PosY);	// �A�C�R���`��
	DrawResidentInfo(PosX, PosY);	// �L�����N�^�[�ʂ̐l���\��
	//DrawBuildingInfo(PosX, PosY + 175);	// ���`��

	return;
}

void Building::DrawBuildingIcon(const int PosX, const int PosY)
{
	// �A�C�R��
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
	//	resource.Font[Font_ID::Yumincho_mini], "%d��", HungerRate);


	return;
}

int Building::FoodConsumptionUpdate()
{
	return FoodConsumption = FOOD_CONSUME_PER * Residents->GetAllResident();
}

void Building::ConsumeFoodProcess()
{
	// �����o��
	if (WorldManager::GetInstance().IsHalfDay)
	{
		FoodConsumptionUpdate();
		ConsumeFoods();
	}

	return;
}

void Building::ConsumeFoods()
{
	// �H�Ƒ��ʂ����Z�ʂ�菭�Ȃ��ꍇ
	if (Items->GetItemAmount(ItemList::Item_ID::Bread) < FoodConsumption)
	{
		// �Q�엦����������Ȃ��������l�ɉ����ĉ��Z ( �H�Ə���� - �H�Ə����� / 500 )
		HungerRate += (FoodConsumption - Items->GetItemAmount(ItemList::Item_ID::Bread)) / 500;
		//	�H�Ƃ������l�Ɍ��Z
		Items->SetItemAmount(ItemList::Item_ID::Bread, 0);
		// �Q�엦������l���傫���Ȃ����ꍇ�A�Q�엦������l�ɐݒ�
		if (HungerRate > HUNGERRATE_MAX) { HungerRate = HUNGERRATE_MAX; }
	}
	// �����ꍇ
	else
	{
		// �H�Ƃ����Z
		Items->ChangeItemAmount(ItemList::Item_ID::Bread, -FoodConsumption);
		// �Q�엦���񕜂���
		HungerRate -= HUNGERRATE_RECOVERYSPEED;
		// �Q�엦�������l��菬�����Ȃ����ꍇ�A�Q�엦�������l�ɐݒ�
		if (HungerRate < HUNGERRATE_MIN) { HungerRate = HUNGERRATE_MIN; }
	}

	return;
}