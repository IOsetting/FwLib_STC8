#include "fw_util.h"
#include "fw_sys.h"


void UTIL_Uart1_24M_9600_Init(void)
{
    SCON = 0x50;		//8 bits and variable baudrate
	AUXR |= 0x40;		//imer clock is 1T mode
	AUXR &= 0xFE;		//UART 1 use Timer1 as baudrate generator
	TMOD &= 0x0F;		//Set timer work mode
	TL1 = 0x8F;		//Initial timer value
	TH1 = 0xFD;		//Initial timer value
	ET1 = 0;		//Disable Timer%d interrupt
	TR1 = 1;		//Timer1 start run
}

void UTIL_Uart1_24M_115200_Init(void)
{
	SCON = 0x50;		//8 bits and variable baudrate
	AUXR |= 0x40;		//imer clock is 1T mode
	AUXR &= 0xFE;		//UART 1 use Timer1 as baudrate generator
	TMOD &= 0x0F;		//Set timer work mode
	TL1 = 0xCC;		//Initial timer value
	TH1 = 0xFF;		//Initial timer value
	ET1 = 0;		//Disable Timer%d interrupt
	TR1 = 1;		//Timer1 start run
}

void UTIL_Uart1_33M1776_9600_Init(void)
{
	SCON = 0x50;		//8 bits and variable baudrate
	AUXR |= 0x40;		//imer clock is 1T mode
	AUXR &= 0xFE;		//UART 1 use Timer1 as baudrate generator
	TMOD &= 0x0F;		//Set timer work mode
	TL1 = 0xA0;		//Initial timer value
	TH1 = 0xFC;		//Initial timer value
	ET1 = 0;		//Disable Timer%d interrupt
	TR1 = 1;		//Timer1 start run
}

void UTIL_Uart1_33M1776_115200_Init(void)
{
	SCON = 0x50;
	AUXR |= 0x40;
	AUXR &= 0xFE;
	TMOD &= 0x0F;
	TL1 = 0xB8;
	TH1 = 0xFF;
	ET1 = 0;
	TR1 = 1;
}

void UTIL_Uart1_35M_9600_Init(void)
{
	SCON = 0x50;
	AUXR |= 0x40;
	AUXR &= 0xFE;
	TMOD &= 0x0F;
	TL1 = 0x70;
	TH1 = 0xFC;
	ET1 = 0;
	TR1 = 1;
}

void UTIL_Uart1_36M864_9600_Init(void)
{
	SCON = 0x50;
	AUXR |= 0x40;
	AUXR &= 0xFE;
	TMOD &= 0x0F;
	TL1 = 0x40;
	TH1 = 0xFC;
	ET1 = 0;
	TR1 = 1;
}

void UTIL_Uart1_36M864_115200_Init(void)
{
	SCON = 0x50;
	AUXR |= 0x40;
	AUXR &= 0xFE;
	TMOD &= 0x0F;
	TL1 = 0xB0;
	TH1 = 0xFF;
	ET1 = 0;
	TR1 = 1;
}

void UTIL_ItrimScan(uint8_t ircband, uint8_t *str)
{
	uint8_t i = 0xFF, j;
    if (ircband & 0x01 > 0)
    {
        i = 0xDE;
    }
	do
	{
		j = 3;
		do
		{
			SYS_SetFOSC(ircband, 0, i, j);
            SYS_Delay(1);
			// UTIL_PrintHex(IRCBAND);
			// UTIL_PrintChar(' ');
			// UTIL_PrintHex(IRTRIM);
			// UTIL_PrintChar(0x20);
			// UTIL_PrintHex(LIRTRIM);
			// UTIL_PrintChar(0x20);
			// UTIL_PrintString(str);
			SYS_Delay(5);
		} while (j--);
	} while (i--);
}