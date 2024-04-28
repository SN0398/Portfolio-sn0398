#include "Build.h"
#include "InterfaceManager.h"
#include "BuildingManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "MapManager.h"

#include "Factory.h"
#include "Farm.h"
#include "Village.h"

#include "MessageBox.h"

Build::Build()
{
	LogManager::GetInstance().Claim("���݂��錚����I�����Ă�������");
	float X, Y;
	X = 50;
	Y = 50;
	ActionButton* obj = nullptr;
	obj = ActionButton::Create
	(Vector2D{ X,Y }, Vector2D{ X + SELECTBOX_SIZE,Y + SELECTBOX_SIZE },
		"��", &Resource::GetInstance().Village[0], BuildingType::BT_Village);
	if (obj != nullptr)
	{
		unique_ptr<ActionButton> AddObj(obj);
		Button.push_back(std::move(AddObj));
		X += 50 + SELECTBOX_SIZE;
	}
	obj = ActionButton::Create
	(Vector2D{ X,Y }, Vector2D{ X + SELECTBOX_SIZE,Y + SELECTBOX_SIZE },
		"�_��", &Resource::GetInstance().Farm[0], BuildingType::BT_Farm);
	if (obj != nullptr)
	{
		unique_ptr<ActionButton> AddObj(obj);
		Button.push_back(std::move(AddObj));
		X += 50 + SELECTBOX_SIZE;
	}
	obj = ActionButton::Create
	(Vector2D{ X,Y }, Vector2D{ X + SELECTBOX_SIZE,Y + SELECTBOX_SIZE },
		"�H��", &Resource::GetInstance().Factory[0], BuildingType::BT_Factory);
	if (obj != nullptr)
	{
		unique_ptr<ActionButton> AddObj(obj);
		Button.push_back(std::move(AddObj));
		X += 50 + SELECTBOX_SIZE;
	}

	return;
}

Build::~Build()
{
	Button.clear();

	return;
}

void Build::Update()
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
			if (AddBuildingProcess(hitObj->Index))
			{
				InterfaceManager::GetInstance().BackInterface();
			}
		}
	}
	return;

	//if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	//{
	//	InterfaceManager::GetInstance().BackInterface();
	//	return;
	//}

	//// �}�E�X���W�擾
	//int MouseX, MouseY;
	//GetMousePoint(&MouseX, &MouseY);
	//Vector2D MPos = { (float)MouseX,(float)MouseY };
	//for (auto& obj : Button)
	//{
	//	if (HitStateUpdate(obj, MPos) &&			// �����蔻��̍X�V�ƕԊ�
	//		MouseInput_Get(MOUSE_INPUT_LEFT) == 1)	// ���N���b�N���������u��
	//	{
	//		// �I�����W�Ɍ������Ȃ����
	//		if (!BuildingManager::GetInstance().GetBuildingInfo(SelectChip))
	//		{
	//			// �I�����W���C
	//			if (MapManager::GetInstance().GetChipID(SelectChip) == 1) { return; }
	//			int MaterialAmount = WorldManager::GetInstance().Item->GetItemAmount(ItemList::Item_ID::Material);
	//			if (MaterialAmount >= obj->MaterialCost)
	//			{
	//				
	//				// ���ނ������
	//				WorldManager::GetInstance().Item->ChangeItemAmount(ItemList::Item_ID::Material, -obj->MaterialCost);
	//				// ������ǉ����đO�̃C���^�[�t�F�[�X�ɖ߂�
	//				AddBuildingProcess(obj);
	//				InterfaceManager::GetInstance().BackInterface();
	//			}
	//		}
	//	}
	//}

	//return;
}

void Build::Draw()
{
	DrawProcess();
	if (!Button.empty())
	{
		for (auto& obj : Button)
		{
			obj->Draw();
		}
	}

	return;
}

bool Build::AddBuildingProcess(int type)
{
	switch (type)
	{
	case Build::BuildingType::BT_Factory:
	{
		BuildingManager::GetInstance().AddRequest(new Factory(SelectChip[0],SelectChip[1]));
		break;
	}
	case Build::BuildingType::BT_Farm:
	{
		BuildingManager::GetInstance().AddRequest(new Farm(SelectChip[0],SelectChip[1]));
		break;
	}
	case Build::BuildingType::BT_Village:
	{
		BuildingManager::GetInstance().AddRequest(new Village(SelectChip[0],SelectChip[1]));
		break;
	}
	default:
	{
		return false;
		break;
	}
	}

	return true;
}