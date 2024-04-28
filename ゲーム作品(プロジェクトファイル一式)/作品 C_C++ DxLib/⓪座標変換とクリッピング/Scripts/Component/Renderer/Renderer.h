#pragma once
#include "MyLib.h"
#include "GameObject/3DModel/3DModel.h"
#include <vector>

// �J�������
struct CameraData
{
	Vector cameraPos;	// �J�������W
	Vector lookAtPos;	// �����_
	Vector upVector;	// ������x�N�g��
};

// ���e���
struct ProjectionData
{
	float FoV;			// ����
	float aspectRatio;	// �A�X�y�N�g��
	float nearPlane;	// �߃N���b�v��
	float farPlane;		// ���N���b�v��
};

// �X�N���[����`���
struct ScreenRect
{
	float Height;		// �c��
	float Width;		// ����
	float OffsetX;
	float OffsetY;
};

class Renderer : public Component
{
public:
	struct RendererBuffer
	{
		Matrix world;
		Matrix view;
		Matrix proj;
		Matrix screen;
	};
	
	enum class ProjectionType
	{
		Perspective,	// �������e
		//Orthogonal		// ���s���e
	};

public:
	Renderer();
	~Renderer();

public:
	void Update() override {}

	void Draw() override {}

	Mesh ClipCoordinate(const Mesh& buff);

	Mesh NormalizedDeviceCoordinate(const Mesh& buff);

	Mesh ScreenCoordinate(const Mesh& buff);

	void Render(const Mesh& buff, COLOR_U8 color);

	// ���W�ϊ��������ʂ̃N���b�v���W�n��Ԃ�
	Vertex Transformed(const Vertex& v);

	// �`��p�̍s����X�V
	void UpdateRendererConfig();

	// ���f���s����擾
	void GetModelMatrix(ModelData model);

	// �J��������ύX
	void UpdateCameraData(CameraData _camera) { camera = _camera; }
	
	// ���e����ύX
	void UpdateProjectionData(ProjectionData _proj) { proj = _proj; }
	
	// �X�N���[������ύX
	void UpdateScreenRect(ScreenRect _window) { window = _window; }
	
	// ���e�ϊ��̕��@��؂�ւ�
	void SwitchProjectionType(ProjectionType _projType) { projType = _projType; }

public:
	RendererBuffer renderer;		// 	
	CameraData camera;				// 
	ProjectionData proj;			// 
	ScreenRect window;				// 
	ProjectionType projType;		// 

};