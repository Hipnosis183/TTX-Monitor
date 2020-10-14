// TTX-Monitor: Open-source Taito Type X loader by Romhack and Hipnosis.

#include "Hook.h"
#include "Global.h"

static int isInitialized = 0;

BOOL APIENTRY HookFunctions()
{
	// File operation function hooks.
	HOOK("kernel32.dll", CreateDirectoryA, H, LP, Hook);
	HOOK("kernel32.dll", CreateDirectoryW, H, LP, Hook);
	HOOK("kernel32.dll", CreateFileA, H, LP, Hook);
	HOOK("kernel32.dll", CreateFileW, H, LP, Hook);
	HOOK("kernel32.dll", ReadFile, H, LP, Hook);
	HOOK("kernel32.dll", WriteFile, H, LP, Hook);

	// Communications devices function hooks.
	HOOK("kernel32.dll", ClearCommError, H, LP, Hook);
	HOOK("kernel32.dll", CloseHandle, H, LP, Hook);
	HOOK("kernel32.dll", EscapeCommFunction, H, LP, Hook);
	HOOK("kernel32.dll", GetCommModemStatus, H, LP, Hook);
	HOOK("kernel32.dll", GetCommState, H, LP, Hook);
	HOOK("kernel32.dll", GetCommTimeouts, H, LP, Hook);
	HOOK("kernel32.dll", SetCommMask, H, LP, Hook);
	HOOK("kernel32.dll", SetCommState, H, LP, Hook);
	HOOK("kernel32.dll", SetCommTimeouts, H, LP, Hook);
	HOOK("kernel32.dll", SetupComm, H, LP, Hook);

	// DirectInput hooks.
	if (mTable[CONFIG_MAHJONG])
	{
		// Hook for mahjong inputs.
		HOOK("DINPUT8.dll", DirectInput8Create, H, h, Hook);
	}

	else
	{
		// Hook for everything else.
		HOOK("DINPUT8.dll", DirectInput8Create, F, LP, Fake);
	}

	return TRUE;
}

BOOL APIENTRY Hook_ClearCommError(HANDLE hFile, LPDWORD lpErrors, LPCOMSTAT lpStat)
{
	if (hFile != hConnection)
	{
		return HClearCommError(hFile, lpErrors, lpStat);
	}

	if (lpStat)
	{
		lpStat->cbInQue = !ReplyBuffer.empty() ? ReplyBuffer.size() : 0;
	}

	return TRUE;
}

BOOL APIENTRY Hook_CloseHandle(HANDLE hObject)
{
	if (hObject != hConnection)
	{
		return HCloseHandle(hObject);
	}

	else
	{
		ResetAddressed();
	}

	return TRUE;
}

BOOL APIENTRY Hook_EscapeCommFunction(HANDLE hFile, DWORD dwFunc)
{
	if (hFile != hConnection)
	{
		return HEscapeCommFunction(hFile, dwFunc);
	}

	return TRUE;
}

BOOL APIENTRY Hook_GetCommModemStatus(HANDLE hFile, LPDWORD lpModemStat)
{
	if (hFile != hConnection)
	{
		return HGetCommModemStatus(hFile, lpModemStat);
	}

	*lpModemStat = IsAddressed() ? 0x10 : 0;

	return TRUE;
}

BOOL APIENTRY Hook_GetCommState(HANDLE hFile, LPDCB lpDCB)
{
	if (hFile != hConnection)
	{
		return HGetCommState(hFile, lpDCB);
	}

	return TRUE;
}

BOOL APIENTRY Hook_GetCommTimeouts(HANDLE hFile, LPCOMMTIMEOUTS lpCommTimeouts)
{
	if (hFile != hConnection)
	{
		return HGetCommTimeouts(hFile, lpCommTimeouts);
	}

	return TRUE;
}

BOOL APIENTRY Hook_SetCommMask(HANDLE hFile, DWORD dwEvtMask)
{
	if (hFile != hConnection)
	{
		return HSetCommMask(hFile, dwEvtMask);
	}

	return TRUE;
}

BOOL APIENTRY Hook_SetCommState(HANDLE hFile, LPDCB lpDCB)
{
	if (hFile != hConnection)
	{
		return HSetCommState(hFile, lpDCB);
	}

	return TRUE;
}

BOOL APIENTRY Hook_SetCommTimeouts(HANDLE hFile, LPCOMMTIMEOUTS lpCommTimeouts)
{
	if (hFile != hConnection)
	{
		return HSetCommTimeouts(hFile, lpCommTimeouts);
	}

	return TRUE;
}

