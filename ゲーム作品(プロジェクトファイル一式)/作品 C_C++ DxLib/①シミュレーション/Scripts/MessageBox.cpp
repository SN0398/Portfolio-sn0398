#include "MessageBox.h"
#include "ResourceManager.h"

void MessageInterface::HitStateUpdate(Vector2D Cpos)
{
	// 当たり判定の更新
	Vector2D Pos1;
	Vector2D Pos2;
	for (int i = 0;i < button.size();i++)
	{
		Pos1 = button.at(i)->Pos1;
		Pos2 = button.at(i)->Pos2;
		button.at(i)->HitFlag = CheckHitBoxToPoint2D(Pos1, Pos2, Cpos);
	}
	return;
}

void MessageInterface::Draw()
{
	int DrawX, DrawY;
	DrawX = SCREEN_WIDTH / 2;
	DrawY = SCREEN_HEIGHT / 2;

	// ウィンドウ描画
	DrawExtendGraph
	(
		DrawX - 150, DrawY - 60,
		DrawX + 150, DrawY + 60,
		Resource::GetInstance().DialogueWindow, FALSE
	);
	Vector2D* Pos1;
	Vector2D* Pos2;
	for (int i = 0;i < button.size();i++)
	{
		Pos1 = &button.at(i)->Pos1;
		Pos2 = &button.at(i)->Pos2;
		// ボタン描画
		DrawExtendGraph
		(
			Pos1->x, Pos1->y,
			Pos2->x, Pos2->y,
			Resource::GetInstance().InfoWindow, FALSE
		);
		// カーソルとボタンが当たっているフラグが立っている状態
		if (button.at(i)->HitFlag)
		{
			// 半透明の黒色を描画する
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
			DrawBox
			(
				Pos1->x, Pos1->y,
				Pos2->x, Pos2->y,
				Resource::GetInstance().Color[Color_ID::Black], TRUE
			);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		// ボタン文字描画
		DrawFormatStringToHandle
		(
			Pos1->x + 25, Pos1->y + 20,
			Resource::GetInstance().Color[Color_ID::White],
			Resource::GetInstance().Font[Font_ID::Yumincho],
			button.at(i)->DisplayName
		);
	}
	int middle = SCREEN_WIDTH / 2;
	// 文字の幅
	int width = GetDrawStringWidthToHandle(DisplayName, strlen(DisplayName), Resource::GetInstance().Font[Font_ID::Yumincho]);
	// ウィンドウ文字描画
	DrawFormatStringToHandle
	(
		middle - width / 2,
		DrawY - 40,
		Resource::GetInstance().Color[Color_ID::White],
		Resource::GetInstance().Font[Font_ID::Yumincho],
		DisplayName
	);

	return;
}

// 派生クラスの仮想関数オーバーライド定義

std::unique_ptr<MessageInterface> MessageInterface_YesOrNo::Create(const char* str)
{
	// MessageInterface_YesOrNo の unique_ptr オブジェクトを生成
	auto AddObj = std::make_unique<MessageInterface_YesOrNo>();

	AddObj->DisplayName = str;

	// ボタンを追加
	AddObj->button.emplace_back(std::make_unique<MessageInterface::Button>
		(MessageInterface::Button{ { 835,530 },{ 935,580 },false,"承諾" }));
	AddObj->button.emplace_back(std::make_unique<MessageInterface::Button>
		(MessageInterface::Button{ { 985,530 },{ 1085,580 },false,"却下" }));

	// unique_ptr<MessageInterface_YesOrNo> 型の unique_ptr オブジェクトに変換して返す
	return std::unique_ptr<MessageInterface_YesOrNo>(std::move(AddObj));
	//return AddObj;
}

int MessageInterface_YesOrNo::GetHitState()
{
	// 当たっているボタンに応じた値を返す
	if (button.at(0)->HitFlag)
	{
		return SELECTED_YES;
	}
	else if (button.at(1)->HitFlag)
	{
		return SELECTED_NO;
	}
	return SELECTED_NONE;
}

std::unique_ptr<MessageInterface> MessageInterface_Ok::Create(const char* str)
{
	// MessageInterface_Ok の unique_ptr オブジェクトを生成
	auto AddObj = std::make_unique<MessageInterface_Ok>();

	AddObj->DisplayName = str;

	// ボタンを追加
	AddObj->button.emplace_back(std::make_unique<MessageInterface::Button>
		(MessageInterface::Button{ { SCREEN_WIDTH / 2-50,530 },{ SCREEN_WIDTH / 2+50,580 },false,"了解" }));

	// unique_ptr<MessageInterface_YesOrNo> 型の unique_ptr オブジェクトに変換して返す
	return std::unique_ptr<MessageInterface_Ok>(std::move(AddObj));
	//return AddObj;
}

int MessageInterface_Ok::GetHitState()
{
	// 当たっているボタンに応じた値を返す
	if (button.front()->HitFlag)
	{
		return SELECTED_OK;
	}
	return SELECTED_NONE;
}
