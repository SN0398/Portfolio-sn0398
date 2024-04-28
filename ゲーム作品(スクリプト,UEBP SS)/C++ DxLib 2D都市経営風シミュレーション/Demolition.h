#pragma once
#include "UserInterface.h"
#include "MyLib.h"
#include "MessageBox.h"

// ����C���^�[�t�F�[�X�F���
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
