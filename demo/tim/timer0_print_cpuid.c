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

static uint16_t counter = 0;


uint8_t readCode(uint8_t offset)
{
    return (*(unsigned char volatile __CODE *)(__CID_ADDR + offset));
}

INTERRUPT(Timer0_Routine, EXTI_VectTimer0)
{
    uint8_t i, j;
    counter++;
    if (counter == 1000)
    {
        i = 0;
        counter = 0;
        UART1_TxString("ADDR: 0x");
        UART1_TxHex(__CID_ADDR >> 8);
        UART1_TxHex(__CID_ADDR & 0xFF);
        UART1_TxString("\r\n");
        UART1_TxString("       VER1     VER2\r\n");
        UART1_TxString("VRTRIM          40M:      ");
        UART1_TxHex(readCode(i++));
        UART1_TxString("\r\n");
        UART1_TxString("VRTRIM          24M:      ");
        UART1_TxHex(readCode(i++));
        UART1_TxString("\r\n");
        UART1_TxString("VRTRIM 35M      ??M:      ");
        UART1_TxHex(readCode(i++));
        UART1_TxString("\r\n");
        UART1_TxString("VRTRIM 20M      ??M:      ");
        UART1_TxHex(readCode(i++));
        UART1_TxString("\r\n");
        UART1_TxString("ITRIM  ---      45M:      ");
        UART1_TxHex(readCode(i++));
        UART1_TxString("\r\n");
        UART1_TxString("ITRIM  ---      40M:      ");
        UART1_TxHex(readCode(i++));
        UART1_TxString("\r\n");
        UART1_TxString("ITRIM 36.864M:            ");
        UART1_TxHex(readCode(i++));
        UART1_TxString("\r\n");
        UART1_TxString("ITRIM 35M:                ");
        UART1_TxHex(readCode(i++));
        UART1_TxString("\r\n");
        UART1_TxString("ITRIM 33.1776M:           ");
        UART1_TxHex(readCode(i++));
        UART1_TxString("\r\n");
        UART1_TxString("ITRIM 30M:                ");
        UART1_TxHex(readCode(i++));
        UART1_TxString("\r\n");
        UART1_TxString("ITRIM 27M:                ");
        UART1_TxHex(readCode(i++));
        UART1_TxString("\r\n");
        UART1_TxString("ITRIM 20M:                ");
        UART1_TxHex(readCode(i++));
        UART1_TxString("\r\n");
        UART1_TxString("ITRIM 24M:                ");
        UART1_TxHex(readCode(i++));
        UART1_TxString("\r\n");
        UART1_TxString("ITRIM 22.1184M:           ");
        UART1_TxHex(readCode(i++));
        UART1_TxString("\r\n");
        UART1_TxString("32kHz PD FreQ:            ");
        UART1_TxHex(readCode(i++));
        UART1_TxHex(readCode(i++));
        UART1_TxString("\r\n");
        UART1_TxString("1.19Vref:                 ");
        UART1_TxHex(readCode(i++));
        UART1_TxHex(readCode(i++));
        UART1_TxString("\r\n");
        UART1_TxString("\r\n");
        UART1_TxString("MCUID: ");
        for (j = 0; j < 7; j++)
        {
            UART1_TxHex(readCode(i+j));
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
    }
}

void main(void)
{
    // Set system clock. Remove this line if system clock is already set by STC-ISP
    SYS_SetClock();
    // UART1 configuration: baud 115200 with Timer2, 1T mode, no interrupt
    UART1_Config8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200);
    // Timer0 configuration: 16-bit auto-reload, interrupt enabled
    TIM_Timer0_Config(HAL_State_ON, TIM_TimerMode_16BitAuto, 1000);
    EXTI_Timer0_SetIntState(HAL_State_ON);
    EXTI_Timer0_SetIntPriority(EXTI_IntPriority_High);
    EXTI_Global_SetIntState(HAL_State_ON);
    TIM_Timer0_SetRunState(HAL_State_ON);

    while(1);
}