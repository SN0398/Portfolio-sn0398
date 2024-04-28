#pragma once
#include "GameObject/GameObject.h"

#include "GameObject/3DModel/3DModel.h"

#include "Component/Renderer/Renderer.h"
#include "Component/MeshInterface/MeshInterface.h"

#include <vector>

using std::vector;
using std::shared_ptr;

class RendererInterface : public GameObject
{
public:
	RendererInterface();
	~RendererInterface();

public:
	void Update() override;

	void Draw() override;

	// •`‰æ
	void Render();

public:
	Renderer renderer;
	vector<shared_ptr<ModelData>> model;
};