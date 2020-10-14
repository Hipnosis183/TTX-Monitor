// TTX-Monitor: Open-source Taito Type X loader by Romhack and Hipnosis.

#include "JVSEmu.h"

InputInfo InInfo;

static WORD P1Coins = 0;
static WORD P2Coins = 0;
static int isAddressed = 0;
static int CoinState[2] = { 0, 0 };

int IsAddressed()
{
	return isAddressed;
}

void ResetAddressed()
{
	isAddressed = 0;
}

DWORD ProcessStream(UINT8 *Stream, DWORD srcSize, BYTE *dAddr, DWORD dSize)
{
	JVSEncoder JVS;

	BYTE *pStream = Stream;
	BYTE *pFunction = NULL;

	BYTE Node = 0;
	int PacketCount = 0;
	BYTE PacketSize = 0;
	WORD PacketAddr = 0;

	JVS.Clear();

	Node = pStream[1];
	PacketSize = pStream[2];
	pFunction = &pStream[3];

	// Available bytes for functions in the package stream.
	PacketCount = (int)PacketSize - 1;

	JVS.BeginStream();

	while (PacketCount > 0)
	{
		int Increment = 0;

		switch (pFunction[0] & 0xFF)
		{
			case 0xF0:
			{
				P1Coins = 0;
				P2Coins = 0;

				Increment = 2;
				break;
			}

			case 0xF1:
			{
				JVS.Report(JVS_REPORT_OK);
				isAddressed = 1;

				Increment = 2;
				break;
			}

			case 0x2F:
			{
				Increment = 1;
				break;
			}

			case 0x10:
			{
				JVS.Report(JVS_REPORT_OK);

				const char *Id = idIO;
				while (*Id)
				{
					JVS.bPush(*Id++);
				}

				JVS.bPush(0);

				Increment = 1;
				break;
			}

			case 0x11:
			{
				JVS.Report(JVS_REPORT_OK);
				JVS.bPush(JVS_COMMAND_REV);

				Increment = 1;
				break;
			}

			case 0x12:
			{
				JVS.Report(JVS_REPORT_OK);
				JVS.bPush(JVS_BOARD_REV);

				Increment = 1;
				break;
			}

			case 0x13:
			{
				JVS.Report(JVS_REPORT_OK);
				JVS.bPush(JVS_COMM_REV);

				Increment = 1;
				break;
			}

			case 0x14:
			{
				JVS.Report(JVS_REPORT_OK);

				JVS.bPush(JVS_IOFUNC_SWINPUT);
				{
					JVS.bPush(JVS_SUPPORT_PLAYERS);
					JVS.bPush(14);
					JVS.bPush(0);
				}

				JVS.bPush(JVS_IOFUNC_COINTYPE);
				{
					JVS.bPush(JVS_SUPPORT_SLOTS);
					JVS.bPush(0);
					JVS.bPush(0);
				}

				JVS.bPush(JVS_IOFUNC_EXITCODE);
				{
					JVS.bPush(0);
					JVS.bPush(0);
					JVS.bPush(0);
				}

				Increment = 1;
				break;
			}

			case 0x01:
			{
				JVS.Report(JVS_REPORT_OK);
				JVS.bPush(1);
				JVS.bPush(0);

				Increment = 2;
				break;
			}

			// Controller status.
			case 0x20:
			{
				JVS.Report(JVS_REPORT_OK);

				// Push to byte 0.
				JVS.bPush(InputMgr.GetState(TEST_MODE) ? 0x80 : 0);

				// Push to bytes 1 and 2.
				JVS.bPush(InInfo.Xp1HiByte());
				JVS.bPush(InInfo.Xp1LoByte());
				JVS.bPush(InInfo.Xp2HiByte());
				JVS.bPush(InInfo.Xp2LoByte());

				Increment = 3;
				break;
			}

			case 0x21:
			{
				int CurrState = InputMgr.GetState(P1_COIN);

				if (!CoinState[0] && (CurrState))
				{
					++P1Coins;
				}

				CoinState[0] = CurrState;
				CurrState = InputMgr.GetState(P2_COIN);

				if (!CoinState[1] && (CurrState))
				{
					++P2Coins;
				}

				CoinState[1] = CurrState;

				JVS.Report(JVS_REPORT_OK);
				JVS.bPush(P1Coins >> 8);
				JVS.bPush(P1Coins & 0xFF);
				JVS.bPush(P2Coins >> 8);
				JVS.bPush(P2Coins & 0xFF);

				Increment = 2;
				break;
			}

			case 0x30:
			{
				WORD fValue = ((ARG(2) & 0xFF) << 8) | (ARG(3) & 0xFF);
				JVS.Report(JVS_REPORT_OK);

				switch (ARG(1))
				{
					case 1:
					{
						P1Coins = fValue > P1Coins ? 0 : P1Coins - fValue;

						break;
					}

					case 2:
					{
						P2Coins = fValue > P2Coins ? 0 : P2Coins - fValue;

						break;
					}

					Increment = 4;
					break;
				}
			}

			case 0x31:
			{
				WORD Value = ((ARG(2) & 0xFF) << 8) | (ARG(3) & 0xFF);
				JVS.Report(JVS_REPORT_OK);

				switch (ARG(1))
				{
					case 1:
					{
						P1Coins += Value;
						break;
					}

					case 2:
					{
						P2Coins += Value;
						break;
					}
				}

				Increment = 4;
				break;
			}

			default:
			{
				JVS.Report(JVS_REPORT_OK);

				Increment = 1;
				break;
			}
		}

		PacketCount -= Increment;
		pFunction += Increment;
	}

	JVS.SetStatus(JVS_STATUS_OK);
	JVS.EndStream();
	JVS.Read(dAddr, dSize);

	return JVS.eSize();
}