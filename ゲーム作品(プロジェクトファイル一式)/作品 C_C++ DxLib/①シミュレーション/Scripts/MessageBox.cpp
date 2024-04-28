#include "MessageBox.h"
#include "ResourceManager.h"

void MessageInterface::HitStateUpdate(Vector2D Cpos)
{
	// �����蔻��̍X�V
	Vector2D Pos1;
	Vector2D Pos2;
	for (int i = 0;i < button.size();i++)
	{
		Pos1 = button.at(i)->Pos1;
		Pos2 = button.at(i)->Pos2;
		button.at(i)->HitFlag = CheckHitBoxToPoint2D(Pos1, Pos2, Cpos);
	}
	return;
}

void MessageInterface::Draw()
{
	int DrawX, DrawY;
	DrawX = SCREEN_WIDTH / 2;
	DrawY = SCREEN_HEIGHT / 2;

	// �E�B���h�E�`��
	DrawExtendGraph
	(
		DrawX - 150, DrawY - 60,
		DrawX + 150, DrawY + 60,
		Resource::GetInstance().DialogueWindow, FALSE
	);
	Vector2D* Pos1;
	Vector2D* Pos2;
	for (int i = 0;i < button.size();i++)
	{
		Pos1 = &button.at(i)->Pos1;
		Pos2 = &button.at(i)->Pos2;
		// �{�^���`��
		DrawExtendGraph
		(
			Pos1->x, Pos1->y,
			Pos2->x, Pos2->y,
			Resource::GetInstance().InfoWindow, FALSE
		);
		// �J�[�\���ƃ{�^�����������Ă���t���O�������Ă�����
		if (button.at(i)->HitFlag)
		{
			// �������̍��F��`�悷��
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
			DrawBox
			(
				Pos1->x, Pos1->y,
				Pos2->x, Pos2->y,
				Resource::GetInstance().Color[Color_ID::Black], TRUE
			);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		// �{�^�������`��
		DrawFormatStringToHandle
		(
			Pos1->x + 25, Pos1->y + 20,
			Resource::GetInstance().Color[Color_ID::White],
			Resource::GetInstance().Font[Font_ID::Yumincho],
			button.at(i)->DisplayName
		);
	}
	int middle = SCREEN_WIDTH / 2;
	// �����̕�
	int width = GetDrawStringWidthToHandle(DisplayName, strlen(DisplayName), Resource::GetInstance().Font[Font_ID::Yumincho]);
	// �E�B���h�E�����`��
	DrawFormatStringToHandle
	(
		middle - width / 2,
		DrawY - 40,
		Resource::GetInstance().Color[Color_ID::White],
		Resource::GetInstance().Font[Font_ID::Yumincho],
		DisplayName
	);

	return;
}

// �h���N���X�̉��z�֐��I�[�o�[���C�h��`

std::unique_ptr<MessageInterface> MessageInterface_YesOrNo::Create(const char* str)
{
	// MessageInterface_YesOrNo �� unique_ptr �I�u�W�F�N�g�𐶐�
	auto AddObj = std::make_unique<MessageInterface_YesOrNo>();

	AddObj->DisplayName = str;

	// �{�^����ǉ�
	AddObj->button.emplace_back(std::make_unique<MessageInterface::Button>
		(MessageInterface::Button{ { 835,530 },{ 935,580 },false,"����" }));
	AddObj->button.emplace_back(std::make_unique<MessageInterface::Button>
		(MessageInterface::Button{ { 985,530 },{ 1085,580 },false,"�p��" }));

	// unique_ptr<MessageInterface_YesOrNo> �^�� unique_ptr �I�u�W�F�N�g�ɕϊ����ĕԂ�
	return std::unique_ptr<MessageInterface_YesOrNo>(std::move(AddObj));
	//return AddObj;
}

int MessageInterface_YesOrNo::GetHitState()
{
	// �������Ă���{�^���ɉ������l��Ԃ�
	if (button.at(0)->HitFlag)
	{
		return SELECTED_YES;
	}
	else if (button.at(1)->HitFlag)
	{
		return SELECTED_NO;
	}
	return SELECTED_NONE;
}

std::unique_ptr<MessageInterface> MessageInterface_Ok::Create(const char* str)
{
	// MessageInterface_Ok �� unique_ptr �I�u�W�F�N�g�𐶐�
	auto AddObj = std::make_unique<MessageInterface_Ok>();

	AddObj->DisplayName = str;

	// �{�^����ǉ�
	AddObj->button.emplace_back(std::make_unique<MessageInterface::Button>
		(MessageInterface::Button{ { SCREEN_WIDTH / 2-50,530 },{ SCREEN_WIDTH / 2+50,580 },false,"����" }));

	// unique_ptr<MessageInterface_YesOrNo> �^�� unique_ptr �I�u�W�F�N�g�ɕϊ����ĕԂ�
	return std::unique_ptr<MessageInterface_Ok>(std::move(AddObj));
	//return AddObj;
}

int MessageInterface_Ok::GetHitState()
{
	// �������Ă���{�^���ɉ������l��Ԃ�
	if (button.front()->HitFlag)
	{
		return SELECTED_OK;
	}
	return SELECTED_NONE;
}
