#include "Camera.h"
#include "DxLib.h"
#include <math.h>
#include "Utility.h"

void CameraUpdate(Player* player)
{
	//VECTOR target = player->position;
	//target.y += 100;
	//VECTOR position = player->position;
	//position.z += 500;

	//SetCameraPositionAndTarget_UpVecY(position, target);

	// �����_�A �ʒu�A �J��������W
	VECTOR target, position, up;
	// ���f��������]�s����擾
	MATRIX rotmat = MV1GetRotationMatrix(player->ModelHandle);
	// �����_
	{
		target = player->position;	// ��Ƀv���C���[������
	}
	// �ʒu
	{
		position = player->position;					// �v���C���[���W
		VECTOR rotation;
		if (!Keyboard_Get(KEY_INPUT_C))					// �@�̂�z500��O(C����������Ă�����500��)
		{
			rotation = VGet(0.0f, 0.0f, 500.0f);
		}
		else
		{
			rotation = VGet(0.0f, 0.0f, -500.0f);
		}
		rotation = VTransform(rotation, rotmat);		// �v���C���[�̉�]�s��ŉ�]������
		position = VAdd(position, rotation);			// �ʒu�ɉ�]�������W�����Z
	}
	// �J��������W
	{
		// �J�����̏�����͋@�̂������Ɍ�����悤��
		up = VGet(0.0f, 1.0f, 0.0f);
		// �J�����̏�������@�̂̌X���ɍ��킹�ĕύX����
		up = VTransform(up, rotmat);
	}
	// �J�����ݒ�K�p
	SetCameraPositionAndTargetAndUpVec(position, target, up);

	return;
}