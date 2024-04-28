#include "Build.h"
#include "InterfaceManager.h"
#include "BuildingManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "MapManager.h"

#include "Factory.h"
#include "Farm.h"
#include "Village.h"

#include "MessageBox.h"

Build::Build()
{
	LogManager::GetInstance().Claim("建設する建物を選択してください");
	float X, Y;
	X = 50;
	Y = 50;
	ActionButton* obj = nullptr;
	obj = ActionButton::Create
	(Vector2D{ X,Y }, Vector2D{ X + SELECTBOX_SIZE,Y + SELECTBOX_SIZE },
		"村", &Resource::GetInstance().Village[0], BuildingType::BT_Village);
	if (obj != nullptr)
	{
		unique_ptr<ActionButton> AddObj(obj);
		Button.push_back(std::move(AddObj));
		X += 50 + SELECTBOX_SIZE;
	}
	obj = ActionButton::Create
	(Vector2D{ X,Y }, Vector2D{ X + SELECTBOX_SIZE,Y + SELECTBOX_SIZE },
		"農場", &Resource::GetInstance().Farm[0], BuildingType::BT_Farm);
	if (obj != nullptr)
	{
		unique_ptr<ActionButton> AddObj(obj);
		Button.push_back(std::move(AddObj));
		X += 50 + SELECTBOX_SIZE;
	}
	obj = ActionButton::Create
	(Vector2D{ X,Y }, Vector2D{ X + SELECTBOX_SIZE,Y + SELECTBOX_SIZE },
		"工場", &Resource::GetInstance().Factory[0], BuildingType::BT_Factory);
	if (obj != nullptr)
	{
		unique_ptr<ActionButton> AddObj(obj);
		Button.push_back(std::move(AddObj));
		X += 50 + SELECTBOX_SIZE;
	}

	return;
}

Build::~Build()
{
	Button.clear();

	return;
}

void Build::Update()
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
			if (AddBuildingProcess(hitObj->Index))
			{
				InterfaceManager::GetInstance().BackInterface();
			}
		}
	}
	return;

	//if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	//{
	//	InterfaceManager::GetInstance().BackInterface();
	//	return;
	//}

	//// マウス座標取得
	//int MouseX, MouseY;
	//GetMousePoint(&MouseX, &MouseY);
	//Vector2D MPos = { (float)MouseX,(float)MouseY };
	//for (auto& obj : Button)
	//{
	//	if (HitStateUpdate(obj, MPos) &&			// 当たり判定の更新と返還
	//		MouseInput_Get(MOUSE_INPUT_LEFT) == 1)	// 左クリックを押した瞬間
	//	{
	//		// 選択座標に建物がない状態
	//		if (!BuildingManager::GetInstance().GetBuildingInfo(SelectChip))
	//		{
	//			// 選択座標が海
	//			if (MapManager::GetInstance().GetChipID(SelectChip) == 1) { return; }
	//			int MaterialAmount = WorldManager::GetInstance().Item->GetItemAmount(ItemList::Item_ID::Material);
	//			if (MaterialAmount >= obj->MaterialCost)
	//			{
	//				
	//				// 資材を消費する
	//				WorldManager::GetInstance().Item->ChangeItemAmount(ItemList::Item_ID::Material, -obj->MaterialCost);
	//				// 建物を追加して前のインターフェースに戻る
	//				AddBuildingProcess(obj);
	//				InterfaceManager::GetInstance().BackInterface();
	//			}
	//		}
	//	}
	//}

	//return;
}

void Build::Draw()
{
	DrawProcess();
	if (!Button.empty())
	{
		for (auto& obj : Button)
		{
			obj->Draw();
		}
	}

	return;
}

bool Build::AddBuildingProcess(int type)
{
	switch (type)
	{
	case Build::BuildingType::BT_Factory:
	{
		BuildingManager::GetInstance().AddRequest(new Factory(SelectChip[0],SelectChip[1]));
		break;
	}
	case Build::BuildingType::BT_Farm:
	{
		BuildingManager::GetInstance().AddRequest(new Farm(SelectChip[0],SelectChip[1]));
		break;
	}
	case Build::BuildingType::BT_Village:
	{
		BuildingManager::GetInstance().AddRequest(new Village(SelectChip[0],SelectChip[1]));
		break;
	}
	default:
	{
		return false;
		break;
	}
	}

	return true;
}