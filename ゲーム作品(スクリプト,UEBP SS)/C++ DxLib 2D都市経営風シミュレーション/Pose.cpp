#include "Pose.h"
#include "ResourceManager.h"
#include "InterfaceManager.h"
#include "SceneManager.h"

Pose::Pose()
{
	Position2D MiddlePos = { SCREEN_WIDTH/2,SCREEN_HEIGHT/2 };
	buttonList.push_back(new Button("続ける",	Continue, Vector2D{ (double)MiddlePos.x-100,(double)MiddlePos.y-175 }, Vector2D{ (double)MiddlePos.x+100,(double)MiddlePos.y-125 }));
	buttonList.push_back(new Button("セーブ",   Save,     Vector2D{ (double)MiddlePos.x-100,(double)MiddlePos.y-75  }, Vector2D{ (double)MiddlePos.x+100,(double)MiddlePos.y-25  }));
	buttonList.push_back(new Button("ロード",	Load,     Vector2D{ (double)MiddlePos.x-100,(double)MiddlePos.y+25  }, Vector2D{ (double)MiddlePos.x+100,(double)MiddlePos.y+75  }));
	buttonList.push_back(new Button("終了",		Close,    Vector2D{ (double)MiddlePos.x-100,(double)MiddlePos.y+125 }, Vector2D{ (double)MiddlePos.x+100,(double)MiddlePos.y+175 }));

	closeDialogue = nullptr;
}

void Pose::Update()
{
	// メッセージボックスが表示されてない状態で処理を選ぶ
	if (closeDialogue.get() == nullptr)
	{
		// Escで戻る
		if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
		{
			InterfaceManager::GetInstance().BackInterface();
			return;
		}
		UpdateButtonCollision();	// コリジョン更新
		// マウスクリック
		if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
		{
			// カーソルと当たっているボタンのタイプ別処理を呼ぶ
			for (auto& obj : buttonList)
			{
				if (obj->inCursor)
				{
					onClickAction(obj->Type);
					return;
				}
			}
		}
	}
	// メッセージボックスが表示されている状態で選択別の処理を呼ぶ
	else
	{
		// Escで戻る
		if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
		{
			closeDialogue = nullptr;
		}
		// メッセージボックスの更新
		// マウスクリック
		if (MouseInput_Get(MOUSE_INPUT_LEFT) == 1)
		{
			int x, y;
			GetMousePoint(&x, &y);
			Vector2D Mpos = { (float)x, (float)y };
			closeDialogue->HitStateUpdate(Mpos);
			if (closeDialogue->GetHitState() == SELECTED_YES)
			{
				SceneManager::GetInstance().PopAllScene();
				return;
			}
			else if (closeDialogue->GetHitState() == SELECTED_NO)
			{
				closeDialogue = nullptr;
			}
		}
	}
	return;
}

void Pose::Draw()
{
	// リソースの別名
	auto& resource = Resource::GetInstance();

	MapManager::GetInstance().DrawMap();
	BuildingManager::GetInstance().Draw();

	// 背景色
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, resource.Color[Color_ID::Black], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// それぞれのボタンと文字列の描画
	for (auto obj : buttonList)
	{
		// ボックス描画
		DrawExtendGraph(obj->Pos1.x, obj->Pos1.y, obj->Pos2.x, obj->Pos2.y, resource.DialogueWindow, FALSE);
		// 中央ぞろえで文字列描画
		// ボックス左端と右端の値
		int middle = (obj->Pos1.x + obj->Pos2.x) / 2;
		// 文字の幅
		int width = GetDrawStringWidthToHandle(obj->DisplayName, strlen(obj->DisplayName), resource.Font[Font_ID::Yumincho]);
		// 描画
		DrawFormatStringToHandle
		(
			middle - width / 2,
			obj->Pos1.y + 17,
			resource.Color[Color_ID::Black],
			resource.Font[Font_ID::Yumincho],
			obj->DisplayName
		);
		// カーソルで選択中の場合のみボックスを半透明の黒で描画する
		if (obj->inCursor)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawBox(obj->Pos1.x, obj->Pos1.y, obj->Pos2.x, obj->Pos2.y, resource.Color[Color_ID::Black], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	};

	// ﾒｯｾｰｼﾞﾎﾞｯｸｽが表示されている状態ではﾒｯｾｰｼﾞﾎﾞｯｸｽ描画
	if (closeDialogue.get() != nullptr)
	{
		closeDialogue->Draw();
	}
	
	return;
}

void Pose::UpdateButtonCollision()
{
	int x, y;
	GetMousePoint(&x, &y);
	Vector2D Mpos = { (float)x, (float)y };
	for (auto& obj : buttonList)
	{
		obj->inCursor = CheckHitBoxToPoint2D(obj->Pos1, obj->Pos2, Mpos);
	}

	return;
}

void Pose::onClickAction(ResponceType type)
{
	switch (type)
	{
	case Continue:
	{
		InterfaceManager::GetInstance().BackInterface();
	}break;
	case Save:
	{

	}break;
	case Load:
	{

	}break;
	case Close:
	{
		closeDialogue = MessageInterface_YesOrNo::Create("終了しますか？");
	}break;
	}

	return;
}