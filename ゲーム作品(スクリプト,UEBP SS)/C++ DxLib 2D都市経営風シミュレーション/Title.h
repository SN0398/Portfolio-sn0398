#pragma once
#include "BaseScene.h"

class Title : public Scene
{
public:

    Title() = default;
    ~Title() = default;

public:

    bool Update();
    void Draw();

};