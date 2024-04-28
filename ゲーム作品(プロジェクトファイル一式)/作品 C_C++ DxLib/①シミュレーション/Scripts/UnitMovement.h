#pragma once
#include <vector>
#include "Astar.h"
#include "MyLib.h"
#include "Item.h"
#include "Building.h"
#include "Singleton.h"
#include "Resident.h"

using namespace Astar;

#define UNITMOVESPEED_DEFAULT					300			// �f�t�H���g�̈ړ����x
#define UNITMOVESPEED_DECREASERATE_INVENTORY	0.435		// �A�C�e�����ɂ��ړ����x������
#define UNITMOVESPEED_DECREASERATE_RESIDENT		0.462		// �L�������ɂ��ړ����x������

#define UNITMOVEMENT_MAXCOUNT					100000.0f	// �ő�ړ��J�E���^

#define UNITMOVEMENT_CLAIM_DENIED_RESIDENT_IS_EMPTY		0
#define UNITMOVEMENT_CLAIM_SUCCESS						1

class UnitMovement : public Singleton<UnitMovement>
{
public:
	struct UnitData
	{
		float offsetX, offsetY;	// �ړ��I�t�Z�b�g
		int Count;				// �ړ��p�J�E���^
		Position NowPos;		// ���W
		vector<Node*> Route;	// �ړ��o�H
		ItemList Inventory;		// �A�C�e��
		ResidentList Residents;	// �L�����N�^�[
		int MoveSpeed;			// �ړ����x
	};

public:
	UnitMovement() {}
	~UnitMovement() {}

public:
	// �ړ��������̍X�V�֐�
	void Update();		
	// �ړ��������̕`��֐�
	void Draw();		
	// �E�B���h�E�Ɉړ��������̏��`��
	void DrawInfo();	
	// �ړ���������
	int Claim(Position start, Position goal, Building* base, ItemList* moveItems, ResidentList* moveResidents);

private:
	vector<UnitData*> dataList;

};