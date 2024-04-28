#pragma once
#include <memory>
#include "Singleton.h"
#include "Item.h"
#include "Faction.h"

#define MONEY_SETTYPE_ADD		1
#define MONEY_SETTYPE_SUB		2
#define MONEY_SETTYPE_CHANGE	3

#define NONE_FACTIONINDEX		0
#define PLAYER_FACTIONINDEX		1

class WorldManager : public Singleton<WorldManager>
{
public:
	WorldManager() = default;
	~WorldManager() = default;
	void Setup();

public:
	void Update();
	void Load() {}
	void Save() {}

public:
	// �v���C���[�Ƒ����͂̊֌W�l���擾����
	int GetFactionRelation(int factionIndex) 
	{
		return Factions->List[PLAYER_FACTIONINDEX]->GetRelationState(factionIndex);
	}

public:
	// ���Ԍn
	int Day, Hour, Minute;	// ���A���A��
	int Tcount;		// �J�E���^
	// �X�e�[�^�X
	bool IsHour;			// �ꎞ�Ԃ��o�߂����^�C�~���O
	bool IsHalfDay;			// �������o�߂����^�C�~���O
	bool IsDay;				// ������o�߂����^�C�~���O
	int Money;				// ������
	int Tax;				// ��l������̐ŋ�
	int HungerRate;			// �Q�엦
	int FoodConsumption;	// �����̐H�Ə����
	int AllResidents;		// ���l��
	std::unique_ptr<FactionList> Factions;	// ���E�ɑ��݂��鐨��
}; 