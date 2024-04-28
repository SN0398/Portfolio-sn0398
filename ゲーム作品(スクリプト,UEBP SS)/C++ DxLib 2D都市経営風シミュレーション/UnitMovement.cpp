#include "UnitMovement.h"
#include "MapManager.h"
#include "ResourceManager.h"
#include "BuildingManager.h"
#include "WorldManager.h"
#include "Camp.h"
#include "LogManager.h"

void UnitMovement::Update()
{
	int Chipsize = MapManager::GetInstance().GetChipSize();
	// 移動している部隊の更新
	for (auto& obj : dataList)
	{
		// カウンタが最大に到達で座標を移動する
		obj->Count += obj->MoveSpeed;
		if (obj->Count >= UNITMOVEMENT_MAXCOUNT)
		{
			// 先頭ノード座標を現在の座標にする
			obj->NowPos = obj->Route[0]->pos;
			// 先頭ノードを削除
			obj->Route.erase(obj->Route.begin());
			// カウンタ初期化
			obj->Count = 0;
		}
		// 目的地に到着で移動を終了
		if (obj->Route.empty())
		{
			// 座標変換
			int pos[2] = { obj->NowPos.x,obj->NowPos.y };
			// 移動先に建物があれば移動してから削除
			auto goalNode = BuildingManager::GetInstance().GetBuildingInfo(pos);
			if (goalNode)
			{
				*goalNode->Items += obj->Inventory;
				*goalNode->Residents += obj->Residents;
			}
			// 移動先に何もなければキャンプを設置する
			else
			{
				Building* addObj = new Camp(obj->NowPos.x, obj->NowPos.y);
				*addObj->Items += obj->Inventory;
				*addObj->Residents += obj->Residents;
				BuildingManager::GetInstance().AddRequest(addObj);
			}
			// 無所属の土地なら自分の土地にする
			if (MapManager::GetInstance().GetChipFactionIndex(pos) == NONE_FACTIONINDEX)
			{
				MapManager::GetInstance().ChangeTerritory(pos, PLAYER_FACTIONINDEX);
			}
			// ログ追加
			string str = "部隊が到着した";
			LogManager::GetInstance().Claim(str.c_str());
			// オブジェクトが存在するイテレータを取得
			auto itr = std::find(dataList.begin(), dataList.end(), obj);
			// オブジェクト削除
			delete *itr;
			dataList.erase(itr);
			return;
		}
		// オフセットの更新	カウンタ * チップサイズ * 方向
		obj->offsetX = (obj->Count / UNITMOVEMENT_MAXCOUNT) *
			Chipsize * (obj->Route[0]->pos.x - obj->NowPos.x);
		obj->offsetY = (obj->Count / UNITMOVEMENT_MAXCOUNT) *
			Chipsize * (obj->Route[0]->pos.y - obj->NowPos.y);
	}

	return;
}

void UnitMovement::Draw()
{
	DrawInfo();

	// 移動している部隊の描画
	for (auto& obj : dataList)
	{
		// 描画座標
		Vector2D DrawPos = 
			MapManager::GetInstance().GetDrawPos({ (float)obj->NowPos.x,(float)obj->NowPos.y });
		// 描画サイズ
		int size = MapManager::GetInstance().GetChipSize();

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

		// 描画
		DrawBox
		(
			DrawPos.x,
			DrawPos.y,
			DrawPos.x + size,
			DrawPos.y + size,
			Resource::GetInstance().Color[Color_ID::Blue], TRUE
		);
		for (auto& node : obj->Route)
		{
			// 描画位置と描画幅取得
			Vector2D startPos = MapManager::GetInstance().GetDrawPos({ (float)node->pos.x,(float)node->pos.y });

			// 描画
			DrawBox
			(
				startPos.x,
				startPos.y,
				startPos.x + size,
				startPos.y + size,
				Resource::GetInstance().Color[Color_ID::Blue], TRUE
			);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// 描画
		DrawCircle
		(
			DrawPos.x + size / 2 + obj->offsetX,
			DrawPos.y + size / 2 + obj->offsetY,
			size / 4,
			GetColor(157, 255, 132),
			TRUE
		);
		DrawCircle
		(
			DrawPos.x + size / 2 + obj->offsetX,
			DrawPos.y + size / 2 + obj->offsetY,
			size / 4,
			GetColor(0, 0, 0),
			FALSE, 5
		);
	}

	return;
}

void UnitMovement::DrawInfo()
{


	return;
}

int UnitMovement::Claim(Position start, Position goal, Building* base, ItemList* moveItems, ResidentList* moveResidents)
{
	// キャラクターが存在しなければ移動部隊を追加しない
	if (moveResidents->GetAllResident() < 1) { return UNITMOVEMENT_CLAIM_DENIED_RESIDENT_IS_EMPTY; }

	UnitData* temp = new UnitData;

	// 変数初期化
	temp->offsetX = 0.0f;
	temp->offsetY = 0.0f;
	temp->Count = 0;

	// コストテーブル更新
	MapManager::GetInstance().CostTableUpdate(MapManager::GetInstance().GetChipFactionIndex(start.x, start.y));

	// 経路探索
	temp->Route = Astar::AStarAlgorithm(start, goal);

	// 初期位置を代入
	temp->NowPos = start;

	// 拠点から物資を取り出す
	temp->Inventory = *moveItems;
	*base->Items -= *moveItems;

	// 拠点からキャラクターを移動する
	temp->Residents = *moveResidents;
	*base->Residents -= *moveResidents;

	// 初期行軍スピードを算出
	temp->MoveSpeed = 300;

	dataList.push_back(temp);

	return UNITMOVEMENT_CLAIM_SUCCESS;
}