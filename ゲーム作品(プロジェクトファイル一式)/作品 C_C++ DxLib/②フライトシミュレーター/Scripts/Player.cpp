#include "Player.h"
#include <malloc.h>
#include "DxLib.h"
#include "Utility.h"
#include <math.h>

Player* PlayerInit()
{
	// �������m��
	Player* player = (Player*)malloc(sizeof(Player));
	// ���f���Ǎ�
	player->ModelHandle = MV1LoadModel("Data/Models/Player/A6M5_Model_52/A6M5_Model_52.mv1");

	// ������
	player->Speed = MAXSPEED;
	player->position = VGet(700.0f, 0.0f, 0.0f);
	player->move = VGet(0.0f, 0.0f, 0.0f);
	
	// �e�̏�����
	player->bdata = BulletDataInit();

	return player;
}

void PlayerClean(Player* player)
{
	// ���f���폜
	MV1DeleteModel(player->ModelHandle);
	// �������j��
	BulletDataClean(player->bdata);	// �e�̃������j��
	free(player);
	player = NULL;
	return;
}

void PlayerUpdate(Player* player)
{
	// ��������
	PlayerRotationProcess(player);

	// ���W����
	PlayerPositionUpdate(player);

	// �e�̏���
	BulletUpdate(player->bdata, player->ModelHandle, player->position);

	return;
}

void PlayerPositionUpdate(Player* player)
{
	// �ړ�����
	PlayerMoveProcess(player);
	// ���W�Ǘ�
	{
		// �C�ʂɐڐG������ʒu��߂�
		if (player->position.y <= -5500.0f)
		{
			player->position = VGet(700.0f, 0.0f, 0.0f);
		}
		// ���W���Ē[�ɂȂ�����X�s�[�h���O�ɂ���
		if (player->position.x > 100000 || player->position.x < -100000 ||
			player->position.z > 100000 || player->position.z < -100000)
		{
			player->Speed = 0;
		}
	}

	return;
}

void PlayerMoveProcess(Player* player)
{
	// �ړ�����
	{
		// �ړ��x�N�g��������
		player->move.x = 0;
		player->move.y = 0;
		// �����E��������
		{
			// �X�s�[�h�͖��t���[�����Z(�O�ȏ�)
			player->Speed = (player->Speed - SPEEDATTENUATION >= 0) ? player->Speed - SPEEDATTENUATION : 0;
			// W�L�[�ŉ���
			if (Keyboard_Get(KEY_INPUT_W) >= 1)
			{
				// MAXSPEED�ȉ��Ɏ��܂�悤�ɂ���
				player->Speed += (player->Speed + SPEEDACCELERATION <= MAXSPEED) ? SPEEDACCELERATION : 0;
			}
			// S�L�[�Ō���
			if (Keyboard_Get(KEY_INPUT_S) >= 1)
			{
				// 0�ȏ�Ɏ��܂�悤�ɂ���
				player->Speed -= (player->Speed - SPEEDDECELERATION >= 0) ? SPEEDDECELERATION : 0;
			}
			// AD�L�[�ō��E
			if (Keyboard_Get(KEY_INPUT_A) >= 1)
			{
				player->move.x += LRSPEED;
			}
			if (Keyboard_Get(KEY_INPUT_D) >= 1)
			{
				player->move.x -= LRSPEED;
			}
		}
		player->move.z = -player->Speed;
		// �ړ��x�N�g�� = �ړ��x�N�g�� * ���f���̉�]�s��
		player->move = VTransform(player->move, MV1GetRotationMatrix(player->ModelHandle));
		// �������x�Z�o
		float FallSpeed = MAXFALLSPEED - player->Speed;
		FallSpeed = (FallSpeed < 0) ? 0 : -FallSpeed;
		// �ړ��x�N�g�����K��
		player->move = Normalize_3D(player->move);
		// �X�s�[�h��Z
		player->move.x *= player->Speed;
		player->move.y *= player->Speed;
		player->move.z *= player->Speed;
		// �ړ��x�N�g������
		player->position.x += player->move.x;
		player->position.y += player->move.y + FallSpeed;
		player->position.z += player->move.z;
		// ���W�ݒ�
		MV1SetPosition(player->ModelHandle, player->position);
	}

	return;
}
;
void PlayerRotationProcess(Player* player)
{
	// ��������
	{
		// ��]��������
		float rotX = 0.0f;
		float rotZ = 0.0f;
		// �����L�[����
		if (Keyboard_Get(KEY_INPUT_NUMPAD8) >= 1)	// NUM8�L�[
		{
			rotX -= DIRECTIONROTATIONSPEED;
		}
		if (Keyboard_Get(KEY_INPUT_NUMPAD5) >= 1)	// NUM5�L�[
		{
			rotX += DIRECTIONROTATIONSPEED;
		}
		if (Keyboard_Get(KEY_INPUT_NUMPAD4) >= 1)	// NUM4�L�[
		{
			rotZ -= DIRECTIONROTATIONSPEED;
		}
		if (Keyboard_Get(KEY_INPUT_NUMPAD6) >= 1)	// NUM6�L�[
		{
			rotZ += DIRECTIONROTATIONSPEED;
		}
		// ��]�s��擾
		MATRIX rx = MGetRotX(rotX);	// X����]
		MATRIX rz = MGetRotZ(rotZ);	// Z����]
		// ��]�s��(x * z)
		MATRIX rot = MMult(rx, rz);
		// ��]�s�� = ��]�s�� * ���[���h�ϊ��s��
		rot = MMult(rot, MV1GetMatrix(player->ModelHandle));
		// ��]�s��Z�b�g
		MV1SetRotationMatrix(player->ModelHandle, rot);
	}

	return;
}

void DrawPlayer(Player* player)
{
	// �v���C���[���f���̕`��
	MV1DrawModel(player->ModelHandle);
	//�e�̕`��
	DrawBullet(player->bdata);

	return;
}