#pragma once
#include "GameObject/GameObject.h"
#include "Component/MeshInterface/MeshInterface.h"

// ���f�����
struct ModelTransform
{
	Vector Position;	// ���W
	Euler Rotation;		// ��]
	Vector Scale;		// �g��k��
};

class ModelData : public GameObject
{
public:
	ModelData() = default;
	ModelData(ModelTransform _transform, Mesh _mesh) 
		: transform(_transform), Model(_mesh) {}
	virtual ~ModelData() = default;

public:
	ModelTransform transform;
	Mesh Model;
	COLOR_U8 color;
};