// TTX-Monitor: Open-source Taito Type X loader by Romhack and Hipnosis.

#pragma once
#include <dinput.h>

extern int isPressed[];

extern void PollInputSingle();
extern void PollInputMulti(int ThreadNumber);

typedef enum
{
	M_START,
	M_A,
	M_B,
	M_C,
	M_D,
	M_E,
	M_F,
	M_G,
	M_H,
	M_I,
	M_J,
	M_K,
	M_L,
	M_M,
	M_N,
	M_KONG,
	M_PON,
	M_CHI,
	M_REACH,
	M_RON,
	M_END
} MAHJONG;

const int VI_CODES[] =
{
	0x4F, // O
	0x31, // 1
	0x32, // 2
	0x33, // 3
	0x34, // 4
	0x35, // 5
	0x36, // 6
	0x37, // 7
	0x38, // 8
	0x39, // 9
	0x30, // 0
	0xDB, // VK_OEM_4
	0x51, // Q
	0x57, // W
	0x45, // E
	0x59, // Y
	0x54, // T
	0x52, // R
	0x55, // U
	0x49, // I
};

const int DIK_CODES[] =
{
	DIK_O,
	DIK_1,
	DIK_2,
	DIK_3,
	DIK_4,
	DIK_5,
	DIK_6,
	DIK_7,
	DIK_8,
	DIK_9,
	DIK_0,
	DIK_MINUS,
	DIK_Q,
	DIK_W,
	DIK_E,
	DIK_Y,
	DIK_T,
	DIK_R,
	DIK_U,
	DIK_I,
};