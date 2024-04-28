#include "ControlPanel.h"
#include "Component/Renderer/Renderer.h"
#include "Resource/ResourceManager.h"

ControlPanel::ControlPanel(Renderer* renderer)
{
	ControlData temp;
	// カメラXのスライダー
	temp =
	{
		"カメラX座標",
		&renderer->camera.cameraPos.x,
		Slider({ 300,100 }, 10, 200, -500, 500)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

	// カメラYのスライダー
	temp =
	{
		"カメラY座標",
		&renderer->camera.cameraPos.y,
		Slider({ 300,200 }, 10, 200, -500, 500)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

	// カメラZのスライダー
	temp =
	{
		"カメラZ座標",
		&renderer->camera.cameraPos.z,
		Slider({ 300,300 }, 10, 200, -500, 500)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

	// 注視点Xのスライダー
	temp =
	{
		"注視点X座標",
		&renderer->camera.lookAtPos.x,
		Slider({ 300,400 }, 10, 200, -500, 500)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

	// 注視点Yのスライダー
	temp =
	{
		"注視点Y座標",
		&renderer->camera.lookAtPos.y,
		Slider({ 300,500 }, 10, 200, -500, 500)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

	// 注視点Zのスライダー
	temp =
	{
		"注視点Z座標",
		&renderer->camera.lookAtPos.z,
		Slider({ 300,600 }, 10, 200, -500, 500)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

	// ニアクリップ面のスライダー
	temp =
	{ 
		"近クリップ面",
		&renderer->proj.nearPlane,
		Slider({ 300,700 }, 10, 200, 50, 500)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

	// ファークリップ面のスライダー
	temp =
	{ 
		"遠クリップ面",
		&renderer->proj.farPlane,
		Slider({ 300,800 }, 10, 200, 500, 1000)
	};
	temp.slider.Set(*temp.ptr);
	slider.push_back(temp);

	// 視野のスライダー
	temp =
	{
		"視野",
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