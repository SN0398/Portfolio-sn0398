#include "Game.h"

// Requires
#include "MyLib.h"
#include "Scene/Game/Game.h"
#include "Scene/SceneManager.h"

// GameObjects
#include "GameObject/RendererInterface/RendererInterface.h"
#include "GameObject/3DModel/Cube/Cube.h"
#include "GameObject/ControlPanel/ControlPanel.h"

void Game::Initialize()
{
	SetBackgroundColor(160, 160, 160);

	{
		auto renderer = std::make_shared<RendererInterface>();
		gameobjects.push_back(renderer);

		for (int i = -5; i < 5; i++)
		{
			for (int j = -5; j < 5; j++)
			{
				for (int k = -5; k < 5; k++)
				{
					auto cube = std::make_shared<Mesh_Cube>();
					cube->transform.Position = Vector(i * 50, j * 50, k * 50);
					cube->transform.Scale = Vector(1.0f, 1.0f, 1.0f);
					if (i == 0 && j == 0 && k == 0)
					{
						cube->color = GetColorU8(255, 255, 0,0);
					}
					gameobjects.push_back(cube);
					renderer->model.push_back(cube);
				}
			}
		}

		//{
		//	auto cube2 = std::make_shared<Mesh_Cube>();
		//	cube2->transform.Position = Vector(100, -40, 30);
		//	cube2->transform.Rotation = Euler(90.0f, 0.0f, 0.0f);
		//	cube2->transform.Scale = Vector(5.0f, 5.0f, 5.0f);
		//	gameobjects.push_back(cube2);
		//	renderer->model.push_back(cube2.get());
		//}

		//{
		//	auto cube3 = std::make_shared<Mesh_Cube>();
		//	cube3->transform.Position = Vector(100, -40, 30);
		//	cube3->transform.Rotation = Euler(0.0f, 90.0f, 0.0f);
		//	cube3->transform.Scale = Vector(5.0f, 5.0f, 5.0f);
		//	gameobjects.push_back(cube3);
		//	renderer->model.push_back(cube3.get());
		//}

		//{
		//	auto cube4 = std::make_shared<Mesh_Cube>();
		//	cube4->transform.Position = Vector(100, -40, 30);
		//	cube4->transform.Rotation = Euler(0.0f, 0.0f, 90.0f);
		//	cube4->transform.Scale = Vector(5.0f, 5.0f, 5.0f);
		//	gameobjects.push_back(cube4);
		//	renderer->model.push_back(cube4.get());
		//}

		gameobjects.push_back(std::make_shared<ControlPanel>(&renderer->renderer));
	}

	{
	}

	return;
}

void Game::Clean()
{
	gameobjects.clear();
	return;
}

void Game::Update()
{
	UpdateGameObjects();

	// Escキーでシーンを一つ前に戻る
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	{
		SceneManager::GetInstance().Back();
		return;
	}
	return;
}

void Game::Draw()
{
	DrawGameObjects();
	return;
}