#pragma once
#include <vector>
#include <memory>
#include "GameObject/GameObject.h"

// 各シーンの基底クラス
class Scene abstract
{
public:
    Scene() = default;
    virtual ~Scene() = default;

public:
    virtual void Initialize() = 0;  // 初期化
    virtual void Clean() = 0;       // 後始末
    virtual void Update() = 0;      // 処理
    virtual void Draw() = 0;        // 描画

    void Process()                  // 処理描画
    {
        Update();
        Draw();
    }
    // ゲームオブジェクト更新
    void UpdateGameObjects()
    {
        for (auto& cmp : gameobjects)
        {
            cmp->Update();
        }
    }
    // ゲームオブジェクト描画
    void DrawGameObjects()
    {
        for (auto& cmp : gameobjects)
        {
            cmp->Draw();
        }
    }

public:
    std::vector<std::shared_ptr<GameObject>> gameobjects;

};