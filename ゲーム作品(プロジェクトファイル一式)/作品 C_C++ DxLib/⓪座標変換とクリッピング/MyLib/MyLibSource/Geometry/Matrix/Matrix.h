#pragma once

class Vector;
using Euler = Vector;
class Quaternion;
class Matrix;

class Matrix
{
public:	// Constructor / Destructor
	Matrix() = default;
	Matrix(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);
	Matrix(const Matrix& m);

public: // operator override
	Matrix operator=(const Matrix& mat);

	Matrix operator+(const Matrix& mat);

	Matrix operator-(const Matrix& mat);

	Matrix operator*(const Matrix& mat);

	Matrix operator*=(const Matrix& mat);

	Matrix operator*(const float& multiply);

	Matrix operator*=(const float& multiply);

	Vector operator*(const Vector& v);

public:	// setter function
	void SetIdent();

	void SetInverse();

	void SetTranspose();

	void SetRotationMatrixX(float xAxis);

	void SetRotationMatrixY(float yAxis);

	void SetRotationMatrixZ(float zAxis);

	void SetTranslationMatrix(Vector v);

	void SetRotationMatrix(Euler e);

	void SetScallingMatrix(Vector v);

	void SetModelMatrix(Vector modelPosition, Euler modelRotation, Vector modelScale);

	void SetViewMatrix(Vector cameraPosition, Vector cameraTarget, Vector upVector);

	void SetProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);

	void SetOrthogonalMatrix(float right, float bottom, float nearPlane, float farPlane);

	void SetPerspectiveMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);

	void SetScreenMatrix(float screenWidth, float screenHeight);

	void SetViewportMatrix(float offsetX, float offsetY, float screenWidth, float screenHeight, float minZ, float maxZ);

public:	// getter function
	Matrix Inversed() const;

	Matrix Transposed() const;

	Euler GetRotationXAxis() const;

	Euler GetRotationYAxis() const;

	Euler GetRotationZAxis() const;

	Quaternion GetRotation() const;

	Vector GetLocation() const;

	Vector GetScale() const;

public:	// static function
	static Matrix Identity();

	static Vector VectorTransform4(const Matrix& m, const Vector& v, const float& w);

	static Vector VectorTransform4(const Matrix& m, const Vector& v, float* w);

	static Matrix MakeRotationMatrixX(float xAxis);

	static Matrix MakeRotationMatrixY(float yAxis);

	static Matrix MakeRotationMatrixZ(float zAxis);

	static Matrix MakeTranslationMatrix(Vector v);

	static Matrix MakeRotationMatrix(Euler e);

	static Matrix MakeScallingMatrix(Vector v);

	static Matrix MakeViewMatrix(Vector cameraPosition, Vector cameraTarget, Vector upVector);

	static Matrix MakeModelMatrix(Vector modelPosition, Euler modelRotation, Vector modelScale);

	static Matrix MakeProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);

	static Matrix MakeOrthogonalMatrix(float right, float bottom, float nearPlane, float farPlane);

	static Matrix MakePerspectiveMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);

	static Matrix MakeScreenMatrix(float screenWidth, float screenHeight);

	static Matrix MakeViewportMatrix(float offsetX, float offsetY, float screenWidth, float screenHeight, float minZ, float maxZ);

public:
	float m[4][4];

};