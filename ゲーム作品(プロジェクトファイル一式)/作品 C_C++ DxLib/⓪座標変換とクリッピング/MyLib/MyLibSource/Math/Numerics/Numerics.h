#pragma once

namespace MyLib
{
	class Float3
	{
	public:
		Float3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		float x, y, z;
	};
	class Float4
	{
	public:
		Float4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
		float x, y, z, w;
	};
	class Float3x3
	{
	public:
		Float3x3
		(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22
		)
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;

			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;

			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
		}
		float m[3][3];
	};
	class Float4x4
	{
	public:
		Float4x4
		(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33
		)
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[0][3] = m03;

			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[1][3] = m13;

			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
			m[2][3] = m23;

			m[3][0] = m30;
			m[3][1] = m31;
			m[3][2] = m32;
			m[3][3] = m33;
		}
		float m[4][4];
	};
	class Float3x4
	{
	public:
		Float3x4
		(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23
		)
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[0][3] = m03;

			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[1][3] = m13;

			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
			m[2][3] = m23;
		}
		float m[3][4];
	};
	class Float4x3
	{
	public:
		Float4x3
		(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22,
			float m30, float m31, float m32
		)
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;

			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;

			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;

			m[3][0] = m30;
			m[3][1] = m31;
			m[3][2] = m32;
		}
		float m[4][3];
	};
}