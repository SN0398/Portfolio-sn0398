#include "Move.h"
#include "UnitMovement.h"
#include "InterfaceManager.h"
#include "ResourceManager.h"

Move::Move()
{
	// 始点初期化
	StartChip[0] = SelectChip[0];
	StartChip[1] = SelectChip[1];
	moveBuilding = BuildingManager::GetInstance().GetBuildingInfo(StartChip);
	LogManager::GetInstance().Claim("移動先を指定する");
	int i = 0;
	int heightMult = 45;
	int height = 800;
	i* height;
	int* value = &moveResidents.Resident[ResidentList::Character::Citizen];
	slider.push_back(std::make_unique<SliderController>(value, &Resource::GetInstance().CharacterIcon[0], "人数", height + i * heightMult, 100, 100 + BarLength, 0, moveBuilding->Residents->GetAllResident()));
	i++;
	value = &moveItems.Item[ItemList::Item_ID::Bread];
	slider.push_back(std::make_unique<SliderController>(value, &Resource::GetInstance().Items[0], "食糧", height + i * heightMult, 100, 100 + BarLength, 0, moveBuilding->Items->GetItemAmount(ItemList::Item_ID::Bread)));
	i++;
	value = &moveItems.Item[ItemList::Item_ID::Material];
	slider.push_back(std::make_unique<SliderController>(value, &Resource::GetInstance().Items[1], "資材", height + i * heightMult, 100, 100 + BarLength, 0, moveBuilding->Items->GetItemAmount(ItemList::Item_ID::Material)));
}

void Move::Update()
{
	UpdateProcess();

	// インターフェースを2個戻る
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	{
		InterfaceManager::GetInstance().BackInterface();
		InterfaceManager::GetInstance().BackInterface();
		return;
	}
	bool sliderSelected = false;

	for (auto& obj : slider)
	{
		// 更新
		if (obj->controller.Update())
		{
			sliderSelected = true;
		}
	}
	
	if (!sliderSelected)
	{
		// 左クリック
		if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
		{
			// カーソルの選択チップを更新
			MapManager::GetInstance().GetChipPos(SelectChip);
			// 選択チップが海チップ以外
			if (MapManager::GetInstance().GetChipID(SelectChip) != MapManager::Chip_ID::Ocean)
			{
				// 敵対勢力の土地
				if (WorldManager::GetInstance().GetFactionRelation
				(MapManager::GetInstance().GetChipFactionIndex(SelectChip)) == FACTION_RELATION_STATE_ENEMY)
				{
					LogManager::GetInstance().Claim("そこは敵対勢力の土地だ");
				}
				else if (!MapManager::GetInstance().GetIsFreeTerritory(SelectChip))
				{
					LogManager::GetInstance().Claim("そこは他勢力の土地だ");
				}
				else
				{
					Position start = { StartChip[0],StartChip[1] };
					Position target = { SelectChip[0],SelectChip[1] };
					// スライダーの値取得
					GetSliderValue();
					// 移動部隊作成
					int claimResponce = UnitMovement::GetInstance().Claim(start, target,
						moveBuilding, &moveItems, &moveResidents);
					// 戻り値別処理
					if (claimResponce == UNITMOVEMENT_CLAIM_SUCCESS)
					{
						InterfaceManager::GetInstance().BackInterface();
						InterfaceManager::GetInstance().BackInterface();
					}
					else if (claimResponce == UNITMOVEMENT_CLAIM_DENIED_RESIDENT_IS_EMPTY)
					{
						LogManager::GetInstance().Claim("移動させるキャラクターが存在しない");
					}
				}
			}
			else
			{
				LogManager::GetInstance().Claim("無意味な入水はやめよう");
			}
		}
	}

	return;
}

void Move::Draw()
{
	MapManager::GetInstance().Draw();
	BuildingManager::GetInstance().Draw();
	DrawStartChip();
	UnitMovement::GetInstance().Draw();
	LogManager::GetInstance().Draw();
	DrawWindow();
	DrawSlider();

	return;
}

void Move::DrawStartChip()
{
	// 描画位置と描画幅取得
	Vector2D SelectPos = MapManager::GetInstance().GetDrawPos({ (float)StartChip[0],(float)StartChip[1] });
	int size = MapManager::GetInstance().GetChipSize();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	// 描画
	DrawBox
	(
		SelectPos.x,
		SelectPos.y,
		SelectPos.x + size,
		SelectPos.y + size,
		Resource::GetInstance().Color[Color_ID::Blue], TRUE
	);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	return;
}

void Move::DrawSlider()
{
	int i = 0;
	int height = 45;
	int graphsize = 32;
	for (auto& obj : slider)
	{
		DrawExtendGraph
		(
			obj->controller.L - 40,
			obj->controller.Y - 20,
			obj->controller.L - 40 + graphsize,
			obj->controller.Y - 20 + graphsize,
			*obj->Graph, TRUE
		);
		DrawFormatStringToHandle
		(
			obj->controller.L + 10,
			obj->controller.Y - 20,
			GetColor(0, 0, 0),
			Resource::GetInstance().Font[Font_ID::Yumincho_medium],
			FormatNumber(obj->controller.Get()).c_str()
		);
		DrawExtendGraph
		(
			obj->controller.L,
			obj->controller.Y - 5,
			obj->controller.R,
			obj->controller.Y + 5,
			Resource::GetInstance().Bar, FALSE
		);
		DrawExtendGraph
		(
			obj->controller.X - SliderGraphSize,
			obj->controller.Y - SliderGraphSize,
			obj->controller.X + SliderGraphSize,
			obj->controller.Y + SliderGraphSize,
			Resource::GetInstance().CircleUI, TRUE
		);
		i++;
	}
	return;
}

void Move::GetSliderValue()
{
	for (auto& obj : slider)
	{
		*obj->Value = obj->controller.Get();
	}
	return;
}