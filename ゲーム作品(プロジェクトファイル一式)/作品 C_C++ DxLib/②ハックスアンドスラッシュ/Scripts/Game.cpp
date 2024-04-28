#include "Game.h"
#include "DxLib.h"
#include "Utility.h"
#include "Define.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "MapMgr.h"
#include "Object.h"

typedef enum _WindowState
{
	WS_NORMAL = 0,
	WS_GAMEOVER,
	WS_POSE,

}WindowState;

// �Q�[�����C��
int Game(bool* PlayMusic)
{
	int RETURNVALUE = GAMESCENE_LEAVE;
	int WindowState = WS_NORMAL;

	Resource* resource = CreateResource();
	Map* map = CreateMap();
	Player* player = CreatePlayer();
	Data* data = CreateData();

	if (*PlayMusic)
	{
		PlaySoundMem(resource->MusicHandle[0], DX_PLAYTYPE_LOOP);
	}

	while (Game_MainLoop())
	{
		FPSUpdate();

		if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
		{
			if (WindowState == WS_POSE || WindowState == WS_GAMEOVER)
			{
				RETURNVALUE = GAMESCENE_TITLE;
				StopSoundMem(resource->MusicHandle[0]);
				break;
			}
			WindowState = WS_POSE;
			StopSoundMem(resource->MusicHandle[0]);
		}
		if (Keyboard_Get(KEY_INPUT_SPACE) == 1)
		{
			if (WindowState == WS_POSE)
			{
				WindowState = WS_NORMAL;
				if (*PlayMusic)
				{
					PlaySoundMem(resource->MusicHandle[0], DX_PLAYTYPE_LOOP, FALSE);
				}
			}
		}

		switch (WindowState)
		{
		case WS_NORMAL:	// ���C������
		{
			// �o�b�N�O���E���h�ɂȂ�����|�[�Y��ʂɑJ��
			if (!GetWindowActiveFlag()) { WindowState = WS_POSE; }
			ObjectUpdate(data, player->x, player->y, &player->Health);	// �I�u�W�F�N�g����
			// �v���C���[�����̖߂�l����ްѵ��ް���Ԃ��ꂽ��ްѵ��ް��ʂɑJ��
			if (PlayerUpdate(player, map->stage, data) == WS_GAMEOVER)
			{
				WindowState = WS_GAMEOVER;
				StopSoundMem(resource->MusicHandle[0]);	// ���y�Đ���~
			}

			DrawMap(map, resource, player->x, player->y);	// �}�b�v�`��
			DrawObject(data, resource, player->x, player->y);	// �I�u�W�F�N�g�`��
			DrawPlayer(player, resource);	//  �v���C���[�`��

			break;
		}
		case WS_GAMEOVER:	// �ްѵ��ް���
		{
			DrawMap(map, resource, player->x, player->y);
			DrawObject(data, resource, player->x, player->y);
			DrawPlayer(player, resource);

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);		//�u�����h���[�h����(128/255)�ɐݒ�
			DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, resource->CHandle[6], TRUE); //�摜�̕`��
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t

			DrawFormatString(580, 375, resource->CHandle[5], "�Q�[���I�[�o�[");

			break;
		}
		case WS_POSE:	// �߰�މ��
		{
			DrawMap(map, resource, player->x, player->y);
			DrawObject(data, resource, player->x, player->y);
			DrawPlayer(player, resource);

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);		//�u�����h���[�h����(128/255)�ɐݒ�
			DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, resource->CHandle[6], TRUE); //�摜�̕`��
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t

			DrawFormatString(610, 375, resource->CHandle[5], "�|�[�Y��");
			break;
		}
		}
		
		FPSWait();
	}

	ReleaseResource(resource);
	ReleaseData(data);
	ReleasePlayer(player);

	return RETURNVALUE;
}