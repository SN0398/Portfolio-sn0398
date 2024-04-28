#include "Factory.h"
#include "ResourceManager.h"

Factory::Factory(int PosX, int PosY)
{
	// �摜�n���h���̃|�C���^
	Graph[0] = &Resource::GetInstance().Factory[0];
	Graph[1] = &Resource::GetInstance().Factory[1];

	// ���N���X�ϐ��̏�����
	IsOverride = false;
	Pos[0] = PosX;
	Pos[1] = PosY;

	// �h���N���X�ϐ��̏�����
	EarningRate = FACTORY_LOW_EARNRATE;
	ProduceItem = ItemList::Item_ID::Material;
	Resident = 0;
	PayRate = 100;
	ProductItemTitle = "���z����";
	DisplayName = "�H��";

	return;
}

void Factory::Update()
{
	ConsumeFoodProcess();
	ItemProduceProcess();

	return;
}

void Factory::Draw()
{
	DrawBuilding();

	return;
}