#pragma once

namespace MyLib
{
	// フレームレート関係:https://dixq.net/g/03_14.html
	bool FPSUpdate();
	void DrawFPSRate(int x, int y, unsigned int _font_color = 0xffffff);
	void FPSWait();
}