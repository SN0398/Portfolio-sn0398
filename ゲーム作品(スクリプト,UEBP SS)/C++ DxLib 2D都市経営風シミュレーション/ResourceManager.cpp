#include "ResourceManager.h"
#include "DxLib.h"

void Resource::Load()
{
	/// �n���h���ǂݍ��� ///
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

	Font[Font_ID::Yumincho] = Resource::LoadFontToHandle("������ Demibold", 15, 9);
	Font[Font_ID::Yumincho_medium] = Resource::LoadFontToHandle("������ Demibold", 12, 1);
	Font[Font_ID::Yumincho_mini] = Resource::LoadFontToHandle("������ Demibold", 7, 1);

	return;
}

void Resource::Delete()
{
	int size = _handle.size();	// �T�C�Y�擾
	// �摜�n���h���ꊇ�폜
	for (int i = 0; i < size; i++)
	{
		DeleteGraph(_handle[i]);
	}
	// ���X�g�J��
	_handle.clear();

	size = _sound.size();	// �T�C�Y�擾
	// �摜�n���h���ꊇ�폜
	for (int i = 0; i < size; i++)
	{
		DeleteGraph(_sound[i]);
	}
	// ���X�g�J��
	_sound.clear();

	size = _font.size();	// �T�C�Y�擾
	// �摜�n���h���ꊇ�폜
	for (int i = 0; i < size; i++)
	{
		DeleteGraph(_font[i]);
	}
	// ���X�g�J��
	_font.clear();

	return;
}

int Resource::LoadGraph(const char* FileName)
{
	// ���[�h
	int Handle = DxLib::LoadGraph(FileName);
	// ���X�g�ɒǉ�
	_handle.push_back(Handle);
	// �ԋp
	return Handle;
}

void Resource::LoadDivGraph(const char* FileName, int AllNum, int XNum, int YNum, int XSize, int YSize, int* HandleArray)
{
	// �����ǂݍ���
	DxLib::LoadDivGraph(FileName, AllNum, XNum, YNum, XSize, YSize, HandleArray);
	// ���X�g�ɒǉ�
	for (int i = 0; i < AllNum; i++)
	{
		if (HandleArray[i] == NULL) { continue; }
		_handle.push_back(HandleArray[i]);
	}
	return;
}

int Resource::LoadFontToHandle(const char* FontName, int size, int Thick)
{
	// ���[�h
	int Handle = DxLib::CreateFontToHandle(FontName, size, Thick);
	// ���X�g�ɒǉ�
	_font.push_back(Handle);
	// �ԋp
	return Handle;
}