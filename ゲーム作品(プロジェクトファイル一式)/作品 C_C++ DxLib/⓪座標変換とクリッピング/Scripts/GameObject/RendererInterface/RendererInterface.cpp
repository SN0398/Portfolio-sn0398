#include "RendererInterface.h"

#include "Component/PolygonClipping/Clipping.h"

RendererInterface::RendererInterface()
{
	CameraData camera;	
	camera.cameraPos = Vector(0.0f, 0.0f, -100.0f);
	camera.lookAtPos = Vector(0.0f, 0.0f, 0.0f);
	camera.upVector = Vector(0.0f, 1.0f, 0.0f);

	ScreenRect window;	
	window.Width = 1920.0f;
	window.Height = 1080.0f;
	window.OffsetX = 0.0f;
	window.OffsetY = 0.0f;
	//window.Width = 1920.0f / 2.0f;
	//window.Height = 1080.0f / 2.0f;
	//window.OffsetX = 1920.0f / 4.0f;
	//window.OffsetY = 1080.0f / 4.0f;

	ProjectionData proj;
	proj.FoV = 3.14159f / 2.0f;
	proj.aspectRatio = window.Width / window.Height;
	proj.nearPlane = 200.0f;
	proj.farPlane = 700.0f;

	Renderer::ProjectionType projType;
	projType = Renderer::ProjectionType::Perspective;

	renderer.UpdateCameraData(camera);
	renderer.UpdateProjectionData(proj);
	renderer.UpdateScreenRect(window);
	renderer.SwitchProjectionType(projType);
}

RendererInterface::~RendererInterface()
{
	model.clear();
}

void RendererInterface::Update()
{
	return;
}

void RendererInterface::Draw()
{
	DrawBox
	(
		0 + renderer.window.OffsetX,
		0 + renderer.window.OffsetY,
		renderer.window.Width + renderer.window.OffsetX,
		renderer.window.Height + renderer.window.OffsetY,
		0xFFFF00, FALSE);

	Render();
	return;
}

void RendererInterface::Render()
{
	for (auto& obj : model)
	{
		Mesh temp = obj->Model;
		renderer.GetModelMatrix(*obj.get());				// ���f���s��X�V
		renderer.UpdateRendererConfig();					// �`��p�ݒ�X�V
		temp = renderer.ClipCoordinate(temp);				// �N���b�v���W�n
		temp = PolygonClipping(temp);						// �|���S���N���b�s���O
		temp = renderer.NormalizedDeviceCoordinate(temp);	// ���K���f�o�C�X���W�n
		temp = renderer.ScreenCoordinate(temp);				// �X�N���[�����W�n
		renderer.Render(temp, obj->color);					// �`��
	}
	return;
}