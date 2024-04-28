#pragma once

class MainSystem
{
public:
	MainSystem() = default;
	~MainSystem() = default;

public:
	// ‰Šú‰»
	bool Init();
	// ”jŠü
	void End();
	// ˆ—
	void Process();
	// ƒ‹[ƒvˆ—
	bool Loop();

};