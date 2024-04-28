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
    // 基本描画
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
    // 当たっていたら半透明の黒で描画
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
    // 当たり判定がtrueならフラグを立てる
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
    // 左クリックが押されている状態
    if (MouseInput_Get(MOUSE_INPUT_LEFT) >= 1)
    {
        // ボタンと接触していたら入力状態を加算する
        if (HitFlag)
        {
            ClickFrame++;
        }
    }
    // 当たっていなければ入力状態を初期化する
    else
    {
        ClickFrame = 0;
    }

    return;
}