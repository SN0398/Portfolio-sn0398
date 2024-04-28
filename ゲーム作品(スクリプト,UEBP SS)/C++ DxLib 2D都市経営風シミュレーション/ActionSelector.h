#pragma once
#include "UserInterface.h"
#include <memory>
#include <vector>
#include "ActionButton.h"
#include "Building.h"

#define SELECTBOX_SIZE	128

// ����C���^�[�t�F�[�X�F�s���I��
class ActionSelector : public UserInterface
{
	// �{�^���̎��ʎq
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

	ActionButton* GetHitButton();	// �����蔻��t���O�������Ă���{�^����Ԃ�
	void ResetButtonList();

private:
	std::vector<std::unique_ptr<ActionButton>> Button;
	std::list<std::unique_ptr<ActionButton>> ButtonList;	// �e��{�^���̊i�[���X�g

};