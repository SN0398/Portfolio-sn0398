#pragma once

#include "ResourceMgr.h"
#include "MapMgr.h"

#define ENEMYMAXNUM	20
#define ENEMYGRAPHSIZEX	64
#define ENEMYGRAPHSIZEY	64
#define ENEMYMAXTYPENUM	2
#define ENEMYRESPAWNINTERVAL	700

#define TREASUREGRAPHSIZEX	64
#define TREASUREGRAPHSIZEY	64

typedef enum _ObjectType
{
	OT_NONE = 0,
	OT_GOLD,
	OT_ENEMY,
	OT_TREASURE,

}ObjectType;

typedef enum _EnemyState
{
	ES_IDLE = 0,
	ES_CHASE,
	ES_ATTACK,
	ES_INDEATH,
	ES_DEAD,
	ES_NUMSTATE,

}EnemyState;

typedef enum _ObjectState
{
	OS_IDLE = 0,
	OS_INOPEN,
	OS_OPEN,
	OS_OPENED,

}ObjectState;

typedef struct _Object
{
	// �������W
	int SpawnPointX;
	int SpawnPointY;
	// ���݂̍��W
	float X;			
	float Y;
	// �ړ�����
	float vecX;
	float vecY;
	// �ړ����x
	float MoveSpeed;
	// �I�u�W�F�N�g��ނ̃C���f�b�N�X
	int objecttype;
	// �U����
	int Attack;
	// �U���̊Ԋu
	int AttackDelay;
	// �U���̃J�E���^
	int CoolDownCount;
	// ���X�|�[���܂ł̎���
	int RespawnInterval;
	// ���
	int state;
	// �A�j���[�V�����n
	int AnimIndex;
	int AnimCount;
	int AnimSpeed;

	// �A���\��
	_Object* NextNode;
	_Object* PrevNode;

}Object;

// �I�u�W�F�N�g�Ǘ��\����
typedef struct _Data
{
	Object* enemy[ENEMYMAXNUM];
	Object* head;

}Data;

/// �֐� ///

// �쐻�E�j��
Data* CreateData();
void ReleaseData(Data* data);

// �I�u�W�F�N�g
// �쐻�E�j��
Object* CreateObject();	// �I�u�W�F�N�g�̊m��
void ReleaseObject(Object* object);	// �I�u�W�F�N�g�̉��
void GenerateEnemy(Object* object);	// �G�̐���
void GenerateTreasureBox(Object* head, int ObjectX, int ObjectY, int objecttype);

// �o�����z���X�g�̃I�u�W�F�N�g�Ǘ��n�֐�
Object* CreateObjectNode();	// �m�[�h�쐬
void InsertObject(Object* Head, Object* Node);	// �m�[�h�}��
Object* DetachObject(Object* Node);	// �w�肵���m�[�h��؂藣��
void ReleaseObjectList(Object* Head);	// �m�[�h�S�J��

// ��{�����n
void ObjectUpdate(Data* data, int PlayerX, int PlayerY, int* PlayerHealth);	// ���C���֐�
void AnimationInitialize(int* AnimIndex, int* AnimCount, int* AnimSpeed, const int AnimDelay);	// �A�j���[�V����������
int AnimationUpdate(int* AnimIndex, int* AnimCount, const int AnimSpeed, const int AnimNum);	// �A�j���[�V��������
void DrawObject(Data* data, Resource* resource, int PlayerX, int PlayerY);	// �����`��
void DrawEnemy(Data* data, Resource* resource, int PlayerX, int PlayerY);	// �G�̕`��
void DrawObjectList(Data* data, Resource* resource, int PlayerX, int PlayerY);	// �I�u�W�F�N�g�`��

// ��ԕʏ����֐�
void EnemyIdleProcess(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth);
void EnemyChaseProcess(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth);
void EnemyAttackProcess(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth);
void EnemyInDeathProcess(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth);
void EnemyDeadProcess(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth);

// ��ԕʏ����̊֐��|�C���^
static void (*StateFunction[ES_NUMSTATE])(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth) =
{
	EnemyIdleProcess,
	EnemyChaseProcess,
	EnemyAttackProcess,
	EnemyInDeathProcess,
	EnemyDeadProcess,
};