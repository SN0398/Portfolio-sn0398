#pragma once
#include <cstring>

class ResidentList
{
public:
	enum Character
	{
		Citizen = 0,	// 市民
		Farmer,			// 農民
		Soldier,		// 兵士
		Builder,		// 建築士
		Merchant,		// 商人

		Dummy,
	};
	
public:
	ResidentList() { memset(Resident, 0, sizeof(Resident)); }
	~ResidentList() = default;
	ResidentList operator+=(ResidentList& obj)
	{
		for (int i = 0; i < Dummy; i++)
		{
			Resident[i] += obj.Resident[i];
		}
		return *this;
	}
	ResidentList operator-=(ResidentList& obj)
	{
		for (int i = 0; i < Dummy; i++)
		{
			Resident[i] -= obj.Resident[i];
		}
		return *this;
	}
	int GetResidents(Character characterID) { return Resident[characterID]; }
	void SetResidents(Character characterID, int num) { Resident[characterID] = num; }
public:
	// 全種含めたキャラクター総数を返す
	int GetAllResident();

public:
	// キャラクター別の人数
	int Resident[Dummy];

};