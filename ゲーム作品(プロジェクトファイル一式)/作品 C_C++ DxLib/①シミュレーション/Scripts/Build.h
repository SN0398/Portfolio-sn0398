#pragma once
#include "UserInterface.h"
#include "MyLib.h"
#include <list>
#include "ActionButton.h"

#define SELECTBOX_SIZE	128

// 操作インターフェース：建築
class Build : public UserInterface
{
public:
	// 建物の識別子
	enum BuildingType
	{
		BT_None = -1,
		BT_Factory,
		BT_Farm,
		BT_Village,
		BT_Dummy,
	};

public:
	Build();
	~Build();

public:
	void Update() override;
	void Draw() override;
	
	bool AddBuildingProcess(int type);

private:
	std::vector<std::unique_ptr<ActionButton>> Button;

};
