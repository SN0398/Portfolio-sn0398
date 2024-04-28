#pragma once
#include "DxLib.h"
#include "Utility.h"
#include "Bullet.h"

// �萔��` ---------------------------------------------------------------------------------------

#define DIRECTIONROTATIONSPEED	0.02f	// ��]��
#define ROTATIONATTENUATION		0.5f	// ��]���x������
#define SPEEDATTENUATION		0.1f	// ���R������
#define MAXSPEED				50.0f	// �ő呬�x
#define SPEEDACCELERATION		0.5f	// ������
#define SPEEDDECELERATION		0.3f	// ������
#define MAXFALLSPEED			30.0f	// �ő嗎�����x
#define FALLSPEEDACCELERATION	0.1f	// �������x������
#define LRSPEED					5.0f	// ���E�̃X�s�[�h

// �\���̒�` -------------------------------------------------------------------------------------

typedef struct _Player
{
	int ModelHandle;
	VECTOR position, move;
	float Speed;
	BulletData* bdata;

}Player;

// �֐��v���g�^�C�v�錾 ---------------------------------------------------------------------------

// �����E�j��
Player* PlayerInit();
void PlayerClean(Player* player);
// �v���C���[�����E�`��
void PlayerUpdate(Player* player);
void PlayerPositionUpdate(Player* player);
void PlayerMoveProcess(Player* player);
void PlayerRotationProcess(Player* player);
void DrawPlayer(Player* player);