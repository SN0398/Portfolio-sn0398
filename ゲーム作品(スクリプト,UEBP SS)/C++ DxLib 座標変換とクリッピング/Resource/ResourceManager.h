#pragma once
#include <vector>
#include <map>
#include <string>
#include "Base/Singleton.h"
#include "Config/Define.h"

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
	HGSminchoE_Large,
	HGSminchoE_Medium,
	HGSminchoE_Mini,
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
	int LoadSoundMem(const char* FileName);
	int LoadFontToHandle(const char* FontName, int size, int Thick);
	int LoadModel(const char* FileName);

public:	// ハンドル格納用変数

	// 色マクロ
	int Color[Color_ID::Color_Dummy];

	// 画像ハンドル
	int DxLogo;

	// 音声ハンドル

	// フォントハンドル
	int Font[Font_ID::Font_Dummy];

	// モデルハンドル

private:
	vector<int> _handle;
	vector<int> _sound;
	vector<int> _font;
	vector<int> _model;

};