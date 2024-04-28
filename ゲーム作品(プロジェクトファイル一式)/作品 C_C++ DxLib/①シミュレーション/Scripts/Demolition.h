#pragma once
#include "UserInterface.h"
#include "MyLib.h"
#include "MessageBox.h"

// 操作インターフェース：解体
class Demolition : public UserInterface
{
public:
	Demolition();
	~Demolition() = default;

public:
	void Update() override;
	void Draw() override;

	void Accept();
	void Deny();

private:
	std::unique_ptr<MessageInterface> MsgBox;
};
