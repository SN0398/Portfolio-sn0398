#pragma once
#include "GameObject/GameObject.h"
#include "Component/MeshInterface/MeshInterface.h"

// モデル情報
struct ModelTransform
{
	Vector Position;	// 座標
	Euler Rotation;		// 回転
	Vector Scale;		// 拡大縮小
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