// Fake DirectInput by Romhack.

#pragma once
#include <dinput.h>

#pragma pack(4)
struct FAR HookIDirectInputDevice
{
	/*** IUnknown methods ***/
	virtual HRESULT QueryInterface(LPVOID _this, REFIID riid, LPVOID* ppvObj);
	virtual ULONG AddRef(LPVOID _this);
	virtual ULONG Release(LPVOID _this);

	/*** IDirectInputDeviceA methods ***/
	virtual HRESULT GetCapabilities(LPVOID _this, LPDIDEVCAPS lpDIDevCaps);
	virtual HRESULT EnumObjects(LPVOID _this, LPDIENUMDEVICEOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags);
	virtual HRESULT GetProperty(LPVOID _this, REFGUID rguidProp, LPDIPROPHEADER pdiph);
	virtual HRESULT SetProperty(LPVOID _this, REFGUID rguidProp, LPCDIPROPHEADER pdiph);
	virtual HRESULT Acquire(LPVOID _this);
	virtual HRESULT Unacquire(LPVOID _this);
	virtual HRESULT GetDeviceState(LPVOID _this, DWORD cbData, LPVOID lpvData);
	virtual HRESULT GetDeviceData(LPVOID _this, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags);
	virtual HRESULT SetDataFormat(LPVOID _this, LPCDIDATAFORMAT lpdf);
	virtual HRESULT SetEventNotification(LPVOID _this, HANDLE hEvent);
	virtual HRESULT SetCooperativeLevel(LPVOID _this, HWND hwnd, DWORD dwFlags);
	virtual HRESULT GetObjectInfo(LPVOID _this, LPDIDEVICEOBJECTINSTANCE pdidoi, DWORD dwObj, DWORD dwHow);
	virtual HRESULT GetDeviceInfo(LPVOID _this, LPDIDEVICEINSTANCE pdidi);
	virtual HRESULT RunControlPanel(LPVOID _this, HWND hwndOwner, DWORD dwFlags);
	virtual HRESULT Initialize(LPVOID _this, HINSTANCE hinst, DWORD dwVersion, REFGUID rguid);
	virtual HRESULT CreateEffect(LPVOID _this, REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT* ppdeff, LPUNKNOWN punkOuter);
	virtual HRESULT EnumEffects(LPVOID _this, LPDIENUMEFFECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwEffType);
	virtual HRESULT GetEffectInfo(LPVOID _this, LPDIEFFECTINFOA pdei, REFGUID rguid);
	virtual HRESULT GetForceFeedbackState(LPVOID _this, LPDWORD pdwOut);
	virtual HRESULT SendForceFeedbackCommand(LPVOID _this, DWORD dwFlags);
	virtual HRESULT EnumCreatedEffectObjects(LPVOID _this, LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl);
	virtual HRESULT Escape(LPVOID _this, LPDIEFFESCAPE pesc);
	virtual HRESULT Poll(LPVOID _this);
	virtual HRESULT SendDeviceData(LPVOID _this, DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl);
	virtual HRESULT EnumEffectsInFile(LPVOID _this, LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags);
	virtual HRESULT WriteEffectToFile(LPVOID _this, LPCSTR lpszFileName, DWORD dwEntries, LPCDIFILEEFFECT rgDiFileEft, DWORD dwFlags);
	virtual HRESULT BuildActionMap(LPVOID _this, LPDIACTIONFORMAT lpdiaf, LPCTSTR lpszUserName, DWORD dwFlags);
	virtual HRESULT SetActionMap(LPVOID _this, LPCDIACTIONFORMAT lpdiActionFormat, LPCTSTR lptszUserName, DWORD dwFlags);
	virtual HRESULT GetImageInfo(LPVOID _this, LPDIDEVICEIMAGEINFOHEADER lpdiDevImageInfoHeader);
};

#pragma pack(4)
struct FAR HookIDirectInput8
{
	/*** IUnknown methods ***/
	virtual HRESULT QueryInterface(LPVOID _this, REFIID riid, LPVOID* ppvObj);
	virtual ULONG AddRef(LPVOID _this);
	virtual ULONG Release(LPVOID _this);

	/*** IDirectInput8 methods ***/
	virtual HRESULT CreateDevice(LPVOID _this, REFGUID rguid, LPDIRECTINPUTDEVICE8A* lplpDirectInputDevice, LPUNKNOWN pUnkOuter);
	virtual HRESULT EnumDevices(LPVOID _this, DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags);
	virtual HRESULT GetDeviceStatus(LPVOID _this, REFGUID rguidInstance);
	virtual HRESULT RunControlPanel(LPVOID _this, HWND hwndOwner, DWORD dwFlags);
	virtual HRESULT Initialize(LPVOID _this, HINSTANCE hinst, DWORD dwVersion);
	virtual HRESULT FindDevice(LPVOID _this, REFGUID rguidClass, LPCTSTR ptszName, LPGUID pguidInstance);
	virtual HRESULT EnumDevicesBySemantics(LPVOID _this, LPCTSTR ptszUserName, LPDIACTIONFORMAT lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCB lpCallback, LPVOID pvRef, DWORD dwFlags);
	virtual HRESULT ConfigureDevices(LPVOID _this, LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMS lpdiCDParams, DWORD dwFlags, LPVOID pvRefData);
};

extern HookIDirectInputDevice* pFakeDevice;
extern HookIDirectInput8* pFakeInterface;