#pragma once
#include "DxLib.h"
#include "Utility.h"

// �萔��` ---------------------------------------------------------------------------------------

#define BULLETSPEED				200.0f	// �e�̃X�s�[�h
#define BULLETMAXNUM			30		// �e�e�̍ő吔
#define SHOTINTERVAL			5		// �ˏo�Ԋu
#define SHOTDELETETIME			100		// �e�e���o����Ă��������܂ł̎���

// �\���̒�` -------------------------------------------------------------------------------------

typedef struct _Bullet
{
	int ModelHandle;
	VECTOR position, move, direction;
	bool Flag;
	int DeleteCount;

}Bullet;

typedef struct _BulletData
{
	int ShootCount;
	Bullet* bullet[BULLETMAXNUM];

}BulletData;

// �֐��v���g�^�C�v�錾 ---------------------------------------------------------------------------

/// �����E�j�� ///

// �e�\���̂̃f�[�^����
BulletData* BulletDataInit();
// �e�\���̂̃f�[�^�j��
void BulletDataClean(BulletData* bulletdata);
// �q�\���̂̃f�[�^����
Bullet* CreateBullet();
// �q�\���̂̃f�[�^�j��
void ReleaseBullet(Bullet* bullet);

/// �e�̏����E�`�� ///

// �e�̏����֐����b�p�[
void BulletUpdate(BulletData* bulletdata, int ModelHandle, VECTOR position);		
// �e�̏������E�A�N�e�B�u��
void GenerateBulletProcess(BulletData* bulletdata, int ModelHandle, VECTOR position);
// �e�̕`��
void DrawBullet(BulletData* bulletdata);