// TTX-Monitor: Open-source Taito Type X loader by Romhack and Hipnosis.

#include "Global.h"

// Exclusive for mahjong inputs.
DWORD iTable[M_END];

InputManager::InputManager()
{
	LastPoll = 0;

	for (int i = P1_START; i < INPUT_END; i++)
	{
		StateTable[i] = 0;
	}

	DirectInput = NULL;
}

InputManager::~InputManager()
{
	for (std::list<LPDIRECTINPUTDEVICE8>::iterator pDevice = lpJoysticks.begin(); pDevice != lpJoysticks.end(); pDevice++)
	{
		(*pDevice)->Release();
	}
	
	lpKeyboard->Release();
}

int InputManager::Poll()
{
	WaitForSingleObject(hPollMutex, INFINITE);
	DWORD tNow = GetTickCount();

	static DIJOYSTATE2 JoyState[16];

	for (std::list<LPDIRECTINPUTDEVICE8>::iterator pDevice = lpJoysticks.begin(); pDevice != lpJoysticks.end(); pDevice++)
	{
		HRESULT Result = (*pDevice)->Poll();

		switch (Result)
		{
			case DIERR_NOTACQUIRED:
			case DIERR_INPUTLOST:
			{
				Result = (*pDevice)->Acquire();
				break;
			}
		}
	}
	
	lpKeyboard->GetDeviceState(sizeof(KeyBuffer), &KeyBuffer);

	bool isPolled[16];

	for (int i = 0; i < 16; i++)
	{
		isPolled[i] = false;
	}

	for (int i = P1_START; i < INPUT_END; i++)
	{
		DWORD InValue = BindTable[i];

		// Check for a joystick command.
		if (IS_JOY_OBJECT(InValue))
		{
			DWORD JoyNumber = GET_JOY_NUM(InValue);

			// Take the device that generated the input.
			LPDIRECTINPUTDEVICE8 lpDevice = GetJoyDevice(JoyNumber);

			if (!lpDevice)
			{
				StateTable[i] = 0;
				continue;
			}

			if (!isPolled[JoyNumber])
			{
				HRESULT Result = lpDevice->GetDeviceState(sizeof(DIJOYSTATE2), &JoyState[JoyNumber]);

				switch (Result)
				{
					case DIERR_NOTACQUIRED:
					case DIERR_INPUTLOST:
					{
						Result = lpDevice->Acquire();
						break;
					}
				}
				
				isPolled[JoyNumber] = true;
			}

			if (IS_JOY_AXIS(InValue))
			{
				WORD Direction = JoyState[JoyNumber].rgdwPOV[0];
				StateTable[i] = 0;

				switch (GET_JOY_AXIS(InValue))
				{
					case AXIS_X:
					{
						if (IS_NEGATIVE_AXIS(InValue))
						{
							if ((JoyState[JoyNumber].lX < -DEADZONE) || (mTable[CONFIG_POVASAXIS] && ((Direction == POV_LEFT) || (Direction == POV_DOWN_LEFT) || (Direction == POV_LEFT_UP))))
							{
								StateTable[i] = 1;
							}
						}
						
						else
						{
							if ((JoyState[JoyNumber].lX > DEADZONE) || (mTable[CONFIG_POVASAXIS] && ((Direction == POV_RIGHT) || (Direction == POV_UP_RIGHT) || (Direction == POV_RIGHT_DOWN))))
							{
								StateTable[i] = 1;
							}
						}

						break;
					}

					case AXIS_Y:
					{
						if (IS_NEGATIVE_AXIS(InValue))
						{
							if ((JoyState[JoyNumber].lY < -DEADZONE) || (mTable[CONFIG_POVASAXIS] && ((Direction == POV_UP) || (Direction == POV_UP_RIGHT) || (Direction == POV_LEFT_UP))))
							{
								StateTable[i] = 1;
							}
						}
						
						else
						{
							if ((JoyState[JoyNumber].lY > DEADZONE) || (mTable[CONFIG_POVASAXIS] && ((Direction == POV_DOWN) || (Direction == POV_RIGHT_DOWN) || (Direction == POV_DOWN_LEFT))))
							{
								StateTable[i] = 1;
							}
						}

						break;
					}

					case AXIS_Z:
					{
						if (IS_NEGATIVE_AXIS(InValue))
						{
							if (JoyState[JoyNumber].lZ < -DEADZONE)
							{
								StateTable[i] = 1;
							}
						}

						else
						{
							if (JoyState[JoyNumber].lZ > DEADZONE)
							{
								StateTable[i] = 1;
							}
						}

						break;
					}

					// For whatever reason the Rx axis uses the full 16-bit range, despite the value set.
					case AXIS_RX:
					{
						if (IS_NEGATIVE_AXIS(InValue))
						{
							if (JoyState[JoyNumber].lRx < 16535)
							{
								StateTable[i] = 1;
							}
						}

						else
						{
							if (JoyState[JoyNumber].lRx > 55535)
							{
								StateTable[i] = 1;
							}
						}

						break;
					}

					case AXIS_RY:
					{
						if (IS_NEGATIVE_AXIS(InValue))
						{
							if (JoyState[JoyNumber].lRy < -DEADZONE)
							{
								StateTable[i] = 1;
							}
						}

						else
						{
							if (JoyState[JoyNumber].lRy > DEADZONE)
							{
								StateTable[i] = 1;
							}
						}

						break;
					}

					case POVN:
					{
						// To avoid problems, mapped POVs are disabled and forced to work as axis if PovAsAxis option is enabled.
						if ((JoyState[JoyNumber].rgdwPOV[0] != -1) && !mTable[CONFIG_POVASAXIS])
						{
							if (GET_JOY_RANGE(InValue) == POV_UP && ((Direction == POV_UP) || (Direction == POV_UP_RIGHT) || (Direction == POV_LEFT_UP)))
							{
								StateTable[i] = 1;
							}

							if (GET_JOY_RANGE(InValue) == POV_RIGHT && ((Direction == POV_RIGHT) || (Direction == POV_UP_RIGHT) || (Direction == POV_RIGHT_DOWN)))
							{
								StateTable[i] = 1;
							}

							if (GET_JOY_RANGE(InValue) == POV_DOWN && ((Direction == POV_DOWN) || (Direction == POV_RIGHT_DOWN) || (Direction == POV_DOWN_LEFT)))
							{
								StateTable[i] = 1;
							}

							if (GET_JOY_RANGE(InValue) == POV_LEFT && ((Direction == POV_LEFT) || (Direction == POV_DOWN_LEFT) || (Direction == POV_LEFT_UP)))
							{
								StateTable[i] = 1;
							}
						}

						break;
					}
				}

			}

			else
			{
				int Button = GET_JOY_BUT(InValue);
				StateTable[i] = JoyState[JoyNumber].rgbButtons[Button] & 0x80 ? 1 : 0;
			}
		}

		else
		{
			StateTable[i] = KeyBuffer[InValue & 0xFF] & 0x80 ? 1 : 0;
		}
	}

	LastPoll = tNow;

	ReleaseMutex(hPollMutex);
	return 1;
}

