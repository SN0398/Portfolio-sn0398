#include "Player.h"
#include "DxLib.h"
#include "Utility.h"
#include "Define.h"

#include <math.h>

Player* CreatePlayer()
{
	Player* player = (Player*)malloc(sizeof(Player));
	memset(player, 0, sizeof(player));

	player->Head = CreateBullet(player->Head);

	player->x = MAPCHIPWIDTH / 2 * MAPCHIPSIZE;
	player->y = MAPCHIPHEIGHT / 2 * MAPCHIPSIZE;
	player->MoveSpeed = 5.0;
	player->Health = DEFAULTMAXHEALTH;
	player->Gold = 0;

	return player;
}

int PlayerUpdate(Player* player, int CollData[][MAPCHIPWIDTH], Data* data)
{
	if (player->Health <= 0) { return 1; }
	// �ړ�����
	PlayerMoveProcess(player, CollData);
	// �e�̐�������
	GenerateBulletProcess(player->Head, player);
	// �e�̏���
	BulletUpdate(player->Head, player, data);

	return 0;
}

void PlayerMoveProcess(Player* player, int CollData[][MAPCHIPWIDTH])
{
	// �ړ��x�N�g����������
	player->vecx = 0;
	player->vecy = 0;
	// �����x�N�g����������
	player->DirectionX = 0;
	player->DirectionY = 0;
	// ���͏���
	MoveProcess(&player->vecx, &player->vecy, player->MoveSpeed);
	if (Keyboard_Get(KEY_INPUT_RIGHT) >= 1 || Keyboard_Get(KEY_INPUT_D) >= 1)
	{
		player->DirectionX += 1;
	}
	if (Keyboard_Get(KEY_INPUT_LEFT) >= 1 || Keyboard_Get(KEY_INPUT_A) >= 1)
	{
		player->DirectionX -= 1;
	}
	if (Keyboard_Get(KEY_INPUT_DOWN) >= 1 || Keyboard_Get(KEY_INPUT_S) >= 1)
	{
		player->DirectionY += 1;
	}
	if (Keyboard_Get(KEY_INPUT_UP) >= 1 || Keyboard_Get(KEY_INPUT_W) >= 1)
	{
		player->DirectionY -= 1;
	}
	// �����蔻��	// �v���P�H
	int MoveX, MoveY;
	MoveX = (player->x + (player->DirectionX * MAPCHIPSIZE / 2) + player->vecx) / MAPCHIPSIZE;
	MoveY = player->y / MAPCHIPSIZE;
	if (CollData[MoveY][MoveX] == 1)
	{
		player->vecx = 0;
		player->x = (((MoveX * MAPCHIPSIZE) + MAPCHIPSIZE / 2) + (-player->DirectionX * MAPCHIPSIZE) / 2) - (player->DirectionX * MAPCHIPSIZE / 2);
	}
	MoveX = player->x / MAPCHIPSIZE;
	MoveY = (player->y + (player->DirectionY * MAPCHIPSIZE / 2) + player->vecy) / MAPCHIPSIZE;
	if (CollData[MoveY][MoveX] == 1)
	{
		player->vecy = 0;
		player->y = (((MoveY * MAPCHIPSIZE) + MAPCHIPSIZE / 2) + (-player->DirectionY * MAPCHIPSIZE) / 2) - (player->DirectionY * MAPCHIPSIZE / 2);
	}
	// ���Z
	player->x += player->vecx;
	player->y += player->vecy;

	return;
}

void DrawPlayer(Player* player, Resource* resource)
{
	// �e�̕`��֐�
	DrawBullet(player->Head, player, resource);
	// �v���C���[�̕`��
	// �v���C���[�����W - ( �v���C���[�����W - �X�N���[���l / 2 )
	DrawExtendGraph
	(
		player->x - (player->x + PLAYERGRAPHSIZEX / 2 - SCREEN_WIDTH / 2),
		player->y - (player->y + PLAYERGRAPHSIZEY / 2 - SCREEN_HEIGHT / 2),
		player->x - (player->x + PLAYERGRAPHSIZEX / 2 - SCREEN_WIDTH / 2) + PLAYERGRAPHSIZEX,
		player->y - (player->y + PLAYERGRAPHSIZEY / 2 - SCREEN_HEIGHT / 2) + PLAYERGRAPHSIZEY,
		resource->PlayerHandle, TRUE
	);
	DrawHealth(player, resource);
	DrawFormatString(220, 20, resource->CHandle[9], "G : %d", player->Gold);
	
	return;
}

