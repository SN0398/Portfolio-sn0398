#include "Bullet.h"

BulletData* BulletDataInit()
{
	// �������m��
	BulletData* bulletdata = (BulletData*)malloc(sizeof(BulletData));

	// �q�\���̂𐶐�
	for (int i = 0;i < BULLETMAXNUM;i++)
	{
		bulletdata->bullet[i] = CreateBullet();
	}

	// ������
	bulletdata->ShootCount = 0;

	return bulletdata;
}

void BulletDataClean(BulletData* bulletdata)
{
	// �q�\���̂̔j��
	for (int i = 0;i < BULLETMAXNUM;i++)
	{
		ReleaseBullet(bulletdata->bullet[i]);
	}

	// �e�\���̂̔j��
	free(bulletdata);
	bulletdata = NULL;

	return;
}

Bullet* CreateBullet()
{
	// �������m��
	Bullet* bullet = (Bullet*)malloc(sizeof(Bullet));
	// ���f���Ǎ�
	bullet->ModelHandle = MV1LoadModel("Data/Models/Bullet/Bullet.mv1");
	// �X�P�[���ύX
	MV1SetScale(bullet->ModelHandle, VScale(VGet(1.0f, 1.0f, 1.0f), 0.1f));
	// ������
	bullet->position = VECTOR{ 0.0f,0.0f,0.0f };
	bullet->direction = VECTOR{ 0.0f,0.0f,0.0f };
	bullet->Flag = false;
	bullet->DeleteCount = 0;

	return bullet;
}

void ReleaseBullet(Bullet* bullet)
{
	// ���f���폜
	MV1DeleteModel(bullet->ModelHandle);
	// �������j��
	free(bullet);
	bullet = NULL;

	return;
}
static float scalebuf = 0.1f;
void BulletUpdate(BulletData* bdata, int MHandle, VECTOR position)
{
	// �X�y�[�X�L�[�����������Ă���ԓ��Ԋu�Œe���A�N�e�B�u�ɂ���֐�
	GenerateBulletProcess(bdata, MHandle, position);

	Bullet* bullet;
	for (int i = 0; i < BULLETMAXNUM; i++)
	{
		// ����f�[�^�̍X�V
		bullet = bdata->bullet[i];

		// ���W�̍X�V
		bullet->position = VAdd(bullet->position, bullet->direction);
		// ���W�A�^�b�`
		MV1SetPosition(bullet->ModelHandle, bullet->position);

		// �A�N�e�B�u�Ȓe�͈�莞�ԂŔ�A�N�e�B�u�ɂ���
		if (++bullet->DeleteCount > SHOTDELETETIME)
		{
			// �A�N�e�B�u�t���O��܂�
			bullet->Flag = false;
		}
	}


	return;
}

void GenerateBulletProcess(BulletData* bdata, int MHandle, VECTOR position)
{
	Bullet* bullet;
	// �X�y�[�X�L�[�����������Ă����
	if (Keyboard_Get(KEY_INPUT_SPACE) >= 1)
	{
		// ���̊Ԋu�ŏe�e���΂�
		if (++bdata->ShootCount >= SHOTINTERVAL)
		{
			//clsDx();
			//printfDx("%0.1f,%0.1f,%0.1f\n\n", MV1GetPosition(MHandle).x, MV1GetPosition(MHandle).y, MV1GetPosition(MHandle).z);
			// �ˏo���ł͂Ȃ��f�[�^��T��
			for (int i = 0; i < BULLETMAXNUM; i++)
			{
				// ����f�[�^�̍X�V
				bullet = bdata->bullet[i];

				// ��t���[���ɂ����e���A�N�e�B�u�ɂ���
				if (!bullet->Flag)
				{
					// �A�N�e�B�u�t���O�𗧂Ă�
					bullet->Flag = true;
					// ���ł܂ł̃J�E���^���Z�b�g
					bullet->DeleteCount = 0;
					// ���W = ���W�␳ * �v���C���[��]�s�� + �v���C���[���W
					bullet->position = 
						VAdd(VTransform(VGet(0.0f, -30.0f, 0.0f), 
							MV1GetRotationMatrix(MHandle)), MV1GetPosition(MHandle));					
					// �ړ��x�N�g��������
					{
						bullet->direction = { 0.0f,0.0f,-0.1f };
						// �ړ��x�N�g�� = �ړ��x�N�g�� * �v���C���[�̉�]�s��
						bullet->direction = VTransform(bullet->direction, MV1GetRotationMatrix(MHandle));
						// �ړ��x�N�g�����K��
						bullet->direction = Normalize_3D(bullet->direction);
						// �X�s�[�h��Z
						bullet->direction = VScale(bullet->direction, BULLETSPEED);
					}
					// ����������
					{
						// ��]�s��Z�b�g
						MV1SetRotationMatrix(bullet->ModelHandle, MV1GetRotationMatrix(MHandle));
					}
					// �J�E���^��������
					bdata->ShootCount = 0;
					
					return;
				}
			}
		}
	}

	return;
}

void DrawBullet(BulletData* bdata)
{
	for (int i = 0; i < BULLETMAXNUM; i++)
	{
		// �A�N�e�B�u�Ȓe�̂ݕ`��
		if (!bdata->bullet[i]->Flag) { continue; }
		MV1DrawModel(bdata->bullet[i]->ModelHandle);
	}

	return;
}