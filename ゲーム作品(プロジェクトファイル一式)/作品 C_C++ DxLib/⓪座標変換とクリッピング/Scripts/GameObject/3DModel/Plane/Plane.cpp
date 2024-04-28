#include "Plane.h"

Mesh_Plane::Mesh_Plane()
{
	transform.Position = Vector(0.0f, 0.0f, 0.0f);
	transform.Rotation = Euler(0.0f, 0.0f, 0.0f);
	transform.Scale = Vector(10.0f, 10.0f, 10.0f);

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
	//polycolor = GetColorU8(0, 0, 0, 0);
	//linecolor = GetColorU8(0, 0, 0, 0);
}