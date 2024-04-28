#include "Village.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "BuildingManager.h"

Village::Village(int PosX, int PosY) :
	Towny(PosX, PosY)
{
	// �摜�n���h���̃|�C���^
	Graph[0] = &Resource::GetInstance().Village[0];
	Graph[1] = &Resource::GetInstance().Village[1];

	// ���N���X�ϐ��̏�����
	DisplayName = "��";
	//IsOverride = false;
	//Pos[0] = PosX;
	//Pos[1] = PosY;
	//Resident = 0;

	// �h���N���X�ϐ��̏�����
	IncreaseRate = VILLAGE_LOW_INCREASE_RATE;

	return;
}

void Village::Update()
{
	// �H�Ə����
	ConsumeFoodProcess();

	// �l����������
	//IncreaseResidentsProcess();

	return;
}

void Village::Draw()
{
	DrawBuilding();

	return;
}