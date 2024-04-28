//#include "Vector.h"
//#include "Matrix.h"
//#include "Quaternion.h"
//
//Vector::Vector(const Matrix& m)
//{
//	*this = m.GetLocation();
//}
//
//Vector Vector::operator=(const Vector& vec)
//{
//	return Vector(x = vec.x, y = vec.y, z = vec.z);
//
//}
//
//Vector Vector::operator+(const Vector& vec)
//{
//	return Vector(x + vec.x, y + vec.y, z + vec.z);
//}
//
//Vector Vector::operator-(const Vector& vec)
//{
//	return Vector(x - vec.x, y - vec.y, z - vec.z);
//}
//
//Vector Vector::operator*(const Vector& vec)
//{
//	return Vector(x * vec.x, y * vec.y, z * vec.z);
//}
//
//Vector Vector::operator*(const float& multiply)
//{
//	return Vector(x * multiply, y * multiply, z * multiply);
//}
//
//Matrix Vector::ToMatrix() const
//{
//	return Matrix();
//}
//
//Matrix Vector::ToRotationMatrix() const
//{
//	return Matrix();
//}
//
//Quaternion Vector::ToQuaternion() const
//{
//	float sx = sin(x / 2.0f);
//	float sy = sin(y / 2.0f);
//	float sz = sin(z / 2.0f);
//
//	float cx = cos(x / 2.0f);
//	float cy = cos(y / 2.0f);
//	float cz = cos(z / 2.0f);
//
//	return Quaternion
//	{
//		sx * cy * cz + cx * sy * sz,	// y
//		cx * sy * cz - sx * cy * sz,	// z
//		cx * cy * sz + sx * sy * cz,	// w
//		cx * cy * cz - sx * sy * sz,	// x
//	};
//	/*
//	w = cx * cy * cz + sx * sy * sz
//	i = sx * cy * cz - cx * sy * sz
//	j = cx * sy * cz + sx * cy * sz
//	k = cx * cy * sz - sx * sy * cz
//	*/
//}
//
//void Vector::MakeVectorFromMatrix(const Matrix& m)
//{
//}
//
//void Vector::MakeEulerFromMatrix(const Matrix& m)
//{
//}
//
//void Vector::MakeEulerFromQuaternion(const Quaternion& q)
//{
//}
//
//void Vector::Normalize()
//{
//}
