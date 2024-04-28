#include "Faction.h"
#include "DxLib.h"

Faction* Faction::Create(string factionName, int factionColor)
{
	Faction* obj = new Faction(factionName);
	obj->Money = 0;
	obj->TotalResidents = 0;
	obj->Color = (factionColor != NULL) ? factionColor : GetColor(GetRand(255), GetRand(255), GetRand(255));
	return obj;
}

void FactionList::Add(string DisplayName, int factionColor)
{
	Faction* faction = Faction::Create(DisplayName, factionColor);
	unique_ptr<Faction> AddObj(faction);
	List.push_back(std::move(AddObj));
	return;
}