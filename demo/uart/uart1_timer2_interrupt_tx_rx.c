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

extern char UART1_RxBuffer[UART_RX_BUFF_SIZE];

INTERRUPT(UART1_Routine, EXTI_VectUART1)
{
    UART1_InterruptHandler();
}

void main(void)
{
    SYS_SetClock();
    // UART1, baud 115200, baud source Timer2, 1T mode, interrupt on
    UART1_Config8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200);
    UART1_SetRxState(HAL_State_ON);
    // Enable UART1 interrupt
    EXTI_Global_SetIntState(HAL_State_ON);
    EXTI_UART1_SetIntState(HAL_State_ON);
    while(1)
    {
        UART1_IntTxChar('R');
        UART1_IntTxChar('X');
        UART1_IntTxChar(':');
        for (uint8_t i = 0; i < UART_RX_BUFF_SIZE; i++) UART1_IntTxChar(UART1_RxBuffer[i]);
        UART1_IntTxChar(' ');
        UART1_IntTxHex(0x41);
        UART1_IntTxHex('A');
        UART1_IntTxString(" string\r\n");
        SYS_Delay(1000);
    }
}