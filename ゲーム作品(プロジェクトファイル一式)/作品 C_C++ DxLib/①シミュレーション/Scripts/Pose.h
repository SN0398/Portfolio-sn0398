#pragma once
#include "UserInterface.h"
#include <list>
#include "MyLib.h"
#include "MessageBox.h"
#include <memory>

// 操作インターフェース：ポーズ画面
class Pose : public UserInterface
{
public:
	enum ResponceType
	{
		Continue = 0,
		Save,
		Load,
		Close,
	};

	struct Button
	{
		const char* DisplayName;
		Vector2D Pos1, Pos2;
		ResponceType Type;
		bool inCursor;				// カーソルと接触しているフラグ
		Button() = delete;
		Button(const char* DisplayName, ResponceType Rtype, Vector2D Pos1, Vector2D Pos2) :
			DisplayName(DisplayName), Type(Rtype), Pos1(Pos1), Pos2(Pos2), inCursor(false) {}
	};

public:
	Pose();
	~Pose() = default;

public:
	void Update() override;
	void Draw() override;
	
	// リスト内オブジェクトの当たり判定更新
	void UpdateButtonCollision();
	// クリック処理
	void onClickAction(ResponceType type);

public:
	std::list<Button*> buttonList;
	std::unique_ptr<MessageInterface> closeDialogue;
};