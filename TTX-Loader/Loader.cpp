// TTX-Monitor: Open-source Taito Type X loader by Romhack and Hipnosis.

#include <iostream>
#include <stdio.h>
#include <string>
#include <tchar.h>
#include <Windows.h>

class LProcess
{
	STARTUPINFO sInfo;
	PROCESS_INFORMATION pInfo;

	BOOL isLoaded;
	HANDLE hDll;

	void Error();

public:
	LProcess(const TCHAR* Name);
	~LProcess();

	DWORD Resume();
	DWORD Write(void* Buffer, void* Dest, int Lenght);
	DWORD Read(void* Buffer, void* Source, int Lenght);
	BOOL InjectDLL(const TCHAR* Name);
};

void LProcess::Error()
{
	MessageBox(0, _TEXT("An error has occurred."), _TEXT("Error"), MB_OK);

	exit(1);
}

LProcess::LProcess(const TCHAR* Name) : isLoaded(FALSE)
{
	ZeroMemory(&sInfo, sizeof(sInfo));
	sInfo.cb = sizeof(sInfo);

	isLoaded = CreateProcess(Name, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &sInfo, &pInfo);

	if (!isLoaded)
	{
		Error();
	}

	isLoaded = TRUE;
}

LProcess::~LProcess()
{
}

DWORD LProcess::Write(void* Buffer, void* Dest, int Lenght)
{
	WriteProcessMemory(pInfo.hProcess, Dest, Buffer, Lenght, 0);

	return 0;
}

DWORD LProcess::Read(void* Buffer, void* Source, int Lenght)
{
	ReadProcessMemory(pInfo.hProcess, Source, Buffer, Lenght, 0);

	return 0;
}

DWORD LProcess::Resume()
{
	return ResumeThread(pInfo.hThread);
}

// The process is loaded suspended, then use VirtualAllocEx to allocate memory to the indicated library
// and then write with WriteProcessMemory. After this, the thread which will do the injection is created.
BOOL LProcess::InjectDLL(const TCHAR* Name)
{
	LPVOID lProc;
	LPVOID pBase;
	DWORD ThreadId;

	lProc = (LPVOID)GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "LoadLibraryA");

	if (!lProc)
	{
		Error();
	}

	pBase = VirtualAllocEx(pInfo.hProcess, NULL, _tcslen(Name), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	if (!pBase)
	{
		Error();
	}

	Write((void*)Name, pBase, _tcslen(Name));

	hDll = CreateRemoteThread(pInfo.hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)lProc, pBase, 0, &ThreadId);

	if (!hDll)
	{
		Error();
	}

	WaitForSingleObject(hDll, INFINITE);

	return TRUE;
}

int _tmain(int argc, _TCHAR* argv[])
{
	LProcess* Process = new LProcess(argc < 2 ? _TEXT("game.exe") : argv[1]);

	Process->InjectDLL(_T("TTX-Monitor.dll"));
	Process->Resume();

	return 0;
}