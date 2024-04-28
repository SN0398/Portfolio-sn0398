#pragma once
#include "Building.h"

#define FACTORY_LOW_EARNRATE	10

class Factory : public Industries
{
public:
	Factory() = default;
	Factory(int PosX, int PosY);
	~Factory() = default;

public:
	void Update() override;
	void Draw() override;
	int GetBuildCost() override { return 300; }

};