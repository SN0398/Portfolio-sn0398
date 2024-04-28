#pragma once
#include "UserInterface.h"
#include <list>
#include <memory>
#include "Slider.h"

// 操作インターフェース：移動画面
class Move : public UserInterface
{
public:
	struct SliderController
	{
		int* Value;
		int* Graph;
		Slider controller;
		std::string str;
		SliderController(int* valuePtr, int* graphPtr, std::string displayName, int PosY, int leftPos, int rightPos, int minValue, int maxValue) :
			Value(valuePtr), Graph(graphPtr), str(displayName), controller(PosY, leftPos, rightPos, minValue, maxValue) {}
	};
public:
	Move();
	~Move() = default;

public:
	void Update() override;
	void Draw() override;
	void DrawStartChip();
	void DrawSlider();
	void GetSliderValue();

private:
	const int SliderGraphSize = 16;
	const int BarLength = 200;
	Building* moveBuilding;
	std::list<std::unique_ptr<SliderController>> slider;
	int StartChip[2];
	ResidentList moveResidents;
	ItemList moveItems;

};