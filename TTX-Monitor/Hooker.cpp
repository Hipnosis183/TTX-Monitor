// TTX-Monitor: Open-source Taito Type X loader by Romhack and Hipnosis.

#include <Windows.h>

#include "udis86/udis86.h"

static LPBYTE HookAddrBase = NULL;
static LPBYTE HookAddr = NULL;
static LPBYTE DasmAddr = NULL;

static ud_t ud_obj;

static int DasmInputHookEIP(ud_t* u)
{
	int Value = (int)*DasmAddr;
	++DasmAddr;

	return Value;
}

DWORD DasmOp(LPVOID Address)
{
	ud_init(&ud_obj);
	ud_set_mode(&ud_obj, 32);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);
	ud_set_input_hook(&ud_obj, DasmInputHookEIP);

	DasmAddr = (LPBYTE)Address;

	return (DWORD)ud_disassemble(&ud_obj);
}

VOID APIENTRY HookItInit()
{
	HookAddrBase = HookAddr = (LPBYTE)VirtualAlloc(NULL, 4096, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
}

LPVOID APIENTRY HookIt(LPCTSTR Module, LPCTSTR Name, LPVOID lpHookFunction)
{
	BYTE ogBytes[32], RestoreSize = 0;
	LPVOID ApiAddr = (LPVOID)GetProcAddress(GetModuleHandle(Module), Name);

	if (!ApiAddr)
	{
		return NULL;
	}

	LPBYTE Address = (LPBYTE)ApiAddr;

	while (RestoreSize < 6)
	{
		DWORD OpSize = DasmOp(Address);
		RestoreSize += OpSize;
		Address += OpSize;
	}

	memcpy(ogBytes, ApiAddr, RestoreSize);

	DWORD OldProtect = 0, NewProtect = 0;
	VirtualProtect(ApiAddr, RestoreSize, PAGE_EXECUTE_READWRITE, &OldProtect);

	LPBYTE TempAddr = (LPBYTE)ApiAddr;

	// JMP Disp32
	*TempAddr = 0xE9;
	++TempAddr;
	*((DWORD*)TempAddr) = ((signed int)(DWORD)(lpHookFunction)) - ((signed int)((DWORD)TempAddr + 4));

	LPBYTE ogAddrCall = HookAddr;
	memcpy(HookAddr, ogBytes, RestoreSize);
	HookAddr += RestoreSize;
	TempAddr = HookAddr;

	// JMP Disp32
	*TempAddr = 0xE9;
	++TempAddr;
	*((DWORD*)TempAddr) = ((signed int)((DWORD)ApiAddr) + RestoreSize) - ((signed int)((DWORD)TempAddr + 4));
	HookAddr += 5;

	return ogAddrCall;
}