void DrawHealth(Player* player, Resource* resource)
{
	DrawExtendGraph(15, 15, 205, 45, resource->MenuUIHandle, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);		//�u�����h���[�h����(128/255)�ɐݒ�
	DrawBox
	(
		20,
		20,
		200,
		40,
		resource->CHandle[1], TRUE
	);
	DrawBox
	(
		20,
		20,
		20 + ((float)player->Health / DEFAULTMAXHEALTH) * (200 - 20),
		40,
		resource->CHandle[2], TRUE
	);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t

	return;
}

void ReleasePlayer(Player* player)
{
	ReleaseBullet(player->Head);

	free(player);
	player = NULL;
	return;
}

Bullet* CreateBullet(Bullet* Head)
{
	Bullet* Node = (Bullet*)malloc(sizeof(Bullet));
	Node->NextNode = Node;
	Node->PrevNode = Node;

	return Node;
}

void InsertBullet(Bullet* Head, Bullet* Node)
{
	Bullet* AddNode = Node;
	Bullet* HeadNode = Head;
	Bullet* PrevNode = Head->PrevNode;

	HeadNode->PrevNode = AddNode;
	PrevNode->NextNode = AddNode;

	AddNode->NextNode = HeadNode;
	AddNode->PrevNode = PrevNode;

	return;
}

Bullet* DetachBullet(Bullet* Node)
{
	// �폜����m�[�h�̃o�b�t�@
	Bullet* DelNode = Node;
	// �폜�m�[�h�̈�O�̃m�[�h�̃|�C���^��ۑ����Ă���
	Bullet* PrevNode = Node->PrevNode;
	// �폜�m�[�h�̑O��m�[�h�̎Q�Ƃ�ύX����
	DelNode->PrevNode->NextNode = DelNode->NextNode;
	DelNode->NextNode->PrevNode = DelNode->PrevNode;
	// �m�[�h���폜
	free(DelNode);

	return PrevNode;
}

void ReleaseBullet(Bullet* Head)
{
	Bullet* Node = Head->NextNode;
	Bullet* DelNode = Node;
	while (Head != Node)
	{
		DelNode = Node;
		Node = Node->NextNode;
		free(DelNode);
		DelNode = NULL;
	}

	free(Head);
	Head = NULL;
	return;
}

void BulletUpdate(Bullet* Head, Player* player, Data* data)
{
	HitProcessPlayerToTreasureBox(player, data);
	if (Head == NULL) { return; }
	if (Head->NextNode == NULL) { return; }
	Bullet* head = Head;
	Bullet* Node = head->NextNode;
	while (Node != head)
	{
		HitProcessBulletToEnemy(player, Node, data);
		Node = BulletMoveProcess(Node, player);
	}

	return;
}

Bullet* BulletMoveProcess(Bullet* Node, Player* player)
{
	Bullet* node = Node;
	node->x += node->vecX * node->Speed;
	node->y += node->vecY * node->Speed;
	//node->x += cos(node->Angle) * node->Speed;
	//node->y += sin(node->Angle) * node->Speed;
	if(
			Node->x - (player->x - SCREEN_WIDTH / 2) < 0 ||
			Node->x - (player->x - SCREEN_WIDTH / 2) > SCREEN_WIDTH ||
			Node->y - (player->y - SCREEN_HEIGHT / 2) < 0 ||
			Node->y - (player->y - SCREEN_HEIGHT / 2) > SCREEN_HEIGHT)
	{
		node = DetachBullet(node);
	}

	return node->NextNode;
}

