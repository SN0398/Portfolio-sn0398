#include "Button.h"
#include "DxLib.h"
#include "MyLibSource/Input/Mouse/Mouse.h"

using namespace MyLib;

Button::Button(Position2D Pos1, Position2D Pos2) :
	Pos1(Pos1), Pos2(Pos2), HitFlag(false)
{
    ClickFrame = 0;
}

bool Button::Update()
{
    HitStateUpdate();

    HitFrameUpdate();

	return HitFlag;
}

void Button::Draw()
{
    // ��{�`��
    DrawBox
    (
        Pos1.x, Pos1.y,
        Pos2.x, Pos2.y,
        GetColor(0, 0, 0), TRUE
    );
    DrawBox
    (
        Pos1.x + ((Pos2.x - Pos1.x) / 32),
        Pos1.y + ((Pos2.y - Pos1.y) / 32),
        Pos2.x - ((Pos2.x - Pos1.x) / 32),
        Pos2.y - ((Pos2.y - Pos1.y) / 32),
        GetColor(255, 255, 255), TRUE
    );
    // �������Ă����甼�����̍��ŕ`��
    if (HitFlag)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        DrawBox
        (
            Pos1.x, Pos1.y,
            Pos2.x, Pos2.y,
            GetColor(0, 0, 0), TRUE
        );
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

	return;
}

void Button::HitStateUpdate()
{
    // �����蔻�肪true�Ȃ�t���O�𗧂Ă�
    int MX, MY;
    GetMousePoint(&MX, &MY);
    if (CheckHitBoxToPoint2D(
        { (double)Pos1.x,(double)Pos1.y },
        { (double)Pos2.x,(double)Pos2.y },
        { (double)MX,(double)MY }))
    {
        HitFlag = true;
    }
    else
    {
        HitFlag = false;
    }

	return;
}

void Button::HitFrameUpdate()
{
    // ���N���b�N��������Ă�����
    if (MouseInput_Get(MOUSE_INPUT_LEFT) >= 1)
    {
        // �{�^���ƐڐG���Ă�������͏�Ԃ����Z����
        if (HitFlag)
        {
            ClickFrame++;
        }
    }
    // �������Ă��Ȃ���Γ��͏�Ԃ�����������
    else
    {
        ClickFrame = 0;
    }

    return;
}