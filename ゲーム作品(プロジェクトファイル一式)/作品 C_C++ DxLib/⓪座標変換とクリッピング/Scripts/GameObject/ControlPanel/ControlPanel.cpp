#include "ControlPanel.h"
#include "Component/Renderer/Renderer.h"
#include "Resource/ResourceManager.h"

ControlPanel::ControlPanel(Renderer* renderer)
{
	ControlData temp;
	// �J����X�̃X���C�_�[
	temp =
	{
		"�J����X���W",
		&renderer->camera.cameraPos.x,
		Slider({ 300,100 }, 10, 200, -500, 500)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

	// �J����Y�̃X���C�_�[
	temp =
	{
		"�J����Y���W",
		&renderer->camera.cameraPos.y,
		Slider({ 300,200 }, 10, 200, -500, 500)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

	// �J����Z�̃X���C�_�[
	temp =
	{
		"�J����Z���W",
		&renderer->camera.cameraPos.z,
		Slider({ 300,300 }, 10, 200, -500, 500)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

	// �����_X�̃X���C�_�[
	temp =
	{
		"�����_X���W",
		&renderer->camera.lookAtPos.x,
		Slider({ 300,400 }, 10, 200, -500, 500)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

	// �����_Y�̃X���C�_�[
	temp =
	{
		"�����_Y���W",
		&renderer->camera.lookAtPos.y,
		Slider({ 300,500 }, 10, 200, -500, 500)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

	// �����_Z�̃X���C�_�[
	temp =
	{
		"�����_Z���W",
		&renderer->camera.lookAtPos.z,
		Slider({ 300,600 }, 10, 200, -500, 500)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

	// �j�A�N���b�v�ʂ̃X���C�_�[
	temp =
	{ 
		"�߃N���b�v��",
		&renderer->proj.nearPlane,
		Slider({ 300,700 }, 10, 200, 50, 500)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

	// �t�@�[�N���b�v�ʂ̃X���C�_�[
	temp =
	{ 
		"���N���b�v��",
		&renderer->proj.farPlane,
		Slider({ 300,800 }, 10, 200, 500, 1000)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

	// ����̃X���C�_�[
	temp =
	{
		"����",
		&renderer->proj.FoV,
		Slider({ 300,900 }, 10, 200, DX_PI_F / 8.0f, DX_PI_F / 1.0f)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

}

ControlPanel::~ControlPanel()
{
	slider.clear();
}

void ControlPanel::Update()
{
	for (auto& obj : slider)
	{
		obj.slider.Update();
		*obj.ptr = obj.slider.Get();
	}
}

void ControlPanel::Draw()
{
	for (auto& obj : slider)
	{
		obj.slider.Draw();
		DrawFormatStringToHandle
		(
			obj.slider.Pos.x - 50, 
			obj.slider.Pos.y - 30, 
			0xFFFFFF, 
			Resource::GetInstance().Font[Font_ID::HGSminchoE_Medium], 
			obj.title.c_str()
		);
	}
}