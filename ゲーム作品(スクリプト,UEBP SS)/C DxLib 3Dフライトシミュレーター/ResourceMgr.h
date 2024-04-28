#pragma once

// 構造体定義 -------------------------------------------------------------------------------------

typedef struct _Resource
{
	int DxLogoHandle;
	int CHandle[10];
	int FHandle[5];

}Resource;

// 関数プロトタイプ宣言 ---------------------------------------------------------------------------

Resource* CreateResource();
void ReleaseResource(Resource* resource);