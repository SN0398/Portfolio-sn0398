#pragma once
#include <vector>
#include <memory>
#include <map>
#include <string>

using namespace std;

// �F�D���
#define FACTION_RELATION_VALUE_ALLY_MAX			300
#define FACTION_RELATION_VALUE_ALLY_MIN			200
// ����
#define FACTION_RELATION_VALUE_NEUTRAL			150
// �G�Ώ��
#define FACTION_RELATION_VALUE_ENEMY_MAX		100
#define FACTION_RELATION_VALUE_ENEMY_MIN		0

// ���͂̊֌W
#define FACTION_RELATION_STATE_ALLY			1		
#define FACTION_RELATION_STATE_NEUTRAL		0	
#define FACTION_RELATION_STATE_ENEMY		-1	

class Faction
{
public:
	Faction() = delete;	// ���͖����w�肵�Ȃ��R���X�g���N�^���g�p���Ȃ�
	~Faction() = default;

private:	// �O������R���X�g���N�^���g�p�����Ȃ�
	Faction(string DisplayName) : DisplayName(DisplayName) {}

public:
	// ������Ԃ̐��͐���
	static Faction* Create(string factionName, int factionColor);
	// �F�D�x�ݒ�
	void SetRelation(int factionIndex, const int relation)
	{
		Relations[factionIndex] = relation;
		// ���E�l�␳
		if (Relations[factionIndex] > 300) { Relations[factionIndex] = 300; }
		if (Relations[factionIndex] < 0) { Relations[factionIndex] = 0; }
	}
	// �F�D�x�擾
	int GetRelation(int factionIndex)
	{
		// �L�[�����łɑ��݂��Ă����炻�̂܂ܕԂ�
		if (Relations.find(factionIndex) != Relations.end())
		{
			return Relations[factionIndex];
		}
		// ���݂��Ȃ����0�ŏ��������ĕԂ�
		else
		{
			return Relations[factionIndex] = FACTION_RELATION_VALUE_NEUTRAL;
		}
	}
	// ���͊֌W�擾
	int GetRelationState(int factionIndex)
	{
		if (GetRelation(factionIndex) > FACTION_RELATION_VALUE_ALLY_MIN)
		{
			return FACTION_RELATION_STATE_ALLY;
		}
		else if (GetRelation(factionIndex) < FACTION_RELATION_VALUE_ENEMY_MAX)
		{
			return FACTION_RELATION_STATE_ENEMY;
		}
		else
		{
			return FACTION_RELATION_STATE_NEUTRAL;
		}
	}

public:
	string DisplayName;					// ���͖�
	int Money;							// ���͂̎���
	int TotalResidents;					// ���l��
	map<int, int> Relations;			// �F�D�x
	int Color;

};

class FactionList
{
public:
	FactionList() = default;
	~FactionList() = default;

public:
	// ���̓��X�g�ɐV�������͂�ǉ�����
	void Add(string DisplayName, int factionColor = NULL);

public:
	vector<unique_ptr<Faction>> List;

};