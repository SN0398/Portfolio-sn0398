#pragma once
#include "Player.h"

// �\���̒�` -------------------------------------------------------------------------------------

typedef struct _Stage
{
	int ModelHandle;
	int SkyDomeModelHandle;

}Stage;

// �֐��v���g�^�C�v�錾 ---------------------------------------------------------------------------

// �����E�j��
Stage* StageInit();
void StageClean(Stage* stage);
// �����E�`��
void StageUpdate(Stage* stage, Player* player);
void DrawStage(Stage* stage);