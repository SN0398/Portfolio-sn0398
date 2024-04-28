#include "WorldManager.h"
#include "BuildingManager.h"

void WorldManager::Setup()
{
	Day = 0;
	Hour = 0;
	Minute = 0;
	Tcount = 0;
	IsHour = false;
	HungerRate = 0;
	Money = 0;
	FoodConsumption = 0;
	Tax = 3;
	Factions = make_unique<FactionList>();
	
	return;
}

void WorldManager::Update()
{	
	// �t���O�̃��Z�b�g
	IsHour	= false;
	IsHalfDay	= false;
	IsDay		= false;
	// �J�E���^��i�߂�
	if (++Tcount >= 60)
	{
		Tcount = 0;							// �J�E���^���Z�b�g
		if (++Minute >= 60)
		{
			IsHour = true;					// �ꎞ�Ԍo�߃t���O			
			Minute = 0;						// �J�E���^���Z�b�g

			Hour++;							// �J�E���^��i�߂�
			// ���Ԃ�12(����)�̏ꍇ
			if (Hour == 12)
			{
				IsHalfDay = true;			// �����o�߃t���O				
			}
			// ���Ԃ�24(���)�̏ꍇ
			if (Hour >= 24)
			{				
				IsDay = true;				// ����o�߃t���O
				Hour = 0;					// ���Z�b�g

				// �ő�l�̐ݒ�
				if (++Day > 999999999)
				{
					Day = 999999999;
				}
			}
		}
	}
	return;
}