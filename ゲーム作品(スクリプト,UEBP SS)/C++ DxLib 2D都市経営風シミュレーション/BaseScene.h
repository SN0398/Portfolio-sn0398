#pragma once

class Scene // 各シーンの基底クラス
{
public:

    Scene() = default;
    virtual ~Scene() = default;

public:

    virtual bool Update() = 0;
    virtual void Draw() = 0;

};