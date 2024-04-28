#include "MapManager.h"
#include "ResourceManager.h"
#include "BuildingManager.h"
#include "WorldManager.h"

void MapManager::SetUp()
{
	Position = Vector2D{ MAP_WIDTH * MAP_CHIP_SIZE_DEFAULT / 2,MAP_HEIGHT * MAP_CHIP_SIZE_DEFAULT / 2 };
 	ChipSize = MAP_CHIP_SIZE_DEFAULT;
	LoadData(MapChip, sizeof(MapChip), MAPDATAPATH);
	//LoadData(TerritoryMap, sizeof(TerritoryMap), TERRITORYDATAPATH);
	memset(TerritoryMap, NONE_FACTIONINDEX, sizeof(TerritoryMap));
	DrawTerritoryMap = false;

	DefaultCostTable[None] = -1;
	DefaultCostTable[Ocean] = 10;
	DefaultCostTable[Grass] = 1;
	DefaultCostTable[Sand] = 2;
	DefaultCostTable[Snow] = 2;
	DefaultCostTable[Gravel] = 2;

	return;
}

void MapManager::Update()
{
	// �Y�[���C���E�A�E�g����
	ZoomProcess();

	// �J�����̕��s�ړ�
	CameraMoveUpdate();

	// �J�[�\�����I�𒆂̃}�b�v���W�X�V
	CursorPositionUpdate();

	// �L�[���͂Ő��͕��z�}�b�v�\���ؑ�
	ChangeDrawTerritoryModify();

	return;
}

void MapManager::Draw()
{
	// �}�b�v�`��
	DrawMap();

	// �J�[�\���`��
	DrawCursor();

	// �f�o�b�O
	//DrawDebugInfo();

	return;
}

void MapManager::ZoomProcess()
{
	// �}�E�X�z�C�[���̉�]�ʂ��擾
	// �Ō�ɌĂ΂�Ă���}�E�X�z�C�[������]�����ʂ𓾂�
	int mouseRot = GetMouseWheelRotVol();
	// �}�E�X�z�C�[������]���Ă���
	if (mouseRot != 0)
	{
		if (ChipSize + mouseRot >= 10 && ChipSize + mouseRot <= 256)
		{
			// �}�b�v�`�b�v�T�C�Y���X�V
			ChipSize += mouseRot * (ChipSize / 8);

			// ���W�␳
			Position.y = (Position.y / (ChipSize - mouseRot)) * ChipSize;
			Position.x = (Position.x / (ChipSize - mouseRot)) * ChipSize;
		}
		else
		{
			// �}�b�v�`�b�v�T�C�Y���X�V
			ChipSize += mouseRot * (ChipSize / 8);
			// ���E�l�␳
			if (ChipSize < 10) { ChipSize = 10; }
			if (ChipSize > 256) { ChipSize = 256; }
		}
	}

	return;
}

void MapManager::CameraMoveUpdate()
{
	// 1�t���[���̈ړ��x�N�g��
	float VecX = 0;
	float VecY = 0;

	// �E�ړ�
	if (Keyboard_Get(KEY_INPUT_D) >= 1)
	{
		VecX += 1;
	}
	// ���ړ�
	if (Keyboard_Get(KEY_INPUT_A) >= 1)
	{
		VecX -= 1;
	}
	// ���ړ�
	if (Keyboard_Get(KEY_INPUT_S) >= 1)
	{
		VecY += 1;
	}
	// ��ړ�
	if (Keyboard_Get(KEY_INPUT_W) >= 1)
	{
		VecY -= 1;
	}
	// �ړ��x�N�g���̐��K��
	Vector2D move = Normalize_2D(GetVec2D(VecX, VecY));

	// ���W�Ɉړ��x�N�g�� * ���x�����Z�������
	Position = AddVec2D(Position, MulVec2D(move, CAMERA_MOVESPEED));

	// ���L�[�Œ����Ɉړ�
	if (Keyboard_Get(KEY_INPUT_DOWN) == 1)
	{
		Position.x = (MAP_WIDTH * ChipSize) / 2;
		Position.y = (MAP_HEIGHT * ChipSize) / 2;
	}
	// ���N���b�N�Ō��Ă���ꏊ�Ɉړ�
	if (MouseInput_Get(MOUSE_INPUT_RIGHT) == 1)
	{
		int MouseX, MouseY;
		GetMousePoint(&MouseX, &MouseY);
		// �}�b�v���W�擾
		Position.x = ((int)Position.x + (MouseX - (MAP_DRAWPOINTX + ((MAP_DRAWWIDTH - (MAP_DRAWWIDTH % (ChipSize * 2))) / 2))));
		Position.y = ((int)Position.y + (MouseY - (MAP_DRAWPOINTY + ((MAP_DRAWHEIGHT - (MAP_DRAWHEIGHT % (ChipSize * 2))) / 2))));
	}

	return;
}

