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
	// 指定IDのアイテムの数をセットする
	void SetItemAmount(const Item_ID itemID, const int Amount) { Item[itemID] = Amount; }
	// 指定IDのアイテムを変動させる
	void ChangeItemAmount(const Item_ID itemID, const int Amount) { Item[itemID] += Amount; }
	// 指定IDのアイテムの数を得る
	int	GetItemAmount(const Item_ID itemID) const { return Item[itemID]; }
	// 全種含めた物資総数を返す
	int GetAllItems()
	{
		int Result = 0;
		for (int i = 0; i < Item_ID::Dummy; i++)
		{
			Result += Item[i];
		}
		return Result;
	}
	// デバッグ用 アイテムの所持数をすべて表示する
	void PrintItemInfo()
	{
		//printfDx("Wheat<%d>\n", Item[static_cast<int>(Item_ID::Wheat)]);
		//printfDx("Bread<%d>\n", Item[static_cast<int>(Item_ID::Bread)]);
	}

public:
	int Item[Dummy];
};