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
        // ���N���b�N���������u��
        if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
        {
            // �����蔻�肪true�Ȃ�t���O�𗧂Ă�
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
        // ���N���b�N�����������Ă�����
        if (sliderSelected) 
        {
            // ���N���b�N�̉�����ԍX�V
            UpdateClickPressed();
            int MY;
            GetMousePoint(&X, &MY);
            // ��������l�␳
            FixSliderPos();
            // �X�V
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
    int Y;                  // �X���C�_�[�o�[�̏c�ʒu
    int X;                  // �X���C�_�[�̈ʒu
    int L;                  // ���[�̈ʒu
    int R;                  // �E�[�̈ʒu
    int minValue;           // �ŏ��l
    int maxValue;           // �ő�l

private:
    int currentValue;       // ���ݒl
    bool shiftKeyPressed;   // shift�L�[�̉������
    bool sliderSelected;    // �N���b�N�̉������

};