#pragma once
#include "UserInterface.h"
#include "MessageBox.h"
#include <memory>

#define START_BUILDING_DATAPATH		"./Save/StartBuilding"

// ����C���^�[�t�F�[�X�F�X�^�[�g���
class Start : public UserInterface
{
public:
	Start();
	~Start() = default;

public:
	void Update() override;
	void Draw() override;

public:
	std::unique_ptr<MessageInterface> Dialogue;
};