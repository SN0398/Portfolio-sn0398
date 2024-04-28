#include "GameObject/GameObject.h"

GameObject::GameObject()
{
	// �ϐ�������
	parent = nullptr;
	position = 0;
}

GameObject::GameObject(GameObject* _parent)
{
	// �ϐ�������
	parent = _parent;

	position = parent->position + 1;
}

void GameObject::SetParent(GameObject* parent)
{
	if (!parent) { return; }
	this->parent = parent;
}

GameObject* GameObject::GetParent() const
{
	return this->parent;
}

void GameObject::Update()
{
	UpdateComponents();
}

void GameObject::Draw()
{
	DrawComponents();
}

void GameObject::UpdateComponents()
{
	for (auto& cmp : components)
	{
		cmp->Update();
	}
}

void GameObject::DrawComponents()
{
	for (auto& cmp : components)
	{
		cmp->Update();
	}
}
