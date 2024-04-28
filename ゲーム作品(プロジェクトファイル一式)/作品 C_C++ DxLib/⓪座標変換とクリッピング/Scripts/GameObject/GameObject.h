#pragma once
#include "Component/Component.h"
#include "DxLib.h"
#include "MyLib.h"

#include <memory>
#include <list>

class GameObject abstract
{
private:
	using ComponentList = std::list<std::shared_ptr<Component>>;

public:
	GameObject();
	GameObject(GameObject* _parent);
	virtual ~GameObject() {}

public:
	// 親ポインタ設定
	void SetParent(GameObject* parent);
	// 親ポインタ取得
	GameObject* GetParent() const;

	virtual void Update();

	virtual void Draw();

	void UpdateComponents();

	void DrawComponents();

public:
	ComponentList components;	// コンポーネント
	GameObject* parent;			// 親オブジェクト
	int position;				// 樹上図での位置

};