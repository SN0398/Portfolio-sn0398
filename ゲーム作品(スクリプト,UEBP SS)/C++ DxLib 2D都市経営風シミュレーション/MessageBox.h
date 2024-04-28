#pragma once
#include "MyLib.h"
#include <list>
#include <memory>
#include <vector>

#define SELECTED_NONE	0
#define SELECTED_YES	1
#define SELECTED_NO		2
#define SELECTED_OK		3

// メッセージボックスの基底クラス
class MessageInterface abstract
{
public:
	// ボタンの構造体
	struct Button
	{
		Vector2D Pos1, Pos2;
		bool HitFlag;
		const char* DisplayName;
	};

public:
	MessageInterface() = default;
	~MessageInterface() = default;

public:
	// 当たりの取得
	virtual int GetHitState() = 0;
	// 当たり判定更新
	void HitStateUpdate(Vector2D Cpos);
	// 描画
	void Draw();

protected:
	// ボタンの配列
	std::vector<std::unique_ptr<Button>> button;
	// タイトル
	const char* DisplayName;

};

class MessageInterface_YesOrNo : public MessageInterface
{
public:
	MessageInterface_YesOrNo() = default;
	~MessageInterface_YesOrNo() = default;

public:
	static std::unique_ptr<MessageInterface> Create(const char* str);
	int GetHitState() override;

};

class MessageInterface_Ok : public MessageInterface
{
public:
	MessageInterface_Ok() = default;
	~MessageInterface_Ok() = default;

public:
	static std::unique_ptr<MessageInterface> Create(const char* str);
	int GetHitState() override;

};