#include "Start.h"
#include "BuildingManager.h"
#include "MapManager.h"
#include "InterfaceManager.h"
#include "LogManager.h"
#include "ChipSelect.h"
#include "Village.h"

Start::Start()
{
	Dialogue = MessageInterface_Ok::Create("Override�ւ悤����!");
}

void Start::Update()
{
	// �V���O���g���N���X�̕ʖ�
	auto& buildingMgr = BuildingManager::GetInstance();
	auto& mapMgr = MapManager::GetInstance();
	auto& interfaceMgr = InterfaceManager::GetInstance();

	// �_�C�A���O���A�N�e�B�u�ȏ��
	if (Dialogue != nullptr)
	{
		// ���b�Z�[�W�{�b�N�X�̍X�V
		// ����
		if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
		{
			int x, y;
			GetMousePoint(&x, &y);
			Vector2D Mpos = { (float)x, (float)y };
			Dialogue->HitStateUpdate(Mpos);
			if (Dialogue->GetHitState() == SELECTED_OK)
			{
				Dialogue = nullptr;
			}
		}
		if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1 ||
			Keyboard_Get(KEY_INPUT_SPACE) == 1)
		{
			Dialogue = nullptr;
		}
		if (Dialogue == nullptr)
		{
			LogManager::GetInstance().Claim("�ŏ��̋��_��I�����Ă�������");
			LogManager::GetInstance().Claim("WASD...���_�ړ�");
			LogManager::GetInstance().Claim("���N���b�N...�I��");
		}
	}
	else
	{
		mapMgr.Update();
		LogManager::GetInstance().Update();

		// �}�E�X�N���b�N�Ō�����ǉ����Ēʏ�UI�ɐ؂�ւ�
		if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
		{
			// �ǉ����錚����������
			int pos[2];
			mapMgr.GetChipPos(pos);			// �J�[�\���ʒu�擾
			// �������l�Ŏ��s
			if (mapMgr.GetMapChipValid(pos))
			{
				// �I�������ꏊ�Ɍ������Ȃ��A�C�`�b�v�ȊO�Ȃ猚����ǉ�����
				if (mapMgr.GetChipID(pos) != MapManager::Chip_ID::Ocean &&
					buildingMgr.GetBuildingInfo(pos) == nullptr)
				{
					Building* AddObj = new Village(pos[0], pos[1]);		// �_������

					AddObj->Items->SetItemAmount(ItemList::Item_ID::Bread, 500);
					AddObj->Items->SetItemAmount(ItemList::Item_ID::Material, 250);
					AddObj->Residents->SetResidents(ResidentList::Character::Farmer, 30);
					AddObj->Residents->SetResidents(ResidentList::Character::Soldier, 10);
					AddObj->Residents->SetResidents(ResidentList::Character::Builder, 10);

					// �ǉ�
					buildingMgr.AddRequest(AddObj);
					// �I�����W�������̐��͂̓y�n�ɂ���
					mapMgr.ChangeTerritory(pos, 1);
					// �C���^�[�t�F�[�X�؂�ւ�
					interfaceMgr.PopTopInterface();
					interfaceMgr.AddInterface<ChipSelect>();
					return;
				}
				else
				{
					LogManager::GetInstance().Claim("�����ɂ͌��Ă��Ȃ�");
				}
			}
		}
	}

	return;
}

void Start::Draw()
{
	MapManager::GetInstance().DrawMap();
	MapManager::GetInstance().DrawCursor();
	BuildingManager::GetInstance().Draw();
	LogManager::GetInstance().Draw();

	// �_�C�A���O���A�N�e�B�u�ȏ��
	if (Dialogue != nullptr)
	{
		Dialogue->Draw();
	}

	return;
}