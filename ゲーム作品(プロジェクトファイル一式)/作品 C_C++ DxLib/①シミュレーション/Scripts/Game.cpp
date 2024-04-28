#include "Game.h"

#include "DxLib.h"
#include "MyLib.h"
#include "SceneManager.h"
#include "ResourceManager.h"

#include "DataManager.h"

#include "WorldManager.h"
#include "MapManager.h"
#include "BuildingManager.h"
#include "InterfaceManager.h"

Game::Game()
{
	DataManager::GetInstance().Load();

	return;
}

Game::~Game()
{

	return;
}

bool Game::Update()
{
	InterfaceManager::GetInstance().Update();

	return true;
}

void Game::Draw()
{
	InterfaceManager::GetInstance().Draw();

	return;
}