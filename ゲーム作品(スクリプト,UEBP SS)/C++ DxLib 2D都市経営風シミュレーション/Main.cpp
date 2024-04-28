#include "DxLib.h"
#include "MainSystem.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MainSystem system;
	if (system.Init())
	{
		system.Process();
	}
	system.End();

	return 0;
}