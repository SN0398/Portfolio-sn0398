#include "ChipSelect.h"
#include "InterfaceManager.h"

#include "ResourceManager.h"
#include "Define.h"

#include "Pose.h"
#include "ActionSelector.h"

void ChipSelect::Update()
{
	UpdateProcess();
	// ���N���b�N���������u��
	if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
	{
		// �N���b�N�����u�ԑI�����Ă����}�b�v�`�b�v���W�𓾂�
		MapManager::GetInstance().GetChipPos(SelectChip);
		// �I���}�b�v�`�b�v�ւ̍s����I�����鏈���֑J�ڂ�����
		InterfaceManager::GetInstance().AddInterface<ActionSelector>();
		return;
	}
	// Esc�L�[�Ń|�[�Y
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	{
		InterfaceManager::GetInstance().AddInterface<Pose>();
		return;
	}

	return;
}

void ChipSelect::Draw()
{
	DrawProcess();

	return;
}