#pragma once
#include <cmath>
#include "DxLib.h"

#include "MyLibSource/Geometry/Vector/Vector.h"
#include "MyLibSource/Geometry/Matrix/Matrix.h"

class Transform
{
public:
	void Rotate(const float& xAngle, const float& yAngle, const float& zAngle);

public:
	Matrix ToMatrix() const;

	Vector GetWorldLocation()
	{
		Vector result = location;
		Transform* _parent = parent;
		while (_parent)
		{
			result = result + _parent->location;
			_parent = _parent->parent;
		}
	}

public:
	Euler   rotation;	// ��]
	Vector  location;	// ���W
	Vector  scale;		// �g��k��

	Transform* parent;

};

// ���x�N�g��
// V * M
Vector4f Vector4Transform(const Vector4f& v, const Matrix& m);
// �c�x�N�g��
// M * V
Vector4f Vector4Transform(const Matrix& m, const Vector4f& v);
