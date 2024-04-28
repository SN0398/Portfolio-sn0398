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
        // �X�V �X���C�_�[�I����ԕԋp
        bool Update();
        // ����̕`��֐�
        void Draw();
        // �l�̎擾
        int Get() { return currentValue; }
        // �l�̐ݒ�
        void Set(float value);

    private:
        // �X���C�_�[�ʒu�X�V
        void UpdateSliderPos();
        //// �V�t�g�L�[������ԍX�V
        //void UpdateShiftKeyPressed();
        // ���N���b�N������ԍX�V
        void UpdateClickPressed();
        // ��������l�␳
        void FixSliderPos();
        // �X���C�_�[�I����Ԏ擾
        bool GetSelectedState() { return sliderSelected; }

    public:
        int Vertical;           // �c�����a
        int Horizontal;         // �������a
        Position2D Pos;         // �X���C�_�[�S�̈ʒu(�������W)
        float min;               // �ŏ��l
        float max;               // �ő�l

    private:
        int SliderX;            // �X���C�_�[�̈ʒu
        int BarL;                  // ���[�̈ʒu
        int BarR;                  // �E�[�̈ʒu

        float currentValue;       // ���ݒl
        //bool shiftKeyPressed;   // shift�L�[�̉������
        bool sliderSelected;    // �N���b�N�̉������

    };
}