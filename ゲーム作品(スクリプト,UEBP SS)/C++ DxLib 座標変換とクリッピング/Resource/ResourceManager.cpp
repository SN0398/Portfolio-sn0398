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

	DxLogo = Resource::LoadGraph("Assets/Data/Images/DxLogo.jpg");

	Font[Font_ID::Yumincho] =			Resource::LoadFontToHandle("������ Demibold", 15, 9);
	Font[Font_ID::HGSminchoE_Large] =	Resource::LoadFontToHandle("HGS����E", 64, 9);
	Font[Font_ID::HGSminchoE_Medium] = Resource::LoadFontToHandle("HGS����E", 16, 9);
	Font[Font_ID::HGSminchoE_Mini] =	Resource::LoadFontToHandle("HGS����E", 8, 9);

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

	size = _model.size();	// �T�C�Y�擾
	// �摜�n���h���ꊇ�폜
	for (int i = 0; i < size; i++)
	{
		MV1DeleteModel(_model[i]);
	}
	// ���X�g�J��
	_model.clear();

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

int Resource::LoadSoundMem(const char* FileName)
{
	// ���[�h
	int Handle = DxLib::LoadSoundMem(FileName);
	// ���X�g�ɒǉ�
	_sound.push_back(Handle);
	// �ԋp
	return Handle;
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

int Resource::LoadModel(const char* FileName)
{
	// ���[�h
	int Handle = DxLib::MV1LoadModel(FileName);
	// ���X�g�ɒǉ�
	_model.push_back(Handle);
	// �ԋp
	return Handle;
}