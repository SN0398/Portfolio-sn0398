#pragma once
#include "MyLib.h"

int Game_MainLoop(int LeaveKeyCode = KEY_INPUT_ESCAPE);		// ゲームループに必要な関数のラッパー

int LeaveProcess(int LeaveKeyCode);		// 終了に移る値を受け取る