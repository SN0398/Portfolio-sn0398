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
	// プレイヤーと他勢力の関係値を取得する
	int GetFactionRelation(int factionIndex) 
	{
		return Factions->List[PLAYER_FACTIONINDEX]->GetRelationState(factionIndex);
	}

public:
	// 時間系
	int Day, Hour, Minute;	// 日、時、分
	int Tcount;		// カウンタ
	// ステータス
	bool IsHour;			// 一時間が経過したタイミング
	bool IsHalfDay;			// 半日が経過したタイミング
	bool IsDay;				// 一日が経過したタイミング
	int Money;				// 所持金
	int Tax;				// 一人当たりの税金
	int HungerRate;			// 飢餓率
	int FoodConsumption;	// 半日の食糧消費量
	int AllResidents;		// 総人口
	std::unique_ptr<FactionList> Factions;	// 世界に存在する勢力
}; 