#include "Pose.h"
#include "ResourceManager.h"
#include "InterfaceManager.h"
#include "SceneManager.h"

Pose::Pose()
{
	Position2D MiddlePos = { SCREEN_WIDTH/2,SCREEN_HEIGHT/2 };
	buttonList.push_back(new Button("������",	Continue, Vector2D{ (double)MiddlePos.x-100,(double)MiddlePos.y-175 }, Vector2D{ (double)MiddlePos.x+100,(double)MiddlePos.y-125 }));
	buttonList.push_back(new Button("�Z�[�u",   Save,     Vector2D{ (double)MiddlePos.x-100,(double)MiddlePos.y-75  }, Vector2D{ (double)MiddlePos.x+100,(double)MiddlePos.y-25  }));
	buttonList.push_back(new Button("���[�h",	Load,     Vector2D{ (double)MiddlePos.x-100,(double)MiddlePos.y+25  }, Vector2D{ (double)MiddlePos.x+100,(double)MiddlePos.y+75  }));
	buttonList.push_back(new Button("�I��",		Close,    Vector2D{ (double)MiddlePos.x-100,(double)MiddlePos.y+125 }, Vector2D{ (double)MiddlePos.x+100,(double)MiddlePos.y+175 }));

	closeDialogue = nullptr;
}

void Pose::Update()
{
	// ���b�Z�[�W�{�b�N�X���\������ĂȂ���Ԃŏ�����I��
	if (closeDialogue.get() == nullptr)
	{
		// Esc�Ŗ߂�
		if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
		{
			InterfaceManager::GetInstance().BackInterface();
			return;
		}
		UpdateButtonCollision();	// �R���W�����X�V
		// �}�E�X�N���b�N
		if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
		{
			// �J�[�\���Ɠ������Ă���{�^���̃^�C�v�ʏ������Ă�
			for (auto& obj : buttonList)
			{
				if (obj->inCursor)
				{
					onClickAction(obj->Type);
					return;
				}
			}
		}
	}
	// ���b�Z�[�W�{�b�N�X���\������Ă����ԂőI��ʂ̏������Ă�
	else
	{
		// Esc�Ŗ߂�
		if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
		{
			closeDialogue = nullptr;
		}
		// ���b�Z�[�W�{�b�N�X�̍X�V
		// �}�E�X�N���b�N
		if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
		{
			int x, y;
			GetMousePoint(&x, &y);
			Vector2D Mpos = { (float)x, (float)y };
			closeDialogue->HitStateUpdate(Mpos);
			if (closeDialogue->GetHitState() == SELECTED_YES)
			{
				SceneManager::GetInstance().PopAllScene();
				return;
			}
			else if (closeDialogue->GetHitState() == SELECTED_NO)
			{
				closeDialogue = nullptr;
			}
		}
	}
	return;
}

void Pose::Draw()
{
	// ���\�[�X�̕ʖ�
	auto& resource = Resource::GetInstance();

	MapManager::GetInstance().DrawMap();
	BuildingManager::GetInstance().Draw();

	// �w�i�F
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, resource.Color[Color_ID::Black], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// ���ꂼ��̃{�^���ƕ�����̕`��
	for (auto obj : buttonList)
	{
		// �{�b�N�X�`��
		DrawExtendGraph(obj->Pos1.x, obj->Pos1.y, obj->Pos2.x, obj->Pos2.y, resource.DialogueWindow, FALSE);
		// �������낦�ŕ�����`��
		// �{�b�N�X���[�ƉE�[�̒l
		int middle = (obj->Pos1.x + obj->Pos2.x) / 2;
		// �����̕�
		int width = GetDrawStringWidthToHandle(obj->DisplayName, strlen(obj->DisplayName), resource.Font[Font_ID::Yumincho]);
		// �`��
		DrawFormatStringToHandle
		(
			middle - width / 2,
			obj->Pos1.y + 17,
			resource.Color[Color_ID::Black],
			resource.Font[Font_ID::Yumincho],
			obj->DisplayName
		);
		// �J�[�\���őI�𒆂̏ꍇ�̂݃{�b�N�X�𔼓����̍��ŕ`�悷��
		if (obj->inCursor)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawBox(obj->Pos1.x, obj->Pos1.y, obj->Pos2.x, obj->Pos2.y, resource.Color[Color_ID::Black], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	};

	// ү�����ޯ�����\������Ă����Ԃł�ү�����ޯ���`��
	if (closeDialogue.get() != nullptr)
	{
		closeDialogue->Draw();
	}
	
	return;
}

void Pose::UpdateButtonCollision()
{
	int x, y;
	GetMousePoint(&x, &y);
	Vector2D Mpos = { (float)x, (float)y };
	for (auto& obj : buttonList)
	{
		obj->inCursor = CheckHitBoxToPoint2D(obj->Pos1, obj->Pos2, Mpos);
	}

	return;
}

void Pose::onClickAction(ResponceType type)
{
	switch (type)
	{
	case Continue:
	{
		InterfaceManager::GetInstance().BackInterface();
	}break;
	case Save:
	{

	}break;
	case Load:
	{

	}break;
	case Close:
	{
		closeDialogue = MessageInterface_YesOrNo::Create("�I�����܂����H");
	}break;
	}

	return;
}