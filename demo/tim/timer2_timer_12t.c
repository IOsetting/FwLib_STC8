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

INTERRUPT(Timer2_Routine, EXTI_VectTimer2)
{
    UART1_TxString("hello\r\n");
}

void main(void)
{
    SYS_SetClock();
    // UART1 configuration: baud 115200 with Timer1, 1T mode, no interrupt
    UART1_Config8bitUart(UART1_BaudSource_Timer1, HAL_State_ON, 115200);
    // 12T mode, prescaler:255+1, frequency: 1, interrupt: ON
    TIM_Timer2_Config(HAL_State_OFF, 0xFF, 1);
    EXTI_Timer2_SetIntState(HAL_State_ON);
    EXTI_Global_SetIntState(HAL_State_ON);
    TIM_Timer2_SetRunState(HAL_State_ON);

    while(1);
}