#pragma once
#include "Item.h"
#include "Resident.h"

#define FOOD_CONSUME_PER			2		// ��l������̐H�Ə����

#define HUNGERRATE_MIN				0		// �ŏ��Q�엦
#define HUNGERRATE_MAX				300		// �ő�Q�엦

#define HUNGERRATE_SPEED			500		// �Q��̃X�s�[�h
#define HUNGERRATE_RECOVERYSPEED	10		// �Q��̉񕜃X�s�[�h

// ���z���̒��ۃN���X
class Building abstract
{
public:
	Building();
	Building(int PosX, int PosY);
	virtual ~Building();

public:
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// ������`�悷��
	void DrawBuilding();
	void DrawBuildingInfoWindow(const int PosX, const int PosY);
	// �����̃A�C�R����`�悷��
	void DrawBuildingIcon(const int PosX, const int PosY);
	// �����̏���`�悷��
	virtual void DrawBuildingInfo(const int PosX, const int PosY) = 0;
	void DrawResidentInfo(const int PosX, const int PosY);
	// ���z�R�X�g�𓾂�
	virtual int GetBuildCost() = 0;
	// ���W�̃|�C���^��Ԃ�
	int* GetChipPos() { return Pos; }
	// �摜�n���h����Ԃ�
	int GetGraphHandle() { return (Graph != nullptr) ? *Graph[IsOverride] : -1; }
	// �l���ɉ������ʂ̐H�Ə���ʂ�Ԃ�
	int GetResidents() { return Resident; }
	// �l���𑝂₷
	void AddResidents(const int Num) { Resident += Num; }
	// �H�Ə���ʂ𓾂�
	int FoodConsumptionUpdate();
	// �H�Ƃ̏����
	void ConsumeFoodProcess();
	// �H�Ƃ������
	void ConsumeFoods();
	// �L�����N�^�[�ƃA�C�e�������݂��邩�m�F����
	bool GetHasContents() { return (Residents->GetAllResident() > 0 && Items->GetAllItems() > 0); }
	
public:
	ItemList* Items;			// ���L�A�C�e��
	ResidentList* Residents;	// �L�����N�^�[�l��
	int Anger;					// �s���x
	int Tax;					// ��l������̐ŋ�
	int HungerRate;				// �Q�엦
	int FoodConsumption;		// �H�Ə����
	int Pos[2];					// ���W
	int Cost;					// ���������z����R�X�g
protected:
	// ���
	int* Graph[2];			// �摜�n���h���̃|�C���^
	const char* DisplayName;	// �����̖��O
	// ���
	int IsOverride;			// �������t���O
	int Resident;			// �l��
	int FoodRate;			// �H�Ƃ̔z����

};

// �X�@���͂̐l����������
// ���Ԍo�߂Ől����������@���g�̐��͂̃����_���Ȍ����ɏ�������
class Towny : public Building
{
public:
	Towny() = default;
	Towny(int PosX, int PosY) : Building(PosX, PosY) {}
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void DrawBuildingInfo(const int PosX, const int PosY) override;
	void IncreaseResidentsProcess();

protected:
	int IncreaseRate;	// �l��������

};

// ���Ǝ{�݁@���͂̂�����������
class Market : public Building
{
public:
	Market() = default;
	Market(int PosX, int PosY) : Building(PosX, PosY) {}
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void DrawBuildingInfo(const int PosX, const int PosY) override {}
};

// ��n�@���m���P��������̋��_�������Ŗh�q����
class Base : public Building
{
public:
	Base() = default;
	Base(int PosX, int PosY) : Building(PosX, PosY) {}
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void DrawBuildingInfo(const int PosX, const int PosY) override {}
};

// �Y�Ɓ@���ԂŃA�C�e���𐶎Y����
class Industries : public Building
{
public:
	Industries() = default;
	Industries(int PosX, int PosY) : Building(PosX, PosY) {}
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void DrawBuildingInfo(const int PosX, const int PosY) override;

protected:
	// �A�C�e�����Y����
	void ItemProduceProcess();
	// ���Y���̎Z�o
	int GetProductValue();

protected:
	// �X�e�[�^�X�n
	int PayRate;			// ����
	int EarningRate;		// ���Y����
	ItemList::Item_ID ProduceItem;	// ���Y����A�C�e����ID
	const char* ProductItemTitle;	// ���Y����A�C�e���̖��O
	int* ProductItemGraphP;	// ���Y����A�C�e���̉摜�n���h���̃|�C���^

};