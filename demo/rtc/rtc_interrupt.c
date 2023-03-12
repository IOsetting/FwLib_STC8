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
 * Demo: RTC
 * Board: STC8H8K64U
 *
 * Note: Cx51 compiler supports interrupt 0~31 only, for interrupts greater 
 *       than 31, you need to 
         1. Define the handler in EXTI_VectUser(vector:006BH)
         2. add an asm code to redirect the interrupt from EXTI_VectRTC(
            vector:0123H) to EXTI_VectUser(vector:006BH)
         
         ASM code example:
         
         CSEG       AT 0123H    ; vector address of EXTI_VectRTC
         LJMP       006BH       ; jump to vector address of EXTI_VectUser
         END
 * 
 *
 */

#include "fw_hal.h"

uint8_t year, month, day, hour, minute, second;

#if defined __CX51__ || defined __C51__
INTERRUPT(RTC_Routine, EXTI_VectUser)
#else
INTERRUPT(RTC_Routine, EXTI_VectRTC)
#endif
{
    SFRX_ON();
    if (RTC_IsSecondInterrupt())
    {
        RTC_ClearSecondInterrupt();
        year = YEAR;
        month = MONTH;
        day = DAY;
        hour = HOUR;
        minute = MIN;
        second = SEC;
    }
    SFRX_OFF();
}

void RTC_Init(void)
{
    // Enable internal 32kHz OSC
    SYS_EnableOscillatorLSI();
    // Set RTC clock source
    RTC_SetClockSource(RTC_ClockSource_Internal);
    // Set clock initial value
    RTC_ConfigClock(22, 1, 9, 18, 59, 03, 0);
    // Init clock
    RTC_ConfigClockApply();
    // Enable second interrupt
    EXTI_RTC_SetSecondIntState(HAL_State_ON);
    // Enable global interrupt
    EXTI_Global_SetIntState(HAL_State_ON);
    // Clear interrupts
    RTC_ClearAllInterrupts();
    // Enable RTC
    RTC_SetRunState(HAL_State_ON);
}

int main(void)
{
    SYS_SetClock();
    UART1_Config8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200);
    RTC_Init();

    while(1)
    {
        SFRX_ON();
        UART1_TxString("RTCCR:");
        UART1_TxHex(RTCCR);
        UART1_TxString(" RTCCFG:");
        UART1_TxHex(RTCCFG);
        UART1_TxString(" RTCIEN:");
        UART1_TxHex(RTCIEN);
        UART1_TxString(" RTCIF:");
        UART1_TxHex(RTCIF);
        SFRX_OFF();
        UART1_TxString(" Year:");
        UART1_TxHex(year);
        UART1_TxString(" Month:");
        UART1_TxHex(month);
        UART1_TxString(" Day:");
        UART1_TxHex(day);
        UART1_TxString(" Hour:");
        UART1_TxHex(hour);
        UART1_TxString(" Minute:");
        UART1_TxHex(minute);
        UART1_TxString(" Second:");
        UART1_TxHex(second);
        UART1_TxString("\r\n");
        SYS_Delay(900);
    }
}
