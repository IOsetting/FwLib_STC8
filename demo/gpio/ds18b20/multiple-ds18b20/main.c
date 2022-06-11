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

/***
 * Example code of communication on 1-Wire bus with multiple DS18B20
 * 
 * Board: STC8H3K32
 * 
 *              P35   -> DQ
 *              GND   -> GND
 *              3.3V  -> VCC
 */

#include "fw_hal.h"
#include "ds18b20.h"

uint8_t DS18B20_Buff[9], addr[8], Search_Stack[8];

void PrintArray(uint8_t *arr, uint8_t start, uint8_t end)
{
    uint8_t i;
    for (i = start; i < end; i++)
    {
        UART1_TxHex(*(arr + i));
    }
}

int main(void)
{
    uint8_t i, sp;

    SYS_SetClock();
    // UART1, baud 115200, baud source Timer1, 1T mode, no interrupt
    UART1_Config8bitUart(UART1_BaudSource_Timer1, HAL_State_ON, 115200);
    DS18B20_Init();

    while(1)
    {
        // Reset split point and search for all DS18B20
        sp = 0;
        do
        {
            // ROM search and store ROM bytes to addr
            sp = DS18B20_Search(addr, Search_Stack, sp);
            // Print the new split point and address
            UART1_TxHex(sp);
            UART1_TxChar(' ');
            PrintArray(addr, 0, 8);
            // Convert and read from this address
            DS18B20_Start(addr);
            while (!DS18B20_AllDone())
            {
                UART1_TxChar('.');
                SYS_Delay(50);
            }
            DS18B20_ReadScratchpadFromAddr(addr, DS18B20_Buff);
            PrintArray(DS18B20_Buff, 0, 9);
            UART1_TxChar(' ');
            i = DS18B20_Crc(DS18B20_Buff, 8);
            UART1_TxString("CRC:");
            UART1_TxHex(i);
            UART1_TxChar(' ');
            UART1_TxString("\r\n");
        } while (sp);

        UART1_TxString("\r\n");
        SYS_Delay(1000);
    }
}
