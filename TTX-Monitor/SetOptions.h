// TTX-Monitor: Open-source Taito Type X loader by Romhack and Hipnosis.

#pragma once
#include <iostream>
#include <Windows.h>

#define MONITOR_MISC_FILENAME	"monitor_misc.bin"

typedef enum
{
	CONFIG_POVASAXIS,
	CONFIG_SAVEPATCH,
	CONFIG_MAHJONG,
	CONFIG_MULTITHREAD,
	CONFIG_END,
} CONFIG;

class ConfigManager
{
	DWORD MiscTable[CONFIG_END];

public:
	ConfigManager();
	~ConfigManager();

	void Load();
	void LoadTable();
};