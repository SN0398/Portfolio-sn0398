#pragma once

// 定数定義 ---------------------------------------------------------------------------------------

// ウィンドウ
#define SCREEN_WIDTH		1280	// スクリーン横の大きさ
#define SCREEN_HEIGHT		800		// スクリーン縦の大きさ

// ゲームシーン
typedef enum _SceneState
{
	GS_TITLE = 0,	// タイトル
	GS_GAME,		// ゲーム
	GS_LEAVE,		// 終了

}SceneState;