BOOL APIENTRY Hook_SetupComm(HANDLE hFile, DWORD dwInQueue, DWORD dwOutQueue)
{
	if (hFile != hConnection)
	{
		return HSetupComm(hFile, dwInQueue, dwOutQueue);
	}

	return TRUE;
}

using namespace std::literals;

// Beautiful recursion. Necessary for games which create subfolders for savedata.
void CreateFolderA(CHAR* SaveFolder, CHAR* SaveSubFolderC)
{
	if (strcmp(SaveFolder, SaveSubFolderC) != 0)
	{
		CHAR SaveSubFolder[MAX_PATH];
		strcpy(SaveSubFolder, SaveSubFolderC);
		strrchr(SaveSubFolderC, '\\')[0] = '\0';

		CreateFolderA(SaveFolder, SaveSubFolderC);

		HCreateDirectoryA(SaveSubFolder, nullptr);
	}

	else
	{
		HCreateDirectoryA(SaveFolder, nullptr);
	}
}

void CreateFolderW(WCHAR* SaveFolder, WCHAR* SaveSubFolderC)
{
	if (wcscmp(SaveFolder, SaveSubFolderC) != 0)
	{
		WCHAR SaveSubFolder[MAX_PATH];
		wcscpy(SaveSubFolder, SaveSubFolderC);
		wcsrchr(SaveSubFolderC, '\\')[0] = '\0';

		CreateFolderW(SaveFolder, SaveSubFolderC);

		HCreateDirectoryW(SaveSubFolder, nullptr);
	}

	else
	{
		HCreateDirectoryW(SaveFolder, nullptr);
	}
}

BOOL APIENTRY Hook_CreateDirectoryA(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	if (mTable[CONFIG_SAVEPATCH])
	{
		// Assuming that no Type X game store data in the C: drive. Excludes relative paths.
		if ((lpPathName[0] != 'C' && lpPathName[0] != 'c') && lpPathName[1] == ':')
		{
			CHAR RootPath[MAX_PATH];
			GetModuleFileNameA(GetModuleHandleA(nullptr), RootPath, _countof(RootPath));
			strrchr(RootPath, '\\')[0] = '\0';

			std::string SavePath = RootPath + "\\sv\\"s;

			return HCreateDirectoryA(SavePath.c_str(), nullptr);
		}
	}

	return HCreateDirectoryA(lpPathName, lpSecurityAttributes);
}

BOOL APIENTRY Hook_CreateDirectoryW(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	if (mTable[CONFIG_SAVEPATCH])
	{
		// Assuming that no Type X game store data in the C: drive. Excludes relative paths.
		if ((lpPathName[0] != L'C' && lpPathName[0] != L'c') && lpPathName[1] == L':')
		{
			WCHAR RootPath[MAX_PATH];
			GetModuleFileNameW(GetModuleHandle(nullptr), RootPath, _countof(RootPath));
			wcsrchr(RootPath, L'\\')[0] = L'\0';

			std::wstring SavePath = RootPath + L"\\sv\\"s;

			return HCreateDirectoryW(SavePath.c_str(), nullptr);
		}
	}

	return HCreateDirectoryW(lpPathName, lpSecurityAttributes);
}

