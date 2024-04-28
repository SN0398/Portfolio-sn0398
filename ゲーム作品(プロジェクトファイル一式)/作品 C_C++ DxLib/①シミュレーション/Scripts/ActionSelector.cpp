#include "ActionSelector.h"

#include "InterfaceManager.h"
#include "ResourceManager.h"
#include "MapManager.h"
#include "BuildingManager.h"
#include "WorldManager.h"

#include "MyLib.h"

#include "Build.h"
#include "Demolition.h"
#include "Move.h"

ActionSelector::ActionSelector()
{
	// �\���{�^��������
	ResetButtonList();
	// ������
	// �I�𒆂̍��W�̌����̏�����ɓ����
	GetSelectChipInfo();

	return;
}

void ActionSelector::Update()
{
	UpdateProcess();
	// �}�E�X���W�擾
	int MX, MY;
	GetMousePoint(&MX, &MY);
	Vector2D MPos = { (float)MX,(float)MY };

	// �{�^���̍X�V
	for (auto& obj : Button)
	{
		// �����蔻��X�V
		obj->HitStateUpdate(MPos);
	}

	// Esc�L�[�őO�̃C���^�[�t�F�[�X�ɖ߂�
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	{
		SelectBuilding = nullptr;
		InterfaceManager::GetInstance().BackInterface();
		return;
	}

	// ���N���b�N
	if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
	{
		// �������Ă����{�^���̃|�C���^�𓾂�
		ActionButton* hitObj = nullptr;		// ������Ԃ̓I�u�W�F�N�g�����݂��Ȃ�
		for (int i = 0; i < Button.size(); i++)
		{
			if (Button[i]->HitFlag)
			{
				hitObj = Button[i].get();
			}
		}
		// �������Ă����I�u�W�F�N�g�����݂���
		if (hitObj != nullptr)
		{
			// �������Ă����{�^���̎��ʎq�ʂ̏���
			switch (hitObj->Index)
			{
			case UI_Build:
			{
				InterfaceManager::GetInstance().AddInterface<Build>();
				return;
			}break;
			case UI_Demolition:
			{
				// �L�����N�^�[���A�C�e������ł����݂���Ή�̂��Ȃ�
				if (SelectBuilding->GetHasContents())
				{
					LogManager::GetInstance().Claim("�L�����N�^�[�������̓A�C�e�������݂��܂��B");
					LogManager::GetInstance().Claim("��̂Ɏ��s");
				}
				else
				{
					InterfaceManager::GetInstance().AddInterface<Demolition>();
				}
				return;
			}break;
			case UI_Move:
			{
				InterfaceManager::GetInstance().AddInterface<Move>();
				return;
			}break;
			default:
			{

			}break;
			}
		}
		// �N���b�N���W���{�^���ɐG��Ă��Ȃ�
		else
		{
			// ����UI�X�V
			ResetButtonList();
		}
	}
	return;
}

void ActionSelector::Draw()
{
	MapManager::GetInstance().Draw();			// �}�b�v�`��
	BuildingManager::GetInstance().Draw();		// �����`��
	UnitMovement::GetInstance().Draw();
	DrawSelectChip();		// �I�𒆂̃`�b�v����
	LogManager::GetInstance().Draw();
	DrawWindow();			// �E�B���h�E�`��
	DrawWorldInfo();		// ���E���`��
	DrawBuildingInfo();		// �����̏��`��

	if (!Button.empty())
	{
		for (auto& obj : Button)
		{
			obj->Draw();
		}
	}
	return;
}

void ActionSelector::ResetButtonList()
{
	// ���X�g���
	Button.clear();

	float X, Y;
	X = 50;
	Y = 50;

	// �N���b�N�����u�ԑI�����Ă����}�b�v�`�b�v���W�𓾂�
	MapManager::GetInstance().GetChipPos(SelectChip);
	// �N���b�N�������W�Ɍ���������΂��̌����̃|�C���^�𓾂�
	GetSelectChipInfo();

	// �y�n�ɉ����Ȃ��ꍇ
	if (!SelectBuilding)
	{
		// �����̓y�n�ŊC�ȊO
		if (MapManager::GetInstance().GetChipFactionIndex(SelectChip) == PLAYER_FACTIONINDEX &&
			MapManager::GetInstance().GetChipID(SelectChip) != MapManager::Chip_ID::Ocean)
		{
			// ����
			{
				ActionButton* obj = ActionButton::Create
				(Vector2D{ X,Y }, Vector2D{ X + SELECTBOX_SIZE,Y + SELECTBOX_SIZE },
					"����", Resource::GetInstance().Farm, ActionIndex::UI_Build);
				if (obj != nullptr)
				{
					unique_ptr<ActionButton> AddObj(obj);
					Button.push_back(std::move(AddObj));
					X += 50 + SELECTBOX_SIZE;
				}
			}
		}
	}
	// ����ꍇ
	else
	{
		// �����̐���
		if (MapManager::GetInstance().GetChipFactionIndex(SelectChip) == PLAYER_FACTIONINDEX)
		{
			// ���
			{
				ActionButton* obj = ActionButton::Create
				(Vector2D{ X,Y }, Vector2D{ X + SELECTBOX_SIZE,Y + SELECTBOX_SIZE },
					"���", Resource::GetInstance().Farm, ActionIndex::UI_Demolition);
				if (obj != nullptr)
				{
					unique_ptr<ActionButton> AddObj(obj);
					Button.push_back(std::move(AddObj));
					X += 50 + SELECTBOX_SIZE;
				}
			}
			// �ړ����I������
			{
				ActionButton* obj = ActionButton::Create
				(Vector2D{ X,Y }, Vector2D{ X + SELECTBOX_SIZE,Y + SELECTBOX_SIZE },
					"�ړ�", Resource::GetInstance().Farm, ActionIndex::UI_Move);
				if (obj != nullptr)
				{
					unique_ptr<ActionButton> AddObj(obj);
					Button.push_back(std::move(AddObj));
					X += 50 + SELECTBOX_SIZE;
				}
			}
		}
		// ������
		else if (MapManager::GetInstance().GetChipFactionIndex(SelectChip) < 1)
		{

		}
	}

	return;
}

ActionButton* ActionSelector::GetHitButton()
{
	for (auto& obj : ButtonList)
	{
		if (obj->HitFlag)
		{
			return obj.get();
		}
	}

	return nullptr;
}