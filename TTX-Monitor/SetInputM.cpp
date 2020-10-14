// TTX-Monitor: Open-source Taito Type X loader by Romhack and Hipnosis.

#include "Global.h"

int isPressed[M_END] = { 0 };

// Indicates if the pointer key of the pressed key is also mapped to another key.
int isPointer[M_END] = { 0xFF };

// Limited by one input at the time, it's the safest option. Despite this, even without
// the hook the game has inconsistent input anyways, most notably with multi key presses,
// so this is a way to fix the original game key behavior as well.
void PollInputSingle()
{
	for (;;)
	{
		for (int i = M_START; i < M_END; i++)
		{
			// +3 is the mahjong inputs offset.
			if (InputMgr.GetState(i + 3))
			{
				isPressed[i] = 1;

				INPUT Input = { 0 };
				Input.type = INPUT_KEYBOARD;
				Input.ki.wScan = MapVirtualKey(LOBYTE(VI_CODES[i]), 0);

				// SendInput loop.
				while (InputMgr.GetState(i + 3))
				{
					Input.ki.dwFlags = KEYEVENTF_SCANCODE;
					SendInput(1, &Input, sizeof(Input));
					Sleep(10); // Pause necessary for the next key to be recognized.
					Input.ki.dwFlags = KEYEVENTF_KEYUP;
					SendInput(1, &Input, sizeof(Input));
				}

				// Wait for another thread to process and reject the last SendInput,
				// in case the sent key pointed to an also mapped key.
				Sleep(50);

				isPressed[i] = 0;
			}
		}

		// Reduce the thread processing.
		Sleep(20);
	}
}

// Only limitation is that if a key is mapped to a pointer of another key, both of those
// can't be pressed at the same time. Example: 'A' is mapped to the 'A' key, and 'B' is
// mapped to '1'. Both can't be pressed at the same time because 'A' points to '1'.
void PollInputMulti(int ThreadNumber)
{
	for (;;)
	{
		// +3 is the mahjong inputs offset.
		if (InputMgr.GetState(ThreadNumber + 3))
		{
			// Avoid the thread to process a key already being processed by another.
			if (isPressed[ThreadNumber] == 0)
			{
				isPressed[ThreadNumber] = 1;

				INPUT Input = { 0 };
				Input.type = INPUT_KEYBOARD;
				Input.ki.wScan = MapVirtualKey(LOBYTE(VI_CODES[ThreadNumber]), 0);

				// Value needed for the releasing of pointed keys.
				int isPointer = 0xFF;

				// Check if the key pressed has a pointer key.
				for (int k = M_START; k < M_END; k++)
				{
					if ((DIK_CODES[ThreadNumber] == iTable[k]))
					{
						isPointer = k;
						break;
					}
				}

				if (isPointer != 0xFF)
				{
					isPressed[isPointer] = 2;
				}

				// SendInput loop.
				while (InputMgr.GetState(ThreadNumber + 3))
				{
					Input.ki.dwFlags = KEYEVENTF_SCANCODE;
					SendInput(1, &Input, sizeof(Input));
					Sleep(10); // Pause necessary for the next key to be recognized.
					Input.ki.dwFlags = KEYEVENTF_KEYUP;
					SendInput(1, &Input, sizeof(Input));
				}

				// Wait for another thread to process and reject the last SendInput,
				// in case the sent key pointed to an also mapped key.
				Sleep(50);

				if (isPointer != 0xFF)
				{
					isPressed[isPointer] = 0;
				}

				isPressed[ThreadNumber] = 0;
			}
		}

		// Reduce the thread processing.
		Sleep(20);
	}
}