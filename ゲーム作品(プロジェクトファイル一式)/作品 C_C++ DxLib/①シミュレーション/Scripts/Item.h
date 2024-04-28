#pragma once
#include "DxLib.h"

class ItemList
{
public:
	enum Item_ID
	{
		Bread = 0,
		Material,

		Dummy,
	};

public:
	ItemList() { memset(Item, 0, sizeof(Item)); }
	~ItemList() = default;
	ItemList operator+=(ItemList& obj)
	{
		for (int i = 0; i < Dummy; i++)
		{
			Item[i] += obj.Item[i];
		}
		return *this;
	}
	ItemList operator-=(ItemList& obj)
	{
		for (int i = 0; i < Dummy; i++)
		{
			Item[i] -= obj.Item[i];
		}
		return *this;
	}

public:
	// �w��ID�̃A�C�e���̐����Z�b�g����
	void SetItemAmount(const Item_ID itemID, const int Amount) { Item[itemID] = Amount; }
	// �w��ID�̃A�C�e����ϓ�������
	void ChangeItemAmount(const Item_ID itemID, const int Amount) { Item[itemID] += Amount; }
	// �w��ID�̃A�C�e���̐��𓾂�
	int	GetItemAmount(const Item_ID itemID) const { return Item[itemID]; }
	// �S��܂߂�����������Ԃ�
	int GetAllItems()
	{
		int Result = 0;
		for (int i = 0; i < Item_ID::Dummy; i++)
		{
			Result += Item[i];
		}
		return Result;
	}
	// �f�o�b�O�p �A�C�e���̏����������ׂĕ\������
	void PrintItemInfo()
	{
		//printfDx("Wheat<%d>\n", Item[static_cast<int>(Item_ID::Wheat)]);
		//printfDx("Bread<%d>\n", Item[static_cast<int>(Item_ID::Bread)]);
	}

public:
	int Item[Dummy];
};