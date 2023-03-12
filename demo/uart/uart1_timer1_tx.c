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

#include "fw_hal.h"

extern __CODE uint16_t ticks_ms;
extern __CODE uint8_t  ticks_us;

void main(void)
{
    SYS_SetClock();
    // UART1, baud 115200, baud source Timer1, 1T mode, no interrupt
    UART1_Config8bitUart(UART1_BaudSource_Timer1, HAL_State_ON, 115200);
    while(1)
    {
        UART1_TxString("ms ticks:0x");
        UART1_TxHex(ticks_ms >> 8);
        UART1_TxHex(ticks_ms & 0xFF);
        UART1_TxString(" us ticks:0x");
        UART1_TxHex(ticks_us);
        UART1_TxString(" clock div:0x");
        UART1_TxHex(__CONF_CLKDIV);
        UART1_TxString(" string\r\n");
        SYS_Delay(1000);
    }
}