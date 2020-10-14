// Fake DirectInput by Romhack.

#include "IDInDevFake.h"

#define COM_NO_WINDOWS_H

HookIDirectInputDevice FakeDevice, * pFakeDevice = &FakeDevice;
HookIDirectInput8 FakeInterface, * pFakeInterface = &FakeInterface;

HRESULT HookIDirectInputDevice::QueryInterface(LPVOID _this, REFIID riid, LPVOID *ppvObj)
{
	*ppvObj = NULL;

	return 0;
}

ULONG HookIDirectInputDevice::AddRef(LPVOID _this)
{
	return 2;
}

ULONG HookIDirectInputDevice::Release(LPVOID _this)
{
	return 0;
}

HRESULT HookIDirectInputDevice::GetCapabilities(LPVOID _this, LPDIDEVCAPS lpDIDevCaps)
{
	return DI_OK;
}

HRESULT HookIDirectInputDevice::EnumObjects(LPVOID _this, LPDIENUMDEVICEOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return DI_OK;
}

HRESULT HookIDirectInputDevice::GetProperty(LPVOID _this, REFGUID rguidProp, LPDIPROPHEADER pdiph)
{
	return DI_OK;
}

HRESULT HookIDirectInputDevice::SetProperty(LPVOID _this, REFGUID rguidProp, LPCDIPROPHEADER pdiph)
{
	return DI_OK;
}

HRESULT HookIDirectInputDevice::Acquire(LPVOID _this)
{
	return DI_OK;
}

HRESULT HookIDirectInputDevice::Unacquire(LPVOID _this)
{
	return DI_OK;
}

HRESULT HookIDirectInputDevice::GetDeviceState(LPVOID _this, DWORD cbData, LPVOID lpvData)
{
	if (lpvData)
	{
		ZeroMemory(lpvData, cbData);
	}

	return DI_OK;
}

HRESULT HookIDirectInputDevice::GetDeviceData(LPVOID _this, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags)
{
	// Necessary function for Chaos Breaker.
	if (rgdod)
	{
		ZeroMemory(rgdod, cbObjectData * (*pdwInOut));
	}

	return DI_OK;
}

HRESULT HookIDirectInputDevice::SetDataFormat(LPVOID _this, LPCDIDATAFORMAT lpdf)
{
	return DI_OK;
}

HRESULT HookIDirectInputDevice::SetEventNotification(LPVOID _this, HANDLE hEvent)
{
	return DI_OK;
}

HRESULT HookIDirectInputDevice::SetCooperativeLevel(LPVOID _this, HWND hwnd, DWORD dwFlags)
{
	return DI_OK;
}

HRESULT HookIDirectInputDevice::GetObjectInfo(LPVOID _this, LPDIDEVICEOBJECTINSTANCE pdidoi, DWORD dwObj, DWORD dwHow)
{
	return DI_OK;
}

HRESULT HookIDirectInputDevice::GetDeviceInfo(LPVOID _this, LPDIDEVICEINSTANCE pdidi)
{
	return DI_OK;
}

HRESULT HookIDirectInputDevice::RunControlPanel(LPVOID _this, HWND hwndOwner, DWORD dwFlags)
{
	return DI_OK;
}

HRESULT HookIDirectInputDevice::Initialize(LPVOID _this, HINSTANCE hinst, DWORD dwVersion, REFGUID rguid)
{
	return DI_OK;
}

HRESULT HookIDirectInputDevice::CreateEffect(LPVOID _this, REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT * ppdeff, LPUNKNOWN punkOuter)
{
	return DIERR_UNSUPPORTED;
}

HRESULT HookIDirectInputDevice::EnumEffects(LPVOID _this, LPDIENUMEFFECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwEffType)
{
	return DIERR_UNSUPPORTED;
}

HRESULT HookIDirectInputDevice::GetEffectInfo(LPVOID _this, LPDIEFFECTINFOA pdei, REFGUID rguid)
{
	return DIERR_UNSUPPORTED;
}

HRESULT HookIDirectInputDevice::GetForceFeedbackState(LPVOID _this, LPDWORD pdwOut)
{
	return DIERR_UNSUPPORTED;
}

