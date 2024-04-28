#pragma once
#include <stack>
#include <list>
#include <iostream>
#include "UserInterface.h"
#include "Singleton.h"

enum class InterfaceState
{
	PopTop,	// 先頭のみ削除
	PopAll,	// 全て削除
	Push,	// 先頭に追加
};

class InterfaceManager : public Singleton<InterfaceManager>
{
public:
	InterfaceManager();
	~InterfaceManager();
	void Initialize();

public:
	void Update();
	void Draw();
	// UI切り替え
	void PopAllInterface() { while (!TemporaryUI.empty()) { PopTopInterface(); } }
	void PopTopInterface() { TemporaryUI.pop(); }
	template <class T>
	void AddInterface() { TemporaryUI.push(std::make_unique<T>()); }
	void BackInterface() { if (TemporaryUI.size() > 1) PopTopInterface(); }

private:
	std::stack<std::unique_ptr<UserInterface>> TemporaryUI;

};