#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <DxLib.h>

// https://kage3.cocolog-nifty.com/blog/2014/03/post-c1b7.html

#ifdef _DEBUG

//*******************************************************
// デバッグ用のコンソールの初期処理(メインループ前に呼ぶ)
//*******************************************************
void initDebugConsole() 
{
    //デバッグ用にコンソールを呼び出す
    AllocConsole();
    // 標準入出力に割り当てる
    FILE* fp = NULL;
    // 昔のコード
    //freopen("CONOUT$", "w", stdout);
    //freopen("CONIN$", "r", stdin);
    // 現在のコード
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONIN$", "r", stdin);
    // デバッグコンソールがアクティブウィンドウになるので
    // ゲーム本体のウィンドウをアクティブにする
    SetForegroundWindow(GetMainWindowHandle());
    return;
}
//*******************************************************
// デバッグ用のコンソールのクリア処理
//*******************************************************
void clearDebugConsole() 
{
    system("cls");
    return;
}
//*******************************************************
// デバッグ用のコンソールの終了処理(メインループ後に呼ぶ)
//*******************************************************
void endDebugConsole()
{
    //コンソール解放
    FreeConsole();
    return;
}

#endif // _DEBUG
