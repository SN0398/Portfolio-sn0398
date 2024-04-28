#pragma once
#include <iostream>
#include <stack>

#include "Singleton.h"
#include "BaseScene.h"
#include "Define.h"

using namespace std;

class SceneManager final :  public Singleton<SceneManager>
{
public:
    // デフォルトコンストラクタ
    SceneManager();
    // デストラクタ
    ~SceneManager();

public:

    // 先頭のシーン削除
    void PopScene();
    // シーン追加
    bool PushScene(Define::SceneType Stype);
    // すべてのシーン削除
    void PopAllScene();
    // シーン変更
    bool ChangeScene(Define::CS_CallType CStype, Define::SceneType Stype = Define::SceneType::None);
    // 先頭シーンのUpdate実行
    bool Update() { return s_stack.top()->Update(); }   // 更新　スタックの一番上のインスタンスのUpdate()を実行
    // 先頭シーンのDraw実行
    void Draw() { return s_stack.top()->Draw(); }   // 描画　スタックの一番上のインスタンスのDraw()を実行
    // シーンが存在しないかを取得
    bool GetEmpty() { return s_stack.empty(); }

private:
    stack<unique_ptr<Scene>> s_stack;    // シーンクラスの所有権を持つスマートポインタを持つコンテナアダプタ:スタック

};
