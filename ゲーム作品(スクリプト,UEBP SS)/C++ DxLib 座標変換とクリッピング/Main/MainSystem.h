#pragma once

class MainSystem
{
public:
	MainSystem() = default;
	~MainSystem() = default;

public:
	// ������
	bool Init();
	// �j��
	void End();
	// ����
	void Process();
	// ���[�v����
	bool Loop();

};