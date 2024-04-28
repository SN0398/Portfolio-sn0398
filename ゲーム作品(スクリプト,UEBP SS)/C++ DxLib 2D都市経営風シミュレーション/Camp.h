#pragma once
#include "Building.h"

class Camp : public Towny
{
public:
	Camp() = default;
	Camp(int PosX, int PosY);
	~Camp() = default;

public:
	void Update() override;
	void Draw() override;
	int GetBuildCost() override { return 0; }

};