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
	int LoadFontToHandle(const char* FontName, int size, int Thick);

public:	// �n���h���i�[�p�ϐ�

	int Color[Color_ID::Color_Dummy];

	// �摜�n���h��
	int DxLogo;
	int Title;
	int TitleStill;
	int Chip[LANDCHIP_NUM];
	// �����̉摜�n���h���@0 = override:false 1 = override:true
	int Farm[BUILDINGCHIP_DATA];
	int Factory[BUILDINGCHIP_DATA];
	int Village[BUILDINGCHIP_DATA];
	int Camp[BUILDINGCHIP_DATA];
	int CharacterIcon[4];
	int Starving;
	int Anger;
	int Coin;
	int Items[2];
	// �E�B���h�E�n
	int InfoWindow;
	int DialogueWindow;
	int MenuWindow;
	int MenuWindowFrame;
	int BuildingInfo;
	int BoxUI;
	int CircleUI;
	int Bar;

	// �����n���h��


	// �t�H���g�n���h��
	int Font[Font_ID::Font_Dummy];

private:
	vector<int> _handle;
	vector<int> _sound;
	vector<int> _font;

};