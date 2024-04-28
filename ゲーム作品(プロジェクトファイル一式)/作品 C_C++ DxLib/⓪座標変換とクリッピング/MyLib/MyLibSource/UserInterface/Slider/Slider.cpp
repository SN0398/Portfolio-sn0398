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

    // ���N���b�N���������u��
    if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
    {
        // �����蔻�肪true�Ȃ�t���O�𗧂Ă�
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
    // ���N���b�N�����������Ă�����
    if (sliderSelected)
    {
        // ���N���b�N�̉�����ԍX�V
        UpdateClickPressed();
        int MY;
        GetMousePoint(&SliderX, &MY);
        // ��������l�␳
        FixSliderPos();
        // �X�V
        UpdateSliderPos();
        selected = true;
    }
    //printfDx("%d %d %d %d %d %d %d\n", X, L,R, sliderSelected, currentValue, minValue, maxValue);

    return selected;
}

void Slider::Draw()
{
    // �o�[
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
    // �X���C�_�[
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
    // ���������Ă����ԂȂ�true������
    sliderSelected = MouseInput_Get(MOUSE_INPUT_LEFT) >= 1;
}

void Slider::FixSliderPos()
{
    int L = Pos.x - Horizontal / 2;
    int R = Pos.x + Horizontal / 2;
    // ���W�␳
    if (SliderX < L) { SliderX = L; }
    if (SliderX > R) { SliderX = R; }
}