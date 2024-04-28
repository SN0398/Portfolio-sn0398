#pragma once
#include "MyLib.h"
#include <list>
#include <memory>
#include <vector>

#define SELECTED_NONE	0
#define SELECTED_YES	1
#define SELECTED_NO		2
#define SELECTED_OK		3

// ���b�Z�[�W�{�b�N�X�̊��N���X
class MessageInterface abstract
{
public:
	// �{�^���̍\����
	struct Button
	{
		Vector2D Pos1, Pos2;
		bool HitFlag;
		const char* DisplayName;
	};

public:
	MessageInterface() = default;
	~MessageInterface() = default;

public:
	// ������̎擾
	virtual int GetHitState() = 0;
	// �����蔻��X�V
	void HitStateUpdate(Vector2D Cpos);
	// �`��
	void Draw();

protected:
	// �{�^���̔z��
	std::vector<std::unique_ptr<Button>> button;
	// �^�C�g��
	const char* DisplayName;

};

class MessageInterface_YesOrNo : public MessageInterface
{
public:
	MessageInterface_YesOrNo() = default;
	~MessageInterface_YesOrNo() = default;

public:
	static std::unique_ptr<MessageInterface> Create(const char* str);
	int GetHitState() override;

};

class MessageInterface_Ok : public MessageInterface
{
public:
	MessageInterface_Ok() = default;
	~MessageInterface_Ok() = default;

public:
	static std::unique_ptr<MessageInterface> Create(const char* str);
	int GetHitState() override;

};