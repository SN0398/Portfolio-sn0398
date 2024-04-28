#pragma once
#include "Building.h"

#define FARM_LOW_EARNRATE	25

class Farm : public Industries
{
public:
	Farm() = default;
	Farm(int OverrideFlag, int PosX, int PosY);
	Farm(int PosX, int PosY);
	~Farm() = default;

public:
	void Update() override;
	void Draw() override;
	int GetBuildCost() override { return 350; }

};