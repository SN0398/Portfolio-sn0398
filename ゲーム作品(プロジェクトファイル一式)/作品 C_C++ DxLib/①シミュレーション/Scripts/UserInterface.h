#pragma once
#include "DxLib.h"
#include "MyLib.h"
#include "Building.h"
#include "MapManager.h"
#include "WorldManager.h"
#include "BuildingManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "UnitMovement.h"

enum class InterfaceType
{
	ChipSelect,
	ActionSelector,
	Shopping,
	Inventory,
	Build,
	Demolition,
	dummy,
};

// 抽象クラス
class UserInterface abstract
{
public:
	 UserInterface() = default;
	~UserInterface() = default;

public:
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// 基本処理関数のラッパー
	void UpdateProcess();
	// 基本描画関数のラッパー
	void DrawProcess();

	// 処理系
	// 選択中の建物の情報更新
	void GetSelectChipInfo();

	// 描画系
	// 選択チップを描画
	void DrawSelectChip();
	// ウィンドウを表示
	void DrawWindow();
	// 時間、所持金などを描画する
	void DrawWorldInfo();
	// 建物の情報を描画する
	void DrawBuildingInfo();
	// アイテム情報を描画する
	void DrawItemInfo();

public:
	static int SelectChip[2];
	static Building* SelectBuilding;	// 選択座標にある建物へのポインタ（建物が存在しなければnullptr）
	static bool ShowBuildingInfo;	// 建物の情報を表示するフラグ	選択中のチップ座標に建物があればtrue

};