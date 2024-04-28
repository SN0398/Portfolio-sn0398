#pragma once
#include "UserInterface.h"
#include "MessageBox.h"
#include <memory>

#define START_BUILDING_DATAPATH		"./Save/StartBuilding"

// 操作インターフェース：スタート画面
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