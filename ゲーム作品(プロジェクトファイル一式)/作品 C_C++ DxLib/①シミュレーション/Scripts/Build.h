#pragma once
#include "UserInterface.h"
#include "MyLib.h"
#include <list>
#include "ActionButton.h"

#define SELECTBOX_SIZE	128

// ����C���^�[�t�F�[�X�F���z
class Build : public UserInterface
{
public:
	// �����̎��ʎq
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
