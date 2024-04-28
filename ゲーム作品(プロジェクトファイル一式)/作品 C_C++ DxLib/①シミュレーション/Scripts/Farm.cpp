#include "Farm.h"
#include "MapManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Item.h"

Farm::Farm(int OverrideFlag, int PosX, int PosY)
{
	// �摜�n���h���̃|�C���^
	Graph[0] = &Resource::GetInstance().Farm[0];
	Graph[1] = &Resource::GetInstance().Farm[1];

	// ���N���X�ϐ��̏�����
	IsOverride = OverrideFlag;
	Pos[0] = PosX;
	Pos[1] = PosY;

	// �h���N���X�ϐ��̏�����
	EarningRate = FARM_LOW_EARNRATE;
	ProduceItem = ItemList::Item_ID::Bread;
	Resident = 1000;
	PayRate = 100;
	ProductItemTitle = "�H��";
	DisplayName = "�_��";

	return;
}

Farm::Farm(int PosX, int PosY)
{
	// �摜�n���h���̃|�C���^
	Graph[0] = &Resource::GetInstance().Farm[0];
	Graph[1] = &Resource::GetInstance().Farm[1];

	// ���N���X�ϐ��̏�����
	IsOverride = false;
	Pos[0] = PosX;
	Pos[1] = PosY;

	// �h���N���X�ϐ��̏�����
	EarningRate = FARM_LOW_EARNRATE;
	ProduceItem = ItemList::Item_ID::Bread;
	Resident = 0;
	PayRate = 100;
	ProductItemTitle = "�H��";
	DisplayName = "�_��";

	return;
}

void Farm::Update()
{
	ConsumeFoodProcess();
	ItemProduceProcess();

	return;
}

void Farm::Draw()
{
	DrawBuilding();

	return;
}