HRESULT HookIDirectInputDevice::SendForceFeedbackCommand(LPVOID _this, DWORD dwFlags)
{
	return DIERR_UNSUPPORTED;
}

HRESULT HookIDirectInputDevice::EnumCreatedEffectObjects(LPVOID _this, LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl)
{
	return DIERR_UNSUPPORTED;
}

HRESULT HookIDirectInputDevice::Escape(LPVOID _this, LPDIEFFESCAPE pesc)
{
	return DIERR_UNSUPPORTED;
}

HRESULT HookIDirectInputDevice::Poll(LPVOID _this)
{
	return DI_NOEFFECT;
}

HRESULT HookIDirectInputDevice::SendDeviceData(LPVOID _this, DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl)
{
	return DIERR_UNSUPPORTED;
}

HRESULT HookIDirectInputDevice::EnumEffectsInFile(LPVOID _this, LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags)
{
	return DIERR_UNSUPPORTED;
}

HRESULT HookIDirectInputDevice::WriteEffectToFile(LPVOID _this, LPCSTR lpszFileName, DWORD dwEntries, LPCDIFILEEFFECT rgDiFileEft, DWORD dwFlags)
{
	return DIERR_UNSUPPORTED;
}

HRESULT HookIDirectInputDevice::BuildActionMap(LPVOID _this, LPDIACTIONFORMAT lpdiaf, LPCTSTR lpszUserName, DWORD dwFlags)
{
	return DIERR_UNSUPPORTED;
}

HRESULT HookIDirectInputDevice::SetActionMap(LPVOID _this, LPCDIACTIONFORMAT lpdiActionFormat, LPCTSTR lptszUserName, DWORD dwFlags)
{ 
	return DIERR_UNSUPPORTED;
}

HRESULT HookIDirectInputDevice::GetImageInfo(LPVOID _this, LPDIDEVICEIMAGEINFOHEADER lpdiDevImageInfoHeader)
{
	return DIERR_UNSUPPORTED;
}

HRESULT HookIDirectInput8::QueryInterface(LPVOID _this, REFIID riid, LPVOID *ppvObj)
{
	*ppvObj = NULL;
	return DIERR_UNSUPPORTED;
}

ULONG HookIDirectInput8::AddRef(LPVOID _this)
{
	return 0;
}

ULONG HookIDirectInput8::Release(LPVOID _this)
{
	return 0;
}

HRESULT HookIDirectInput8::CreateDevice(LPVOID _this, REFGUID rguid, LPDIRECTINPUTDEVICE8A * lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
{
	*lplpDirectInputDevice = (LPDIRECTINPUTDEVICE8A) pFakeDevice;
	
	if (pUnkOuter)
	{
		pUnkOuter = (LPUNKNOWN) NULL;
	}
	
	return DI_OK;
}

HRESULT HookIDirectInput8::EnumDevices(LPVOID _this, DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return DI_OK;
}

HRESULT HookIDirectInput8::GetDeviceStatus(LPVOID _this, REFGUID rguidInstance)
{
	return DI_OK;
}

HRESULT HookIDirectInput8::RunControlPanel(LPVOID _this, HWND hwndOwner, DWORD dwFlags)
{
	return DIERR_UNSUPPORTED;
}

HRESULT HookIDirectInput8::Initialize(LPVOID _this, HINSTANCE hinst, DWORD dwVersion)
{
	return DI_OK;
}

HRESULT HookIDirectInput8::FindDevice(LPVOID _this, REFGUID rguidClass, LPCTSTR ptszName, LPGUID pguidInstance)
{
	return DI_OK;
}

HRESULT HookIDirectInput8::EnumDevicesBySemantics(LPVOID _this, LPCTSTR ptszUserName, LPDIACTIONFORMAT lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCB lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return DI_OK;
}

HRESULT HookIDirectInput8::ConfigureDevices(LPVOID _this, LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMS lpdiCDParams, DWORD dwFlags, LPVOID pvRefData)
{
	return DI_OK;
}