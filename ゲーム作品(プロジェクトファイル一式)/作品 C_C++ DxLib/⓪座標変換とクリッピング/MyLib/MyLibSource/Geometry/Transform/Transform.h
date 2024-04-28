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
	Euler   rotation;	// 回転
	Vector  location;	// 座標
	Vector  scale;		// 拡大縮小

	Transform* parent;

};

// 横ベクトル
// V * M
Vector4f Vector4Transform(const Vector4f& v, const Matrix& m);
// 縦ベクトル
// M * V
Vector4f Vector4Transform(const Matrix& m, const Vector4f& v);
