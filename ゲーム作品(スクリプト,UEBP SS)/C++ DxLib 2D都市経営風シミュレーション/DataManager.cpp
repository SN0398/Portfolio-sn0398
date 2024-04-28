#include "DataManager.h"

#include "BuildingManager.h"
#include "MapManager.h"
#include "WorldManager.h"
#include "InterfaceManager.h"

#include <iostream>
#include <fstream>
#include <filesystem>

#include "Village.h"
#include "Farm.h"
#include "Factory.h"
#include "Shop.h"

int DataManager::Load()
{
	// インスタンス生成
	WorldManager::GetInstance().Setup();
	MapManager::GetInstance().SetUp();
	BuildingManager::GetInstance().Load();
	std::list<Building*> building;

	{
		Building* AddObj = new Farm(35, 32);		// 村生成
		AddObj->Items->SetItemAmount(ItemList::Item_ID::Bread, 3000);
		AddObj->Items->SetItemAmount(ItemList::Item_ID::Material, 300);
		AddObj->Residents->SetResidents(ResidentList::Character::Farmer, 1000);
		AddObj->Residents->SetResidents(ResidentList::Character::Soldier, 0);
		AddObj->Residents->SetResidents(ResidentList::Character::Builder, 0);
		building.push_back(AddObj);

		MapManager::GetInstance().ChangeTerritory(AddObj->Pos, PLAYER_FACTIONINDEX);
	}
	for (auto obj : building)
	{
		BuildingManager::GetInstance().AddRequest(obj);
	}
	building.clear();

	InterfaceManager::GetInstance().Initialize();

	WorldManager::GetInstance().Factions->Add("無所属", GetColor(0, 0, 0));
	WorldManager::GetInstance().Factions->Add("プレイヤーの勢力", GetColor(0, 0, 255));

	return 1;
}