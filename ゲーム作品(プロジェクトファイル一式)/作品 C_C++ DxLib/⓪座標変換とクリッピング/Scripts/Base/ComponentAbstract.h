//#pragma once
//#include "MyLib.h"
//
//class Component abstract
//{
//public:
//	Component() : parent(nullptr) {}
//	Component(Component* _parent) : parent(_parent) {}
//	~Component() = default;
//
//public:
//	void SetParent(Component* parent)
//	{
//		if (!parent) { return; }
//		this->parent = parent;
//	}
//	Component* GetParent() const
//	{
//		return this->parent;
//	}
//
//	virtual void Update() = 0;
//	virtual void Draw() = 0;
//
//protected:
//	Component* parent;
//
//};