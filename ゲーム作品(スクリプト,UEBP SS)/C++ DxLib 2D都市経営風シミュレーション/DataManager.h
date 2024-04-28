#pragma once
#include "Singleton.h"

class DataManager : public Singleton<DataManager>
{
public:
	DataManager() = default;
	~DataManager() = default;

public:
	int Load();

};