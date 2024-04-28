#pragma once
#include "Scene/BaseScene.h"

class Game : public Scene
{
public:
    Game() { Initialize(); }
    ~Game() { Clean(); }

public:
    void Initialize() override;
    void Clean() override;
    void Update() override;
    void Draw() override;

};