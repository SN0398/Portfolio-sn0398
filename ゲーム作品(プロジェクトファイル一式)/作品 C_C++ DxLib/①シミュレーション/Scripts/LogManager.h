#pragma once
#include <queue>
#include <vector>
#include <list>
#include <memory>
#include <string>
#include "Singleton.h"

#define LOG_DEFAULT_X_LEFT				0.0
#define LOG_DEFAULT_X_RIGHT				500.0

#define DEFAULT_OFFSETXLEFT				-300
#define DEFAULT_OFFSETYRIGHT			300
#define OFFSETY_SCROLLSPEED				300

#define POPUPMAXCOUNT					30
#define LOG_MAXCOUNT					150
#define DISAPPEARMAXCOUNT				200
#define MAXOFFSETX						(LOG_DEFAULT_X_LEFT + LOG_DEFAULT_X_RIGHT)
#define POPUPDEFAULTOFFSETX				-MAXOFFSETX

class LogManager : public Singleton<LogManager>
{
public:
	struct LogData
	{
		std::string DisplayText;
		int offsetX, offsetY;
		int Count;
		LogData(const char* DisplayText) :
			DisplayText(DisplayText), offsetX(POPUPDEFAULTOFFSETX), offsetY(0),Count(0) {}
	};

public:
	LogManager() = default;
	~LogManager() = default;

	void Update();
	void Draw();
	void Claim(const char* DisplayText)
	{
		ActiveLog.push_back(std::make_unique<LogData>(DisplayText));
	}

private:
	std::list<std::unique_ptr<LogData>> ActiveLog;
	//std::vector<std::unique_ptr<LogData>> ArchiveLog;
};