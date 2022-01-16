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

/**
 * Built-in Readonly CHIPID on following MCU types with firmwaire version >= 7.4.4
 *  STC8H8K64U, 
 *  STC8H4K64LCD,
 *  STC8H4K64TLR, 
 *  STC8H4K64TLCD
*/
#include "fw_hal.h"

uint8_t __XDATA i, buff[32] = {0};

void PrintBuff(void)
{
    for (i = 0; i < 32; i++)
    {
        UART1_TxHex(*(buff + i));
        if (i % 8 == 7) UART1_TxChar(0x20);
    }
    UART1_TxString("\r\n           STC8H8K64U   ");
    UART1_TxString("\r\nCPUID:                  ");
    for (i = 0; i < 7; i++)
    {
        UART1_TxHex(*(buff + i));
    }
    UART1_TxString("\r\nVref 1.19V:             0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\n32KHz:                  0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\n22.1184MHz:             0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\n24MHz:                  0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\n20MHz       27MHz:      0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\n27MHz       30MHz:      0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\n30MHz       33.1176MHz: 0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\n33.1776MHz  35MHz:      0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\n35MHz       36.864MHz:  0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\n36.864MHz   40MHz:      0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\n40MHz       44.2368MHz: 0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\n45MHz       48MHz:      0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\nVRTRIM 6MHz:            0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\nVRTRIM 10MHz:           0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\nVRTRIM 27MHz:           0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\nVRTRIM 44MHz:           0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\n00:                     0x");
    UART1_TxHex(*(buff + i++));
    UART1_TxString("\r\n\r\n");
    UART1_TxString("Current IRCBAND:");
    UART1_TxHex(IRCBAND);
    UART1_TxString(", VRTRIM:");
    UART1_TxHex(VRTRIM);
    UART1_TxString(", IRTRIM:");
    UART1_TxHex(IRTRIM);
    UART1_TxString(", LIRTRIM:");
    UART1_TxHex(LIRTRIM);
    UART1_TxString("\r\n\r\n");
}

void ItrimScan(uint8_t ircband, uint8_t vrtrim_limit, uint8_t irtrim_limit)
{
	uint8_t i = 0, j = 0;
    while (i++ < vrtrim_limit)
    {
        j = 0;
        while (j++ < irtrim_limit)
        {
            SYS_SetFOSC(ircband, i, j, 0);
            SYS_Delay(10);
            PrintBuff();
        }
    }
}

void main(void)
{
    SYS_SetClock();
    // UART1 configuration: baud 115200 with Timer2, 1T mode, no interrupt
    UART1_Config8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200);
    MEM_ReadChipID(buff);
    PrintBuff();

    while(1)
    {
        /**
         * Uncomment this line if vrtrim and irtrim are unknown,
         * this will scan all possible vrtrim and irtrim values between [0, 0xE0]
        */
        //ItrimScan(__CONF_IRCBAND, 0xE0, 0xE0);
    }
}