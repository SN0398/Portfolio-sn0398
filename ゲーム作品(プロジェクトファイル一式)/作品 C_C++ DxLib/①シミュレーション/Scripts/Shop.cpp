#include "Shop.h"
#include "MapManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Item.h"

Shop::Shop(int OverrideFlag, int PosX, int PosY)
{
	// �摜�n���h���̃|�C���^
	Graph[0] = &Resource::GetInstance().Village[0];
	Graph[1] = &Resource::GetInstance().Village[1];

	// ���N���X�ϐ��̏�����
	IsOverride = OverrideFlag;
	Pos[0] = PosX;
	Pos[1] = PosY;

	return;
}

void Shop::Update()
{


	return;
}

void Shop::Draw()
{
	DrawBuilding();

	return;
}