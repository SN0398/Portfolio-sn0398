#include "ActionButton.h"

#include "ResourceManager.h"
#include "InterfaceManager.h"

ActionButton* ActionButton::Create(Vector2D Pos1, Vector2D Pos2, std::string text, int* graph, int index)
{
	// ��O
	if (text.empty()) { return nullptr; }
	if (graph == nullptr) { return nullptr; }
	// �C���X�^���X����
	ActionButton* tmp = new ActionButton(text);
	// ������
	tmp->Icon_ptr = graph;
	tmp->HitFlag = false;
	tmp->Pos1 = Pos1;
	tmp->Pos2 = Pos2;
	tmp->Index = index;

	// �ԋp
	return tmp;
}

void ActionButton::Draw()
{
	auto& instance = Resource::GetInstance();
	// �{�b�N�X�`��
	DrawExtendGraph(Pos1.x, Pos1.y, Pos2.x, Pos2.y, instance.BoxUI, FALSE);
	// �A�C�R���`��
	DrawExtendGraph(Pos1.x, Pos1.y, Pos2.x, Pos2.y, *Icon_ptr, TRUE);
	// �J�[�\�����������Ă����甼�����̍��F��`��
	if (HitFlag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DrawBox(Pos1.x, Pos1.y, Pos2.x, Pos2.y, instance.Color[Color_ID::Black], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	// �����`��
	DrawExtendFormatStringToHandle
	(
		Pos1.x, Pos1.y, 
		1.0f, 1.0f, 
		instance.Color[Color_ID::White],
		instance.Font[Font_ID::Yumincho], 
		DiaplayName.c_str()
	);
	return;
}

void ActionButton::HitStateUpdate(const Vector2D PointPos)
{
	// ��`�Ɠ_�𓖂��蔻��
	HitFlag = CheckHitBoxToPoint2D(Pos1, Pos2, PointPos);
	return;
}