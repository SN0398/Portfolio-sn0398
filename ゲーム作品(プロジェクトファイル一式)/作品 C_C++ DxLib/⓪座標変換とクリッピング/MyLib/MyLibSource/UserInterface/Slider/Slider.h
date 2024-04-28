#pragma once
#include "MyLibSource/2D/2D.h"

namespace MyLib
{
    class Slider
    {
    public:
        Slider() {}
        Slider(Position2D sliderPos, int vertical, int horizontal, float minValue, float maxValue);

    public:
        // 更新 スライダー選択状態返却
        bool Update();
        // 既定の描画関数
        void Draw();
        // 値の取得
        int Get() { return currentValue; }
        // 値の設定
        void Set(float value);

    private:
        // スライダー位置更新
        void UpdateSliderPos();
        //// シフトキー押下状態更新
        //void UpdateShiftKeyPressed();
        // 左クリック押下状態更新
        void UpdateClickPressed();
        // 上限下限値補正
        void FixSliderPos();
        // スライダー選択状態取得
        bool GetSelectedState() { return sliderSelected; }

    public:
        int Vertical;           // 縦軸直径
        int Horizontal;         // 横軸直径
        Position2D Pos;         // スライダー全体位置(中央座標)
        float min;               // 最小値
        float max;               // 最大値

    private:
        int SliderX;            // スライダーの位置
        int BarL;                  // 左端の位置
        int BarR;                  // 右端の位置

        float currentValue;       // 現在値
        //bool shiftKeyPressed;   // shiftキーの押下状態
        bool sliderSelected;    // クリックの押下状態

    };
}