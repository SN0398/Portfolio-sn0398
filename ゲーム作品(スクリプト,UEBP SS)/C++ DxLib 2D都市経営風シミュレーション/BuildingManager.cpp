#include "BuildingManager.h"

#include "MapManager.h"

#include "Farm.h"
#include "Village.h"

void BuildingManager::Load()
{

	return;
}

void BuildingManager::Release()
{
	for (Building* obj : list)
	{
		if (obj == nullptr) { continue; }
		delete obj;
	}
	list.clear();
	return;
}

BuildingManager::~BuildingManager()
{
	Release();

	return;
}

void BuildingManager::Update()
{
	for (Building* obj : list)
	{
		obj->Update();
	}
	EraseProcess();

	return;
}

void BuildingManager::Draw()
{
	for (Building* obj : list)
	{
		obj->Draw();
	}

	return;
}

void BuildingManager::AddRequest(Building* AddObj)
{
	list.push_back(AddObj);
	return;
}

void BuildingManager::EraseRequest(Building* EraseObj)
{
	eraseQueue.push(EraseObj);
		
	return;
}

void BuildingManager::EraseProcess()
{
	while (!eraseQueue.empty())
	{
		auto itr = find(list.begin(), list.end(), eraseQueue.front());
		eraseQueue.pop();
		delete (*itr);
		list.erase(itr);
	}
		
	return;
}

Building* BuildingManager::GetBuildingInfo(int ChipPos[2])
{
	int* ChipPosBuff;	// ����|�C���^
	for (auto obj : list)	// ��
	{
		ChipPosBuff = obj->GetChipPos();	// obj�̍��W���󂯎��
		if (ChipPosBuff[0] == ChipPos[0] &&	// X�������v�@����
			ChipPosBuff[1] == ChipPos[1])	// Y�������v
		{
			// ���v�����C���X�^���X��Ԃ�
			return obj;
		}
	}
	// �󂯎�������W�ƍ��v���錚�����������nullptr��Ԃ�
	return nullptr;
}

Building* BuildingManager::GetRandomBuilding()
{
	// �����_���Ȍ����𓾂�
	if (!list.empty())
	{
		int size = GetRand(list.size() - 1);
		auto itr = list.begin();
		if (size > 0) { std::advance(itr, size); }
		return *itr;
	}
	return nullptr;
}

int BuildingManager::GetFactionBuildingNum(int factionIndex)
{
	int result = 0;
	int pos[2];
	for (auto& obj : list)
	{
		pos[0] = obj->Pos[0];
		pos[1] = obj->Pos[1];
		if (MapManager::GetInstance().GetChipFactionIndex(pos) == factionIndex)
		{
			result++;
		}
	
	}
	return result;
}

int BuildingManager::GetConsumeFoodValue()
{
	int value = 0;
	for (auto obj : list)	// ��
	{
		// �H�Ə���� = ��l������̐H�Ə���� * ���l��
		value += FOOD_CONSUME_PER * GetAllResident();
	}
	return value;
}

int BuildingManager::GetAllResident()
{
	int temp = 0;
	for (auto obj : list)
	{
		temp += obj->GetResidents();
	}
	return temp;
}