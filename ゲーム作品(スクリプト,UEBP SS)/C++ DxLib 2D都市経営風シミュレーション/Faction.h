#pragma once
#include <vector>
#include <memory>
#include <map>
#include <string>

using namespace std;

// 友好状態
#define FACTION_RELATION_VALUE_ALLY_MAX			300
#define FACTION_RELATION_VALUE_ALLY_MIN			200
// 普通
#define FACTION_RELATION_VALUE_NEUTRAL			150
// 敵対状態
#define FACTION_RELATION_VALUE_ENEMY_MAX		100
#define FACTION_RELATION_VALUE_ENEMY_MIN		0

// 勢力の関係
#define FACTION_RELATION_STATE_ALLY			1		
#define FACTION_RELATION_STATE_NEUTRAL		0	
#define FACTION_RELATION_STATE_ENEMY		-1	

class Faction
{
public:
	Faction() = delete;	// 勢力名を指定しないコンストラクタを使用しない
	~Faction() = default;

private:	// 外部からコンストラクタを使用させない
	Faction(string DisplayName) : DisplayName(DisplayName) {}

public:
	// 初期状態の勢力生成
	static Faction* Create(string factionName, int factionColor);
	// 友好度設定
	void SetRelation(int factionIndex, const int relation)
	{
		Relations[factionIndex] = relation;
		// 限界値補正
		if (Relations[factionIndex] > 300) { Relations[factionIndex] = 300; }
		if (Relations[factionIndex] < 0) { Relations[factionIndex] = 0; }
	}
	// 友好度取得
	int GetRelation(int factionIndex)
	{
		// キーがすでに存在していたらそのまま返す
		if (Relations.find(factionIndex) != Relations.end())
		{
			return Relations[factionIndex];
		}
		// 存在しなければ0で初期化して返す
		else
		{
			return Relations[factionIndex] = FACTION_RELATION_VALUE_NEUTRAL;
		}
	}
	// 勢力関係取得
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
	string DisplayName;					// 勢力名
	int Money;							// 勢力の資金
	int TotalResidents;					// 総人数
	map<int, int> Relations;			// 友好度
	int Color;

};

class FactionList
{
public:
	FactionList() = default;
	~FactionList() = default;

public:
	// 勢力リストに新しい勢力を追加する
	void Add(string DisplayName, int factionColor = NULL);

public:
	vector<unique_ptr<Faction>> List;

};