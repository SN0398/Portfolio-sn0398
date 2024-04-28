#pragma once
#include <vector>
#include "Astar.h"
#include "MyLib.h"
#include "Item.h"
#include "Building.h"
#include "Singleton.h"
#include "Resident.h"

using namespace Astar;

#define UNITMOVESPEED_DEFAULT					300			// デフォルトの移動速度
#define UNITMOVESPEED_DECREASERATE_INVENTORY	0.435		// アイテム数による移動速度減衰量
#define UNITMOVESPEED_DECREASERATE_RESIDENT		0.462		// キャラ数による移動速度減衰量

#define UNITMOVEMENT_MAXCOUNT					100000.0f	// 最大移動カウンタ

#define UNITMOVEMENT_CLAIM_DENIED_RESIDENT_IS_EMPTY		0
#define UNITMOVEMENT_CLAIM_SUCCESS						1

class UnitMovement : public Singleton<UnitMovement>
{
public:
	struct UnitData
	{
		float offsetX, offsetY;	// 移動オフセット
		int Count;				// 移動用カウンタ
		Position NowPos;		// 座標
		vector<Node*> Route;	// 移動経路
		ItemList Inventory;		// アイテム
		ResidentList Residents;	// キャラクター
		int MoveSpeed;			// 移動速度
	};

public:
	UnitMovement() {}
	~UnitMovement() {}

public:
	// 移動中部隊の更新関数
	void Update();		
	// 移動中部隊の描画関数
	void Draw();		
	// ウィンドウに移動中部隊の情報描画
	void DrawInfo();	
	// 移動部隊生成
	int Claim(Position start, Position goal, Building* base, ItemList* moveItems, ResidentList* moveResidents);

private:
	vector<UnitData*> dataList;

};