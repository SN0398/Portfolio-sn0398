#include "MyLibSource/Geometry/Vector/Vector.h"
#include "MyLibSource/Geometry/Matrix/Matrix.h"

//#define COLUMN_MAJOR_ORDER
#define ROW_MAJOR_ORDER

Matrix::Matrix(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
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

Matrix::Matrix(const Matrix& m)
{
	this->m[0][0] = m.m[0][0];
	this->m[0][1] = m.m[0][1];
	this->m[0][2] = m.m[0][2];
	this->m[0][3] = m.m[0][3];

	this->m[1][0] = m.m[1][0];
	this->m[1][1] = m.m[1][1];
	this->m[1][2] = m.m[1][2];
	this->m[1][3] = m.m[1][3];

	this->m[2][0] = m.m[2][0];
	this->m[2][1] = m.m[2][1];
	this->m[2][2] = m.m[2][2];
	this->m[2][3] = m.m[2][3];

	this->m[3][0] = m.m[3][0];
	this->m[3][1] = m.m[3][1];
	this->m[3][2] = m.m[3][2];
	this->m[3][3] = m.m[3][3];
}

Matrix Matrix::operator=(const Matrix& mat)
{
	m[0][0] = mat.m[0][0];
	m[0][1] = mat.m[0][1];
	m[0][2] = mat.m[0][2];
	m[0][3] = mat.m[0][3];

	m[1][0] = mat.m[1][0];
	m[1][1] = mat.m[1][1];
	m[1][2] = mat.m[1][2];
	m[1][3] = mat.m[1][3];

	m[2][0] = mat.m[2][0];
	m[2][1] = mat.m[2][1];
	m[2][2] = mat.m[2][2];
	m[2][3] = mat.m[2][3];

	m[3][0] = mat.m[3][0];
	m[3][1] = mat.m[3][1];
	m[3][2] = mat.m[3][2];
	m[3][3] = mat.m[3][3];
	return *this;
}

Matrix Matrix::operator+(const Matrix& mat)
{
	Matrix result;

	result.m[0][0] = m[0][0] + mat.m[0][0];
	result.m[0][1] = m[0][1] + mat.m[0][1];
	result.m[0][2] = m[0][2] + mat.m[0][2];
	result.m[0][3] = m[0][3] + mat.m[0][3];

	result.m[1][0] = m[1][0] + mat.m[1][0];
	result.m[1][1] = m[1][1] + mat.m[1][1];
	result.m[1][2] = m[1][2] + mat.m[1][2];
	result.m[1][3] = m[1][3] + mat.m[1][3];

	result.m[2][0] = m[2][0] + mat.m[2][0];
	result.m[2][1] = m[2][1] + mat.m[2][1];
	result.m[2][2] = m[2][2] + mat.m[2][2];
	result.m[2][3] = m[2][3] + mat.m[2][3];

	result.m[3][0] = m[3][0] + mat.m[3][0];
	result.m[3][1] = m[3][1] + mat.m[3][1];
	result.m[3][2] = m[3][2] + mat.m[3][2];
	result.m[3][3] = m[3][3] + mat.m[3][3];

	return result;
}

Matrix Matrix::operator-(const Matrix& mat)
{
	Matrix result;

	result.m[0][0] = m[0][0] - mat.m[0][0];
	result.m[0][1] = m[0][1] - mat.m[0][1];
	result.m[0][2] = m[0][2] - mat.m[0][2];
	result.m[0][3] = m[0][3] - mat.m[0][3];

	result.m[1][0] = m[1][0] - mat.m[1][0];
	result.m[1][1] = m[1][1] - mat.m[1][1];
	result.m[1][2] = m[1][2] - mat.m[1][2];
	result.m[1][3] = m[1][3] - mat.m[1][3];

	result.m[2][0] = m[2][0] - mat.m[2][0];
	result.m[2][1] = m[2][1] - mat.m[2][1];
	result.m[2][2] = m[2][2] - mat.m[2][2];
	result.m[2][3] = m[2][3] - mat.m[2][3];

	result.m[3][0] = m[3][0] - mat.m[3][0];
	result.m[3][1] = m[3][1] - mat.m[3][1];
	result.m[3][2] = m[3][2] - mat.m[3][2];
	result.m[3][3] = m[3][3] - mat.m[3][3];

	return result;
}

Matrix Matrix::operator*(const Matrix& mat)
{
	Matrix Result;

#ifdef ROW_MAJOR_ORDER
	// çsóDêÊ
	Result.m[0][0] = m[0][0] * mat.m[0][0] + m[0][1] * mat.m[1][0] + m[0][2] * mat.m[2][0] + m[0][3] * mat.m[3][0];
	Result.m[0][1] = m[0][0] * mat.m[0][1] + m[0][1] * mat.m[1][1] + m[0][2] * mat.m[2][1] + m[0][3] * mat.m[3][1];
	Result.m[0][2] = m[0][0] * mat.m[0][2] + m[0][1] * mat.m[1][2] + m[0][2] * mat.m[2][2] + m[0][3] * mat.m[3][2];
	Result.m[0][3] = m[0][0] * mat.m[0][3] + m[0][1] * mat.m[1][3] + m[0][2] * mat.m[2][3] + m[0][3] * mat.m[3][3];

	Result.m[1][0] = m[1][0] * mat.m[0][0] + m[1][1] * mat.m[1][0] + m[1][2] * mat.m[2][0] + m[1][3] * mat.m[3][0];
	Result.m[1][1] = m[1][0] * mat.m[0][1] + m[1][1] * mat.m[1][1] + m[1][2] * mat.m[2][1] + m[1][3] * mat.m[3][1];
	Result.m[1][2] = m[1][0] * mat.m[0][2] + m[1][1] * mat.m[1][2] + m[1][2] * mat.m[2][2] + m[1][3] * mat.m[3][2];
	Result.m[1][3] = m[1][0] * mat.m[0][3] + m[1][1] * mat.m[1][3] + m[1][2] * mat.m[2][3] + m[1][3] * mat.m[3][3];

	Result.m[2][0] = m[2][0] * mat.m[0][0] + m[2][1] * mat.m[1][0] + m[2][2] * mat.m[2][0] + m[2][3] * mat.m[3][0];
	Result.m[2][1] = m[2][0] * mat.m[0][1] + m[2][1] * mat.m[1][1] + m[2][2] * mat.m[2][1] + m[2][3] * mat.m[3][1];
	Result.m[2][2] = m[2][0] * mat.m[0][2] + m[2][1] * mat.m[1][2] + m[2][2] * mat.m[2][2] + m[2][3] * mat.m[3][2];
	Result.m[2][3] = m[2][0] * mat.m[0][3] + m[2][1] * mat.m[1][3] + m[2][2] * mat.m[2][3] + m[2][3] * mat.m[3][3];

	Result.m[3][0] = m[3][0] * mat.m[0][0] + m[3][1] * mat.m[1][0] + m[3][2] * mat.m[2][0] + m[3][3] * mat.m[3][0];
	Result.m[3][1] = m[3][0] * mat.m[0][1] + m[3][1] * mat.m[1][1] + m[3][2] * mat.m[2][1] + m[3][3] * mat.m[3][1];
	Result.m[3][2] = m[3][0] * mat.m[0][2] + m[3][1] * mat.m[1][2] + m[3][2] * mat.m[2][2] + m[3][3] * mat.m[3][2];
	Result.m[3][3] = m[3][0] * mat.m[0][3] + m[3][1] * mat.m[1][3] + m[3][2] * mat.m[2][3] + m[3][3] * mat.m[3][3];

#endif // ROW_MAJOR_ORDER

#ifdef COLUMN_MAJOR_ORDER
	// óÒóDêÊ
	Result.m[0][0] = m[0][0] * mat.m[0][0] + m[1][0] * mat.m[0][1] + m[2][0] * mat.m[0][2] + m[3][0] * mat.m[0][3];
	Result.m[0][1] = m[0][0] * mat.m[1][0] + m[1][0] * mat.m[1][1] + m[2][0] * mat.m[1][2] + m[3][0] * mat.m[1][3];
	Result.m[0][2] = m[0][0] * mat.m[2][0] + m[1][0] * mat.m[2][1] + m[2][0] * mat.m[2][2] + m[3][0] * mat.m[2][3];
	Result.m[0][3] = m[0][0] * mat.m[3][0] + m[1][0] * mat.m[3][1] + m[2][0] * mat.m[3][2] + m[3][0] * mat.m[3][3];

	Result.m[1][0] = m[0][1] * mat.m[0][0] + m[1][1] * mat.m[0][1] + m[2][1] * mat.m[0][2] + m[3][1] * mat.m[0][3];
	Result.m[1][1] = m[0][1] * mat.m[1][0] + m[1][1] * mat.m[1][1] + m[2][1] * mat.m[1][2] + m[3][1] * mat.m[1][3];
	Result.m[1][2] = m[0][1] * mat.m[2][0] + m[1][1] * mat.m[2][1] + m[2][1] * mat.m[2][2] + m[3][1] * mat.m[2][3];
	Result.m[1][3] = m[0][1] * mat.m[3][0] + m[1][1] * mat.m[3][1] + m[2][1] * mat.m[3][2] + m[3][1] * mat.m[3][3];

	Result.m[2][0] = m[0][2] * mat.m[0][0] + m[1][2] * mat.m[0][1] + m[2][2] * mat.m[0][2] + m[3][2] * mat.m[0][3];
	Result.m[2][1] = m[0][2] * mat.m[1][0] + m[1][2] * mat.m[1][1] + m[2][2] * mat.m[1][2] + m[3][2] * mat.m[1][3];
	Result.m[2][2] = m[0][2] * mat.m[2][0] + m[1][2] * mat.m[2][1] + m[2][2] * mat.m[2][2] + m[3][2] * mat.m[2][3];
	Result.m[2][3] = m[0][2] * mat.m[3][0] + m[1][2] * mat.m[3][1] + m[2][2] * mat.m[3][2] + m[3][2] * mat.m[3][3];

	Result.m[3][0] = m[0][3] * mat.m[0][0] + m[1][3] * mat.m[0][1] + m[2][3] * mat.m[0][2] + m[3][3] * mat.m[0][3];
	Result.m[3][1] = m[0][3] * mat.m[1][0] + m[1][3] * mat.m[1][1] + m[2][3] * mat.m[1][2] + m[3][3] * mat.m[1][3];
	Result.m[3][2] = m[0][3] * mat.m[2][0] + m[1][3] * mat.m[2][1] + m[2][3] * mat.m[2][2] + m[3][3] * mat.m[2][3];
	Result.m[3][3] = m[0][3] * mat.m[3][0] + m[1][3] * mat.m[3][1] + m[2][3] * mat.m[3][2] + m[3][3] * mat.m[3][3];

#endif // COLUMN_MAJOR_ORDER

	return Result;
}

Matrix Matrix::operator*=(const Matrix& mat)
{
	return *this = *this * mat;
}

Matrix Matrix::operator*(const float& multiply)
{
	// ÉXÉPÅ[ÉäÉìÉO
	Matrix Result;

	Result.m[0][0] *= multiply;
	Result.m[0][1] *= multiply;
	Result.m[0][2] *= multiply;
	Result.m[0][3] *= multiply;

	Result.m[1][0] *= multiply;
	Result.m[1][1] *= multiply;
	Result.m[1][2] *= multiply;
	Result.m[1][3] *= multiply;

	Result.m[2][0] *= multiply;
	Result.m[2][1] *= multiply;
	Result.m[2][2] *= multiply;
	Result.m[2][3] *= multiply;

	Result.m[3][0] *= multiply;
	Result.m[3][1] *= multiply;
	Result.m[3][2] *= multiply;
	Result.m[3][3] *= multiply;

	return Result;
}

Matrix Matrix::operator*=(const float& multiply)
{
	return *this = *this * multiply;
}

Vector Matrix::operator*(const Vector& v)
{
	// ècÉxÉNÉgÉã
	Vector result;
	result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
	result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
	result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
	return result;
}

void Matrix::SetIdent()
{
	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

void Matrix::SetInverse()
{
	Matrix result = Identity();
	Matrix temp = *this;
	for (int i = 0; i < 4; i++)
	{
		float buf = 1 / temp.m[i][i];
		for (int j = 0; j < 4; j++)
		{
			temp.m[i][j] *= buf;
			result.m[i][j] *= buf;
		}
		for (int j = 0; j < 4; j++)
		{
			if (i != j)
			{
				buf = temp.m[j][i];
				for (int k = 0; k < 4; k++)
				{
					temp.m[j][k] -= temp.m[i][k] * buf;
					result.m[j][k] -= result.m[i][k] * buf;
				}
			}
		}
	}
}

void Matrix::SetTranspose()
{
	Matrix result = Identity();
	result.m[0][0] = m[0][0];
	result.m[0][1] = m[1][0];
	result.m[0][2] = m[2][0];
	result.m[0][3] = m[3][0];

	result.m[1][0] = m[0][1];
	result.m[1][1] = m[1][1];
	result.m[1][2] = m[2][1];
	result.m[1][3] = m[3][1];

	result.m[2][0] = m[0][2];
	result.m[2][1] = m[1][2];
	result.m[2][2] = m[2][2];
	result.m[2][3] = m[3][2];

	result.m[3][0] = m[0][3];
	result.m[3][1] = m[1][3];
	result.m[3][2] = m[2][3];
	result.m[3][3] = m[3][3];
	*this = result;
}

void Matrix::SetRotationMatrixX(float xAxis)
{
	*this *= MakeRotationMatrixX(xAxis);
}

void Matrix::SetRotationMatrixY(float yAxis)
{
	*this *= MakeRotationMatrixY(yAxis);
}

void Matrix::SetRotationMatrixZ(float zAxis)
{
	*this *= MakeRotationMatrixZ(zAxis);
}

void Matrix::SetTranslationMatrix(Vector v)
{
	*this *= MakeTranslationMatrix(v);
}

void Matrix::SetRotationMatrix(Euler e)
{
	*this *= MakeRotationMatrix(e);
}

void Matrix::SetScallingMatrix(Vector v)
{
	*this *= MakeScallingMatrix(v);
}

void Matrix::SetModelMatrix(Vector modelPosition, Euler modelRotation, Vector modelScale)
{
	*this *= MakeModelMatrix(modelPosition, modelRotation, modelScale);
}

void Matrix::SetViewMatrix(Vector cameraPosition, Vector cameraTarget, Vector upVector)
{
	*this *= MakeViewMatrix(cameraPosition, cameraTarget, upVector);
}

void Matrix::SetProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	*this *= MakeProjectionMatrix(fov, aspectRatio, nearPlane, farPlane);
}

void Matrix::SetOrthogonalMatrix(float right, float bottom, float nearPlane, float farPlane)
{
	*this *= MakeOrthogonalMatrix(right, bottom, nearPlane, farPlane);
}

void Matrix::SetPerspectiveMatrix(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	*this *= MakePerspectiveMatrix(fov, aspectRatio, nearPlane, farPlane);
}

void Matrix::SetScreenMatrix(float screenWidth, float screenHeight)
{
	*this *= MakeScreenMatrix(screenWidth, screenHeight);
}

void Matrix::SetViewportMatrix(float offsetX, float offsetY, float screenWidth, float screenHeight, float minZ, float maxZ)
{
	*this *= MakeViewportMatrix(offsetX, offsetY, screenWidth, screenHeight, minZ, maxZ);
}

Matrix Matrix::Inversed() const
{
	return Matrix();
}

Matrix Matrix::Transposed() const
{
	return Matrix();
}

Euler Matrix::GetRotationXAxis() const
{
	return Euler();
}

Euler Matrix::GetRotationYAxis() const
{
	return Euler();
}

Euler Matrix::GetRotationZAxis() const
{
	return Euler();
}

Vector Matrix::GetLocation() const
{
	return Vector();
}

Vector Matrix::GetScale() const
{
	return Vector();
}

Matrix Matrix::Identity()
{
	Matrix m;
	m.m[0][0] = 1.0f;
	m.m[0][1] = 0.0f;
	m.m[0][2] = 0.0f;
	m.m[0][3] = 0.0f;

	m.m[1][0] = 0.0f;
	m.m[1][1] = 1.0f;
	m.m[1][2] = 0.0f;
	m.m[1][3] = 0.0f;

	m.m[2][0] = 0.0f;
	m.m[2][1] = 0.0f;
	m.m[2][2] = 1.0f;
	m.m[2][3] = 0.0f;

	m.m[3][0] = 0.0f;
	m.m[3][1] = 0.0f;
	m.m[3][2] = 0.0f;
	m.m[3][3] = 1.0f;

	return m;
}

Vector Matrix::VectorTransform4(const Matrix& m, const Vector& v, const float& w)
{
	Vector result;

#ifdef ROW_MAJOR_ORDER
	// çsóDêÊ
	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * w;
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * w;
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * w;

#endif // ROW_MAJOR_ORDER

#ifdef COLUMN_MAJOR_ORDER
	// óÒóDêÊ
	result.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[3][0] * w;
	result.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z + m.m[3][1] * w;
	result.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z + m.m[3][2] * w;

#endif // COLUMN_MAJOR_ORDER

	return result;
}

Vector Matrix::VectorTransform4(const Matrix& m, const Vector& v, float* w)
{
	Vector result;

#ifdef ROW_MAJOR_ORDER
	// çsóDêÊ
	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * *w;
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * *w;
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * *w;
	*w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * *w;

#endif // ROW_MAJOR_ORDER

#ifdef COLUMN_MAJOR_ORDER
	// óÒóDêÊ
	result.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[3][0] * *w;
	result.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z + m.m[3][1] * *w;
	result.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z + m.m[3][2] * *w;
	*w = m.m[0][3] * v.x + m.m[1][3] * v.y + m.m[2][3] * v.z + m.m[3][3] * *w;

#endif // COLUMN_MAJOR_ORDER

	return result;
}

Matrix Matrix::MakeRotationMatrixX(float xAxis)
{
	float Sin, Cos;
	Sin = sin(xAxis);
	Cos = cos(xAxis);

	Matrix result = Identity();

#ifdef ROW_MAJOR_ORDER
	// çsóDêÊ
	result.m[1][1] = Cos;
	result.m[2][1] = Sin;
	result.m[1][2] = -Sin;
	result.m[2][2] = Cos;

#endif // ROW_MAJOR_ORDER

#ifdef COLUMN_MAJOR_ORDER
	// óÒóDêÊ
	result.m[1][1] = Cos;
	result.m[1][2] = Sin;
	result.m[2][1] = -Sin;
	result.m[2][2] = Cos;

#endif // COLUMN_MAJOR_ORDER

	return result;
}

Matrix Matrix::MakeRotationMatrixY(float yAxis)
{
	float Sin, Cos;
	Sin = sin(yAxis);
	Cos = cos(yAxis);

	Matrix result = Identity();

#ifdef ROW_MAJOR_ORDER
	// çsóDêÊ
	result.m[0][0] = Cos;
	result.m[2][0] = -Sin;
	result.m[0][2] = Sin;
	result.m[2][2] = Cos;

#endif // ROW_MAJOR_ORDER

#ifdef COLUMN_MAJOR_ORDER
	// óÒóDêÊ
	result.m[0][0] = Cos;
	result.m[2][0] = -Sin;
	result.m[0][2] = Sin;
	result.m[2][2] = Cos;

#endif // COLUMN_MAJOR_ORDER

	return result;
}

Matrix Matrix::MakeRotationMatrixZ(float zAxis)
{
	float Sin, Cos;
	Sin = sin(zAxis);
	Cos = cos(zAxis);

	Matrix result = Identity();

#ifdef ROW_MAJOR_ORDER
	// çsóDêÊ
	result.m[0][0] = Cos;
	result.m[1][0] = Sin;
	result.m[0][1] = -Sin;
	result.m[1][1] = Cos;

#endif // ROW_MAJOR_ORDER

#ifdef COLUMN_MAJOR_ORDER
	// óÒóDêÊ
	result.m[0][0] = Cos;
	result.m[0][1] = Sin;
	result.m[1][0] = -Sin;
	result.m[1][1] = Cos;

#endif // COLUMN_MAJOR_ORDER

	return result;
}

Matrix Matrix::MakeTranslationMatrix(Vector v)
{
	Matrix result = Matrix::Identity();

#ifdef ROW_MAJOR_ORDER
	// çsóDêÊ
	result.m[0][3] = v.x;
	result.m[1][3] = v.y;
	result.m[2][3] = v.z;

#endif // ROW_MAJOR_ORDER

#ifdef COLUMN_MAJOR_ORDER
	// óÒóDêÊ
	result.m[3][0] = v.x;
	result.m[3][1] = v.y;
	result.m[3][2] = v.z;

#endif // COLUMN_MAJOR_ORDER

	return result;
}

Matrix Matrix::MakeRotationMatrix(Euler e)
{
	// âÒì]èáèò : X - Y - Z
	return Matrix
	(
		MakeRotationMatrixZ(e.z)
		*
		MakeRotationMatrixY(e.y)
		*
		MakeRotationMatrixX(e.x)
	);
}

Matrix Matrix::MakeScallingMatrix(Vector v)
{
	Matrix result = Matrix::Identity();
	result.m[0][0] = v.x;
	result.m[1][1] = v.y;
	result.m[2][2] = v.z;
	return result;
}

Matrix Matrix::MakeViewMatrix(Vector cameraPosition, Vector cameraTarget, Vector upVector)
{
	// éãì_Å®íçéãì_ÇÃï˚å¸ÉxÉNÉgÉã
	Vector dir = cameraTarget - cameraPosition;

	// éãì_Ç…êÇíºÇ»ÉxÉNÉgÉãÇìæÇÈ
	Vector up = upVector;

	// êVÇwé≤ÇÃÉxÉNÉgÉãÇéZèo
	Vector vx = Vector::Cross(up, dir);

	// êVÇxé≤ÇÃÉxÉNÉgÉãÇéZèo
	Vector vy = Vector::Cross(dir, vx);

	// êVÇyé≤ÇÃÉxÉNÉgÉãÇÉZÉbÉg
	Vector vz = dir;

	// äeÉxÉNÉgÉãÇÃê≥ãKâª
	vx.Normalize();
	vy.Normalize();
	vz.Normalize();

	Matrix result = Matrix::Identity();

	// ÉrÉÖÅ[çsóÒÇÃçÏê¨

#ifdef ROW_MAJOR_ORDER
	// çsóDêÊ
	result.m[0][0] = vx.x;
	result.m[0][1] = vx.y;
	result.m[0][2] = vx.z;
	result.m[0][3] = -(cameraPosition.x * vx.x + cameraPosition.y * vx.y + cameraPosition.z * vx.z);

	result.m[1][0] = vy.x;
	result.m[1][1] = vy.y;
	result.m[1][2] = vy.z;
	result.m[1][3] = -(cameraPosition.x * vy.x + cameraPosition.y * vy.y + cameraPosition.z * vy.z);

	result.m[2][0] = vz.x;
	result.m[2][1] = vz.y;
	result.m[2][2] = vz.z;
	result.m[2][3] = -(cameraPosition.x * vz.x + cameraPosition.y * vz.y + cameraPosition.z * vz.z);

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

#endif // ROW_MAJOR_ORDER

#ifdef COLUMN_MAJOR_ORDER
	// óÒóDêÊ
	result.m[0][0] = vx.x;
	result.m[0][1] = vy.x;
	result.m[0][2] = vz.x;
	result.m[0][3] = 0.0f;

	result.m[1][0] = vx.y;
	result.m[1][1] = vy.y;
	result.m[1][2] = vz.y;
	result.m[1][3] = 0.0f;

	result.m[2][0] = vx.z;
	result.m[2][1] = vy.z;
	result.m[2][2] = vz.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = -(cameraPosition.x * vx.x + cameraPosition.y * vx.y + cameraPosition.z * vx.z);
	result.m[3][1] = -(cameraPosition.x * vy.x + cameraPosition.y * vy.y + cameraPosition.z * vy.z);
	result.m[3][2] = -(cameraPosition.x * vz.x + cameraPosition.y * vz.y + cameraPosition.z * vz.z);
	result.m[3][3] = 1.0f;

#endif // COLUMN_MAJOR_ORDER

	return result;
}

Matrix Matrix::MakeModelMatrix(Vector modelPosition, Euler modelRotation, Vector modelScale)
{
	Matrix translationMat = MakeTranslationMatrix(modelPosition);
	Matrix rotationMat = MakeRotationMatrix(modelRotation);
	Matrix scaleMat = MakeScallingMatrix(modelScale);

	Matrix result = Matrix::Identity();

#ifdef ROW_MAJOR_ORDER
	// çsóDêÊ
	result = translationMat * rotationMat * scaleMat;

#endif // ROW_MAJOR_ORDER

#ifdef COLUMN_MAJOR_ORDER
	// óÒóDêÊ
	result = scaleMat * rotationMat * translationMat;

#endif // COLUMN_MAJOR_ORDER

	return result;
}

Matrix Matrix::MakeProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	return MakePerspectiveMatrix(fov, aspectRatio, nearPlane, farPlane);
}