void MapManager::CursorPositionUpdate()
{
	int MouseX, MouseY;
	GetMousePoint(&MouseX, &MouseY);

	// �}�b�v���W�擾
	SelectChip[0] = ((int)Position.x + (MouseX - (MAP_DRAWPOINTX + ((MAP_DRAWWIDTH - (MAP_DRAWWIDTH % (ChipSize * 2))) / 2))));
	SelectChip[1] = ((int)Position.y + (MouseY - (MAP_DRAWPOINTY + ((MAP_DRAWHEIGHT - (MAP_DRAWHEIGHT % (ChipSize * 2))) / 2))));

	// �J�[�\�����}�b�v���Ɏ��܂��Ă���t���O�𗧂Ă�
	CursorInMap = true;
	// �}�b�v���W��0~63�̊ԂłȂ�������t���O��܂�
	if (!GetMapChipValid(SelectChip))
	{
		CursorInMap = false;
	}

	return;
}

void MapManager::CostTableUpdate(int FactionIndex)
{
	// �R�X�g�̍X�V
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			// ������
			CostTable[i][j] = 0;
			// �`�b�v�̈ړ��R�X�g
			CostTable[i][j] += DefaultCostTable[MapChip[i][j]];
			// �����͈ȊO�̓y�n
			if (TerritoryMap[i][j] != FactionIndex)
			{
				CostTable[i][j] += 2;
			}
			// �F�D���͂��������̓y�n�ł͂Ȃ�
			if(WorldManager::GetInstance().Factions->List[FactionIndex]->
				GetRelationState(TerritoryMap[i][j]) != FACTION_RELATION_STATE_ALLY ||
				!GetIsFreeTerritory(i, j))
			{
				CostTable[i][j] += 3;
			}

			// �G�ΐ��͂̓y�n
			if (WorldManager::GetInstance().Factions->List[FactionIndex]->
				GetRelationState(TerritoryMap[i][j]) == FACTION_RELATION_STATE_ENEMY)
			{
				CostTable[i][j] += 5;
				int chip[2] = { i,j };
				// �G�ΐ��͂̌�������������ړ��s�\
				if (BuildingManager::GetInstance().GetBuildingInfo(chip))
				{
					CostTable[i][j] = -1;
					continue;
				}
			}
		}
	}

	return;
}

