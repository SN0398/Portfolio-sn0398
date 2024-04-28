#pragma once

class MainSystem
{
public:

	MainSystem() = default;
	~MainSystem() = default;

public:

	bool Init();
	void End();
	void Process();
	bool Loop();

};