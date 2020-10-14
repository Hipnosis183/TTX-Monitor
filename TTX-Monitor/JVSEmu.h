// TTX-Monitor: Open-source Taito Type X loader by Romhack and Hipnosis.

#pragma once
#include "Global.h"

#define JVS_TRUE				0x01
#define JVS_FALSE				0x00
#define JVS_SYNC_CODE			0xE0
#define JVS_REPORT_CODE			0x01
#define JVS_COMMAND_REV			0x13
#define JVS_BOARD_REV			0x30
#define JVS_COMM_REV			0x10
#define JVS_ADDR_MASTER			0x00
#define JVS_STATUS_OK			0x01
#define JVS_STATUS_UNKNOWN_CMD	0x02
#define JVS_STATUS_SUM_ERROR	0x03
#define JVS_STATUS_ACK_OVERFLOW	0x04
#define JVS_REPORT_OK			0x01
#define JVS_REPORT_INVAL_PARAM1	0x02
#define JVS_REPORT_INVAL_PARAM2	0x03
#define JVS_REPORT_BUSY			0x04
#define JVS_STREAM_SIZE			1024

#define JVS_OP_RESET			0xF0
#define JVS_OP_ADDRESS			0xF1
#define JVS_OP_CHECKSUM_ERROR	0x2F

#define JVS_IOFUNC_SWINPUT		0x01
#define JVS_IOFUNC_COINTYPE		0x02
#define JVS_IOFUNC_EXITCODE		0x00

#define JVS_SUPPORT_PLAYERS		2
#define JVS_SUPPORT_SLOTS		2

#define ARG(n)	((DWORD)pFunction[n])

//  For each received function a report is needed, after which a checksum is generated in response.
//
//  Package received:
//
// +-----------+---------------+------+-------+-------+----------+
// | SYNC_CODE | SLAVE_ADDRESS | SIZE | FUNC1 | FUNCn | CHECKSUM |
// +-----------+---------------+------+-------+-------+----------+
//
//  Package sent:
//
// +-----------+--------------------+------+--------+---------+---------+----------+
// | SYNC_CODE | MASTER_ADDRESS (0) | SIZE | STATUS | REPORT1 | REPORTn | CHECKSUM |
// +-----------+--------------------+------+--------+---------+---------+----------+
//
//  Switch input data:
//
// +--------+--------+---------+--------+--------+-------+-------+--------+--------+
// |        | BIT 7  | BIT 6   | BIT 5  | BIT 4  | BIT 3 | BIT 2 | BIT 1  | BIT 0  |
// +--------+--------+---------+--------+--------+-------+-------+--------+--------+
// | Byte 0 | TEST   |         |        |        |       |       |        |        |
// +--------+--------+---------+--------+--------+-------+-------+--------+--------+
// | Byte 1 | START  | SERVICE | UP     | DOWN   | LEFT  | RIGHT | PUSH 1 | PUSH 2 |
// +--------+--------+---------+--------+--------+-------+-------+--------+--------+
// | Byte 2 | PUSH 3 | PUSH 4  | PUSH 5 | PUSH 6 |       |       |        |        |
// +--------+--------+---------+--------+--------+-------+-------+--------+--------+

class InputInfo
{
public:
	InputInfo() {}
	~InputInfo() {}

	BYTE Xp1HiByte()
	{
		BYTE Byte = 0;

		if (InputMgr.GetState(P1_START))
		{
			Byte |= 0x80;
		}

		if (InputMgr.GetState(P1_SERVICE))
		{
			Byte |= 0x40;
		}

		if (InputMgr.GetState(P1_UP))
		{
			Byte |= 0x20;
		}

		if (InputMgr.GetState(P1_DOWN))
		{
			Byte |= 0x10;
		}

		if (InputMgr.GetState(P1_RIGHT))
		{
			Byte |= 0x04;
		}

		if (InputMgr.GetState(P1_LEFT))
		{
			Byte |= 0x08;
		}

		if (InputMgr.GetState(P1_BUTTON_1))
		{
			Byte |= 0x02;
		}

		if (InputMgr.GetState(P1_BUTTON_2))
		{
			Byte |= 0x01;
		}

		return Byte;
	}

	BYTE Xp1LoByte()
	{
		BYTE Byte = 0;

		if (InputMgr.GetState(P1_BUTTON_3))
		{
			Byte |= 0x80;
		}

		if (InputMgr.GetState(P1_BUTTON_4))
		{
			Byte |= 0x40;
		}

		if (InputMgr.GetState(P1_BUTTON_5))
		{
			Byte |= 0x20;
		}

		if (InputMgr.GetState(P1_BUTTON_6))
		{
			Byte |= 0x10;
		}

		return Byte;
	}

