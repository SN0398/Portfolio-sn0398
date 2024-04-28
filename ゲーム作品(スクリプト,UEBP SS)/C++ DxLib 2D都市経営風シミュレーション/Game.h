#pragma once
#include "BaseScene.h"
#include "MapManager.h"

class Game : public Scene
{
public:
    Game();
    ~Game();

public:
    bool Update();
    void Draw();

};