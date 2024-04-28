#include "../MyLib.h"
#include <math.h>

// �w�肵��2D�x�N�g���𓾂�
Vector2D GetVec2D(float X, float Y)
{
	return Vector2D{ X,Y };
}

// ���2D�x�N�g������������2D�x�N�g���𓾂�
Vector2D AddVec2D(Vector2D VecA, Vector2D VecB)
{
	return Vector2D{ VecA.x + VecB.x, VecA.y + VecB.y };
}

// ���2D�x�N�g�������Z����2D�x�N�g���𓾂�
Vector2D SubVec2D(Vector2D VecA, Vector2D VecB)
{
	return Vector2D{ VecA.x - VecB.x, VecA.y - VecB.y };
}

// 2D�x�N�g������Z�����x�N�g���𓾂�
Vector2D MulVec2D(Vector2D Vec, float mult)
{
	return Vector2D{ Vec.x * mult, Vec.y * mult };
}

// ��`���m�̓����蔻��
int CheckHitBoxToBox2D(Vector2D StartPosA, Vector2D EndPosA, Vector2D StartPosB, Vector2D EndPosB)
{
	return ((StartPosA.x > StartPosB.x && StartPosA.x < EndPosB.x) ||
		(StartPosB.x > StartPosA.x && StartPosB.x < EndPosA.x)) &&
		((StartPosA.y > StartPosB.y && StartPosA.y < EndPosB.y) ||
			(StartPosB.y > StartPosA.y && StartPosB.y < EndPosA.y));
}

// ��`�Ɠ_�Ƃ̓����蔻��
int CheckHitBoxToPoint2D(Vector2D StartPos, Vector2D EndPos, Vector2D pos)
{
	return (pos.y >= StartPos.y && pos.y <= EndPos.y &&
		pos.x >= StartPos.x && pos.x <= EndPos.x);
}

// 2D�x�N�g���̐��K��
Vector2D Normalize_2D(Vector2D pos)
{
	float X = pos.x;
	float Y = pos.y;
	float L = sqrt(X * X + Y * Y);

	if (L <= 0.00001f) { return pos; }

	X /= L;
	Y /= L;
	
	return Vector2D{ X,Y };
}

// �����x�N�g���𓾂�
Vector2D GetDirection(Vector2D pos, Vector2D target)
{
	return Vector2D
	{
		target.x - pos.x,
		target.y - pos.y
	};
}

// 2�_�Ԃ̋������擾����
float GetDistance_2D(Vector2D pos1, Vector2D pos2)
{
	// �����x�N�g��
	double x = pos1.x - pos2.x;
	double y = pos1.y - pos2.y;
	// �x�N�g���̑傫�������߂�
	return sqrt(x * x + y * y);
}

// 2D�x�N�g���̑傫���𓾂�
float GetMagniture2D(float x, float y)
{
	return sqrt(x * x + y * y);
}

// �\���L�[�ł�2D�ړ��x�N�g������
void MoveProcess(Vector2D* pos, double MoveSpeed)
{
	// 1�t���[���̈ړ��x�N�g��
	float VecX = 0;
	float VecY = 0;

	// �E�ړ�
	if (Keyboard_Get(KEY_INPUT_RIGHT) >= 1 || Keyboard_Get(KEY_INPUT_D) >= 1)
	{
		VecX += 1;
	}
	// ���ړ�
	if (Keyboard_Get(KEY_INPUT_LEFT) >= 1 || Keyboard_Get(KEY_INPUT_A) >= 1)
	{
		VecX -= 1;
	}
	// ���ړ�
	if (Keyboard_Get(KEY_INPUT_DOWN) >= 1 || Keyboard_Get(KEY_INPUT_S) >= 1)
	{
		VecY += 1;
	}
	// ��ړ�
	if (Keyboard_Get(KEY_INPUT_UP) >= 1 || Keyboard_Get(KEY_INPUT_W) >= 1)
	{
		VecY -= 1;
	}
	// �ړ��x�N�g���̐��K��
	Vector2D move = Normalize_2D(GetVec2D(VecX, VecY));
	// ���W�Ɉړ��x�N�g��*���x�����Z�������
	*pos = AddVec2D(*pos, MulVec2D(move, MoveSpeed));

	return;
}