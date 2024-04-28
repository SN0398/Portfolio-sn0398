#pragma once
#include "Singleton.h"
#include "MyLib.h"

#define DEFAULTDATAPATH			"./Assets/Files/DefaultData/"
#define DATAPATH				"./Assets/Files/Map.dat"
#define MAPDATAPATH				"./Assets/Files/MapData.dat"
#define TERRITORYDATAPATH		"./Assets/Files/Territory.dat"
#define BUIDINGDATAPATH			"./Assets/Files/Building.dat"
#define BUILDINGSTATEDATAPATH	"./Assets/Files/BState.dat"

#define MAP_WIDTH				64
#define MAP_HEIGHT				64

#define MAP_DRAWPOINTX			((SCREEN_WIDTH/2) - (MAP_DRAWWIDTH/2))
#define MAP_DRAWPOINTY			((SCREEN_HEIGHT/2) - (MAP_DRAWHEIGHT/2))

#define MAP_DRAWWIDTH			SCREEN_WIDTH
#define MAP_DRAWHEIGHT			SCREEN_HEIGHT

#define MAPWINDOW_CHIPSIZE		6
#define MAP_CHIP_SIZE_DEFAULT	10

#define CAMERA_MOVESPEED		5

#define MAP_WINDOWFRAME_SIZE	700
#define MAP_WINDOW_DIFF			30

class MapManager : public Singleton<MapManager>
{
public:
	enum Chip_ID
	{
		None = 0,
		Ocean,
		Grass,
		Sand,
		Snow,
		Gravel,
		Dummy,
	};

public:
	MapManager() = default;
	~MapManager() = default;
	void SetUp();

public:
	// 基本処理・描画
	void Update();
	void Draw();

	// 処理系
	void ZoomProcess();
	void CameraMoveUpdate();
	void CursorPositionUpdate();
	void ChangeDrawTerritoryModify();
	void CostTableUpdate(int FactionIndex);

	// 描画系
	void DrawMap();
	void DrawCursor();
	void DrawDebugInfo();

	// 外部系
	int GetChipSize() { return ChipSize; }
	Vector2D GetDrawPos(Vector2D pos);
	void GetChipPos(int* pChip);

	int GetChipID(int* Pos) { return MapChip[Pos[1]][Pos[0]]; }
	int GetChipID(int x, int y) { return MapChip[y][x]; }

	bool GetIsFreeTerritory(int* Pos);
	bool GetIsFreeTerritory(int x, int y);

	int GetChipFactionIndex(int* Pos) { return TerritoryMap[Pos[1]][Pos[0]]; }
	int GetChipFactionIndex(int x, int y) { return TerritoryMap[y][x]; }

	void ChangeTerritory(int* pChip, int index);
	bool GetMapChipValid(int Chip[2]);

	int GetCost(int x, int y) { return CostTable[y][x]; }

private:
	int DefaultCostTable[Dummy];
	int TerritoryMap[MAP_HEIGHT][MAP_WIDTH];
	int MapChip[MAP_HEIGHT][MAP_WIDTH];
	int CostTable[MAP_HEIGHT][MAP_WIDTH];
	int ChipSize;
	Vector2D Position;
	int SelectChip[2];
	bool CursorInMap;
	int DrawTerritoryMap;
	int DayLightScheme[24];	// 1時間ごとのマップの暗さ　アルファ値 (0 ～ 255)

};