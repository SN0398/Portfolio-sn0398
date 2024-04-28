#include "Cube.h"

Mesh_Cube::Mesh_Cube()
{
	transform.Position = Vector(0.0f, 0.0f, 0.0f);
	transform.Rotation = Euler(0.0f, 0.0f, 0.0f);
	transform.Scale = Vector(1.0f, 1.0f, 1.0f);

	Model =
	{
		8,
		{
			{-10.0f,-10.0f,-10.0f,1.0f},
			{-10.0f,-10.0f, 10.0f,1.0f},
			{ 10.0f,-10.0f, 10.0f,1.0f},
			{ 10.0f,-10.0f,-10.0f,1.0f},
			{-10.0f, 10.0f, 10.0f,1.0f},
			{-10.0f, 10.0f,-10.0f,1.0f},
			{ 10.0f, 10.0f,-10.0f,1.0f},
			{ 10.0f, 10.0f, 10.0f,1.0f},
		},
		6,
		{
			{5,{0,1,2,3,0}},
			{5,{4,5,6,7,4}},
			{5,{0,1,4,5,0}},
			{5,{2,3,6,7,2}},
			{5,{0,3,6,5,0}},
			{5,{1,2,7,4,1}},
		},
	};
	color = GetColorU8(0, 148, 255, 0);
}

void Mesh_Cube::Update()
{
	static const float power = 5.5f;
	UpdateComponents();
	if (Keyboard_Get(KEY_INPUT_Q) >= 1)
	{
		this->transform.Position.x += power;
	}
	if (Keyboard_Get(KEY_INPUT_A) >= 1)
	{
		this->transform.Position.x -= power;
	}
	if (Keyboard_Get(KEY_INPUT_W) >= 1)
	{
		this->transform.Position.y += power;
	}
	if (Keyboard_Get(KEY_INPUT_S) >= 1)
	{
		this->transform.Position.y -= power;
	}
	if (Keyboard_Get(KEY_INPUT_E) >= 1)
	{
		this->transform.Position.z += power;
	}
	if (Keyboard_Get(KEY_INPUT_D) >= 1)
	{
		this->transform.Position.z -= power;
	}
	if (Keyboard_Get(KEY_INPUT_Z) >= 1)
	{
		this->transform.Rotation.x -= power;
	}
	if (Keyboard_Get(KEY_INPUT_X) >= 1)
	{
		this->transform.Rotation.y -= power;
	}
	if (Keyboard_Get(KEY_INPUT_C) >= 1)
	{
		this->transform.Rotation.z -= power;
	}
}
