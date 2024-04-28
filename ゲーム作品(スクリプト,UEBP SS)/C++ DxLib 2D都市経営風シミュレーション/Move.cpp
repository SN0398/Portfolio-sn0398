#include "Move.h"
#include "UnitMovement.h"
#include "InterfaceManager.h"
#include "ResourceManager.h"

Move::Move()
{
	// �n�_������
	StartChip[0] = SelectChip[0];
	StartChip[1] = SelectChip[1];
	moveBuilding = BuildingManager::GetInstance().GetBuildingInfo(StartChip);
	LogManager::GetInstance().Claim("�ړ�����w�肷��");
	int i = 0;
	int heightMult = 45;
	int height = 800;
	i* height;
	int* value = &moveResidents.Resident[ResidentList::Character::Citizen];
	slider.push_back(std::make_unique<SliderController>(value, &Resource::GetInstance().CharacterIcon[0], "�l��", height + i * heightMult, 100, 100 + BarLength, 0, moveBuilding->Residents->GetAllResident()));
	i++;
	value = &moveItems.Item[ItemList::Item_ID::Bread];
	slider.push_back(std::make_unique<SliderController>(value, &Resource::GetInstance().Items[0], "�H��", height + i * heightMult, 100, 100 + BarLength, 0, moveBuilding->Items->GetItemAmount(ItemList::Item_ID::Bread)));
	i++;
	value = &moveItems.Item[ItemList::Item_ID::Material];
	slider.push_back(std::make_unique<SliderController>(value, &Resource::GetInstance().Items[1], "����", height + i * heightMult, 100, 100 + BarLength, 0, moveBuilding->Items->GetItemAmount(ItemList::Item_ID::Material)));
}

void Move::Update()
{
	UpdateProcess();

	// �C���^�[�t�F�[�X��2�߂�
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	{
		InterfaceManager::GetInstance().BackInterface();
		InterfaceManager::GetInstance().BackInterface();
		return;
	}
	bool sliderSelected = false;

	for (auto& obj : slider)
	{
		// �X�V
		if (obj->controller.Update())
		{
			sliderSelected = true;
		}
	}
	
	if (!sliderSelected)
	{
		// ���N���b�N
		if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
		{
			// �J�[�\���̑I���`�b�v���X�V
			MapManager::GetInstance().GetChipPos(SelectChip);
			// �I���`�b�v���C�`�b�v�ȊO
			if (MapManager::GetInstance().GetChipID(SelectChip) != MapManager::Chip_ID::Ocean)
			{
				// �G�ΐ��͂̓y�n
				if (WorldManager::GetInstance().GetFactionRelation
				(MapManager::GetInstance().GetChipFactionIndex(SelectChip)) == FACTION_RELATION_STATE_ENEMY)
				{
					LogManager::GetInstance().Claim("�����͓G�ΐ��͂̓y�n��");
				}
				else if (!MapManager::GetInstance().GetIsFreeTerritory(SelectChip))
				{
					LogManager::GetInstance().Claim("�����͑����͂̓y�n��");
				}
				else
				{
					Position start = { StartChip[0],StartChip[1] };
					Position target = { SelectChip[0],SelectChip[1] };
					// �X���C�_�[�̒l�擾
					GetSliderValue();
					// �ړ������쐬
					int claimResponce = UnitMovement::GetInstance().Claim(start, target,
						moveBuilding, &moveItems, &moveResidents);
					// �߂�l�ʏ���
					if (claimResponce == UNITMOVEMENT_CLAIM_SUCCESS)
					{
						InterfaceManager::GetInstance().BackInterface();
						InterfaceManager::GetInstance().BackInterface();
					}
					else if (claimResponce == UNITMOVEMENT_CLAIM_DENIED_RESIDENT_IS_EMPTY)
					{
						LogManager::GetInstance().Claim("�ړ�������L�����N�^�[�����݂��Ȃ�");
					}
				}
			}
			else
			{
				LogManager::GetInstance().Claim("���Ӗ��ȓ����͂�߂悤");
			}
		}
	}

	return;
}

void Move::Draw()
{
	MapManager::GetInstance().Draw();
	BuildingManager::GetInstance().Draw();
	DrawStartChip();
	UnitMovement::GetInstance().Draw();
	LogManager::GetInstance().Draw();
	DrawWindow();
	DrawSlider();

	return;
}

void Move::DrawStartChip()
{
	// �`��ʒu�ƕ`�敝�擾
	Vector2D SelectPos = MapManager::GetInstance().GetDrawPos({ (float)StartChip[0],(float)StartChip[1] });
	int size = MapManager::GetInstance().GetChipSize();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	// �`��
	DrawBox
	(
		SelectPos.x,
		SelectPos.y,
		SelectPos.x + size,
		SelectPos.y + size,
		Resource::GetInstance().Color[Color_ID::Blue], TRUE
	);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	return;
}

void Move::DrawSlider()
{
	int i = 0;
	int height = 45;
	int graphsize = 32;
	for (auto& obj : slider)
	{
		DrawExtendGraph
		(
			obj->controller.L - 40,
			obj->controller.Y - 20,
			obj->controller.L - 40 + graphsize,
			obj->controller.Y - 20 + graphsize,
			*obj->Graph, TRUE
		);
		DrawFormatStringToHandle
		(
			obj->controller.L + 10,
			obj->controller.Y - 20,
			GetColor(0, 0, 0),
			Resource::GetInstance().Font[Font_ID::Yumincho_medium],
			FormatNumber(obj->controller.Get()).c_str()
		);
		DrawExtendGraph
		(
			obj->controller.L,
			obj->controller.Y - 5,
			obj->controller.R,
			obj->controller.Y + 5,
			Resource::GetInstance().Bar, FALSE
		);
		DrawExtendGraph
		(
			obj->controller.X - SliderGraphSize,
			obj->controller.Y - SliderGraphSize,
			obj->controller.X + SliderGraphSize,
			obj->controller.Y + SliderGraphSize,
			Resource::GetInstance().CircleUI, TRUE
		);
		i++;
	}
	return;
}

void Move::GetSliderValue()
{
	for (auto& obj : slider)
	{
		*obj->Value = obj->controller.Get();
	}
	return;
}