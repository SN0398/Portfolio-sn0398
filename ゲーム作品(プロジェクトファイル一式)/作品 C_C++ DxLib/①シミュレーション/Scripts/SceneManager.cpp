#include "SceneManager.h"

#include "Title.h"
#include "Game.h"

using namespace std;

SceneManager::SceneManager()
{
    return;
}

SceneManager::~SceneManager()
{
    PopAllScene();
    return;
}

void SceneManager::PopScene()
{
    s_stack.pop();
    return;
}

bool SceneManager::PushScene(Define::SceneType Stype)
{
    switch (Stype)
    {
    case Define::SceneType::Title:
    {
        s_stack.push(make_unique<Title>());
        break;
    }
    case Define::SceneType::Game:
    {
        s_stack.push(make_unique<Game>());
        break;
    }
    default:
    {
        return false;
    }
    }
    return true;
}

void SceneManager::PopAllScene()
{
    // スタックを全削除
    while (!s_stack.empty())
    {
        PopScene();
    }
}

bool SceneManager::ChangeScene(Define::CS_CallType CStype, Define::SceneType Stype)
{
    switch (CStype)
    {
    case Define::CS_CallType::PopAll:   // スタック内をすべて消してから先頭に追加
    {
        PopAllScene();
        return PushScene(Stype);
    }
    case Define::CS_CallType::PopTop:   // 先頭のスタックを消す
    {
        PopScene();
        return true;
    }
    case Define::CS_CallType::Push:     // 先頭に追加
    {
        return PushScene(Stype);
    }
    default:
    {
        break;
    }
    }
    return false;
}