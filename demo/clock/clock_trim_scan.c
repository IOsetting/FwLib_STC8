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
 * Scan to find most close VRTRIM and IRTRIM for specified frequency.
 * 
 * Change build_flags in platformio.ini
 *   D__CONF_FOSC       -> target frequency, e.g. 36864000UL
 *   D__CONF_MCU_MODEL  -> MCU type, e.g. MCU_MODEL_STC8H3K64S2
 *   D__CONF_IRCBAND    -> frequency band depending on the frequency
 *                          STC8H1K          - 00:20MHz, 01:35MHz
 *                          STC8H3K,STC8H8K  - 02:24MHz, 03:40MHz
 * 
 * Connect UART at baud 115200 and read output, when the output is not garbled,
 * find the middle value of VRTRIM and IRTRIM, lower VRTRIM is preferred
*/
#include "fw_hal.h"


uint8_t readCode(uint8_t offset)
{
    return (*(unsigned char volatile __CODE *)(__CID_ADDR + offset));
}

void main(void)
{
    uint8_t i, j, vrtrim = 0x01, irtrim = 0;

    // Set system clock. Invoke it to set the frequency band
    SYS_SetClock();
    // UART1 configuration: baud 115200 with Timer2, 1T mode, no interrupt
    UART1_Config8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200);

    while(1)
    {
        // The upper limit of IRTRIM depends on VRTRIM, MCU becomes unstable if it goes 
        // too high, set 0x30 to a lower value if scan stucks at beginning
        if (++irtrim == 0x30 + vrtrim) 
        {
            irtrim = 0x00;
            // VRTRIM controls the voltage level, normally it won't exceed 0x40
            if (++vrtrim == 0x40) 
            {
                vrtrim = 0x00;
            }
        }
        SYS_TrimClock(vrtrim, irtrim);

        UART1_TxString("ADDR: 0x");
        UART1_TxHex(__CID_ADDR >> 8);
        UART1_TxHex(__CID_ADDR & 0xFF);
        UART1_TxString("\r\n");
        UART1_TxString("MCUID: ");
        for (j = 0; j < 7; j++)
        {
            UART1_TxHex(readCode(18 + j));
            UART1_TxChar(' ');
        }
        UART1_TxString("\r\n");
        UART1_TxString("Current IRCBAND:");
        UART1_TxHex(IRCBAND);
        UART1_TxString(", VRTRIM:");
        UART1_TxHex(VRTRIM);
        UART1_TxString(", IRTRIM:");
        UART1_TxHex(IRTRIM);
        UART1_TxString(", LIRTRIM:");
        UART1_TxHex(LIRTRIM);
        UART1_TxString("\r\n\r\n");

        SYS_Delay(50);
    }
}