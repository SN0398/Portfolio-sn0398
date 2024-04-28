#pragma once
#include "GameObject/3DModel/3DModel.h"

class Mesh_Cube : public ModelData
{
public:
	Mesh_Cube();
	~Mesh_Cube() = default;

public:
	void Update() override;
};