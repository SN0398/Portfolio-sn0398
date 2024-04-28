#include "LogManager.h"
#include "DxLib.h"
#include "ResourceManager.h"

void LogManager::Update()
{
	for (auto& obj : ActiveLog)
	{
		if (obj->Count < POPUPMAXCOUNT)
		{
			//obj->offsetX = -300 + (300.0 / A) * counter;
			obj->offsetX = POPUPDEFAULTOFFSETX + (MAXOFFSETX / POPUPMAXCOUNT) * obj->Count;
		}
		else if (obj->Count < LOG_MAXCOUNT)
		{
			obj->offsetX = 0;
		}
		else if (obj->Count < DISAPPEARMAXCOUNT)
		{
			//xOffset = 0 + (-300.0 / (C - B)) * (counter - B);
			obj->offsetX = 0 + (POPUPDEFAULTOFFSETX / (DISAPPEARMAXCOUNT - LOG_MAXCOUNT)) * (obj->Count - LOG_MAXCOUNT);
		}

		if (++obj->Count > DISAPPEARMAXCOUNT)
		{
			auto& eraseObj = obj;
			for (auto itr = ActiveLog.begin(); itr != ActiveLog.end(); )
			{
				if (*itr == obj)
				{
					itr = ActiveLog.erase(itr);
					return;
				}
			}
		}
	}

	return;
}

void LogManager::Draw()
{
	auto& resource = Resource::GetInstance();
	int y = 200;
	int XL, XR;
	int count = 0;
	for (auto itr = ActiveLog.rbegin(); itr != ActiveLog.rend() && count < 5; ++itr, ++count)
	{
		XL = LOG_DEFAULT_X_LEFT + itr->get()->offsetX;
		XR = LOG_DEFAULT_X_RIGHT + +itr->get()->offsetX;

		DrawExtendGraph(XL, y, XR, y + 60, resource.BuildingInfo, FALSE);
		// �������낦�ŕ�����`��
		// �{�b�N�X���[�ƉE�[�̒l
		int middle = (XL + XR) / 2;
		// �����̕�
		int width = GetDrawStringWidthToHandle(itr->get()->DisplayText.c_str(), 
			strlen(itr->get()->DisplayText.c_str()), resource.Font[Font_ID::Yumincho]);
		// �`��
		DrawFormatStringToHandle
		(
			middle - width / 2,
			y + 20,
			resource.Color[Color_ID::Black],
			resource.Font[Font_ID::Yumincho],
			itr->get()->DisplayText.c_str()
		);
		y += 65;
	}

	return;
}