// Some games like The King Of Fighters '98, Gouketsuji Ichizoku Senzo Kuyou and
// Trouble Witches will store data but won't read it. In the case of the latter,
// it may be solved by force-disabling the save directory read-only attribute,
// the rest need a save patch. This might be fixable, but I'm done with this.
HANDLE APIENTRY Hook_CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	if (!strcmp(lpFileName, "COM2"))
	{
		if (!isInitialized)
		{
			InputMgr.Init();
			isInitialized = 1;
		}

		return hConnection;
	}

	if (mTable[CONFIG_SAVEPATCH])
	{
		// Assuming that no Type X game store data in the C: drive. Excludes relative paths.
		if ((lpFileName[0] != 'C' && lpFileName[0] != 'c') && lpFileName[1] == ':')
		{
			// Get game working directory.
			CHAR RootPath[MAX_PATH];
			GetModuleFileNameA(GetModuleHandleA(nullptr), RootPath, _countof(RootPath));

			// Strip executable filename from path.
			strrchr(RootPath, '\\')[0] = '\0';

			std::string FilePath = lpFileName;
			// Forced to 3 to skip both slashes and backslashes.
			std::string FileName = FilePath.substr(3);

			// Get working directory lenght.
			int PathLenght = 0;

			for (int i = 0; i < MAX_PATH; i++)
			{
				if (RootPath[i] == '\0')
				{
					PathLenght = i;
					break;
				}
			}

			// Exclude directory files. Avoids screwing up normal file operations.
			if (strncmp(lpFileName, RootPath, PathLenght) != 0)
			{
				std::string SavePath = RootPath + "\\sv\\"s;
				std::string SaveFile = SavePath + FileName;

				std::string SaveSubFolderS = SaveFile.substr(0, SaveFile.length() - (FileName.length() - FileName.rfind('\\')));

				CHAR SaveFolder[MAX_PATH];
				strcpy(SaveFolder, (SavePath.substr(0, SavePath.length() - 1)).c_str());

				CHAR SaveSubFolderC[MAX_PATH];
				strcpy(SaveSubFolderC, SaveSubFolderS.c_str());

				CreateFolderA(SaveFolder, SaveSubFolderC);

				return HCreateFileA(SaveFile.c_str(), dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
			}
		}
	}

	return HCreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HANDLE APIENTRY Hook_CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	if (!wcscmp(lpFileName, L"COM2"))
	{
		if (!isInitialized)
		{
			InputMgr.Init();
			isInitialized = 1;
		}

		return hConnection;
	}

	if (mTable[CONFIG_SAVEPATCH])
	{
		// Assuming that no Type X game store data in the C: drive. Excludes relative paths.
		if ((lpFileName[0] != L'C' && lpFileName[0] != L'c') && lpFileName[1] == L':')
		{
			// Get game working directory.
			WCHAR RootPath[MAX_PATH];
			GetModuleFileNameW(GetModuleHandle(nullptr), RootPath, _countof(RootPath));

			// Strip executable filename from path.
			wcsrchr(RootPath, L'\\')[0] = L'\0';

			std::wstring FilePath = lpFileName;
			// Forced to 3 to skip both slashes and backslashes.
			std::wstring FileName = FilePath.substr(3);

			// Get working directory lenght.
			int PathLenght = 0;

			for (int i = 0; i < MAX_PATH; i++)
			{
				if (RootPath[i] == L'\0')
				{
					PathLenght = i;
					break;
				}
			}

			// Exclude directory files. Avoids screwing up normal file operations.
			if (wcsncmp(lpFileName, RootPath, PathLenght) != 0)
			{
				std::wstring SavePath = RootPath + L"\\sv\\"s;
				std::wstring SaveFile = SavePath + FileName;

				std::wstring SaveSubFolderS = SaveFile.substr(0, SaveFile.length() - (FileName.length() - FileName.rfind('\\')));

				WCHAR SaveFolder[MAX_PATH];
				wcscpy(SaveFolder, (SavePath.substr(0, SavePath.length() - 1)).c_str());

				WCHAR SaveSubFolderC[MAX_PATH];
				wcscpy(SaveSubFolderC, SaveSubFolderS.c_str());

				CreateFolderW(SaveFolder, SaveSubFolderC);

				return HCreateFileW(SaveFile.c_str(), dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
			}
		}
	}

	return HCreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

BOOL APIENTRY Hook_ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)
{
	if (hFile != hConnection)
	{
		return HReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
	}

	if (ReplyBuffer.size())
	{
		if (nNumberOfBytesToRead >= ReplyBuffer.size())
		{
			nNumberOfBytesToRead = ReplyBuffer.size();
		}

		*lpNumberOfBytesRead = nNumberOfBytesToRead;
		BYTE* pBuffer = (BYTE*)lpBuffer;

		for (DWORD i = 0; i < nNumberOfBytesToRead; i++)
		{
			if (!ReplyBuffer.empty())
			{
				*pBuffer++ = ReplyBuffer.front();
				ReplyBuffer.pop();
			}

			else
			{
				*pBuffer++ = 0;
			}
		}
	}

	else
	{
		*lpNumberOfBytesRead = 0;
	}

	return TRUE;
}

BOOL APIENTRY Hook_WriteFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
	if (hFile != hConnection)
	{
		return HWriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
	}

	BYTE* pBuffer = (BYTE*)lpBuffer;
	*lpNumberOfBytesWritten = nNumberOfBytesToWrite;

	static BYTE rBuffer[1024];
	DWORD Stream = ProcessStream((LPBYTE)lpBuffer, nNumberOfBytesToWrite, rBuffer, 1024);

	if (Stream != 1)
	{
		for (DWORD i = 0; i < Stream; i++)
		{
			ReplyBuffer.push(rBuffer[i]);
		}
	}

	return TRUE;
}