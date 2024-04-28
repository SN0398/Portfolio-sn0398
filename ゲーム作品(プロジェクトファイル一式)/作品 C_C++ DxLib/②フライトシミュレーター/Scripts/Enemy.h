#pragma once
#include "DxLib.h"
#include "Utility.h"
#include "Bullet.h"

// �萔��` ---------------------------------------------------------------------------------------

#define ENEMYMAXNUM		1		// �G�̍ő吔
#define DAMAGERADIUS	200.0f	// �_���[�W���󂯂�͈�

// �\���̒�` -------------------------------------------------------------------------------------

// �G�̏�Ԃ̘A��
typedef enum _EnemyState
{
	ES_OK = 0,		// ����(�A�N�e�B�u)
	ES_NOTOK,		// ��e
	ES_DEAD,		// ��A�N�e�B�u

}EnemyState;

// �G�̃p�����[�^���܂Ƃ߂��\����
typedef struct _Enemy
{
	int ModelHandle;	// ���f��
	int State;			// ���
	VECTOR position, move, rotation, direction;
	float Speed;	// �ړ����x
	VECTOR target;	// �ڕW�̈ʒu

}Enemy;

// ���ׂĂ̓G�̏����܂Ƃ߂��\����
typedef struct _EnemyList
{
	Enemy* enemy[ENEMYMAXNUM];	// �G�̍\���̔z��

}EnemyList;

// �֐��v���g�^�C�v�錾 ---------------------------------------------------------------------------

/// �����E�j�� ///

// �f�[�^����
EnemyList* EnemyInit();
// �f�[�^�j��
void EnemyClean(EnemyList* list);
// �f�[�^�m��
Enemy* CreateEnemy(VECTOR position);
// �f�[�^���
void ReleaseEnemy(Enemy* enemy);

/// �����E�`�� ///

// �G�̏����܂Ƃ߂��\���̂��X�V
void EnemyListUpdate(EnemyList* list, VECTOR TargetPosition, BulletData* bulletdata);
// �G�̍X�V
void EnemyUpdate(Enemy* enemy, VECTOR TargetPosition, BulletData* bulletdata);
// �e�ƓG�̓����蔻��
void CheckHitUpdate(Enemy* enemy, BulletData* bulletdata);
// �G�̕`��
void DrawEnemy(EnemyList* list);