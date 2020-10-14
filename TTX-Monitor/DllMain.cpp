// TTX-Monitor: Open-source Taito Type X loader by Romhack and Hipnosis.

#include "Global.h"

HANDLE hMutex;
HINSTANCE hInstance;

InputManager InputMgr;
ConfigManager ConfigMgr;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			hMutex = CreateMutex(0, 0, NULL);
			hInstance = GetModuleHandle(0);

			// Uncomment to use logging functions.
			// LogInitialize();

			// Initialize the configuration.
			ConfigMgr.Load();
			ConfigMgr.LoadTable();

			// Prepare the hooking function.
			HookItInit();
			// Start the WinAPI and DInput hooking.
			HookFunctions();

			break;
		}
		
		case DLL_THREAD_ATTACH: break;
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH: break;
	}

	return TRUE;
}