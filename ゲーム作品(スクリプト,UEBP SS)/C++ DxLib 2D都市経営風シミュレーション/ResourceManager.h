#pragma once
#include <vector>
#include "Singleton.h"
#include "Define.h"

#define LANDCHIP_NUM		6
#define BUILDINGCHIP_DATA	2

using namespace std;

enum Color_ID
{
	White,
	Black,
	Red,
	Green,
	Blue,
	Color_Dummy,
};

enum Font_ID
{
	Yumincho,
	Yumincho_medium,
	Yumincho_mini,
	Font_Dummy,
};

// 画像ハンドル等の管理クラス
class Resource : public Singleton<Resource>
{
public:	// コンストラクタ・デストラクタ
	Resource() = default;
	~Resource() = default;

public: // ハンドルの生成・破棄
	void Load();
	void Delete();

private:	// 読み込み
	int LoadGraph(const char* FileName);
	void LoadDivGraph(const char* FileName, int AllNum, int XNum, int YNum, int XSize, int YSize, int* HandleArray);
	int LoadFontToHandle(const char* FontName, int size, int Thick);

public:	// ハンドル格納用変数

	int Color[Color_ID::Color_Dummy];

	// 画像ハンドル
	int DxLogo;
	int Title;
	int TitleStill;
	int Chip[LANDCHIP_NUM];
	// 建物の画像ハンドル　0 = override:false 1 = override:true
	int Farm[BUILDINGCHIP_DATA];
	int Factory[BUILDINGCHIP_DATA];
	int Village[BUILDINGCHIP_DATA];
	int Camp[BUILDINGCHIP_DATA];
	int CharacterIcon[4];
	int Starving;
	int Anger;
	int Coin;
	int Items[2];
	// ウィンドウ系
	int InfoWindow;
	int DialogueWindow;
	int MenuWindow;
	int MenuWindowFrame;
	int BuildingInfo;
	int BoxUI;
	int CircleUI;
	int Bar;

	// 音声ハンドル


	// フォントハンドル
	int Font[Font_ID::Font_Dummy];

private:
	vector<int> _handle;
	vector<int> _sound;
	vector<int> _font;

};