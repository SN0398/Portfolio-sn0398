#pragma once
#include <iostream>
#include <stack>

#include "Base/ManagerAbstract.h"
#include "Base/Singleton.h"
#include "BaseScene.h"
#include "Config/Define.h"

using namespace std;

class SceneManager final :
    public ManagerAbstract<Scene>,
    public Singleton<SceneManager>
{
public:
    friend class MainSystem;

    // デフォルトコンストラクタ
    SceneManager() = default;
    // デストラクタ
    ~SceneManager() = default;

public:
    // スタックの一番上のインスタンス(先頭)の処理
    // 更新
    void Update() { Instance.top()->Update(); }
    // 描画
    void Draw() { Instance.top()->Draw(); }
    // ラッパー
    void Process() { Instance.top()->Process(); }

};