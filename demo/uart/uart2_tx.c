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

void main(void)
{
    SYS_SetClock();
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