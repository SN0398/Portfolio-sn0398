#pragma once
#include "DxLib.h"
#include "MyLib.h"
#include "Building.h"
#include "MapManager.h"
#include "WorldManager.h"
#include "BuildingManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "UnitMovement.h"

enum class InterfaceType
{
	ChipSelect,
	ActionSelector,
	Shopping,
	Inventory,
	Build,
	Demolition,
	dummy,
};

// ���ۃN���X
class UserInterface abstract
{
public:
	 UserInterface() = default;
	~UserInterface() = default;

public:
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// ��{�����֐��̃��b�p�[
	void UpdateProcess();
	// ��{�`��֐��̃��b�p�[
	void DrawProcess();

	// �����n
	// �I�𒆂̌����̏��X�V
	void GetSelectChipInfo();

	// �`��n
	// �I���`�b�v��`��
	void DrawSelectChip();
	// �E�B���h�E��\��
	void DrawWindow();
	// ���ԁA�������Ȃǂ�`�悷��
	void DrawWorldInfo();
	// �����̏���`�悷��
	void DrawBuildingInfo();
	// �A�C�e������`�悷��
	void DrawItemInfo();

public:
	static int SelectChip[2];
	static Building* SelectBuilding;	// �I�����W�ɂ��錚���ւ̃|�C���^�i���������݂��Ȃ����nullptr�j
	static bool ShowBuildingInfo;	// �����̏���\������t���O	�I�𒆂̃`�b�v���W�Ɍ����������true

};