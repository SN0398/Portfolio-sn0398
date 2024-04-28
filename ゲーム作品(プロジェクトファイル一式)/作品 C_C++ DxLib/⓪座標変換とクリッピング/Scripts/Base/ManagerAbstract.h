#pragma once
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template <class T>
class ManagerAbstract abstract
{
public:
    enum Approach_Calltype
    {
        AC_PopTop,     // 先頭を消してから先頭に追加する
        AC_PopAll,     // 全て消してから先頭に追加する
        AC_Push,       // 先頭に追加するだけ
        AC_Back,       // 先頭を消すだけ
    };

public:
    // デフォルトコンストラクタ
    ManagerAbstract() = default;
    // デストラクタ
    virtual ~ManagerAbstract()
    {
        PopAll();
        while (!ChangeList.empty())
        {
            ChangeList.pop();
        }
    }

public:
    // スタックのサイズを得る
    int GetSize() { return Instance.size(); }

    // 先頭の変更リクエストを送る
    template <class U>
    void Change(Approach_Calltype type = AC_Push) { ChangeList.push({ type,make_unique<U>() }); }

    // 先頭を削除するリクエストを送る
    void Back() { ChangeList.push({ AC_Back, nullptr }); }    

protected:
    // 先頭インスタンス削除
    void Pop() { Instance.pop(); }

    // すべてのインスタンス削除
    void PopAll() { while (!Instance.empty()) { Pop(); } }

    // シーン変更リクエストを消化
    void ChangeProcess()
    {
        // 消化しきるまでループ
        while (!ChangeList.empty())
        {
            auto& request = ChangeList.front(); // 先頭インスタンス取得
            unique_ptr<T> temp;

            // シーンのポインタが正常な値の場合に所有権を移動
            if (request.second) { temp = move(request.second); }
            // ポインタが不正な値の場合は先頭シーンを削除するだけにする
            else { request.first = AC_Back; }

            // 本処理
            switch (request.first)
            {
            case AC_PopTop:    // 先頭を消してから先頭に追加する
            {
                Pop();
                Instance.push(move(temp));
            }break;
            case AC_PopAll:    // 全て消してから先頭に追加する
            {
                PopAll();
                Instance.push(move(temp));
            }break;
            case AC_Push:      // 先頭に追加するだけ
            {
                Instance.push(move(temp));
            }break;
            case AC_Back:      // 先頭を消すだけ
            {
                Pop();
            }break;
            default: {}break;
            }
            ChangeList.pop();   // インスタンスを消化
        }
    }

protected:
    stack<unique_ptr<T>> Instance;   // スタック
    queue<pair<Approach_Calltype, unique_ptr<T>>> ChangeList;    // 消化待ちの変更リクエストリスト

};