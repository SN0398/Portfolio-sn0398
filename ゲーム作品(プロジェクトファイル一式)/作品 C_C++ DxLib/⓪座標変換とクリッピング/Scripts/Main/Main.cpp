#include "DxLib.h"
#include "MainSystem.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MainSystem system;	// �S�̂̊Ǘ��N���X
	if (system.Init())	// ����������
	{
		system.Process();	// �{����
	}
	system.End();	// �I������

	return 0;
}