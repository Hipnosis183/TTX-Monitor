// TTX-Monitor: Open-source Taito Type X loader by Romhack and Hipnosis.

#include "Global.h"

FILE *FileLog = NULL;
static HANDLE hLogMutex = 0;

void APIENTRY LogInitialize()
{
	FILE *Stream;
	Stream = fopen("monitor_log.txt", "w");

	if (!Stream)
	{
		return;
	}
	
	hLogMutex = CreateMutex(0, 0, NULL);
	FileLog = Stream;
}

void APIENTRY LogMessage(const CHAR *TextMessage, ...)
{
	if (FileLog)
	{
		WaitForSingleObject(hLogMutex, INFINITE);
		FILE *Stream = FileLog;

		va_list va;
		va_start(va, TextMessage);
		vfprintf(Stream, TextMessage, va);
		fflush(Stream);
		va_end(va);
		
		ReleaseMutex(hLogMutex);
	}
}

void APIENTRY LogMessageW(const WCHAR* TextMessage, ...)
{
	if (FileLog)
	{
		WaitForSingleObject(hLogMutex, INFINITE);
		FILE* Stream = FileLog;

		va_list va;
		va_start(va, TextMessage);
		vfwprintf(Stream, TextMessage, va);
		fflush(Stream);
		va_end(va);

		ReleaseMutex(hLogMutex);
	}
}