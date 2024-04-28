#include "Enemy.h"
#include <math.h>

EnemyList* EnemyInit()
{
	// �������m��
	EnemyList* list = (EnemyList*)malloc(sizeof(EnemyList));

	// �G�̐�����������
	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		list->enemy[i] = CreateEnemy(VGet(-1000.0f + i * 200.0f, 0.0f, 1000.0f));
	}

	return list;
}

void EnemyClean(EnemyList* list)
{
	// �������j��
	free(list);
	list = NULL;
	return;
}

Enemy* CreateEnemy(VECTOR position)
{
	// �������m��
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));

	// ������
	enemy->ModelHandle = MV1LoadModel("Data/Models/Player/ROKN ngear/F-35E ROKN.mv1");	// ���f���̃n���h��
	enemy->position = position;	// �����ʒu
	enemy->Speed = 15.0f;	// �ړ����x
	enemy->direction = { 0.0f,0.0f,1.0f };	// �i�s����

	// �傫���ύX
	MV1SetScale(enemy->ModelHandle, VScale(VGet(1.0f, 1.0f, 1.0f), 0.5f));
	// ���f���S�̂̃R���W���������\�z
	MV1SetupCollInfo(enemy->ModelHandle, -1, 8, 8, 8);

	return enemy;
}

void ReleaseEnemy(Enemy* enemy)
{
	// �������j��
	free(enemy);
	enemy = NULL;
	return;
}

void EnemyListUpdate(EnemyList* list, VECTOR target, BulletData* bdata)
{
	// �G�̐���������
	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		EnemyUpdate(list->enemy[i], target, bdata);
	}
	return;
}

void EnemyUpdate(Enemy* enemy, VECTOR target, BulletData* bdata)
{
	// �ڕW�̈ʒu���X�V����
	enemy->target = target;
	
	// �ړ�����
	{
		// �ړ��x�N�g��������
		enemy->move = VGet(0.0f, 0.0f, 0.0f);
		// �ړ��x�N�g���͐i�s����*�ړ����x
		enemy->move = VScale(enemy->direction, enemy->Speed);
		// �ړ��x�N�g�����Z
		enemy->position = VAdd(enemy->position, enemy->move);
		// ���f���ɍ��W��ݒ�
		MV1SetPosition(enemy->ModelHandle, enemy->position);
	}
	// ��������
	{
		// �i�s�����̍X�V �z�[�~���O
		VECTOR addDir = VScale(VNorm(VSub(target, enemy->position)), 0.01f);
		enemy->direction = VNorm(VAdd(enemy->direction, addDir));

		enemy->rotation = VSub(enemy->position, VAdd(enemy->position, enemy->move));
		// ���f���̌������Z�b�g(�i�s����)
		MV1SetRotationZYAxis(enemy->ModelHandle, enemy->rotation, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	}
	// �C�ʂɐڐG�������A�N�e�B�u�ɂ���
	if (enemy->position.y <= -5500.0f)
	{
		enemy->State = ES_NOTOK;
	}
	if (enemy->State == ES_NOTOK)
	{
		enemy->State = ES_DEAD;
	}
	if (enemy->State == ES_DEAD)
	{
		enemy->position = { 0.0f,0.0f,0.0f };
		enemy->State = ES_OK;
	}

	// �e�ƓG�̓����蔻��i�͈͂Ŕ���j
	CheckHitUpdate(enemy, bdata);

	return;
}

void CheckHitUpdate(Enemy* enemy, BulletData* bdata)
{
	Bullet* bullet;
	float X, Y, Z;

	for (int i = 0; i < BULLETMAXNUM; i++)
	{
		// ����f�[�^
		bullet = bdata->bullet[i];

		// �e����A�N�e�B�u�Ȃ��΂�
		if (!bullet->Flag) { continue; }

		// �����擾
		X = enemy->position.x - bullet->position.x;
		Y = enemy->position.y - bullet->position.y;
		Z = enemy->position.z - bullet->position.z;

		// �G�ƒe�̋���
		if (sqrt(X * X + Y * Y + Z * Z) <= DAMAGERADIUS)
		{
			// ���������e���A�N�e�B�u�ɂ���
			bullet->Flag = false;
			// �G���e��Ԃɂ���
			enemy->State = ES_DEAD;
		}
	}

	return;
}

void DrawEnemy(EnemyList* list)
{
	// �G�̐������`��
	for (int i = 0; i < ENEMYMAXNUM; i++)
	{
		// ��Ԃ����S���̓G�͕`�悵�Ȃ�
		if (list->enemy[i]->State == ES_DEAD) { continue; }
		// ���f���`��
		MV1DrawModel(list->enemy[i]->ModelHandle);
	}

	return;
}