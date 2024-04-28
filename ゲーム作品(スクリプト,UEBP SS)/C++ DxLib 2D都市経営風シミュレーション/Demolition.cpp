#include "Demolition.h"
#include "ResourceManager.h"
#include "InterfaceManager.h"
#include "BuildingManager.h"
#include "Define.h"

Demolition::Demolition()
{
	MsgBox = MessageInterface_YesOrNo::Create("建物を解体しますか？");

	return;
}

void Demolition::Update()
{
	int Mpos[2];
	GetMousePoint(&Mpos[0], &Mpos[1]);
	Vector2D Point = { (float)Mpos[0],(float)Mpos[1] };
	MsgBox->HitStateUpdate(Point);
	if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
	{
		int HitType = MsgBox->GetHitState();
		if (HitType == SELECTED_YES) { Accept(); }
		else if (HitType == SELECTED_NO) { Deny(); }
	}

	return;
}

void Demolition::Draw()
{
	MapManager::GetInstance().DrawMap();
	BuildingManager::GetInstance().Draw();
	DrawWindow();
	DrawWorldInfo();

	if (MsgBox.get() == nullptr) { return; }
	MsgBox->Draw();

	return;
}

void Demolition::Accept()
{
	// 選択中の建物を削除する
	BuildingManager::GetInstance().EraseRequest(SelectBuilding);
	SelectBuilding = nullptr;
	// シーンを戻す
	InterfaceManager::GetInstance().BackInterface();
	return;
}

void Demolition::Deny()
{
	// 何もせずにシーンを戻す
	InterfaceManager::GetInstance().BackInterface();
	return;
}