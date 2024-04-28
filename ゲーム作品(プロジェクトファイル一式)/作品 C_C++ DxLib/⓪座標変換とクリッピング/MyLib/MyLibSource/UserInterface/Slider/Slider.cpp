#include "Slider.h"
#include "DxLib.h"
#include "MyLibSource/Input/Keyboard/Keyboard.h"
#include "MyLibSource/Input/Mouse/Mouse.h"

using namespace MyLib;

Slider::Slider(Position2D sliderPos, int vertical, int horizontal, float minValue, float maxValue)
{
    Pos = sliderPos;
    Vertical = vertical;
    Horizontal = horizontal;
    min = minValue;
    max = maxValue;
    SliderX = ((Pos.x - Horizontal / 2) + (Pos.x + Horizontal / 2)) / 2;
    currentValue = (min + max) / 2;
    //shiftKeyPressed = false;
    sliderSelected = false;
}

bool Slider::Update()
{
    //UpdateShiftKeyPressed();

    // 左クリックを押した瞬間
    if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
    {
        // 当たり判定がtrueならフラグを立てる
        int MX, MY;
        GetMousePoint(&MX, &MY);
        if (CheckHitBoxToPoint2D(
            { (double)Pos.x - Horizontal / 2,(double)Pos.y - Vertical / 2 },
            { (double)Pos.x + Horizontal / 2,(double)Pos.y + Vertical / 2 },
            { (double)MX,(double)MY }))
        {
            sliderSelected = true;
        }
    }

    int selected = false;
    // 左クリックを押し続けている状態
    if (sliderSelected)
    {
        // 左クリックの押下状態更新
        UpdateClickPressed();
        int MY;
        GetMousePoint(&SliderX, &MY);
        // 上限下限値補正
        FixSliderPos();
        // 更新
        UpdateSliderPos();
        selected = true;
    }
    //printfDx("%d %d %d %d %d %d %d\n", X, L,R, sliderSelected, currentValue, minValue, maxValue);

    return selected;
}

void Slider::Draw()
{
    // バー
    DrawBox
    (
        Pos.x - Horizontal / 2,
        Pos.y - Vertical / 2,
        Pos.x + Horizontal / 2,
        Pos.y + Vertical / 2,
        GetColor(0, 0, 0), TRUE
    );
    DrawBox
    (
        Pos.x - Horizontal / 2 + (Vertical / 8),
        Pos.y - Vertical / 2 + (Vertical / 8),
        Pos.x + Horizontal / 2 - (Vertical / 8),
        Pos.y + Vertical / 2 - (Vertical / 8),
        GetColor(255, 255, 255), TRUE
    );
    // スライダー
    DrawCircle
    (
        SliderX, 
        Pos.y, 
        (Vertical / 2) + (Vertical / 2), 
        GetColor(0, 0, 0), 
        TRUE
    );
    DrawCircle
    (
        SliderX, 
        Pos.y, 
        (Vertical / 2) + (Vertical / 2) - (Vertical / 8),
        GetColor(255, 255, 255), TRUE
    );

    return;
}

void MyLib::Slider::Set(float value)
{
    currentValue = (value < min) ? min : value;
    currentValue = (value > max) ? max : value;
    int L = Pos.x - Horizontal / 2;
    int R = Pos.x + Horizontal / 2;
    float ratio = (float)(currentValue - min) / (max - min);
    SliderX = L + ratio * (R - L);
    return;
}

void Slider::UpdateSliderPos()
{
    int L = Pos.x - Horizontal / 2;
    int R = Pos.x + Horizontal / 2;
    float ratio = (float)(SliderX - L) / (R - L);
    currentValue = min + ratio * (max - min);
    return;
}

void Slider::UpdateClickPressed()
{
    // 押し続けている状態ならtrueが入る
    sliderSelected = MouseInput_Get(MOUSE_INPUT_LEFT) >= 1;
}

void Slider::FixSliderPos()
{
    int L = Pos.x - Horizontal / 2;
    int R = Pos.x + Horizontal / 2;
    // 座標補正
    if (SliderX < L) { SliderX = L; }
    if (SliderX > R) { SliderX = R; }
}