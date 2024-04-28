#include "ResourceMgr.h"
#include "DxLib.h"

Resource* CreateResource()
{
	Resource* resource = (Resource*)malloc(sizeof(Resource));
	
	resource->DxLogoHandle = LoadGraph("Data/Images/DxLogo.jpg");

	resource->CHandle[1] = GetColor(255, 0, 0);		// Ô
	resource->CHandle[2] = GetColor(0, 255, 0);		// —Î
	resource->CHandle[3] = GetColor(0, 0, 255);		// Â
	resource->CHandle[4] = GetColor(128, 128, 128);	// ŠD
	resource->CHandle[5] = GetColor(255, 255, 255);	// ”’
	resource->CHandle[6] = GetColor(0, 0, 0);		// •
	resource->CHandle[7] = GetColor(0, 255, 255);	// …
	resource->CHandle[8] = GetColor(255, 0, 255);	// Ž‡
	resource->CHandle[9] = GetColor(255, 255, 0);	// ‰©

	return resource;
}

void ReleaseResource(Resource* resource)
{
	DeleteGraph(resource->DxLogoHandle);

	DeleteGraph(resource->CHandle[0]);
	DeleteGraph(resource->CHandle[1]);
	DeleteGraph(resource->CHandle[2]);
	DeleteGraph(resource->CHandle[3]);
	DeleteGraph(resource->CHandle[4]);
	DeleteGraph(resource->CHandle[5]);
	DeleteGraph(resource->CHandle[6]);
	DeleteGraph(resource->CHandle[7]);
	DeleteGraph(resource->CHandle[8]);
	DeleteGraph(resource->CHandle[9]);

	free(resource);
	resource = NULL;
	return;
}