#pragma once
#include "DxLib.h"

namespace MyLib
{
	// �E�B���h�E�̃X�^�C��
	const int WINDOW_STYLE_DEFAULT			  = 0;		// �ő剻�؂�ւ��\�ȃE�B���h�E
	const int WINDOW_STYLE_VIRTUAL_FULLSCREEN = 1;		// ���z�t���X�N���[��

	void SetWindowProperty(int WindowWidth, int WindowHeight, int WindowStyle = WINDOW_STYLE_DEFAULT);	// �E�B���h�E�̃Z�b�g�A�b�v
}