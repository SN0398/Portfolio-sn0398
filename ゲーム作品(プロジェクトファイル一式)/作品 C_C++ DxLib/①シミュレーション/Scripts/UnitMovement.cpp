#include "UnitMovement.h"
#include "MapManager.h"
#include "ResourceManager.h"
#include "BuildingManager.h"
#include "WorldManager.h"
#include "Camp.h"
#include "LogManager.h"

void UnitMovement::Update()
{
	int Chipsize = MapManager::GetInstance().GetChipSize();
	// �ړ����Ă��镔���̍X�V
	for (auto& obj : dataList)
	{
		// �J�E���^���ő�ɓ��B�ō��W���ړ�����
		obj->Count += obj->MoveSpeed;
		if (obj->Count >= UNITMOVEMENT_MAXCOUNT)
		{
			// �擪�m�[�h���W�����݂̍��W�ɂ���
			obj->NowPos = obj->Route[0]->pos;
			// �擪�m�[�h���폜
			obj->Route.erase(obj->Route.begin());
			// �J�E���^������
			obj->Count = 0;
		}
		// �ړI�n�ɓ����ňړ����I��
		if (obj->Route.empty())
		{
			// ���W�ϊ�
			int pos[2] = { obj->NowPos.x,obj->NowPos.y };
			// �ړ���Ɍ���������Έړ����Ă���폜
			auto goalNode = BuildingManager::GetInstance().GetBuildingInfo(pos);
			if (goalNode)
			{
				*goalNode->Items += obj->Inventory;
				*goalNode->Residents += obj->Residents;
			}
			// �ړ���ɉ����Ȃ���΃L�����v��ݒu����
			else
			{
				Building* addObj = new Camp(obj->NowPos.x, obj->NowPos.y);
				*addObj->Items += obj->Inventory;
				*addObj->Residents += obj->Residents;
				BuildingManager::GetInstance().AddRequest(addObj);
			}
			// �������̓y�n�Ȃ玩���̓y�n�ɂ���
			if (MapManager::GetInstance().GetChipFactionIndex(pos) == NONE_FACTIONINDEX)
			{
				MapManager::GetInstance().ChangeTerritory(pos, PLAYER_FACTIONINDEX);
			}
			// ���O�ǉ�
			string str = "��������������";
			LogManager::GetInstance().Claim(str.c_str());
			// �I�u�W�F�N�g�����݂���C�e���[�^���擾
			auto itr = std::find(dataList.begin(), dataList.end(), obj);
			// �I�u�W�F�N�g�폜
			delete *itr;
			dataList.erase(itr);
			return;
		}
		// �I�t�Z�b�g�̍X�V	�J�E���^ * �`�b�v�T�C�Y * ����
		obj->offsetX = (obj->Count / UNITMOVEMENT_MAXCOUNT) *
			Chipsize * (obj->Route[0]->pos.x - obj->NowPos.x);
		obj->offsetY = (obj->Count / UNITMOVEMENT_MAXCOUNT) *
			Chipsize * (obj->Route[0]->pos.y - obj->NowPos.y);
	}

	return;
}

void UnitMovement::Draw()
{
	DrawInfo();

	// �ړ����Ă��镔���̕`��
	for (auto& obj : dataList)
	{
		// �`����W
		Vector2D DrawPos = 
			MapManager::GetInstance().GetDrawPos({ (float)obj->NowPos.x,(float)obj->NowPos.y });
		// �`��T�C�Y
		int size = MapManager::GetInstance().GetChipSize();

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

		// �`��
		DrawBox
		(
			DrawPos.x,
			DrawPos.y,
			DrawPos.x + size,
			DrawPos.y + size,
			Resource::GetInstance().Color[Color_ID::Blue], TRUE
		);
		for (auto& node : obj->Route)
		{
			// �`��ʒu�ƕ`�敝�擾
			Vector2D startPos = MapManager::GetInstance().GetDrawPos({ (float)node->pos.x,(float)node->pos.y });

			// �`��
			DrawBox
			(
				startPos.x,
				startPos.y,
				startPos.x + size,
				startPos.y + size,
				Resource::GetInstance().Color[Color_ID::Blue], TRUE
			);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// �`��
		DrawCircle
		(
			DrawPos.x + size / 2 + obj->offsetX,
			DrawPos.y + size / 2 + obj->offsetY,
			size / 4,
			GetColor(157, 255, 132),
			TRUE
		);
		DrawCircle
		(
			DrawPos.x + size / 2 + obj->offsetX,
			DrawPos.y + size / 2 + obj->offsetY,
			size / 4,
			GetColor(0, 0, 0),
			FALSE, 5
		);
	}

	return;
}

void UnitMovement::DrawInfo()
{


	return;
}

int UnitMovement::Claim(Position start, Position goal, Building* base, ItemList* moveItems, ResidentList* moveResidents)
{
	// �L�����N�^�[�����݂��Ȃ���Έړ�������ǉ����Ȃ�
	if (moveResidents->GetAllResident() < 1) { return UNITMOVEMENT_CLAIM_DENIED_RESIDENT_IS_EMPTY; }

	UnitData* temp = new UnitData;

	// �ϐ�������
	temp->offsetX = 0.0f;
	temp->offsetY = 0.0f;
	temp->Count = 0;

	// �R�X�g�e�[�u���X�V
	MapManager::GetInstance().CostTableUpdate(MapManager::GetInstance().GetChipFactionIndex(start.x, start.y));

	// �o�H�T��
	temp->Route = Astar::AStarAlgorithm(start, goal);

	// �����ʒu����
	temp->NowPos = start;

	// ���_���畨�������o��
	temp->Inventory = *moveItems;
	*base->Items -= *moveItems;

	// ���_����L�����N�^�[���ړ�����
	temp->Residents = *moveResidents;
	*base->Residents -= *moveResidents;

	// �����s�R�X�s�[�h���Z�o
	temp->MoveSpeed = 300;

	dataList.push_back(temp);

	return UNITMOVEMENT_CLAIM_SUCCESS;
}