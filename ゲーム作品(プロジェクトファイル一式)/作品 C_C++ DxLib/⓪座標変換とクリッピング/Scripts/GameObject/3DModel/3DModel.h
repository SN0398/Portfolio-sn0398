#pragma once
#include "GameObject/GameObject.h"
#include "Component/MeshInterface/MeshInterface.h"

// ƒ‚ƒfƒ‹î•ñ
struct ModelTransform
{
	Vector Position;	// À•W
	Euler Rotation;		// ‰ñ“]
	Vector Scale;		// Šg‘åk¬
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