BOOL InputManager::EnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	InputManager *InManager = (InputManager *) pvRef;
	InManager->DIDevices.push_back(lpddi);

	LPDIRECTINPUTDEVICE8 lpDevice;

	if (InManager->DirectInput->CreateDevice(lpddi->guidInstance, &lpDevice, NULL) == DI_OK)
	{
		lpDevice->SetDataFormat(&c_dfDIJoystick2);
		InManager->lpJoysticks.push_back(lpDevice);
		lpDevice->EnumObjects((LPDIENUMDEVICEOBJECTSCALLBACK) &InputManager::EnumDeviceObjectsCallback, lpDevice, DIDFT_ALL);

		return DIENUM_CONTINUE;
	}

	return DIENUM_STOP;
}

BOOL InputManager::EnumDeviceObjectsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	LPDIRECTINPUTDEVICE8 Device = (LPDIRECTINPUTDEVICE8) pvRef;

	if (lpddoi->dwType & DIDFT_AXIS)
	{
		DIPROPRANGE DIPRange;
		DIPRange.diph.dwSize = sizeof(DIPROPRANGE);
		DIPRange.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		DIPRange.diph.dwHow = DIPH_BYID;
		DIPRange.diph.dwObj = lpddoi->dwType;
		DIPRange.lMin = -MAX_AXIS_VAL;
		DIPRange.lMax = +MAX_AXIS_VAL;

		Device->SetProperty(DIPROP_RANGE, &DIPRange.diph);

		DIPROPDWORD DIPDWord;
		memset(&DIPDWord, 0, sizeof(DIPROPDWORD));
		DIPDWord.diph.dwSize = sizeof(DIPROPDWORD);
		DIPDWord.diph.dwHeaderSize =  sizeof(DIPROPHEADER);
		DIPDWord.diph.dwHow = DIPH_BYID;
		DIPDWord.diph.dwObj = lpddoi->dwType;
		DIPDWord.dwData = DEADZONE;

		Device->SetProperty(DIPROP_DEADZONE, &DIPDWord.diph);
	}

	return DIENUM_CONTINUE;
}

