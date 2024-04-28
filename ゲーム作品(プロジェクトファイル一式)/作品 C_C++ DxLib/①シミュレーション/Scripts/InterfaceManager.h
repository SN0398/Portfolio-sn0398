#pragma once
#include <stack>
#include <list>
#include <iostream>
#include "UserInterface.h"
#include "Singleton.h"

enum class InterfaceState
{
	PopTop,	// æ“ª‚Ì‚İíœ
	PopAll,	// ‘S‚Äíœ
	Push,	// æ“ª‚É’Ç‰Á
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
	// UIØ‚è‘Ö‚¦
	void PopAllInterface() { while (!TemporaryUI.empty()) { PopTopInterface(); } }
	void PopTopInterface() { TemporaryUI.pop(); }
	template <class T>
	void AddInterface() { TemporaryUI.push(std::make_unique<T>()); }
	void BackInterface() { if (TemporaryUI.size() > 1) PopTopInterface(); }

private:
	std::stack<std::unique_ptr<UserInterface>> TemporaryUI;

};