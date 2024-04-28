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

	DxLogo = Resource::LoadGraph("Assets/Data/Images/DxLogo.jpg");

	Font[Font_ID::Yumincho] =			Resource::LoadFontToHandle("游明朝 Demibold", 15, 9);
	Font[Font_ID::HGSminchoE_Large] =	Resource::LoadFontToHandle("HGS明朝E", 64, 9);
	Font[Font_ID::HGSminchoE_Medium] = Resource::LoadFontToHandle("HGS明朝E", 16, 9);
	Font[Font_ID::HGSminchoE_Mini] =	Resource::LoadFontToHandle("HGS明朝E", 8, 9);

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

	size = _model.size();	// サイズ取得
	// 画像ハンドル一括削除
	for (int i = 0; i < size; i++)
	{
		MV1DeleteModel(_model[i]);
	}
	// リスト開放
	_model.clear();

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

int Resource::LoadSoundMem(const char* FileName)
{
	// ロード
	int Handle = DxLib::LoadSoundMem(FileName);
	// リストに追加
	_sound.push_back(Handle);
	// 返却
	return Handle;
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

int Resource::LoadModel(const char* FileName)
{
	// ロード
	int Handle = DxLib::MV1LoadModel(FileName);
	// リストに追加
	_model.push_back(Handle);
	// 返却
	return Handle;
}