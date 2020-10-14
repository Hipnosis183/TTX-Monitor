// TTX-Monitor: Open-source Taito Type X loader by Romhack and Hipnosis.

#include "Global.h"

DWORD mTable[CONFIG_END];

ConfigManager::ConfigManager()
{
	for (int i = 0; i < CONFIG_END; i++)
	{
		MiscTable[i] = 0;
		mTable[i] = 0;
	}		
}

ConfigManager::~ConfigManager()
{
}

void ConfigManager::Load()
{
	FILE *Stream = fopen(MONITOR_MISC_FILENAME, "r");

	if (Stream)
	{
		fread(MiscTable, 4, CONFIG_END, Stream);
		fclose(Stream);
	}
}

void ConfigManager::LoadTable()
{
	FILE *Stream = fopen(MONITOR_MISC_FILENAME, "r");

	if (Stream)
	{
		fread(mTable, 4, CONFIG_END, Stream);
		fclose(Stream);
	}
}