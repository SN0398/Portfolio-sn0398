#include "ActionSelector.h"

#include "InterfaceManager.h"
#include "ResourceManager.h"
#include "MapManager.h"
#include "BuildingManager.h"
#include "WorldManager.h"

#include "MyLib.h"

#include "Build.h"
#include "Demolition.h"
#include "Move.h"

ActionSelector::ActionSelector()
{
	// 表示ボタン初期化
	ResetButtonList();
	// 初期化
	// 選択中の座標の建物の情報を手に入れる
	GetSelectChipInfo();

	return;
}

void ActionSelector::Update()
{
	UpdateProcess();
	// マウス座標取得
	int MX, MY;
	GetMousePoint(&MX, &MY);
	Vector2D MPos = { (float)MX,(float)MY };

	// ボタンの更新
	for (auto& obj : Button)
	{
		// 当たり判定更新
		obj->HitStateUpdate(MPos);
	}

	// Escキーで前のインターフェースに戻る
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	{
		SelectBuilding = nullptr;
		InterfaceManager::GetInstance().BackInterface();
		return;
	}

	// 左クリック
	if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
	{
		// 当たっていたボタンのポインタを得る
		ActionButton* hitObj = nullptr;		// 初期状態はオブジェクトが存在しない
		for (int i = 0; i < Button.size(); i++)
		{
			if (Button[i]->HitFlag)
			{
				hitObj = Button[i].get();
			}
		}
		// 当たっていたオブジェクトが存在する
		if (hitObj != nullptr)
		{
			// 当たっていたボタンの識別子別の処理
			switch (hitObj->Index)
			{
			case UI_Build:
			{
				InterfaceManager::GetInstance().AddInterface<Build>();
				return;
			}break;
			case UI_Demolition:
			{
				// キャラクターかアイテムが一つでも存在すれば解体しない
				if (SelectBuilding->GetHasContents())
				{
					LogManager::GetInstance().Claim("キャラクターもしくはアイテムが存在します。");
					LogManager::GetInstance().Claim("解体に失敗");
				}
				else
				{
					InterfaceManager::GetInstance().AddInterface<Demolition>();
				}
				return;
			}break;
			case UI_Move:
			{
				InterfaceManager::GetInstance().AddInterface<Move>();
				return;
			}break;
			default:
			{

			}break;
			}
		}
		// クリック座標がボタンに触れていない
		else
		{
			// 操作UI更新
			ResetButtonList();
		}
	}
	return;
}

void ActionSelector::Draw()
{
	MapManager::GetInstance().Draw();			// マップ描画
	BuildingManager::GetInstance().Draw();		// 建物描画
	UnitMovement::GetInstance().Draw();
	DrawSelectChip();		// 選択中のチップ可視化
	LogManager::GetInstance().Draw();
	DrawWindow();			// ウィンドウ描画
	DrawWorldInfo();		// 世界情報描画
	DrawBuildingInfo();		// 建物の情報描画

	if (!Button.empty())
	{
		for (auto& obj : Button)
		{
			obj->Draw();
		}
	}
	return;
}

void ActionSelector::ResetButtonList()
{
	// リスト解放
	Button.clear();

	float X, Y;
	X = 50;
	Y = 50;

	// クリックした瞬間選択していたマップチップ座標を得る
	MapManager::GetInstance().GetChipPos(SelectChip);
	// クリックした座標に建物があればその建物のポインタを得る
	GetSelectChipInfo();

	// 土地に何もない場合
	if (!SelectBuilding)
	{
		// 自分の土地で海以外
		if (MapManager::GetInstance().GetChipFactionIndex(SelectChip) == PLAYER_FACTIONINDEX &&
			MapManager::GetInstance().GetChipID(SelectChip) != MapManager::Chip_ID::Ocean)
		{
			// 建設
			{
				ActionButton* obj = ActionButton::Create
				(Vector2D{ X,Y }, Vector2D{ X + SELECTBOX_SIZE,Y + SELECTBOX_SIZE },
					"建設", Resource::GetInstance().Farm, ActionIndex::UI_Build);
				if (obj != nullptr)
				{
					unique_ptr<ActionButton> AddObj(obj);
					Button.push_back(std::move(AddObj));
					X += 50 + SELECTBOX_SIZE;
				}
			}
		}
	}
	// ある場合
	else
	{
		// 自分の勢力
		if (MapManager::GetInstance().GetChipFactionIndex(SelectChip) == PLAYER_FACTIONINDEX)
		{
			// 解体
			{
				ActionButton* obj = ActionButton::Create
				(Vector2D{ X,Y }, Vector2D{ X + SELECTBOX_SIZE,Y + SELECTBOX_SIZE },
					"解体", Resource::GetInstance().Farm, ActionIndex::UI_Demolition);
				if (obj != nullptr)
				{
					unique_ptr<ActionButton> AddObj(obj);
					Button.push_back(std::move(AddObj));
					X += 50 + SELECTBOX_SIZE;
				}
			}
			// 移動先を選択する
			{
				ActionButton* obj = ActionButton::Create
				(Vector2D{ X,Y }, Vector2D{ X + SELECTBOX_SIZE,Y + SELECTBOX_SIZE },
					"移動", Resource::GetInstance().Farm, ActionIndex::UI_Move);
				if (obj != nullptr)
				{
					unique_ptr<ActionButton> AddObj(obj);
					Button.push_back(std::move(AddObj));
					X += 50 + SELECTBOX_SIZE;
				}
			}
		}
		// 他勢力
		else if (MapManager::GetInstance().GetChipFactionIndex(SelectChip) < 1)
		{

		}
	}

	return;
}

ActionButton* ActionSelector::GetHitButton()
{
	for (auto& obj : ButtonList)
	{
		if (obj->HitFlag)
		{
			return obj.get();
		}
	}

	return nullptr;
}