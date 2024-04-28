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
	// フラグのリセット
	IsHour	= false;
	IsHalfDay	= false;
	IsDay		= false;
	// カウンタを進める
	if (++Tcount >= 60)
	{
		Tcount = 0;							// カウンタリセット
		if (++Minute >= 60)
		{
			IsHour = true;					// 一時間経過フラグ			
			Minute = 0;						// カウンタリセット

			Hour++;							// カウンタを進める
			// 時間が12(半日)の場合
			if (Hour == 12)
			{
				IsHalfDay = true;			// 半日経過フラグ				
			}
			// 時間が24(一日)の場合
			if (Hour >= 24)
			{				
				IsDay = true;				// 一日経過フラグ
				Hour = 0;					// リセット

				// 最大値の設定
				if (++Day > 999999999)
				{
					Day = 999999999;
				}
			}
		}
	}
	return;
}