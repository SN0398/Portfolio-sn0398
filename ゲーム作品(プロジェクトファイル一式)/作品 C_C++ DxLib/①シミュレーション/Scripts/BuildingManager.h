#pragma once
#include "DxLib.h"
#include "Building.h"
#include "Singleton.h"
#include <list>
#include <queue>

class BuildingManager : public Singleton<BuildingManager>
{
public:
	BuildingManager() = default;
	~BuildingManager();
	void Load();
	void Release();

public:
	void Update();
	void Draw();

	void AddRequest(Building* AddObj);
	void EraseRequest(Building* EraseObj);
	void EraseProcess();
	Building* GetBuildingInfo(int ChipPos[2]);
	Building* GetRandomBuilding();
	// 指定の勢力に所属する建物の数を得る
	int GetFactionBuildingNum(int factionIndex);
	int GetConsumeFoodValue();
	int GetAllResident();
	bool GetListIsEmpty() { return list.empty(); }

private:
	std::list<Building*> list;
	std::queue<Building*> eraseQueue;

};