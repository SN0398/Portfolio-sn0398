#include "../Utility.h"
#include <math.h>

// ����
float DotProduct(VECTOR pos1, VECTOR pos2)
{
	return pos1.x * pos2.x + pos1.y * pos2.y + pos1.z * pos2.z;
}

// �O��
VECTOR CrossProduct(VECTOR pos1, VECTOR pos2)
{
	VECTOR pos =
	{
		pos1.y * pos2.z - pos1.z * pos2.y,
		pos1.z * pos2.x - pos1.x * pos2.z,
		pos1.x * pos2.y - pos1.y * pos2.x,
	};
	return pos;
}

// �x�N�g���̑傫���𓾂�
float GetMagnitude(VECTOR pos)
{
	// ������
	return sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
}

// 3D�x�N�g���̐��K��
VECTOR Normalize_3D(VECTOR pos)
{
	// �x�N�g���̒����擾
	float Length = GetMagnitude(pos);
	// �x�N�g���̒������O�i�v�Z�s�\�Ȓl�j�Ȃ�v�Z�����ɔ�����
	if (Length <= 0.000001f) { return pos; }
	// ���U���g
	return VECTOR
	{
		pos.x / Length,
		pos.y / Length,
		pos.z / Length,
	};
}