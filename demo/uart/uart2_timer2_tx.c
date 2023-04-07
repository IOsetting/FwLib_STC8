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
 * Demo:  UART2 TX
 * 
 *   Pin connection:
 *   STC8G/STC8H       USB2TTL
 *   P10            -> TX
 *   P11            -> RX
 */
#include "fw_hal.h"

void main(void)
{
    SYS_SetClock();
    // P10:RX, P11:TX
    UART2_SwitchPort(UART2_AlterPort_P10_P11);
    // GPIO Config
    GPIO_P1_SetMode(GPIO_Pin_0|GPIO_Pin_1, GPIO_Mode_InOut_QBD);
    // UART2, baud 115200, baud source Timer2, 1T mode, no interrupt
    UART2_Set8bitUART();
    UART2_Config(HAL_State_ON, 115200);
    while(1)
    {
        UART2_TxChar('T');
        UART2_TxHex(0x41);
        UART2_TxString("U");
        UART2_TxString(" string\r\n");
        SYS_Delay(1000);
    }
}