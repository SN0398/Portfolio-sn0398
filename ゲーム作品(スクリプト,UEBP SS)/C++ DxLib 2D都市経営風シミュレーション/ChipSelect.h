#pragma once
#include "UserInterface.h"

// 操作インターフェース：デフォルト
class ChipSelect : public UserInterface
{
public:
	ChipSelect() = default;
	~ChipSelect() = default;

public:
	void Update() override;
	void Draw() override;
};