void MapManager::DrawMap()
{
	int MapDrawPointX, MapDrawPointY;		// �`�悷��}�b�v���W�l
	int DrawMapChipNumX, DrawMapChipNumY;	// �`�悷��}�b�v�`�b�v�̐�
	int DrawPointX, DrawPointY;				// �`�悷����W
	int ScrollX, ScrollY;					// �`��p�␳�l

	// �`�悷��}�b�v�`�b�v�̐����Z�b�g
	// �}�b�v�ɕ`��ł���`�b�v���ƕ␳�p�l
	DrawMapChipNumX = MAP_DRAWWIDTH / ChipSize + 2;
	DrawMapChipNumY = MAP_DRAWHEIGHT / ChipSize + 2;

	// ��ʍ���ɕ`�悷��}�b�v���W���Z�b�g
	MapDrawPointX = ((int)Position.x / ChipSize) - (DrawMapChipNumX / 2 - 1);
	MapDrawPointY = ((int)Position.y / ChipSize) - (DrawMapChipNumY / 2 - 1);

	// �`��ʒu���Z�b�g
	DrawPointX = MAP_DRAWPOINTX;
	DrawPointY = MAP_DRAWPOINTY;

	// �␳�l�̃Z�b�g
	ScrollX = -((int)Position.x % ChipSize);
	ScrollY = -((int)Position.y % ChipSize);

	// �}�b�v��`��
	for (int i = -1; i < DrawMapChipNumY; i++)
	{
		for (int j = -1; j < DrawMapChipNumX; j++)
		{
			// �`��ʒu�̍X�V
			DrawPointX = MAP_DRAWPOINTX + (j * ChipSize);
			DrawPointY = MAP_DRAWPOINTY + (i * ChipSize);

			// ��ʂ���͂ݏo���ʒu
			if (j + MapDrawPointX < 0 || i + MapDrawPointY < 0 ||
				j + MapDrawPointX >= MAP_WIDTH || i + MapDrawPointY >= MAP_HEIGHT)
			{
				// �C�`��
				DrawExtendGraph
				(
					DrawPointX + ScrollX,
					DrawPointY + ScrollY,
					DrawPointX + ScrollX + ChipSize,
					DrawPointY + ScrollY + ChipSize,
					Resource::GetInstance().Chip[1], FALSE
				);
				continue;
			}
			// �}�b�v�`��
			DrawExtendGraph
			(
				DrawPointX + ScrollX,
				DrawPointY + ScrollY,
				DrawPointX + ScrollX + ChipSize,
				DrawPointY + ScrollY + ChipSize,
				Resource::GetInstance().Chip[MapChip[i + MapDrawPointY][j + MapDrawPointX]], FALSE
			);
		}
	}
	// ���͒n�}�\���t���O
	if (DrawTerritoryMap)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		// �}�b�v��`��
		for (int i = -1; i < DrawMapChipNumY; i++)
		{
			for (int j = -1; j < DrawMapChipNumX; j++)
			{
				// �`��ʒu�̍X�V
				DrawPointX = MAP_DRAWPOINTX + (j * ChipSize);
				DrawPointY = MAP_DRAWPOINTY + (i * ChipSize);

				// ��ʂ���͂ݏo���ʒu
				if (j + MapDrawPointX < 0 || i + MapDrawPointY < 0 ||
					j + MapDrawPointX >= MAP_WIDTH || i + MapDrawPointY >= MAP_HEIGHT)
				{
					continue;
				}
				// �}�b�v�`��
				int factionIndex = TerritoryMap[i + MapDrawPointY][j + MapDrawPointX];
				// ���͂����݂��Ȃ���������s���Ȃ�
				if (factionIndex < WorldManager::GetInstance().Factions->List.size() &&
					factionIndex >= 1)
				{
					DrawBox
					(
						DrawPointX + ScrollX,
						DrawPointY + ScrollY,
						DrawPointX + ScrollX + ChipSize,
						DrawPointY + ScrollY + ChipSize,
						WorldManager::GetInstance().Factions->List[factionIndex]->Color,
						TRUE
					);
				}
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	return;
}

void MapManager::ChangeDrawTerritoryModify()
{
	// �L�[���͂Ő��͕��z�}�b�v�\���ؑ�
	if (Keyboard_Get(KEY_INPUT_F1) == 1)
	{
		++DrawTerritoryMap %= 2;
	}

	return;
}

void MapManager::DrawCursor()
{
	// �J�[�\�����}�b�v�`�b�v���Ɏ��܂��Ă���t���O�������Ă��Ȃ���Ώ����𔲂���
	if (!CursorInMap) { return; }
	// �ϐ�
	int DrawPointX, DrawPointY;				// �`�悷����W
	int MouseX, MouseY;						// �}�E�X�ʒu
	int ScrollX, ScrollY;					// �`��p�␳�l
	int SizeDiffX, SizeDiffY;				// �`��ʒu�ƃ`�b�v�T�C�Y�̍��W���
	int MPosX, MPosY;						// �J�[�\���őI�𒆂̉�ʓ��}�b�v���W

	GetMousePoint(&MouseX, &MouseY);

	// �␳�l�̃Z�b�g
	ScrollX = -((int)Position.x % ChipSize);
	ScrollY = -((int)Position.y % ChipSize);

	// ���W�ƃ`�b�v�T�C�Y�̕␳�l
	SizeDiffX = MAP_DRAWPOINTX % ChipSize;
	SizeDiffY = MAP_DRAWPOINTY % ChipSize;

	// �J�[�\���őI�𒆂̉�ʓ��}�b�v���W
	MPosX = ((MouseX - SizeDiffX - ScrollX) / ChipSize);
	MPosY = ((MouseY - SizeDiffY - ScrollY) / ChipSize);

	// �`��ʒu�̍X�V
	DrawPointX = MPosX * ChipSize + SizeDiffX;
	DrawPointY = MPosY * ChipSize + SizeDiffY;

	// ����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	// �J�[�\���`��
	DrawBox
	(
		DrawPointX + ScrollX,
		DrawPointY + ScrollY,
		DrawPointX + ScrollX + ChipSize,
		DrawPointY + ScrollY + ChipSize,
		Resource::GetInstance().Color[Color_ID::White], TRUE
	);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	return;
}

void MapManager::DrawDebugInfo()
{
	clsDx();
	printfDx("\n[Map Class]\n");
	printfDx("�J�������W<%0.1f,%0.1f>\n", Position.x, Position.y);
	printfDx("�J�������W(�`�b�v)<%d,%d>\n", (int)Position.x / ChipSize, (int)Position.y / ChipSize);
	printfDx("�I�����W<%d,%d>\n", SelectChip[0], SelectChip[1]);
	printfDx("�I�����W(�`�b�v)<%d,%d>\n", SelectChip[0] / ChipSize, SelectChip[1] / ChipSize);
	printfDx("InMap<%d>\n", CursorInMap);
	printfDx("Size<%d>\n", ChipSize);

	return;
}

Vector2D MapManager::GetDrawPos(Vector2D pos)
{
	int DrawDiffX = MAP_DRAWWIDTH / 2 % ChipSize;
	int DrawDiffY = MAP_DRAWHEIGHT / 2 % ChipSize;
	Vector2D result;
	result.x = (MAP_DRAWPOINTX + (MAP_DRAWWIDTH  / 2)) + ((pos.x * ChipSize) - ((int)Position.x) - DrawDiffX);
	result.y = (MAP_DRAWPOINTY + (MAP_DRAWHEIGHT / 2)) + ((pos.y * ChipSize) - ((int)Position.y) - DrawDiffY);
	return result;
}

void MapManager::GetChipPos(int* pChip)
{
	if (!CursorInMap || pChip == nullptr)
	{
		return; 
	}
	pChip[0] = SelectChip[0] / ChipSize;
	pChip[1] = SelectChip[1] / ChipSize;
	return;
}

bool MapManager::GetIsFreeTerritory(int* Pos)
{
	// ���͂̃C���f�b�N�X1�͎�����
	// 1�����͖�����

	// �v���C���[�����ł���y�n���ǂ������ʂ���
	if (TerritoryMap[Pos[1]][Pos[0]] <= 1)
	{
		return true;
	}
	return false;
}

bool MapManager::GetIsFreeTerritory(int x, int y)
{
	// ���͂̃C���f�b�N�X1�͎�����
	// 1�����͖�����

	// �v���C���[�����ł���y�n���ǂ������ʂ���
	if (TerritoryMap[y][x] <= 1)
	{
		return true;
	}
	return false;
}

void MapManager::ChangeTerritory(int* pChip, int index)
{
	if (pChip == nullptr) { return; }

	TerritoryMap[pChip[1]][pChip[0]] = index;

	return;
}

bool MapManager::GetMapChipValid(int Chip[2])
{
	// �}�b�v���W��0~63�̊ԂłȂ�������false��Ԃ�
	if (SelectChip[0] < 0 || SelectChip[0] > MAP_WIDTH * ChipSize ||
		SelectChip[1] < 0 || SelectChip[1] > MAP_HEIGHT * ChipSize)
	{
		return false;
	}
	return true;
}