Matrix Matrix::MakeOrthogonalMatrix(float right, float bottom, float nearPlane, float farPlane)
{
	Matrix result = Matrix::Identity();

#ifdef ROW_MAJOR_ORDER
	// çsóDêÊ
	result.m[0][0] = 2.0f / right;
	result.m[1][1] = 2.0f / bottom;
	result.m[2][2] = -2.0f / farPlane - nearPlane;
	result.m[0][3] = -right;
	result.m[1][3] = -bottom;
	result.m[2][3] = -(farPlane + nearPlane / farPlane - nearPlane);

#endif // ROW_MAJOR_ORDER

#ifdef COLUMN_MAJOR_ORDER
	// óÒóDêÊ
	result.m[0][0] = 2.0f / right;
	result.m[1][1] = 2.0f / bottom;
	result.m[2][2] = -2.0f / farPlane - nearPlane;
	result.m[3][0] = -right;
	result.m[3][1] = -bottom;
	result.m[3][2] = -(farPlane + nearPlane / farPlane - nearPlane);

#endif // COLUMN_MAJOR_ORDER

	return result;
}

Matrix Matrix::MakePerspectiveMatrix(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	Matrix result = Matrix::Identity();
	float scale = 1.0f / tan(fov / 2.0f);

#ifdef ROW_MAJOR_ORDER
	// çsóDêÊ
	result.m[0][0] = scale / aspectRatio;
	result.m[1][1] = scale;
	result.m[2][2] = (farPlane + nearPlane) / (farPlane - nearPlane);
	result.m[2][3] = -farPlane * nearPlane / (farPlane - nearPlane);
	result.m[3][2] = 1.0f;
	result.m[3][3] = 0.0f;

#endif // ROW_MAJOR_ORDER

#ifdef COLUMN_MAJOR_ORDER
	// óÒóDêÊ
	result.m[0][0] = scale / aspectRatio;
	result.m[1][1] = scale;
	result.m[2][2] = (farPlane + nearPlane) / (farPlane - nearPlane);
	result.m[3][2] = -farPlane * nearPlane / (farPlane - nearPlane);
	result.m[2][3] = 1.0f;
	result.m[3][3] = 0.0f;

#endif // COLUMN_MAJOR_ORDER

	return result;
}

