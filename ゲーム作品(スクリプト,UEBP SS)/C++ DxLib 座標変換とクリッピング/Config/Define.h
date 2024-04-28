#pragma once

// 定数クラス群
namespace Define
{
    // ChangeSceneCallType
    enum class CS_CallType
    {
        PopTop,     // 先頭を消す
        PopAll,     // 全て消してから戦闘に追加する
        Push,       // 先頭に追加するだけ
    };
}

// 解像度
#define SCREEN_WIDTH		1920	// スクリーン横の大きさ
#define SCREEN_HEIGHT		1080		// スクリーン縦の大きさ

// ウィンドウの大きさ
#define WINDOW_WIDTH		960		// ウィンドウの長さ
#define WINDOW_HEIGHT		540		// ウィンドウの高さ