#pragma once
#include "MyLib.h"

class Slider 
{
public:
    Slider(int y, int leftPos, int rightPos, int min, int max) 
    {
        Y = y;
        L = leftPos;
        R = rightPos;
        X = (L + R) / 2;

        minValue = min;
        maxValue = max;
        currentValue = (min + max) / 2;
        shiftKeyPressed = false;
        sliderSelected = false;
    }

public:
    bool Update()
    {
        UpdateShiftKeyPressed();
        // 左クリックを押した瞬間
        if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
        {
            // 当たり判定がtrueならフラグを立てる
            int MX, MY;
            GetMousePoint(&MX, &MY);
            if (CheckHitBoxToPoint2D(
                { (double)L,(double)Y - 10 },
                { (double)R,(double)Y + 10 },
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
            GetMousePoint(&X, &MY);
            // 上限下限値補正
            FixSliderPos();
            // 更新
            UpdateSliderPos();
            selected = true;
        }
        //printfDx("%d %d %d %d %d %d %d\n", X, L,R, sliderSelected, currentValue, minValue, maxValue);

        return selected;
    }
    int Get()
    {
        return currentValue;
    }
    void UpdateSliderPos()
    {
        double ratio = (double)(X - L) / (R - L);
        currentValue = minValue + ratio * (maxValue - minValue);
    }
    void UpdateShiftKeyPressed() 
    {
        shiftKeyPressed = Keyboard_Get(KEY_INPUT_LSHIFT) >= 1;
    }
    void UpdateClickPressed()
    {
        sliderSelected = MouseInput_Get(MOUSE_INPUT_LEFT) >= 1;
    }
    void FixSliderPos()
    {
        if (X < L) { X = L; }
        if (X > R) { X = R; }
    }

public:
    int Y;                  // スライダーバーの縦位置
    int X;                  // スライダーの位置
    int L;                  // 左端の位置
    int R;                  // 右端の位置
    int minValue;           // 最小値
    int maxValue;           // 最大値

private:
    int currentValue;       // 現在値
    bool shiftKeyPressed;   // shiftキーの押下状態
    bool sliderSelected;    // クリックの押下状態

};