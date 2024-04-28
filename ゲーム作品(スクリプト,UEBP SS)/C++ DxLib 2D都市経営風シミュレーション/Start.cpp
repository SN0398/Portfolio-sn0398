#include "Start.h"
#include "BuildingManager.h"
#include "MapManager.h"
#include "InterfaceManager.h"
#include "LogManager.h"
#include "ChipSelect.h"
#include "Village.h"

Start::Start()
{
	Dialogue = MessageInterface_Ok::Create("Overrideへようこそ!");
}

void Start::Update()
{
	// シングルトンクラスの別名
	auto& buildingMgr = BuildingManager::GetInstance();
	auto& mapMgr = MapManager::GetInstance();
	auto& interfaceMgr = InterfaceManager::GetInstance();

	// ダイアログがアクティブな状態
	if (Dialogue != nullptr)
	{
		// メッセージボックスの更新
		// 入力
		if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
		{
			int x, y;
			GetMousePoint(&x, &y);
			Vector2D Mpos = { (float)x, (float)y };
			Dialogue->HitStateUpdate(Mpos);
			if (Dialogue->GetHitState() == SELECTED_OK)
			{
				Dialogue = nullptr;
			}
		}
		if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1 ||
			Keyboard_Get(KEY_INPUT_SPACE) == 1)
		{
			Dialogue = nullptr;
		}
		if (Dialogue == nullptr)
		{
			LogManager::GetInstance().Claim("最初の拠点を選択してください");
			LogManager::GetInstance().Claim("WASD...視点移動");
			LogManager::GetInstance().Claim("左クリック...選択");
		}
	}
	else
	{
		mapMgr.Update();
		LogManager::GetInstance().Update();

		// マウスクリックで建物を追加して通常UIに切り替え
		if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
		{
			// 追加する建物を初期化
			int pos[2];
			mapMgr.GetChipPos(pos);			// カーソル位置取得
			// 正しい値で実行
			if (mapMgr.GetMapChipValid(pos))
			{
				// 選択した場所に建物がなく、海チップ以外なら建物を追加する
				if (mapMgr.GetChipID(pos) != MapManager::Chip_ID::Ocean &&
					buildingMgr.GetBuildingInfo(pos) == nullptr)
				{
					Building* AddObj = new Village(pos[0], pos[1]);		// 農村生成

					AddObj->Items->SetItemAmount(ItemList::Item_ID::Bread, 500);
					AddObj->Items->SetItemAmount(ItemList::Item_ID::Material, 250);
					AddObj->Residents->SetResidents(ResidentList::Character::Farmer, 30);
					AddObj->Residents->SetResidents(ResidentList::Character::Soldier, 10);
					AddObj->Residents->SetResidents(ResidentList::Character::Builder, 10);

					// 追加
					buildingMgr.AddRequest(AddObj);
					// 選択座標を自分の勢力の土地にする
					mapMgr.ChangeTerritory(pos, 1);
					// インターフェース切り替え
					interfaceMgr.PopTopInterface();
					interfaceMgr.AddInterface<ChipSelect>();
					return;
				}
				else
				{
					LogManager::GetInstance().Claim("そこには建てられない");
				}
			}
		}
	}

	return;
}

void Start::Draw()
{
	MapManager::GetInstance().DrawMap();
	MapManager::GetInstance().DrawCursor();
	BuildingManager::GetInstance().Draw();
	LogManager::GetInstance().Draw();

	// ダイアログがアクティブな状態
	if (Dialogue != nullptr)
	{
		Dialogue->Draw();
	}

	return;
}