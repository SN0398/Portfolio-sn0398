#include "Object.h"
#include "DxLib.h"
#include "Define.h"
#include "Utility.h"

Data* CreateData()
{
	Data* data = (Data*)malloc(sizeof(Data));
	for (int i = 0;i < ENEMYMAXNUM;i++)
	{
		data->enemy[i] = CreateObject();
		GenerateEnemy(data->enemy[i]);
		data->head = CreateObjectNode();
	}

	return data;
}

void ReleaseData(Data* data)
{
	free(data);
	data = NULL;

	return;
}

Object* CreateObject()
{
	Object* object = (Object*)malloc(sizeof(Object));
	memset(object, 0, sizeof(Object));

	return object;
}

void ReleaseObject(Object* object)
{
	free(object);
	object = NULL;

	return;
}

void GenerateEnemy(Object* object)
{
	object->SpawnPointX = GetRand(MAPCHIPWIDTH - 2) * MAPCHIPSIZE + MAPCHIPSIZE / 2;
	object->SpawnPointY = GetRand(MAPCHIPHEIGHT - 2) * MAPCHIPSIZE + MAPCHIPSIZE / 2;
	object->X = object->SpawnPointX;
	object->Y = object->SpawnPointY;
	object->objecttype = OT_ENEMY;
	object->state = ES_IDLE;
	object->MoveSpeed = 7.0;
	object->AttackDelay = 100;
	object->Attack = 40;

	return;
}

void GenerateTreasureBox(Object* head, int ObjectX, int ObjectY, int objecttype)
{
	Object* Node = CreateObjectNode();

	Node->objecttype = objecttype;
	Node->SpawnPointX = 0;
	Node->SpawnPointY = 0;
	Node->X = ObjectX;
	Node->Y = ObjectY;
	Node->vecX = 0.0;
	Node->vecY = 0.0;
	Node->MoveSpeed = 0, 0;
	Node->AttackDelay = 0;
	Node->CoolDownCount = 0;
	Node->RespawnInterval = 0;
	Node->state = OS_IDLE;

	InsertObject(head, Node);

	return;
}

void ObjectUpdate(Data* data, int PlayerX, int PlayerY, int* PlayerHealth)
{
	for (int i = 0;i < ENEMYMAXNUM;i++)
	{
		StateFunction[data->enemy[i]->state](data->enemy[i], data->head, PlayerX, PlayerY, PlayerHealth);
	}

	return;
}

void AnimationInitialize(int* AnimIndex, int* AnimCount, int* AnimSpeed, const int AnimDelay)
{
	*AnimIndex = 0;
	*AnimCount = 0;
	*AnimSpeed = AnimDelay;
	return;
}

int AnimationUpdate(int* AnimIndex, int* AnimCount, const int AnimSpeed, const int AnimNum)
{
	// ���t���[�����Z����l����Ұ��ݑ��x�𒴂���α�Ұ��ݔԍ������Z
	if (++ * AnimCount > AnimSpeed)
	{
		// ��Ұ��ݔԍ����w��l�𒴂������Ұ��ݔԍ������������ĂP��Ԃ�
		if (++ * AnimIndex >= AnimNum)
		{
			*AnimIndex = 0;
			return 1;
		}
		*AnimCount = 0;
	}
	return 0;
}

void DrawObject(Data* data, Resource* resource, int PlayerX, int PlayerY)
{
	DrawEnemy(data, resource, PlayerX, PlayerY);
	DrawObjectList(data, resource, PlayerX, PlayerY);
	return;
}

void DrawEnemy(Data* data, Resource* resource, int PlayerX, int PlayerY)
{
	// �G�̕`��
	for (int i = 0;i < ENEMYMAXNUM;i++)
	{
		if (data->enemy[i]->state != ES_DEAD)
		{
			DrawExtendGraph
			(
				data->enemy[i]->X - (ENEMYGRAPHSIZEX / 2) - PlayerX + SCREEN_WIDTH / 2,
				data->enemy[i]->Y - (ENEMYGRAPHSIZEY / 2) - PlayerY + SCREEN_HEIGHT / 2,
				data->enemy[i]->X + (ENEMYGRAPHSIZEX / 2) - PlayerX + SCREEN_WIDTH / 2,
				data->enemy[i]->Y + (ENEMYGRAPHSIZEY / 2) - PlayerY + SCREEN_HEIGHT / 2,
				resource->EnemyHandle, TRUE
			);
			if (data->enemy[i]->state == ES_INDEATH)
			{
				DrawExtendGraph
				(
					data->enemy[i]->X - (ENEMYGRAPHSIZEX / 2) - PlayerX + SCREEN_WIDTH / 2,
					data->enemy[i]->Y - (ENEMYGRAPHSIZEY / 2) - PlayerY + SCREEN_HEIGHT / 2,
					data->enemy[i]->X + (ENEMYGRAPHSIZEX / 2) - PlayerX + SCREEN_WIDTH / 2,
					data->enemy[i]->Y + (ENEMYGRAPHSIZEY / 2) - PlayerY + SCREEN_HEIGHT / 2,
					resource->ExplosionHandle[data->enemy[i]->AnimIndex], TRUE
				);
			}
			//DrawFormatString
			//(
			//	data->enemy[i]->X - (ENEMYGRAPHSIZEX / 2) - PlayerX + SCREEN_WIDTH / 2,
			//	data->enemy[i]->Y - (ENEMYGRAPHSIZEY / 2) - PlayerY + SCREEN_HEIGHT / 2,
			//	GetColor(255, 0, 0),
			//	"%d %d\n%0.1f",
			//	(int)data->enemy[i]->Y / ENEMYGRAPHSIZEY,
			//	(int)data->enemy[i]->X / ENEMYGRAPHSIZEX,
			//	GetDistance_2D(data->enemy[i]->X, data->enemy[i]->Y, PlayerX, PlayerY)
			//);
		}
		
	}

	return;
}

