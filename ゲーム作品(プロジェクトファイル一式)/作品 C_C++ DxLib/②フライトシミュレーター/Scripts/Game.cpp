#include "Game.h"
#include "DxLib.h"
#include "Utility.h"
#include "Define.h"
#include "ResourceMgr.h"
#include "Stage.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"

// �Q�[�����C��
int Game()
{
	// �߂�l�i�V�[���ԍ��j�f�t�H���g�͏I�������V�[��
	int RETURNVALUE = GS_LEAVE;

	// �f�[�^����
	Resource* resource = CreateResource();
	Stage* stage = StageInit();
	Player* player = PlayerInit();
	EnemyList* enemylist = EnemyInit();

	// ���C�����[�v(Esc�Ń��[�v�𔲂��Ȃ�)
	while (Game_MainLoop(NULL))
	{
		// FPS�X�V
		FPSUpdate();

		// ����
		PlayerUpdate(player);		// �v���C���[
		StageUpdate(stage, player);	// �X�e�[�W
		CameraUpdate(player);		// �J����
		EnemyListUpdate(enemylist, player->position, player->bdata);	// �G

		// �`��
		DrawStage(stage);	// �X�e�[�W
		DrawEnemy(enemylist);	// �G
		DrawPlayer(player); // �v���C���[

		// FPS����
		FPSWait();
	}

	// �f�[�^�j��
	ReleaseResource(resource);
	StageClean(stage); 
	PlayerClean(player);

	return RETURNVALUE;
}