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
	// w’è‚Ì¨—Í‚ÉŠ‘®‚·‚éŒš•¨‚Ì”‚ğ“¾‚é
	int GetFactionBuildingNum(int factionIndex);
	int GetConsumeFoodValue();
	int GetAllResident();
	bool GetListIsEmpty() { return list.empty(); }

private:
	std::list<Building*> list;
	std::queue<Building*> eraseQueue;

};