void DrawObjectList(Data* data, Resource* resource, int PlayerX, int PlayerY)
{
	// �m�[�h�Ƀ_�~�[�������Ȃ���΃v���O�����𔲂���
	if (data->head->NextNode == data->head) { return; }
	// ����m�[�h���_�~�[���������擪�m�[�h�ɂ���
	Object* Node = data->head->NextNode;
	// ����m�[�h���_�~�[�ɂȂ�܂ŌJ��Ԃ�
	while (Node != data->head)
	{
		// �����W - ( �����l - �X�N���[���l / 2 )
		DrawExtendGraph
		(
			Node->X - (PlayerX + TREASUREGRAPHSIZEX/2 - SCREEN_WIDTH / 2),
			Node->Y - (PlayerY + TREASUREGRAPHSIZEY/2 - SCREEN_HEIGHT / 2),
			Node->X - (PlayerX - TREASUREGRAPHSIZEX/2 - SCREEN_WIDTH / 2),
			Node->Y - (PlayerY - TREASUREGRAPHSIZEY/2 - SCREEN_HEIGHT / 2),
			resource->TreasureBoxHandle, TRUE
		);
		// ����m�[�h�����̃m�[�h�ɂ���
		Node = Node->NextNode;
	}

	return;
}

Object* CreateObjectNode()
{
	Object* Node = (Object*)malloc(sizeof(Object));
	Node->NextNode = Node;
	Node->PrevNode = Node;

	return Node;
}

void InsertObject(Object* Head, Object* Node)
{
	Object* AddNode = Node;
	Object* HeadNode = Head;
	Object* PrevNode = Head->PrevNode;

	HeadNode->PrevNode = AddNode;
	PrevNode->NextNode = AddNode;

	AddNode->NextNode = HeadNode;
	AddNode->PrevNode = PrevNode;

	return;
}

Object* DetachObject(Object* Node)
{
	// �폜����m�[�h�̃o�b�t�@
	Object* DelNode = Node;
	// �폜�m�[�h�̈�O�̃m�[�h�̃|�C���^��ۑ����Ă���
	Object* PrevNode = Node->PrevNode;
	// �폜�m�[�h�̑O��m�[�h�̎Q�Ƃ�ύX����
	DelNode->PrevNode->NextNode = DelNode->NextNode;
	DelNode->NextNode->PrevNode = DelNode->PrevNode;
	// �m�[�h���폜
	free(DelNode);

	return PrevNode;
}

void ReleaseObjectList(Object* Head)
{
	Object* Node = Head->NextNode;
	Object* DelNode = Node;
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

void EnemyIdleProcess(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth)
{
	// �v���C���[�����G�͈͓��ɐN��������ǐՏ�ԂɑJ�ڂ�����
	if (GetDistance_2D(object->X, object->Y, PlayerX, PlayerY) < 1600)
	{
		object->state = ES_CHASE;
	}

	return;
}

void EnemyChaseProcess(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth)
{
	// �v���C���[�Ɍ������Ĉړ�
	object->vecX = PlayerX - object->X;
	object->vecY = PlayerY - object->Y;
	Normalize_2D(&object->vecX, &object->vecY);
	object->vecX *= object->MoveSpeed;
	object->vecY *= object->MoveSpeed;
	object->X += object->vecX;
	object->Y += object->vecY;
	// �v���C���[�����G�͈͂���O�ꂽ��A�C�h����ԂɑJ��
	if (GetDistance_2D(object->X, object->Y, PlayerX, PlayerY) > 1600)
	{
		object->state = ES_IDLE;
	}
	// �v���C���[���U���͈͂ɓ�������U����ԂɑJ��
	if (GetDistance_2D(object->X, object->Y, PlayerX, PlayerY) < 50)
	{
		*PlayerHealth -= object->Attack;
		if (*PlayerHealth < 0) { *PlayerHealth = 0; }
		object->state = ES_ATTACK;
	}

	return;
}

void EnemyAttackProcess(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth)
{
	if (++object->CoolDownCount > object->AttackDelay)
	{
		object->CoolDownCount = 0;
		object->state = ES_IDLE;
	}
}

void EnemyInDeathProcess(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth)
{
	if (AnimationUpdate(&object->AnimIndex, &object->AnimCount, object->AnimSpeed, 7))
	{
		GenerateTreasureBox(head, object->X, object->Y, OT_TREASURE);
		object->state = ES_DEAD;
	}
	
	return;
}

void EnemyDeadProcess(Object* object, Object* head, int PlayerX, int PlayerY, int* PlayerHealth)
{
	if (++object->RespawnInterval > ENEMYRESPAWNINTERVAL)
	{
		object->RespawnInterval = 0;
		GenerateEnemy(object);
	}

	return;
}