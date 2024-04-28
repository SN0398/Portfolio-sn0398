#pragma once
#include "UserInterface.h"
#include <memory>
#include <vector>
#include "ActionButton.h"
#include "Building.h"

#define SELECTBOX_SIZE	128

// 操作インターフェース：行動選択
class ActionSelector : public UserInterface
{
	// ボタンの識別子
	enum ActionIndex
	{
		UI_Build = 0,
		UI_Demolition,
		UI_Move,
	};

public:
	ActionSelector();
	~ActionSelector() = default;

public:
	void Update() override;
	void Draw() override;

	ActionButton* GetHitButton();	// 当たり判定フラグが立っているボタンを返す
	void ResetButtonList();

private:
	std::vector<std::unique_ptr<ActionButton>> Button;
	std::list<std::unique_ptr<ActionButton>> ButtonList;	// 各種ボタンの格納リスト

};