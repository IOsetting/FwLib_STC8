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

__BIT dir = SET;
uint8_t dc = 0; 

void main(void)
{
    SYS_SetClock();
    // UART1, baud 115200, baud source Timer1, 1T mode, no interrupt
    UART1_Config8bitUart(UART1_BaudSource_Timer1, HAL_State_ON, 115200);

    // Set GPIO pin mode
    GPIO_P3_SetMode(GPIO_Pin_2|GPIO_Pin_3, GPIO_Mode_Output_PP);

    // Stop PCA/PWM 
    PCA_SetCounterState(HAL_State_OFF);
    // Stop counter in idle mode
    PCA_SetStopCounterInIdle(HAL_State_ON);
    // Use SYSCLK as clock source
    PCA_SetClockSource(PCA_ClockSource_SysClk);
    // Turn off overflow interrupt
    PCA_EnableCounterOverflowInterrupt(HAL_State_OFF);

    // Set PCA0 and PCA1 to PWM mode
    PCA_PCA0_SetWorkMode(PCA_WorkMode_PWM_NonInterrupt);
    PCA_PCA1_SetWorkMode(PCA_WorkMode_PWM_NonInterrupt);
    // Set both to 8-bit PWM
    PCA_PWM0_SetBitWidth(PCA_PWM_BitWidth_8);
    PCA_PWM1_SetBitWidth(PCA_PWM_BitWidth_8);
    // Set initial duty cycle
    PCA_PCA0_SetCompareValue(dc);
    PCA_PCA1_SetCompareValue(~dc);
    // Set output port for STC8G1K08A, PWM0:P32, PWM1:P33
    PCA_SetPort(PCA_AlterPort_G1K08A_P55_P32_P33_P54);
    // Start PWM
    PCA_SetCounterState(HAL_State_ON);

    while(1)
    {
        PCA_PCA0_ChangeCompareValue(dc);
        PCA_PCA1_ChangeCompareValue(~dc);
        UART1_TxHex(dc);
        UART1_TxChar(' ');
        UART1_TxHex(~dc);
        if (dir)
        {
            dc++;
            if (dc == 0xFF) dir = !dir;
        }
        else
        {
            dc--;
            if (dc == 0) dir = !dir;
        }
        UART1_TxString("\r\n");
        SYS_Delay(10);
    }
}