#pragma once
#include "UserInterface.h"

// ����C���^�[�t�F�[�X�F�f�t�H���g
class ChipSelect : public UserInterface
{
public:
	ChipSelect() = default;
	~ChipSelect() = default;

public:
	void Update() override;
	void Draw() override;
};