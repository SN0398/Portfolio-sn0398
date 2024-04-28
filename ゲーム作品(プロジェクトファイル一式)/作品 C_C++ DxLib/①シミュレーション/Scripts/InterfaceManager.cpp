#include "InterfaceManager.h"
#include "ResourceManager.h"
#include "BuildingManager.h"

#include "Start.h"
#include "ChipSelect.h"

int UserInterface::SelectChip[2];
Building* UserInterface::SelectBuilding = nullptr;
bool UserInterface::ShowBuildingInfo = false;

InterfaceManager::InterfaceManager()
{
	return;
}

InterfaceManager::~InterfaceManager()
{
	// スタック内を空にする 
	while (!TemporaryUI.empty())
	{
		TemporaryUI.pop();
	}

	return;
}

void InterfaceManager::Initialize()
{
	// 自勢力の建物が一つもない場合
	// 建物を追加するｲﾝﾀｰﾌｪｰｽから始める
	if (BuildingManager::GetInstance().GetFactionBuildingNum(PLAYER_FACTIONINDEX) < 1)
	{
		AddInterface<Start>();
	}
	// そうでない場合は通常のｲﾝﾀｰﾌｪｰｽから始める
	else
	{
		AddInterface<ChipSelect>();
	}

	return;
}

void InterfaceManager::Update()
{
	TemporaryUI.top()->Update();

	return;
}

void InterfaceManager::Draw()
{
	// 派生クラスの描画関数
	TemporaryUI.top()->Draw();
	return;
}