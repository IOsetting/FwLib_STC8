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
 * Demo: Watchdog Reset
 */

#include "fw_hal.h"

int main(void)
{
    uint8_t count = 9;
    SYS_SetClock();
    UART1_Config8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200);
    UART1_TxString("Watchdog test restarted\r\n");
    /**
     * Set countdown time to around 3 seconds(FOSC = 36.864MHz)
    */
    WDT_SetCounterPrescaler(0x07);
    WDT_StartWatchDog();
    while(1)
    {
        UART1_TxString("Countdown: ");
        UART1_TxHex(count--);
        UART1_TxString("\r\n");
        SYS_Delay(1000);
    }
}
