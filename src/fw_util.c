// Copyright 2021 IOsetting <iosetting(at)outlook.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "fw_util.h"
#include "fw_sys.h"

__CODE char HEX_TABLE[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

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
