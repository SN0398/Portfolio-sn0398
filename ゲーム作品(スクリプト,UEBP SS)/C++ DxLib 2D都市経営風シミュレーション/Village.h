#pragma once
#include "Building.h"

#define VILLAGE_LOW_INCREASE_RATE	200

class Village : public Towny
{
public:
	Village() = default;
	Village(int PosX, int PosY);
	~Village() = default;

public:
	void Update() override;
	void Draw() override;
	int GetBuildCost() override { return 350; }
};