void GenerateBulletProcess(Bullet* Head, Player* player)
{
	// ���N���b�N�Ńm�[�h�쐬�E�}��
	if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
	{
		Bullet* Node = CreateBullet(Head);
		int x, y;
		GetMousePoint(&x, &y);
		Node->x = player->x;
		Node->y = player->y;
		Node->vecX = x - SCREEN_WIDTH / 2;
		Node->vecY = y - SCREEN_HEIGHT / 2;
		Normalize_2D(&Node->vecX, &Node->vecY);
		//x = (x - SCREEN_WIDTH / 2);
		//y = -(y - SCREEN_HEIGHT / 2);
		//Node->Angle = (float)atan2((double)x, (double)y) * 180 / DX_PI -45;
		Node->Speed = 5.0;
		Node->State = 1;

		InsertBullet(Head, Node);
		
	}
	return;
}

void HitProcessBulletToEnemy(Player* player, Bullet* Node, Data* data)
{
	// �ʂƓG�̐ڐG����
	{
		for (int i = 0; i < ENEMYMAXNUM; i++)
		{
			// ��Ԃ����S�F���S���ł͂Ȃ�
			if (data->enemy[i]->state < ES_INDEATH)
			{
				// �_�Ƌ�`�̓����蔻��
				if (Node->x >= data->enemy[i]->X - (ENEMYGRAPHSIZEX / 2) &&
					Node->x <= data->enemy[i]->X + (ENEMYGRAPHSIZEY / 2) &&
					Node->y >= data->enemy[i]->Y - (ENEMYGRAPHSIZEX / 2) &&
					Node->y <= data->enemy[i]->Y + (ENEMYGRAPHSIZEY / 2))
				{
					// �m����Ԃɂ���
					data->enemy[i]->state = ES_INDEATH;
					// �m���A�j���[�V����������
					AnimationInitialize(&data->enemy[i]->AnimIndex, &data->enemy[i]->AnimCount, &data->enemy[i]->AnimSpeed, 5);
				}
			}
		}
	}
	return;
}

void HitProcessPlayerToTreasureBox(Player* player, Data* data)
{
	// �󔠂ƃv���C���[�̐ڐG����
	{
		// �m�[�h�Ƀ_�~�[�������Ȃ���΃v���O�����𔲂���
		if (data->head->NextNode == data->head) { return; }
		// ����m�[�h���_�~�[���������擪�m�[�h�ɂ���
		Object* node = data->head->NextNode;
		// ����m�[�h���_�~�[�ɂȂ�܂ŌJ��Ԃ�
		while (node != data->head)
		{
			// �v���C���[�ƕ󔠂̋�����50����
			if (GetDistance_2D(player->x, player->y, node->X, node->Y) < 50)
			{
				// �X�R�A���Z
				player->Gold += 200;
				// �m�[�h�폜
				node = DetachObject(node);
			}
			//printfDx("%0.1f %0.1f %0.1f %0.1f %0.1f\n", GetDistance_2D(player->x, player->y, node->X, node->Y), player->x, player->y, node->X, node->Y);
			// ����m�[�h�����̃m�[�h�ɂ���
			node = node->NextNode;
		}
	}

	return;
}

void DrawBullet(Bullet* Head, Player* player, Resource* resource)
{
	// �m�[�h�Ƀ_�~�[�������Ȃ���΃v���O�����𔲂���
	if (Head->NextNode == Head) { return; }
	// ����m�[�h���_�~�[���������擪�m�[�h�ɂ���
	Bullet* Node = Head->NextNode;
	// ����m�[�h���_�~�[�ɂȂ�܂ŌJ��Ԃ�
	while (Node != Head)
	{
		// �e���ł��o����Ă����ԂȂ�`�悷��
		// �����W - ( �����l - �X�N���[���l / 2 )
		if (Node->State == 1)
		{
			DrawExtendGraph
			(
				Node->x - (player->x - BULLETRADIUS - SCREEN_WIDTH / 2),
				Node->y - (player->y - BULLETRADIUS - SCREEN_HEIGHT / 2),
				Node->x - (player->x + BULLETRADIUS - SCREEN_WIDTH / 2),
				Node->y - (player->y + BULLETRADIUS - SCREEN_HEIGHT / 2),
				resource->BulletHandle, TRUE
			);
		}
		// ����m�[�h�����̃m�[�h�ɂ���
		Node = Node->NextNode;
	}

	return;
}