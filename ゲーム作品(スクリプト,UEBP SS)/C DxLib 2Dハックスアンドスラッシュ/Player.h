#pragma once

#include "ResourceMgr.h"
#include "MapMgr.h"
#include "Object.h"

#define PLAYERGRAPHSIZEX	64
#define PLAYERGRAPHSIZEY	64
#define BULLETRADIUS		5
#define DEFAULTMAXHEALTH	200

// �\���̒�` -------------------------------------------------------------------------------------

struct Bullet
{
	float x;
	float y;
	float vecX;
	float vecY;
	float Speed;
	int State;

	Bullet* NextNode;
	Bullet* PrevNode;

};

typedef struct _Player
{
	float x;
	float y;
	float vecx;
	float vecy;
	float MoveSpeed;
	int DirectionX;
	int DirectionY;
	int Health;
	int Gold;

	Bullet* Head;

}Player;

// �֐��v���g�^�C�v�錾 ---------------------------------------------------------------------------

// �v���C���[�\���̊Ǘ��n�֐�
Player* CreatePlayer();	// �v���C���[�\���̍쐬
int PlayerUpdate(Player* player,int CollData[][MAPCHIPWIDTH], Data* data);	// �{����
void PlayerMoveProcess(Player* player, int CollData[][MAPCHIPWIDTH]);	// �ړ�����
void DrawPlayer(Player* player, Resource* resource);	// �v���C���[�`��
void DrawHealth(Player* player, Resource* resource);	// �̗͕`��
void ReleasePlayer(Player* player);	// �v���C���[�\���̉��

// Bullet�\���̃��X�g�Ǘ��n�֐�
Bullet* CreateBullet(Bullet* Head);	// �m�[�h�쐬
void InsertBullet(Bullet* Head, Bullet* Node);	// �m�[�h�}��
Bullet* DetachBullet(Bullet* Node);	// �w�肵���m�[�h��؂藣��
void ReleaseBullet(Bullet* Head);	// �m�[�h�S�J��

// Bullet�\���̊�{�����n�֐�
void BulletUpdate(Bullet* Head, Player* player, Data* data);	// ���C���֐�
Bullet* BulletMoveProcess(Bullet* Node, Player* player);	// �ړ�����
void GenerateBulletProcess(Bullet* Head, Player* player);	// ��������
void HitProcessBulletToEnemy(Player* player, Bullet* Node, Data* data);
void HitProcessPlayerToTreasureBox(Player* player, Data* data);
void DrawBullet(Bullet* Head, Player* player, Resource* resource);	// �`�揈��