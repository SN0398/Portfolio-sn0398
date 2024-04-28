//#include "Shopping.h"
//
//#include "InterfaceManager.h"
//#include "WorldManager.h"
//#include "ResourceManager.h"
//
//Shopping::Shopping()
//{
//	wlist.push_back(SetShopWindow({ 50,50 }, { 150,100 }, "食糧", ItemList::Item_ID::Bread, 3000));
//	wlist.push_back(SetShopWindow({ 50,130 }, { 150,180 }, "資材", ItemList::Item_ID::Material, 5000));
//
//	return;
//}
//
//void Shopping::Update()
//{
//	HitStateUpdate();
//	// 左クリックを押した瞬間
//	if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
//	{
//		for (auto& obj : wlist)
//		{
//			if (obj->HitFlag)
//			{
//				// 所持金が値段より高ければ購入する
//				if (WorldManager::GetInstance().Money >= obj->Value)
//				{
//					// お金を消費する
//					WorldManager::GetInstance().SetMoney(obj->Value, MONEY_SETTYPE_SUB);
//					// 100個単位
//					WorldManager::GetInstance().Item->ChangeItemAmount(obj->BuyItemId, 100);
//				}
//			}
//		}
//	}
//	// Escキーでタイトルに戻る
//	if (Keyboard_Get(KEY_INPUT_E) == 1)
//	{
//		InterfaceManager::GetInstance().ChangeInterface();
//	}
//
//	return;
//}
//
//void Shopping::Draw()
//{
//	Resource& instance = Resource::GetInstance();
//	for (auto& obj : wlist)
//	{
//		// フレーム描画
//		DrawExtendGraph
//		(
//			obj->Pos1.x, obj->Pos1.y,
//			obj->Pos2.x, obj->Pos2.y,
//			instance.BoxUI, TRUE
//		);
//		// カーソルが当たっていたら透明な黒を描画
//		if (obj->HitFlag)
//		{
//			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
//			DrawBox
//			(
//				obj->Pos1.x, obj->Pos1.y,
//				obj->Pos2.x, obj->Pos2.y,
//				instance.Color[Color_ID::Black], TRUE
//			);
//			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//		}
//		// 文字列描画
//		DrawFormatStringToHandle
//		(
//			obj->Pos1.x, obj->Pos1.y,
//			instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
//			obj->DisplayName
//		);
//		DrawFormatStringToHandle
//		(
//			obj->Pos1.x, obj->Pos1.y + 30, 
//			instance.Color[Color_ID::White], instance.Font[Font_ID::Yumincho],
//			"%d", obj->Value
//		);
//	}
//
//
//	return;
//}
//
//Shopping::ShopWindow* Shopping::SetShopWindow(Vector2D Pos1, Vector2D Pos2, const char* str, ItemList::Item_ID id, int Value)
//{
//	ShopWindow* AddObj = new ShopWindow;
//	AddObj->Pos1 = Pos1;
//	AddObj->Pos2 = Pos2;
//	AddObj->HitFlag = false;
//	AddObj->BuyItemId = id;
//	AddObj->DisplayName = (char*)str;
//	AddObj->Value = Value;
//	return AddObj;
//}
//
//void Shopping::HitStateUpdate()
//{
//	int MouseX, MouseY;
//	GetMousePoint(&MouseX, &MouseY);
//	Vector2D MPos = { (float)MouseX,(float)MouseY };
//
//	for (auto& obj : wlist)
//	{
//		obj->HitFlag = CheckHitBoxToPoint2D(obj->Pos1, obj->Pos2, MPos);
//	}
//
//	return;
//}