#pragma once

class MainSystem
{
public:
	MainSystem() = default;
	~MainSystem() = default;

public:
	// 初期化
	bool Init();
	// 破棄
	void End();
	// 処理
	void Process();
	// ループ処理
	bool Loop();

};