#pragma once

class Scene // �e�V�[���̊��N���X
{
public:

    Scene() = default;
    virtual ~Scene() = default;

public:

    virtual bool Update() = 0;
    virtual void Draw() = 0;

};