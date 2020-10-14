// DirectInputHook by Sparten, evilbert and mcMike.
// Fake DirectInput by Romhack.
// Hybrid DirectInput hook by Hipnosis.

#include "IDInDev.h"
#include "IDInDevFake.h"
#include "Global.h"

#define WIN32_LEAN_AND_MEAN
#define DIRECTINPUT_VERSION 0x0800

hkIDirectInput8 hkDInput8;	
IDirectInput8 *g_pDInInt8 = NULL;
hkIDirectInput8 *phkDInput8 = NULL;				
IDirectInputDevice8 *g_pDInDev8 = NULL;			
hkIDirectInputDevice8 *phkDInputDevice8 = NULL;	
LPVOID *Value;

hDirectInput8Create HDirectInput8Create;
LPDirectInput8Create FDirectInput8Create;

HRESULT APIENTRY Hook_DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter)
{
	if (DIMagicCall)
	{
		return HDirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
	}

	else
	{
		HRESULT Result = HDirectInput8Create(hinst, dwVersion, riidltf, (LPVOID*)&g_pDInInt8, punkOuter);

		phkDInput8 = &hkDInput8;
		*ppvOut = phkDInput8;
		Value = ppvOut;

		return Result;
	}	
}

// Prevents the games of having access to input devices.
HRESULT APIENTRY Fake_DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter)
{
	if (DIMagicCall)
	{
		return FDirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
	}

	else
	{
		*ppvOut = (LPVOID)pFakeInterface;
		punkOuter = NULL;

		return DI_OK;
	}
}