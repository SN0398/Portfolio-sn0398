#include "ResourceManager.h"
#include "DxLib.h"

void Resource::Load()
{
	/// ハンドル読み込み ///
	Color[Color_ID::White] = GetColor(255, 255, 255);
	Color[Color_ID::Black] = GetColor(0, 0, 0);
	Color[Color_ID::Red] = GetColor(255, 0, 0);
	Color[Color_ID::Green] = GetColor(0, 255, 0);
	Color[Color_ID::Blue] = GetColor(0, 0, 255);
	
	DxLogo =			Resource::LoadGraph("Assets/Data/Images/DxLogo.jpg");
	Title =				Resource::LoadGraph("Assets/Data/Images/Title.png");
	TitleStill =		Resource::LoadGraph("Assets/Data/Images/Title Still.png");
	InfoWindow =		Resource::LoadGraph("Assets/Data/Images/InfoWindow.png");
	DialogueWindow =	Resource::LoadGraph("Assets/Data/Images/DialogueWindow.png");
	MenuWindow =		Resource::LoadGraph("Assets/Data/Images/MenuWindow.png");
	MenuWindowFrame =	Resource::LoadGraph("Assets/Data/Images/MenuFrameWindow.png");
	BuildingInfo =		Resource::LoadGraph("Assets/Data/Images/BuildingInfoWindow.png");
	BoxUI =				Resource::LoadGraph("Assets/Data/Images/BoxUi.png");
	Starving =			Resource::LoadGraph("Assets/Data/Images/Starving.png");
	Anger =				Resource::LoadGraph("Assets/Data/Images/Anger.png");
	Coin =				Resource::LoadGraph("Assets/Data/Images/Coin.png");
	CircleUI =			Resource::LoadGraph("Assets/Data/Images/Circle.png");
	Bar =				Resource::LoadGraph("Assets/Data/Images/Bar.png");

	CharacterIcon[0] =	Resource::LoadGraph("Assets/Data/Images/Icon_Innocent.png");
	CharacterIcon[1] =	Resource::LoadGraph("Assets/Data/Images/Icon_Farmer.png");
	CharacterIcon[2] =	Resource::LoadGraph("Assets/Data/Images/Icon_Builder.png");
	CharacterIcon[3] =	Resource::LoadGraph("Assets/Data/Images/Icon_Soldier.png");

	Resource::LoadDivGraph("Assets/Data/Images/Items.png", 2, 2, 1, 128, 128, Items);
	Resource::LoadDivGraph("Assets/Data/Images/Chip.png", 6, 6, 1, 256, 256, Chip);

	Resource::LoadDivGraph("Assets/Data/Images/Farm.png", 2, 2, 1, 256, 256, Farm);
	Resource::LoadDivGraph("Assets/Data/Images/Factory.png", 2, 2, 1, 256, 256, Factory);
	Resource::LoadDivGraph("Assets/Data/Images/Village.png", 2, 2, 1, 256, 256, Village);
	Resource::LoadDivGraph("Assets/Data/Images/Camp.png", 2, 2, 1, 256, 256, Camp);

	Font[Font_ID::Yumincho] = Resource::LoadFontToHandle("游明朝 Demibold", 15, 9);
	Font[Font_ID::Yumincho_medium] = Resource::LoadFontToHandle("游明朝 Demibold", 12, 1);
	Font[Font_ID::Yumincho_mini] = Resource::LoadFontToHandle("游明朝 Demibold", 7, 1);

	return;
}

void Resource::Delete()
{
	int size = _handle.size();	// サイズ取得
	// 画像ハンドル一括削除
	for (int i = 0; i < size; i++)
	{
		DeleteGraph(_handle[i]);
	}
	// リスト開放
	_handle.clear();

	size = _sound.size();	// サイズ取得
	// 画像ハンドル一括削除
	for (int i = 0; i < size; i++)
	{
		DeleteGraph(_sound[i]);
	}
	// リスト開放
	_sound.clear();

	size = _font.size();	// サイズ取得
	// 画像ハンドル一括削除
	for (int i = 0; i < size; i++)
	{
		DeleteGraph(_font[i]);
	}
	// リスト開放
	_font.clear();

	return;
}

int Resource::LoadGraph(const char* FileName)
{
	// ロード
	int Handle = DxLib::LoadGraph(FileName);
	// リストに追加
	_handle.push_back(Handle);
	// 返却
	return Handle;
}

void Resource::LoadDivGraph(const char* FileName, int AllNum, int XNum, int YNum, int XSize, int YSize, int* HandleArray)
{
	// 分割読み込み
	DxLib::LoadDivGraph(FileName, AllNum, XNum, YNum, XSize, YSize, HandleArray);
	// リストに追加
	for (int i = 0; i < AllNum; i++)
	{
		if (HandleArray[i] == NULL) { continue; }
		_handle.push_back(HandleArray[i]);
	}
	return;
}

int Resource::LoadFontToHandle(const char* FontName, int size, int Thick)
{
	// ロード
	int Handle = DxLib::CreateFontToHandle(FontName, size, Thick);
	// リストに追加
	_font.push_back(Handle);
	// 返却
	return Handle;
}