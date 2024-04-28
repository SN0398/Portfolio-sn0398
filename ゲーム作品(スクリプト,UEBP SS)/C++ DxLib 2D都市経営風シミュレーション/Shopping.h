//#pragma once
//#include "UserInterface.h"
//#include "MyLib.h"
//#include <list>
//#include "Item.h"
//
//// 操作インターフェース：チップ選択
//class Shopping : public UserInterface
//{
//public:
//	struct ShopWindow
//	{
//		Vector2D Pos1, Pos2;
//		bool HitFlag;
//		char* DisplayName;
//		ItemList::Item_ID BuyItemId;
//		int Value;
//	};
//public:
//	Shopping();
//	~Shopping() = default;
//
//	ShopWindow* SetShopWindow(Vector2D Pos1, Vector2D Pos2, const char* str, ItemList::Item_ID id, int Value);
//	void HitStateUpdate();
//
//public:
//	void Update() override;
//	void Draw() override;
//
//private:
//	std::list<ShopWindow*> wlist;
//};