#pragma once
#include "DxLib.h"
#include <string>

namespace MyLib
{
    // カウンタ
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

	// 汎用関数
	int MyMessageBoxYN(const char Text[], const char Title[]);	// メッセージボックスから Yes か No を返す
	int DeleteDivGraph(int HandleArray[], int AllNum);	// 分割画像ハンドルの削除
    std::string FormatNumber(int num);
    int GetStringCenter(std::string str, int font, int leftX, int rightX);

}