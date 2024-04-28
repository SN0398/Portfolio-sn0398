#pragma once
#include "Building.h"

class Shop : public Market
{
public:
	Shop() = default;
	Shop(int OverrideFlag, int PosX, int PosY);
	~Shop() = default;

public:
	void Update() override;
	void Draw() override;
};