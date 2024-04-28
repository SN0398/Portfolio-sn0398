#include "ChipSelect.h"
#include "InterfaceManager.h"

#include "ResourceManager.h"
#include "Define.h"

#include "Pose.h"
#include "ActionSelector.h"

void ChipSelect::Update()
{
	UpdateProcess();
	// 左クリックを押した瞬間
	if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
	{
		// クリックした瞬間選択していたマップチップ座標を得る
		MapManager::GetInstance().GetChipPos(SelectChip);
		// 選択マップチップへの行動を選択する処理へ遷移させる
		InterfaceManager::GetInstance().AddInterface<ActionSelector>();
		return;
	}
	// Escキーでポーズ
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	{
		InterfaceManager::GetInstance().AddInterface<Pose>();
		return;
	}

	return;
}

void ChipSelect::Draw()
{
	DrawProcess();

	return;
}