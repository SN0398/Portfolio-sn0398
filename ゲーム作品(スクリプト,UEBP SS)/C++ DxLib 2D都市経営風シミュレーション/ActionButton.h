#pragma once
#include "MyLib.h"
#include "UserInterface.h"
#include <string>

class ActionButton
{
private:	
	// �t�@�N�g���[����Ȃ��R���X�g���N�^�͋֎~
	ActionButton() = default;
	ActionButton(std::string text) :
		DiaplayName(text) {}

public:
	~ActionButton() = default;

public:
	// �C���X�^���X�������\�b�h
	static ActionButton* Create(Vector2D Pos1, Vector2D Pos2, std::string text, int* graph, int index = 0);
	// GUI�`��
	void Draw();
	// �����蔻��X�V
	void HitStateUpdate(const Vector2D PointPos);
	// �����蔻��擾
	bool GetHitState() { return HitFlag; }

public:
	int* Icon_ptr;				// �摜�̃|�C���^
	std::string DiaplayName;	// ����
	Vector2D Pos1, Pos2;		// ��`�̎n�_�I�_
	int HitFlag;				// �_�Ƌ�`�̓����蔻��t���O	true = �������Ă���
	int Index;					// �C���f�b�N�X

};