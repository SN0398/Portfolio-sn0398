#pragma once
#include "GameObject/GameObject.h"
#include <vector>
#include <string>

class Renderer;

class ControlPanel : public GameObject
{
public:
	struct ControlData
	{
		std::string title;
		float* ptr;
		Slider slider;
	};

public:
	ControlPanel() = default;
	ControlPanel(Renderer* renderer);
	~ControlPanel();

public:
	void Update() override;
	void Draw() override;

public:
	std::vector<ControlData> slider;

};