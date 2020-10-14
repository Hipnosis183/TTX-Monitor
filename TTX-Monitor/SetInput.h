// TTX-Monitor: Open-source Taito Type X loader by Romhack and Hipnosis.

#pragma once
#include <iostream>
#include <list>
#include <thread>

#include "SetInputM.h"

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#define MONITOR_INPUT_FILENAME	"monitor_input.bin"

#define DIRECTINPUT_VERSION	0x800

#define IS_JOY_OBJECT(n)	(n & 0x80000000)
#define IS_JOY_AXIS(n)		(n & 0x000F0000)
#define GET_JOY_NUM(n)		((n >> 24) & 0x0F)
#define GET_JOY_BUT(n)		(n & 0xFF)
#define GET_JOY_AXIS(n)		((n >> 16) & 0xF)
#define GET_JOY_RANGE(n)	(n & 0xFFFF)
#define IS_NEGATIVE_AXIS(n)	((n >> 20) & 1)
#define JOYV(joy, v)		(0x80000000 | ((joy & 0x0F) << 24) | (v & 0xFFFFFF))
#define KEYV(vk)			(vk)
#define JOYB(n)				(n & 0xFF)
#define JOYAXIS(a, n, v)	(((n & 1) << 20) | ((a & 0xF) << 16) | (v & 0xFFFF))
#define AXIS_X				1
#define AXIS_Y				2
#define AXIS_Z				3
#define AXIS_RX				4
#define AXIS_RY				5
#define POVN				10

#define POV_CENTER			-1
#define POV_UP				0
#define POV_UP_RIGHT		4500
#define POV_RIGHT			9000
#define POV_RIGHT_DOWN		13500
#define POV_DOWN			18000
#define POV_DOWN_LEFT		22500
#define POV_LEFT			27000
#define POV_LEFT_UP			31500

#define MAX_AXIS_VAL		1000
#define DEADZONE_DIV		100
#define DEADZONE			500 // (MAX_AXIS_VAL / DEADZONE_DIV)
#define POLL_INTERVAL		30

extern BOOL DIMagicCall;
extern DWORD hPollThreadId;

typedef enum
{
	P1_START,
	P1_COIN,
	P1_SERVICE,
	P1_UP,
	P1_DOWN,
	P1_LEFT,
	P1_RIGHT,
	P1_BUTTON_1,
	P1_BUTTON_2,
	P1_BUTTON_3,
	P1_BUTTON_4,
	P1_BUTTON_5,
	P1_BUTTON_6,
	P2_START,
	P2_COIN,
	P2_SERVICE,
	P2_UP,
	P2_DOWN,
	P2_LEFT,
	P2_RIGHT,
	P2_BUTTON_1,
	P2_BUTTON_2,
	P2_BUTTON_3,
	P2_BUTTON_4,
	P2_BUTTON_5,
	P2_BUTTON_6,
	TEST_MODE,
	EXIT_CODE,
	INPUT_END,
} INPUTS;

class InputManager
{
	LPDIRECTINPUT8 DirectInput;

	static BOOL EnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);
	static BOOL EnumDeviceObjectsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);
	
	char KeyBuffer[256];
	int StateTable[INPUT_END];
	DWORD BindTable[INPUT_END];
	DWORD LastPoll;

	std::list<LPCDIDEVICEINSTANCE> DIDevices;
	std::list<LPDIRECTINPUTDEVICE8> lpJoysticks;

	LPDIRECTINPUTDEVICE8 lpKeyboard;
	LPDIRECTINPUTDEVICE8 GetJoyDevice(int n);

	ATOM ClsId;
	HWND hSelfWin;
	DWORD ThreadId;
	WNDCLASS WndCls;
	HANDLE hPollMutex;

	static int PollThread(InputManager* pThis);
	void Setup();

public:
	char StrBuf[128];

	InputManager();
	~InputManager();

	int Poll();
	int GetState(int Index);
	void Load();
	void LoadTable();
	BOOL Init();
};