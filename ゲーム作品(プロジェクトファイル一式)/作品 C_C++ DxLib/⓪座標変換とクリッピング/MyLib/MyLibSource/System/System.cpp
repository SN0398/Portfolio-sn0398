#include "System.h"

using namespace MyLib;

// �E�B���h�E�ݒ�̃Z�b�g
void MyLib::SetWindowProperty(int WindowWidth, int WindowHeight, int WindowStyle)
{
	HWND windowHandle = GetMainWindowHandle();
	int taskBarHeight = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYSIZEFRAME);

	switch (WindowStyle)
	{
	case 0:
	{
		// �E�B���h�E���[�h�̕ύX
		ChangeWindowMode(TRUE);
		// �E�B���h�E�̌����ڂ�ύX����
		SetWindowStyleMode(0);
		// ��ʂ̃T�C�Y��ύX�ł���悤�ɂ��邩�ǂ���
		SetWindowSizeChangeEnableFlag(TRUE);

		SetWindowSize(WindowWidth, WindowHeight);

		int currentWindowStyle = GetWindowLong(windowHandle, GWL_STYLE);
		SetWindowLong(windowHandle, GWL_STYLE, currentWindowStyle | WS_MAXIMIZEBOX);

		//SetWindowStyleMode(7);

		break;
	}
	case 1:
	{
		//// �E�B���h�E���[�h�̕ύX
		//ChangeWindowMode(TRUE);
		//// �E�B���h�E�̌����ڂ�ύX����
		//SetWindowStyleMode(2);
		//// ��ʂ̃T�C�Y��ύX�ł���悤�ɂ��邩�ǂ���
		//SetWindowSizeChangeEnableFlag(FALSE);

		//int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		//int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		//SetWindowSize(screenWidth, screenHeight);

		// �E�B���h�E���[�h�̕ύX
		ChangeWindowMode(TRUE);
		// �E�B���h�E�̌����ڂ�ύX����
		SetWindowStyleMode(2);
		// ��ʂ̃T�C�Y��ύX�ł���悤�ɂ��邩�ǂ���
		SetWindowSizeChangeEnableFlag(FALSE);

		ShowWindow(GetMainWindowHandle(), SW_MAXIMIZE);

		break;
	}
	}

	return;
}