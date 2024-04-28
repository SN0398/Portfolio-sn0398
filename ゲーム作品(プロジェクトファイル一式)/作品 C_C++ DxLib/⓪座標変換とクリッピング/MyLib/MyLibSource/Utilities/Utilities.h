#pragma once
#include "DxLib.h"
#include <string>

namespace MyLib
{
    // �J�E���^
    class Counter
    {
    public:
        Counter() = default;
        Counter(const int CountSpeed) :
            Count(0), Speed(CountSpeed) {}
        ~Counter() = default;
    public:
        void Reset() { Count = 0; }
        bool Process()
        {
            if (++Count >= Speed)
            {
                Count = 0;
                return true;
            }

            return false;
        }
    public:
        int Count;
        int Speed;

    };

	// �ėp�֐�
	int MyMessageBoxYN(const char Text[], const char Title[]);	// ���b�Z�[�W�{�b�N�X���� Yes �� No ��Ԃ�
	int DeleteDivGraph(int HandleArray[], int AllNum);	// �����摜�n���h���̍폜
    std::string FormatNumber(int num);
    int GetStringCenter(std::string str, int font, int leftX, int rightX);

}