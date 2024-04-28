#pragma once
#include "Item.h"
#include "Resident.h"

#define FOOD_CONSUME_PER			2		// 一人当たりの食糧消費量

#define HUNGERRATE_MIN				0		// 最小飢餓率
#define HUNGERRATE_MAX				300		// 最大飢餓率

#define HUNGERRATE_SPEED			500		// 飢餓のスピード
#define HUNGERRATE_RECOVERYSPEED	10		// 飢餓の回復スピード

// 建築物の抽象クラス
class Building abstract
{
public:
	Building();
	Building(int PosX, int PosY);
	virtual ~Building();

public:
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// 建物を描画する
	void DrawBuilding();
	void DrawBuildingInfoWindow(const int PosX, const int PosY);
	// 建物のアイコンを描画する
	void DrawBuildingIcon(const int PosX, const int PosY);
	// 建物の情報を描画する
	virtual void DrawBuildingInfo(const int PosX, const int PosY) = 0;
	void DrawResidentInfo(const int PosX, const int PosY);
	// 建築コストを得る
	virtual int GetBuildCost() = 0;
	// 座標のポインタを返す
	int* GetChipPos() { return Pos; }
	// 画像ハンドルを返す
	int GetGraphHandle() { return (Graph != nullptr) ? *Graph[IsOverride] : -1; }
	// 人数に応じた量の食糧消費量を返す
	int GetResidents() { return Resident; }
	// 人数を増やす
	void AddResidents(const int Num) { Resident += Num; }
	// 食糧消費量を得る
	int FoodConsumptionUpdate();
	// 食糧の消費処理
	void ConsumeFoodProcess();
	// 食糧を消費する
	void ConsumeFoods();
	// キャラクターとアイテムが存在するか確認する
	bool GetHasContents() { return (Residents->GetAllResident() > 0 && Items->GetAllItems() > 0); }
	
public:
	ItemList* Items;			// 所有アイテム
	ResidentList* Residents;	// キャラクター人数
	int Anger;					// 不満度
	int Tax;					// 一人当たりの税金
	int HungerRate;				// 飢餓率
	int FoodConsumption;		// 食糧消費量
	int Pos[2];					// 座標
	int Cost;					// 建物を建築するコスト
protected:
	// 情報
	int* Graph[2];			// 画像ハンドルのポインタ
	const char* DisplayName;	// 建物の名前
	// 状態
	int IsOverride;			// 活動中フラグ
	int Resident;			// 人数
	int FoodRate;			// 食糧の配給量

};

// 街　勢力の人数が増える
// 時間経過で人数が増える　自身の勢力のランダムな建物に所属する
class Towny : public Building
{
public:
	Towny() = default;
	Towny(int PosX, int PosY) : Building(PosX, PosY) {}
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void DrawBuildingInfo(const int PosX, const int PosY) override;
	void IncreaseResidentsProcess();

protected:
	int IncreaseRate;	// 人数増加率

};

// 商業施設　勢力のお金が増える
class Market : public Building
{
public:
	Market() = default;
	Market(int PosX, int PosY) : Building(PosX, PosY) {}
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void DrawBuildingInfo(const int PosX, const int PosY) override {}
};

// 基地　兵士を訓練し周りの拠点を自動で防衛する
class Base : public Building
{
public:
	Base() = default;
	Base(int PosX, int PosY) : Building(PosX, PosY) {}
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void DrawBuildingInfo(const int PosX, const int PosY) override {}
};

// 産業　時間でアイテムを生産する
class Industries : public Building
{
public:
	Industries() = default;
	Industries(int PosX, int PosY) : Building(PosX, PosY) {}
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void DrawBuildingInfo(const int PosX, const int PosY) override;

protected:
	// アイテム生産処理
	void ItemProduceProcess();
	// 生産数の算出
	int GetProductValue();

protected:
	// ステータス系
	int PayRate;			// 給料
	int EarningRate;		// 生産効率
	ItemList::Item_ID ProduceItem;	// 生産するアイテムのID
	const char* ProductItemTitle;	// 生産するアイテムの名前
	int* ProductItemGraphP;	// 生産するアイテムの画像ハンドルのポインタ

};