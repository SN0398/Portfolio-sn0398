#pragma once

#include "MyLibSource/Geometry/Matrix/Matrix.h"

#include "DxLib.h"

#include <math.h>

class Quaternion;
class Matrix;

// 三次元ベクトルクラス
class Vector
{
public:	// Constructor / Destructor
	Vector() = default;
	Vector(float _x, float _y, float _z) :
		x(_x), y(_y), z(_z) {}
	Vector(const Vector& v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}
	Vector(const Matrix& m)
	{
		*this = m.GetLocation();
	}

public: // operator override
	Vector operator=(const Vector& vec)
	{
		return Vector(x = vec.x, y = vec.y, z = vec.z);
	}
	Vector operator+(const Vector& vec)
	{
		return Vector(x + vec.x, y + vec.y, z + vec.z);
	}
	Vector operator-(const Vector& vec)
	{
		return Vector(x - vec.x, y - vec.y, z - vec.z);
	}
	Vector operator*(const Vector& vec)
	{
		return Vector(x * vec.x, y * vec.y, z * vec.z);
	}
	Vector operator*(const float& multiply)
	{
		return Vector(x * multiply, y * multiply, z * multiply);
	}
	Vector operator*=(const float& multiply)
	{
		*this = Vector(x * multiply, y * multiply, z * multiply);
		return *this;
	}

	void Normalize()
	{
		const float square = x * x + y * y + z * z;
		if (square > 1.e-8f)
		{
			const float scale = sqrt(square);
			x /= scale;
			y /= scale;
			z /= scale;
			return;
		}
		return;
	}

	float Dot(const Vector v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	void Cross(const Vector v)
	{
		x = y * v.z - z * v.y;
		y = z * v.x - x * v.z;
		z = x * v.y - y * v.x;
	}

public: // getter function
	Vector Normalized() const
	{
		Vector Result(*this);
		Result.Normalize();
		return Result;
	}

public:	// static function
	static Vector DegreeToRadian(Vector v)
	{
		return Euler
		(
			v.x * (DX_PI_F / 180.f),
			v.y * (DX_PI_F / 180.f),
			v.z * (DX_PI_F / 180.f)
		);
	}
	static Vector RadianToDegree(Vector v)
	{
		return Euler
		(
			v.x * (180.0f / DX_PI_F),
			v.y * (180.0f / DX_PI_F),
			v.z * (180.0f / DX_PI_F)
		);
	}

	static float Length(const Vector& v)
	{
		return pow((v.x * v.x) + (v.y * v.y) + (v.z * v.z), 0.5f);
	}

	static float Dot(const Vector& v1, const Vector& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	static Vector Cross(const Vector& v1, const Vector& v2)
	{
		return Vector
		(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		);
	}

	static float Angle(const Vector& v1, const Vector& v2)
	{
		float len1 = Length(v1);
		float len2 = Length(v2);

		float cs = Dot(v1, v2) / (len1 * len2);

		float result = acos(cs);

		return result;
	}

public:
	float x, y, z;
};

using Euler = Vector;

class Vector2f
{
public:
	Vector2f() = default;
	Vector2f(float x, float y) : x(x), y(y) {}
public:
	float x, y;
};

class Vector4f
{
public:
	Vector4f() = default;
	Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Vector4f(Vector v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}
public:
	float x, y, z, w;
};