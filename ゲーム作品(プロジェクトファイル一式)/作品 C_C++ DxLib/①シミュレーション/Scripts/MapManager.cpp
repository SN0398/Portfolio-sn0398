#include "MapManager.h"
#include "ResourceManager.h"
#include "BuildingManager.h"
#include "WorldManager.h"

void MapManager::SetUp()
{
	Position = Vector2D{ MAP_WIDTH * MAP_CHIP_SIZE_DEFAULT / 2,MAP_HEIGHT * MAP_CHIP_SIZE_DEFAULT / 2 };
 	ChipSize = MAP_CHIP_SIZE_DEFAULT;
	LoadData(MapChip, sizeof(MapChip), MAPDATAPATH);
	//LoadData(TerritoryMap, sizeof(TerritoryMap), TERRITORYDATAPATH);
	memset(TerritoryMap, NONE_FACTIONINDEX, sizeof(TerritoryMap));
	DrawTerritoryMap = false;

	DefaultCostTable[None] = -1;
	DefaultCostTable[Ocean] = 10;
	DefaultCostTable[Grass] = 1;
	DefaultCostTable[Sand] = 2;
	DefaultCostTable[Snow] = 2;
	DefaultCostTable[Gravel] = 2;

	return;
}

void MapManager::Update()
{
	// ズームイン・アウト処理
	ZoomProcess();

	// カメラの平行移動
	CameraMoveUpdate();

	// カーソルが選択中のマップ座標更新
	CursorPositionUpdate();

	// キー入力で勢力分布マップ表示切替
	ChangeDrawTerritoryModify();

	return;
}

void MapManager::Draw()
{
	// マップ描画
	DrawMap();

	// カーソル描画
	DrawCursor();

	// デバッグ
	//DrawDebugInfo();

	return;
}

void MapManager::ZoomProcess()
{
	// マウスホイールの回転量を取得
	// 最後に呼ばれてからマウスホイールが回転した量を得る
	int mouseRot = GetMouseWheelRotVol();
	// マウスホイールが回転している
	if (mouseRot != 0)
	{
		if (ChipSize + mouseRot >= 10 && ChipSize + mouseRot <= 256)
		{
			// マップチップサイズを更新
			ChipSize += mouseRot * (ChipSize / 8);

			// 座標補正
			Position.y = (Position.y / (ChipSize - mouseRot)) * ChipSize;
			Position.x = (Position.x / (ChipSize - mouseRot)) * ChipSize;
		}
		else
		{
			// マップチップサイズを更新
			ChipSize += mouseRot * (ChipSize / 8);
			// 限界値補正
			if (ChipSize < 10) { ChipSize = 10; }
			if (ChipSize > 256) { ChipSize = 256; }
		}
	}

	return;
}

void MapManager::CameraMoveUpdate()
{
	// 1フレームの移動ベクトル
	float VecX = 0;
	float VecY = 0;

	// 右移動
	if (Keyboard_Get(KEY_INPUT_D) >= 1)
	{
		VecX += 1;
	}
	// 左移動
	if (Keyboard_Get(KEY_INPUT_A) >= 1)
	{
		VecX -= 1;
	}
	// 下移動
	if (Keyboard_Get(KEY_INPUT_S) >= 1)
	{
		VecY += 1;
	}
	// 上移動
	if (Keyboard_Get(KEY_INPUT_W) >= 1)
	{
		VecY -= 1;
	}
	// 移動ベクトルの正規化
	Vector2D move = Normalize_2D(GetVec2D(VecX, VecY));

	// 座標に移動ベクトル * 速度を加算代入する
	Position = AddVec2D(Position, MulVec2D(move, CAMERA_MOVESPEED));

	// ↓キーで中央に移動
	if (Keyboard_Get(KEY_INPUT_DOWN) == 1)
	{
		Position.x = (MAP_WIDTH * ChipSize) / 2;
		Position.y = (MAP_HEIGHT * ChipSize) / 2;
	}
	// 左クリックで見ている場所に移動
	if (MouseInput_Get(MOUSE_INPUT_RIGHT) == 1)
	{
		int MouseX, MouseY;
		GetMousePoint(&MouseX, &MouseY);
		// マップ座標取得
		Position.x = ((int)Position.x + (MouseX - (MAP_DRAWPOINTX + ((MAP_DRAWWIDTH - (MAP_DRAWWIDTH % (ChipSize * 2))) / 2))));
		Position.y = ((int)Position.y + (MouseY - (MAP_DRAWPOINTY + ((MAP_DRAWHEIGHT - (MAP_DRAWHEIGHT % (ChipSize * 2))) / 2))));
	}

	return;
}

void MapManager::CursorPositionUpdate()
{
	int MouseX, MouseY;
	GetMousePoint(&MouseX, &MouseY);

	// マップ座標取得
	SelectChip[0] = ((int)Position.x + (MouseX - (MAP_DRAWPOINTX + ((MAP_DRAWWIDTH - (MAP_DRAWWIDTH % (ChipSize * 2))) / 2))));
	SelectChip[1] = ((int)Position.y + (MouseY - (MAP_DRAWPOINTY + ((MAP_DRAWHEIGHT - (MAP_DRAWHEIGHT % (ChipSize * 2))) / 2))));

	// カーソルがマップ内に収まっているフラグを立てる
	CursorInMap = true;
	// マップ座標が0~63の間でなかったらフラグを折る
	if (!GetMapChipValid(SelectChip))
	{
		CursorInMap = false;
	}

	return;
}

