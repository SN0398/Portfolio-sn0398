#include "Title.h"

#include "DxLib.h"
#include "MyLib.h"
#include "SceneManager.h"
#include "ResourceManager.h"

bool Title::Update()
{
	if (Keyboard_Get(KEY_INPUT_SPACE) == 1)
	{
		SceneManager::GetInstance().ChangeScene(Define::CS_CallType::Push, Define::SceneType::Game);
	}
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	{
		return false;
	}

	return true;
}

void Title::Draw()
{
	DrawExtendGraph
	(
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		Resource::GetInstance().TitleStill, FALSE
	);

	return;
}