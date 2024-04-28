#include "../MyLib.h"
#include <math.h>

// �x�N�g���̑傫���𓾂�
float GetMagnitude3D(Vector3D pos)
{
	// ������
	return sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
}

// 3D�x�N�g���̐��K��
Vector3D Normalize_3D(Vector3D pos)
{
	// �x�N�g���̒����擾
	float Length = GetMagnitude3D(pos);
	// �x�N�g���̒������O�i�v�Z�s�\�Ȓl�j�Ȃ�v�Z�����ɔ�����
	if (Length <= 0.00001f) { return pos; }
	// ���U���g
	return Vector3D
	{
		pos.x / Length,
		pos.y / Length,
		pos.z / Length,
	};
}