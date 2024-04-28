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
	// �e�|�C���^�ݒ�
	void SetParent(GameObject* parent);
	// �e�|�C���^�擾
	GameObject* GetParent() const;

	virtual void Update();

	virtual void Draw();

	void UpdateComponents();

	void DrawComponents();

public:
	ComponentList components;	// �R���|�[�l���g
	GameObject* parent;			// �e�I�u�W�F�N�g
	int position;				// ����}�ł̈ʒu

};