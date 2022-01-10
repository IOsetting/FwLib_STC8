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
 * Demo: Watchdog Clear And Reset
 */

#include "fw_hal.h"

static uint8_t c0 = 0, c1 = 0;

INTERRUPT(Timer0_Routine, EXTI_VectTimer0)
{
    c0++;
    if (c0 == 100)
    {
        c0 = 0;
        c1++;
        if (c1 < 5)
        {
            UART1_TxString("Round ");
            UART1_TxHex(c1);
            UART1_TxString(", reset watchdog counter\r\n");
            WDT_ResetCounter();
        }
        else
        {
            UART1_TxString("Round ");
            UART1_TxHex(c1);
            UART1_TxString(", no operation\r\n");
        }
    }
}

int main(void)
{
    uint8_t count = 9;
    SYS_SetClock();
    UART1_Config8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200);
    UART1_TxString("Watchdog test restarted\r\n");
    // Timer0: 12T mode, frequency 100Hz
    TIM_Timer0_Config(HAL_State_OFF, TIM_TimerMode_16BitAuto, 100);
    EXTI_Timer0_SetIntState(HAL_State_ON);
    EXTI_Timer0_SetIntPriority(EXTI_IntPriority_High);
    EXTI_Global_SetIntState(HAL_State_ON);
    TIM_Timer0_SetRunState(HAL_State_ON);
    UART1_TxString("Timer 0 started\r\n");
    /**
     * Set countdown time to around 3 seconds(FOSC = 36.864MHz)
    */
    WDT_SetCounterPrescaler(0x07);
    WDT_StartWatchDog();
    while(1);
}
