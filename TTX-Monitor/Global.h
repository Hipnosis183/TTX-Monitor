// TTX-Monitor: Open-source Taito Type X loader by Romhack and Hipnosis.

#pragma once
#include <dinput.h>
#include <iostream>
#include <list>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <thread>
#include <Windows.h>

#include "SetInput.h"
#include "SetOptions.h"

#define _WIN32_WINDOWS 0x0410
#define WIN32_LEAN_AND_MEAN
#define DIRECTINPUT_VERSION 0x800

typedef unsigned char UINT8;
extern DWORD iTable[M_END];
extern DWORD mTable[CONFIG_END];

extern HANDLE hMutex;
extern HINSTANCE hInstance;

extern InputManager InputMgr;
extern ConfigManager ConfigMgr;

int IsAddressed();
void ResetAddressed();
DWORD ProcessStream(UINT8 *stream, DWORD srcsize, BYTE *dst, DWORD dstsize);

// DirectInput
extern int DIMagicCall;

HRESULT APIENTRY Hook_DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter);
HRESULT APIENTRY Fake_DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter);

typedef HRESULT(APIENTRY* hDirectInput8Create)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter);
typedef HRESULT(APIENTRY* LPDirectInput8Create)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter);

extern hDirectInput8Create HDirectInput8Create;
extern LPDirectInput8Create FDirectInput8Create;

// Hooking engine.
VOID APIENTRY HookItInit();
BOOL APIENTRY HookFunctions();
LPVOID APIENTRY HookIt(LPCTSTR Module, LPCTSTR Name, LPVOID lpHookFunction);

// Logging engine.
void APIENTRY LogInitialize();
void APIENTRY LogMessage(const CHAR* TextMessage, ...);
void APIENTRY LogMessageW(const WCHAR* TextMessage, ...);