#include "Camp.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "BuildingManager.h"

Camp::Camp(int PosX, int PosY) :
	Towny(PosX, PosY)
{
	// �摜�n���h���̃|�C���^
	Graph[0] = &Resource::GetInstance().Camp[0];
	Graph[1] = &Resource::GetInstance().Camp[1];

	// ���N���X�ϐ��̏�����
	DisplayName = "�L�����v";

	// �h���N���X�ϐ��̏�����
	IncreaseRate = 0;

	return;
}

void Camp::Update()
{
	// ���_�ɉ������݂��Ȃ��Ȃ�����L�����v���폜
	if (!GetHasContents())
	{
		BuildingManager::GetInstance().EraseRequest(this);
		return;
	}
	// �H�Ə����
	ConsumeFoodProcess();

	// �l����������
	//IncreaseResidentsProcess();

	return;
}

void Camp::Draw()
{
	DrawBuilding();

	return;
}