void InputManager::Load()
{
	FILE* Stream = fopen(MONITOR_INPUT_FILENAME, "r");

	if (Stream)
	{
		if (mTable[CONFIG_MAHJONG])
		{
			fseek(Stream, INPUT_END * sizeof(DWORD), SEEK_SET);
		}
		
		fread(BindTable, INPUT_END * sizeof(DWORD), 1, Stream);
		fclose(Stream);
	}
}

void InputManager::LoadTable()
{
	FILE *Stream = fopen(MONITOR_INPUT_FILENAME, "r");

	if (Stream)
	{
		// +3 is the mahjong inputs offset.
		fseek(Stream, (INPUT_END + 3) * sizeof(DWORD), SEEK_SET);
		fread(iTable, M_END * sizeof(DWORD), 1, Stream);
		fclose(Stream);
	}
}

LPDIRECTINPUTDEVICE8 InputManager::GetJoyDevice(int n)
{
	int i = 0;

	if (lpJoysticks.empty())
	{
		return NULL;
	}

	for (std::list<LPDIRECTINPUTDEVICE8>::iterator pDevice = lpJoysticks.begin(); pDevice != lpJoysticks.end(); pDevice++)
	{
		if (i == n)
		{
			return *pDevice;
		}

		else
		{
			i++;
		}
	}

	return NULL;
}

int InputManager::GetState(int Index)
{
	return StateTable[Index];
}

int DIMagicCall = 0;
DWORD hPollThreadId = 0;

int InputManager::PollThread(InputManager* pThis)
{
	HANDLE CurrThread = GetCurrentThread();
	hPollThreadId = GetCurrentThreadId();
	SetThreadPriority(CurrThread, 1);

	pThis->Setup();
	pThis->Load();
	pThis->LoadTable();

	for (;;)
	{
		pThis->Poll();

		if (pThis->GetState(EXIT_CODE))
		{
			ExitProcess(-1);
		}

		Sleep(20);
	}

	return 0;
}

void InputManager::Setup()
{
	hPollMutex = CreateMutex(0, 0, "poll_mutex");

	ZeroMemory(&WndCls, sizeof(WNDCLASS));

	WndCls.lpfnWndProc = DefWindowProcA;
	WndCls.hInstance = GetModuleHandle(0);
	WndCls.hbrBackground = (HBRUSH) 2;
	WndCls.lpszClassName = "dinput_fdp";

	ClsId = RegisterClass(&WndCls);

	if (!ClsId)
	{
		DWORD Error = GetLastError();

		if (Error != ERROR_CLASS_ALREADY_EXISTS)
		{
			ExitProcess(-1);
		}
	}

	hSelfWin = CreateWindowEx(0, "dinput_fdp", "dinput_muito_fdp", WS_POPUP, 0, 0, 0, 0, NULL, NULL, GetModuleHandle(0), NULL);

	if (!hSelfWin)
	{
		ExitProcess(-2);
	}

	DIMagicCall = 1;

	if (DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID *) &DirectInput, NULL) != DI_OK)
	{
		ExitProcess(-3);
	}

	DIMagicCall = 0;

	DirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACKA) &InputManager::EnumDevicesCallback, (LPVOID) this, 0);

	for (std::list<LPDIRECTINPUTDEVICE8>::iterator i = lpJoysticks.begin(); i != lpJoysticks.end(); i++)
	{
		(*i)->Acquire();
	}		

	DirectInput->CreateDevice(GUID_SysKeyboard, &lpKeyboard, NULL);

	lpKeyboard->SetDataFormat(&c_dfDIKeyboard);
	lpKeyboard->SetCooperativeLevel(hSelfWin, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	lpKeyboard->Acquire();
}

BOOL InputManager::Init()
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&InputManager::PollThread, (LPVOID)this, 0, 0);
	
	if (mTable[CONFIG_MAHJONG])
	{
		if (mTable[CONFIG_MULTITHREAD])
		{
			for (int i = M_START; i < M_END; i++)
			{
				std::thread(PollInputMulti, i).detach();
			}
		}

		else
		{
			std::thread(PollInputSingle).detach();
		}
	}
	
	return TRUE;
}