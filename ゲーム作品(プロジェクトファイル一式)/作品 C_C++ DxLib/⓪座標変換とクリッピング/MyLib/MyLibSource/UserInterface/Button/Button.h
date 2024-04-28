#pragma once
#include "MyLibSource/2D/2D.h"

namespace MyLib
{
	class Button
	{
	public:
		Button() = delete;
		Button(Position2D Pos1, Position2D Pos2);

	public:
		// �X�V �{�^��������ԕԋp
		bool Update();
		// ����̕`��֐�
		void Draw();

	private:
		// �����蔻��X�V
		void HitStateUpdate();
		// �q�b�g��ԍX�V
		void HitFrameUpdate();
		// �{�^�����͏�Ԏ擾
		int Get() { return ClickFrame; }

	public:
		Position2D Pos1, Pos2;		// ��`�̎n�_�I�_

	private:
		bool HitFlag;				// �_�Ƌ�`�̓����蔻��t���O	true = �������Ă���
		int  ClickFrame;			// �{�^�����͏�Ԋi�[�p�ϐ�

	};
}