	BYTE Xp2HiByte()
	{
		BYTE Byte = 0;

		if (InputMgr.GetState(P2_START))
		{
			Byte |= 0x80;
		}

		if (InputMgr.GetState(P2_SERVICE))
		{
			Byte |= 0x40;
		}

		if (InputMgr.GetState(P2_UP))
		{
			Byte |= 0x20;
		}

		if (InputMgr.GetState(P2_DOWN))
		{
			Byte |= 0x10;
		}

		if (InputMgr.GetState(P2_RIGHT))
		{
			Byte |= 0x04;
		}

		if (InputMgr.GetState(P2_LEFT))
		{
			Byte |= 0x08;
		}

		if (InputMgr.GetState(P2_BUTTON_1))
		{
			Byte |= 0x02;
		}

		if (InputMgr.GetState(P2_BUTTON_2))
		{
			Byte |= 0x01;
		}

		return Byte;
	}

	BYTE Xp2LoByte()
	{
		BYTE Byte = 0;

		if (InputMgr.GetState(P2_BUTTON_3))
		{
			Byte |= 0x80;
		}

		if (InputMgr.GetState(P2_BUTTON_4))
		{
			Byte |= 0x40;
		}

		if (InputMgr.GetState(P2_BUTTON_5))
		{
			Byte |= 0x20;
		}

		if (InputMgr.GetState(P2_BUTTON_6))
		{
			Byte |= 0x10;
		}

		return Byte;
	}
};

static const char* idIO = "NAMCO LTD.;I/O PCB-1000;ver1.0;for domestic only,no analog input";

class JVSEncoder
{
	BYTE Buffer[1024];
	DWORD StatusAddr;
	DWORD SizeAddr;
	DWORD SumAddr;
	DWORD StartAddr;
	DWORD xPos;
	DWORD enSize;
	DWORD nReplies;

public:
	JVSEncoder()
	{
		memset(Buffer, 0, 1024);
		xPos = 0;
	}

	~JVSEncoder()
	{
		memset(Buffer, 0, 1024);
		xPos = 0;
	}

	void AddReply()
	{
		nReplies++;
	}

	void SetStatus(BYTE sCode)
	{
		Buffer[StatusAddr] = sCode;
	}

	void Clear()
	{
		memset(Buffer, 0, 1024);
		enSize = 0;
		xPos = 0;
	}

	void BeginStream()
	{
		zPush(JVS_SYNC_CODE);
		SumAddr = xPos;
		zPush(JVS_ADDR_MASTER);
		SizeAddr = xPos;
		bPush(0);
		StatusAddr = xPos;
		bPush(JVS_STATUS_OK);
	}

	void bPush(BYTE Value)
	{
		if (Value == 0xD0)
		{
			Buffer[xPos++] = 0xD0;
			Buffer[xPos++] = 0xCF;
		}

		else if (Value == 0xE0)
		{
			Buffer[xPos++] = 0xD0;
			Buffer[xPos++] = 0xDF;
		}

		else
		{
			Buffer[xPos++] = Value;
		}
	}

	void zPush(BYTE Value)
	{
		Buffer[xPos++] = Value;
	}

	void Report(BYTE Value)
	{
		bPush(Value);
	}

	void EndStream()
	{
		if (xPos == (StatusAddr + 1))
		{
			Clear();
			return;
		}

		DWORD sSize = 0;

		for (DWORD i = SizeAddr; i < xPos; i++)
		{
			if (Buffer[i] != 0xD0)
			{
				++sSize;
			}
		}

		// Set the package stream size.
		Buffer[SizeAddr] = sSize;

		// Calculate the checksum.
		DWORD Checksum = 0;

		for (DWORD i = SumAddr, k = 0; i < xPos; i++)
		{
			if (Buffer[i] == 0xD0)
			{
				k = 1;
			}

			else
			{
				Checksum += (DWORD)((Buffer[i] + k) & 0xFF);

				if (k)
				{
					k = 0;
				}
			}
		}

		Checksum &= 0xFF;
		bPush(Checksum);
		enSize = xPos;
	}

	void Read(BYTE* dAddr, DWORD eSize)
	{
		if (eSize > enSize)
		{
			eSize = enSize;
		}

		memcpy(dAddr, &Buffer[0], eSize);
	}

	DWORD eSize()
	{
		return enSize;
	}
};