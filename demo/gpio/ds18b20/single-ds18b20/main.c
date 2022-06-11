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
 * Example code of communication with single DS18B20
 * 
 * Board: STC8H3K32
 * 
 *   Normal Power Mode:
 *          P35         -> DQ
 *          GND         -> GND
 *          5V/3.3V     -> VDD
 * 
 *   Parasite Power Mode:
 *     Parasite power mode requires both DS18B20 GND and Vdd to be 
 *     connected to ground. The DQ pin is the data/parasite power line, 
 *     which requires a pull-up resistor (set by PxPU command)
 *          P35   -> DQ
 *          GND   -> GND -> VDD
 *          5V
 * 
 *   Parasite Power Mode Emulation:
 *     In case some DS18B20 doesn't work in parasite mode, you can add one
 *     0.1uF capacitor and one 1N4148 to achieve it. In thise way DS18B20
 *     actually works in normal power mode
 *
 *                +-----1N4148-|>|-----+
 *                |                    |
 *                |     |DS18B20|-VCC--+
 *                |     |       |      |
 *          P35 --+-DQ--|DS18B20|     0.1uF
 *                      |       |      |
 *          GND ----GND-|DS18B20|-GND--+
 * 
 */


#include "fw_hal.h"
#include "ds18b20.h"

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
    uint8_t buff[9], i;

    SYS_SetClock();
    // UART1, baud 115200, baud source Timer1, 1T mode, no interrupt
    UART1_Config8bitUart(UART1_BaudSource_Timer1, HAL_State_ON, 115200);
    DS18B20_Init();

    while(1)
    {
        DS18B20_StartAll();
        /*
         In Parasite Power Mode, replace the while block below with 
         SYS_Delay(x), x can be [500, 1000]
         */
        while (!DS18B20_AllDone())
        {
            UART1_TxChar('.');
            SYS_Delay(50);
        }
        DS18B20_ReadScratchpad(buff);
        PrintArray(buff, 0, 9);
        UART1_TxChar(' ');
        i = DS18B20_Crc(buff, 8);
        UART1_TxString("CRC:");
        UART1_TxHex(i);
        UART1_TxChar(' ');
        UART1_TxString("\r\n");
        SYS_Delay(1000);
    }
}