void MapManager::CostTableUpdate(int FactionIndex)
{
	// コストの更新
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			// 初期化
			CostTable[i][j] = 0;
			// チップの移動コスト
			CostTable[i][j] += DefaultCostTable[MapChip[i][j]];
			// 自勢力以外の土地
			if (TerritoryMap[i][j] != FactionIndex)
			{
				CostTable[i][j] += 2;
			}
			// 友好勢力か無所属の土地ではない
			if(WorldManager::GetInstance().Factions->List[FactionIndex]->
				GetRelationState(TerritoryMap[i][j]) != FACTION_RELATION_STATE_ALLY ||
				!GetIsFreeTerritory(i, j))
			{
				CostTable[i][j] += 3;
			}

			// 敵対勢力の土地
			if (WorldManager::GetInstance().Factions->List[FactionIndex]->
				GetRelationState(TerritoryMap[i][j]) == FACTION_RELATION_STATE_ENEMY)
			{
				CostTable[i][j] += 5;
				int chip[2] = { i,j };
				// 敵対勢力の建物があったら移動不能
				if (BuildingManager::GetInstance().GetBuildingInfo(chip))
				{
					CostTable[i][j] = -1;
					continue;
				}
			}
		}
	}

	return;
}

void MapManager::DrawMap()
{
	int MapDrawPointX, MapDrawPointY;		// 描画するマップ座標値
	int DrawMapChipNumX, DrawMapChipNumY;	// 描画するマップチップの数
	int DrawPointX, DrawPointY;				// 描画する座標
	int ScrollX, ScrollY;					// 描画用補正値

	// 描画するマップチップの数をセット
	// マップに描画できるチップ数と補正用値
	DrawMapChipNumX = MAP_DRAWWIDTH / ChipSize + 2;
	DrawMapChipNumY = MAP_DRAWHEIGHT / ChipSize + 2;

	// 画面左上に描画するマップ座標をセット
	MapDrawPointX = ((int)Position.x / ChipSize) - (DrawMapChipNumX / 2 - 1);
	MapDrawPointY = ((int)Position.y / ChipSize) - (DrawMapChipNumY / 2 - 1);

	// 描画位置をセット
	DrawPointX = MAP_DRAWPOINTX;
	DrawPointY = MAP_DRAWPOINTY;

	// 補正値のセット
	ScrollX = -((int)Position.x % ChipSize);
	ScrollY = -((int)Position.y % ChipSize);

	// マップを描く
	for (int i = -1; i < DrawMapChipNumY; i++)
	{
		for (int j = -1; j < DrawMapChipNumX; j++)
		{
			// 描画位置の更新
			DrawPointX = MAP_DRAWPOINTX + (j * ChipSize);
			DrawPointY = MAP_DRAWPOINTY + (i * ChipSize);

			// 画面からはみ出た位置
			if (j + MapDrawPointX < 0 || i + MapDrawPointY < 0 ||
				j + MapDrawPointX >= MAP_WIDTH || i + MapDrawPointY >= MAP_HEIGHT)
			{
				// 海描画
				DrawExtendGraph
				(
					DrawPointX + ScrollX,
					DrawPointY + ScrollY,
					DrawPointX + ScrollX + ChipSize,
					DrawPointY + ScrollY + ChipSize,
					Resource::GetInstance().Chip[1], FALSE
				);
				continue;
			}
			// マップ描画
			DrawExtendGraph
			(
				DrawPointX + ScrollX,
				DrawPointY + ScrollY,
				DrawPointX + ScrollX + ChipSize,
				DrawPointY + ScrollY + ChipSize,
				Resource::GetInstance().Chip[MapChip[i + MapDrawPointY][j + MapDrawPointX]], FALSE
			);
		}
	}
	// 勢力地図表示フラグ
	if (DrawTerritoryMap)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		// マップを描く
		for (int i = -1; i < DrawMapChipNumY; i++)
		{
			for (int j = -1; j < DrawMapChipNumX; j++)
			{
				// 描画位置の更新
				DrawPointX = MAP_DRAWPOINTX + (j * ChipSize);
				DrawPointY = MAP_DRAWPOINTY + (i * ChipSize);

				// 画面からはみ出た位置
				if (j + MapDrawPointX < 0 || i + MapDrawPointY < 0 ||
					j + MapDrawPointX >= MAP_WIDTH || i + MapDrawPointY >= MAP_HEIGHT)
				{
					continue;
				}
				// マップ描画
				int factionIndex = TerritoryMap[i + MapDrawPointY][j + MapDrawPointX];
				// 勢力が存在しなかったら実行しない
				if (factionIndex < WorldManager::GetInstance().Factions->List.size() &&
					factionIndex >= 1)
				{
					DrawBox
					(
						DrawPointX + ScrollX,
						DrawPointY + ScrollY,
						DrawPointX + ScrollX + ChipSize,
						DrawPointY + ScrollY + ChipSize,
						WorldManager::GetInstance().Factions->List[factionIndex]->Color,
						TRUE
					);
				}
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	return;
}

void MapManager::ChangeDrawTerritoryModify()
{
	// キー入力で勢力分布マップ表示切替
	if (Keyboard_Get(KEY_INPUT_F1) == 1)
	{
		++DrawTerritoryMap %= 2;
	}

	return;
}

void MapManager::DrawCursor()
{
	// カーソルがマップチップ内に収まっているフラグが立っていなければ処理を抜ける
	if (!CursorInMap) { return; }
	// 変数
	int DrawPointX, DrawPointY;				// 描画する座標
	int MouseX, MouseY;						// マウス位置
	int ScrollX, ScrollY;					// 描画用補正値
	int SizeDiffX, SizeDiffY;				// 描画位置とチップサイズの座標補間
	int MPosX, MPosY;						// カーソルで選択中の画面内マップ座標

	GetMousePoint(&MouseX, &MouseY);

	// 補正値のセット
	ScrollX = -((int)Position.x % ChipSize);
	ScrollY = -((int)Position.y % ChipSize);

	// 座標とチップサイズの補正値
	SizeDiffX = MAP_DRAWPOINTX % ChipSize;
	SizeDiffY = MAP_DRAWPOINTY % ChipSize;

	// カーソルで選択中の画面内マップ座標
	MPosX = ((MouseX - SizeDiffX - ScrollX) / ChipSize);
	MPosY = ((MouseY - SizeDiffY - ScrollY) / ChipSize);

	// 描画位置の更新
	DrawPointX = MPosX * ChipSize + SizeDiffX;
	DrawPointY = MPosY * ChipSize + SizeDiffY;

	// 透過
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	// カーソル描画
	DrawBox
	(
		DrawPointX + ScrollX,
		DrawPointY + ScrollY,
		DrawPointX + ScrollX + ChipSize,
		DrawPointY + ScrollY + ChipSize,
		Resource::GetInstance().Color[Color_ID::White], TRUE
	);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	return;
}

void MapManager::DrawDebugInfo()
{
	clsDx();
	printfDx("\n[Map Class]\n");
	printfDx("カメラ座標<%0.1f,%0.1f>\n", Position.x, Position.y);
	printfDx("カメラ座標(チップ)<%d,%d>\n", (int)Position.x / ChipSize, (int)Position.y / ChipSize);
	printfDx("選択座標<%d,%d>\n", SelectChip[0], SelectChip[1]);
	printfDx("選択座標(チップ)<%d,%d>\n", SelectChip[0] / ChipSize, SelectChip[1] / ChipSize);
	printfDx("InMap<%d>\n", CursorInMap);
	printfDx("Size<%d>\n", ChipSize);

	return;
}

Vector2D MapManager::GetDrawPos(Vector2D pos)
{
	int DrawDiffX = MAP_DRAWWIDTH / 2 % ChipSize;
	int DrawDiffY = MAP_DRAWHEIGHT / 2 % ChipSize;
	Vector2D result;
	result.x = (MAP_DRAWPOINTX + (MAP_DRAWWIDTH  / 2)) + ((pos.x * ChipSize) - ((int)Position.x) - DrawDiffX);
	result.y = (MAP_DRAWPOINTY + (MAP_DRAWHEIGHT / 2)) + ((pos.y * ChipSize) - ((int)Position.y) - DrawDiffY);
	return result;
}

void MapManager::GetChipPos(int* pChip)
{
	if (!CursorInMap || pChip == nullptr)
	{
		return; 
	}
	pChip[0] = SelectChip[0] / ChipSize;
	pChip[1] = SelectChip[1] / ChipSize;
	return;
}

bool MapManager::GetIsFreeTerritory(int* Pos)
{
	// 勢力のインデックス1は自勢力
	// 1未満は無所属

	// プレイヤーが干渉できる土地かどうか判別する
	if (TerritoryMap[Pos[1]][Pos[0]] <= 1)
	{
		return true;
	}
	return false;
}

bool MapManager::GetIsFreeTerritory(int x, int y)
{
	// 勢力のインデックス1は自勢力
	// 1未満は無所属

	// プレイヤーが干渉できる土地かどうか判別する
	if (TerritoryMap[y][x] <= 1)
	{
		return true;
	}
	return false;
}

void MapManager::ChangeTerritory(int* pChip, int index)
{
	if (pChip == nullptr) { return; }

	TerritoryMap[pChip[1]][pChip[0]] = index;

	return;
}

bool MapManager::GetMapChipValid(int Chip[2])
{
	// マップ座標が0~63の間でなかったらfalseを返す
	if (SelectChip[0] < 0 || SelectChip[0] > MAP_WIDTH * ChipSize ||
		SelectChip[1] < 0 || SelectChip[1] > MAP_HEIGHT * ChipSize)
	{
		return false;
	}
	return true;
}
