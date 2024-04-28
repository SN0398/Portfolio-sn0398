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
	// �X�^�b�N������ɂ��� 
	while (!TemporaryUI.empty())
	{
		TemporaryUI.pop();
	}

	return;
}

void InterfaceManager::Initialize()
{
	// �����͂̌���������Ȃ��ꍇ
	// ������ǉ��������̪������n�߂�
	if (BuildingManager::GetInstance().GetFactionBuildingNum(PLAYER_FACTIONINDEX) < 1)
	{
		AddInterface<Start>();
	}
	// �����łȂ��ꍇ�͒ʏ�̲���̪������n�߂�
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
	// �h���N���X�̕`��֐�
	TemporaryUI.top()->Draw();
	return;
}