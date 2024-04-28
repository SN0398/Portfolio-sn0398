#pragma once
#include <cstring>

class ResidentList
{
public:
	enum Character
	{
		Citizen = 0,	// �s��
		Farmer,			// �_��
		Soldier,		// ���m
		Builder,		// ���z�m
		Merchant,		// ���l

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
	// �S��܂߂��L�����N�^�[������Ԃ�
	int GetAllResident();

public:
	// �L�����N�^�[�ʂ̐l��
	int Resident[Dummy];

};