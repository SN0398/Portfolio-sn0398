#pragma once

// �\���̒�` -------------------------------------------------------------------------------------

typedef struct _Resource
{
	int DxLogoHandle;
	int CHandle[10];
	int FHandle[5];

}Resource;

// �֐��v���g�^�C�v�錾 ---------------------------------------------------------------------------

Resource* CreateResource();
void ReleaseResource(Resource* resource);