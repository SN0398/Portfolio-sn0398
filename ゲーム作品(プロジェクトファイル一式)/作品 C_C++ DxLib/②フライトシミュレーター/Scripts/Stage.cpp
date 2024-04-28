#include "Stage.h"
#include "DxLib.h"

// �����E�j��
Stage* StageInit()
{
	// �������m��
	Stage* stage = (Stage*)malloc(sizeof(Stage));
	// ���f���̓ǂݍ���
	stage->ModelHandle = 
		MV1LoadModel("Data/Models/Stage/Stage.mv1");	// �C
	stage->SkyDomeModelHandle = 
		MV1LoadModel("Data/Models/Stage/Skydome_TN8/Dome_TN802.mv1");	// �X�J�C�h�[��
	// ���f���̃X�P�[���ύX
	MV1SetScale(stage->ModelHandle, VScale(VGet(1, 1, 1), 10));
	MV1SetScale(stage->SkyDomeModelHandle, VScale(VGet(1, 1, 1), 20));
	// ���f���̈ʒu�ύX
	MV1SetPosition(stage->ModelHandle, VGet(0, -5500, 0));

	return stage;
}

void StageClean(Stage* stage)
{
	// ���f���폜
	MV1DeleteModel(stage->ModelHandle);
	MV1DeleteModel(stage->SkyDomeModelHandle);
	// ���������
	free(stage);
	stage = NULL;
	return;
}

// �����E�`��
void StageUpdate(Stage* stage, Player* player)
{
	// �X�J�C�h�[�����W�͏�Ƀv���C���[�̍��W�����S�ɂȂ�悤�ɂ���
	MV1SetPosition(stage->SkyDomeModelHandle, player->position);

	return;
}

void DrawStage(Stage* stage)
{
	// ���f���̕`��
	MV1DrawModel(stage->SkyDomeModelHandle);
	MV1DrawModel(stage->ModelHandle);
	return;
}