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

// �摜�n���h�����̊Ǘ��N���X
class Resource : public Singleton<Resource>
{
public:	// �R���X�g���N�^�E�f�X�g���N�^
	Resource() = default;
	~Resource() = default;

public: // �n���h���̐����E�j��
	void Load();
	void Delete();

private:	// �ǂݍ���
	int LoadGraph(const char* FileName);
	void LoadDivGraph(const char* FileName, int AllNum, int XNum, int YNum, int XSize, int YSize, int* HandleArray);
	int LoadSoundMem(const char* FileName);
	int LoadFontToHandle(const char* FontName, int size, int Thick);
	int LoadModel(const char* FileName);

public:	// �n���h���i�[�p�ϐ�

	// �F�}�N��
	int Color[Color_ID::Color_Dummy];

	// �摜�n���h��
	int DxLogo;

	// �����n���h��

	// �t�H���g�n���h��
	int Font[Font_ID::Font_Dummy];

	// ���f���n���h��

private:
	vector<int> _handle;
	vector<int> _sound;
	vector<int> _font;
	vector<int> _model;

};