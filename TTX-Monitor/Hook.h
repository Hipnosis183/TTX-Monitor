// TTX-Monitor: Open-source Taito Type X loader by Romhack and Hipnosis.

#pragma once
#include <queue>
#include <Windows.h>

#define HOOK(Module, Name, Def, HookDef, HookName) Def ##Name = (HookDef ##Name) HookIt(Module, #Name, (LPVOID) HookName## _ ##Name)

// File operation functions.
typedef BOOL(APIENTRY* LPCreateDirectoryA)(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
typedef BOOL(APIENTRY* LPCreateDirectoryW)(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
typedef HANDLE(APIENTRY* LPCreateFileA)(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
typedef HANDLE(APIENTRY* LPCreateFileW)(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
typedef BOOL(APIENTRY* LPReadFile)(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
typedef BOOL(APIENTRY* LPWriteFile)(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);

// Communications devices functions.
typedef BOOL(APIENTRY* LPClearCommError)(HANDLE hFile, LPDWORD lpErrors, LPCOMSTAT lpStat);
typedef BOOL(APIENTRY* LPCloseHandle)(HANDLE hObject);
typedef BOOL(APIENTRY* LPEscapeCommFunction)(HANDLE hFile, DWORD dwFunc);
typedef BOOL(APIENTRY* LPGetCommModemStatus)(HANDLE hFile, LPDWORD lpModemStat);
typedef BOOL(APIENTRY* LPGetCommState)(HANDLE hFile, LPDCB lpDCB);
typedef BOOL(APIENTRY* LPGetCommTimeouts)(HANDLE hFile, LPCOMMTIMEOUTS lpCommTimeouts);
typedef BOOL(APIENTRY* LPSetCommMask)(HANDLE hFile, DWORD dwEvtMask);
typedef BOOL(APIENTRY* LPSetCommState)(HANDLE hFile, LPDCB lpDCB);
typedef BOOL(APIENTRY* LPSetCommTimeouts)(HANDLE hFile, LPCOMMTIMEOUTS lpCommTimeouts);
typedef BOOL(APIENTRY* LPSetupComm)(HANDLE hFile, DWORD dwInQueue, DWORD dwOutQueue);

// File operation function hooks.
BOOL APIENTRY Hook_CreateDirectoryA(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
BOOL APIENTRY Hook_CreateDirectoryW(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
HANDLE APIENTRY Hook_CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
HANDLE APIENTRY Hook_CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
BOOL APIENTRY Hook_ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
BOOL APIENTRY Hook_WriteFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);

// Communications devices function hooks.
BOOL APIENTRY Hook_ClearCommError(HANDLE hFile, LPDWORD lpErrors, LPCOMSTAT lpStat);
BOOL APIENTRY Hook_CloseHandle(HANDLE hObject);
BOOL APIENTRY Hook_EscapeCommFunction(HANDLE hFile, DWORD dwFunc);
BOOL APIENTRY Hook_GetCommModemStatus(HANDLE hFile, LPDWORD lpModemStat);
BOOL APIENTRY Hook_GetCommState(HANDLE hFile, LPDCB lpDCB);
BOOL APIENTRY Hook_GetCommTimeouts(HANDLE hFile, LPCOMMTIMEOUTS lpCommTimeouts);
BOOL APIENTRY Hook_SetCommMask(HANDLE hFile, DWORD dwEvtMask);
BOOL APIENTRY Hook_SetCommState(HANDLE hFile, LPDCB lpDCB);
BOOL APIENTRY Hook_SetCommTimeouts(HANDLE hFile, LPCOMMTIMEOUTS lpCommTimeouts);
BOOL APIENTRY Hook_SetupComm(HANDLE hFile, DWORD dwInQueue, DWORD dwOutQueue);

// Variables and constants definition.
std::queue<BYTE> ReplyBuffer;

static const HANDLE hConnection = (HANDLE)0xCAFEBEEF;

static LPCreateDirectoryA  HCreateDirectoryA = NULL;
static LPCreateDirectoryW  HCreateDirectoryW = NULL;
static LPCreateFileA  HCreateFileA = NULL;
static LPCreateFileW  HCreateFileW = NULL;
static LPReadFile HReadFile = NULL;
static LPWriteFile HWriteFile = NULL;

static LPClearCommError HClearCommError = NULL;
static LPCloseHandle HCloseHandle = NULL;
static LPEscapeCommFunction HEscapeCommFunction = NULL;
static LPGetCommModemStatus HGetCommModemStatus = NULL;
static LPGetCommState  HGetCommState = NULL;
static LPGetCommTimeouts  HGetCommTimeouts = NULL;
static LPSetCommMask  HSetCommMask = NULL;
static LPSetCommState  HSetCommState = NULL;
static LPSetCommTimeouts  HSetCommTimeouts = NULL;
static LPSetupComm  HSetupComm = NULL;