Matrix Matrix::MakeScreenMatrix(float screenWidth, float screenHeight)
{
	float halfWidth = screenWidth / 2.0f;
	float halfHeight = screenHeight / 2.0f;

	Matrix result = Matrix::Identity();

#ifdef ROW_MAJOR_ORDER
	// çsóDêÊ
	result.m[0][0] = halfWidth;
	result.m[1][1] = halfHeight;
	result.m[0][3] = halfWidth;
	result.m[1][3] = halfHeight;

#endif // ROW_MAJOR_ORDER

#ifdef COLUMN_MAJOR_ORDER
	// óÒóDêÊ
	result.m[0][0] = halfWidth;
	result.m[1][1] = halfHeight;
	result.m[3][0] = halfWidth;
	result.m[3][1] = halfHeight;

#endif // COLUMN_MAJOR_ORDER

	return result;
}

Matrix Matrix::MakeViewportMatrix(float offsetX, float offsetY, float screenWidth, float screenHeight, float minZ, float maxZ)
{
	float halfWidth = screenWidth / 2.0f;
	float halfHeight = screenHeight / 2.0f;

	Matrix result = Matrix::Identity();

#ifdef ROW_MAJOR_ORDER
	// çsóDêÊ
	result.m[0][0] = halfWidth;
	result.m[1][1] = -halfHeight;
	result.m[2][2] = maxZ - minZ;
	result.m[0][3] = halfWidth + offsetX;
	result.m[1][3] = halfHeight + offsetY;
	result.m[2][3] = minZ;

#endif // ROW_MAJOR_ORDER

#ifdef COLUMN_MAJOR_ORDER
	// óÒóDêÊ
	result.m[0][0] = halfWidth;
	result.m[1][1] = -halfHeight;
	result.m[2][2] = maxZ - minZ;
	result.m[3][0] = halfWidth + offsetX;
	result.m[3][1] = halfHeight + offsetY;
	result.m[3][2] = minZ;

#endif // COLUMN_MAJOR_ORDER

	return result;
}

Vector4f Vector4Transform(const Vector4f& v, const Matrix& m)
{
	Vector4f result;
	result.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[3][0] * v.w;
	result.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z + m.m[3][1] * v.w;
	result.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z + m.m[3][2] * v.w;
	result.w = m.m[0][3] * v.x + m.m[1][3] * v.y + m.m[2][3] * v.z + m.m[3][3] * v.w;
	return result;
}

Vector4f Vector4Transform(const Matrix& m, const Vector4f& v)
{
	Vector4f result;
	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
	result.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;
	return result;
}
