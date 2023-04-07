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
 * Demo:  LED Blink From All Ports(P0~P7)
 */

#include "fw_hal.h"

void GPIO_Init(void)
{
    GPIO_P0_SetMode(GPIO_Pin_All, GPIO_Mode_Output_PP);
    GPIO_P1_SetMode(GPIO_Pin_All, GPIO_Mode_Output_PP);
    GPIO_P2_SetMode(GPIO_Pin_All, GPIO_Mode_Output_PP);
    GPIO_P3_SetMode(GPIO_Pin_All, GPIO_Mode_Output_PP);
    GPIO_P4_SetMode(GPIO_Pin_All, GPIO_Mode_Output_PP);
    GPIO_P5_SetMode(GPIO_Pin_All, GPIO_Mode_Output_PP);
    GPIO_P6_SetMode(GPIO_Pin_All, GPIO_Mode_Output_PP);
    GPIO_P7_SetMode(GPIO_Pin_All, GPIO_Mode_Output_PP);
}

int main(void)
{
    SYS_SetClock();
    GPIO_Init();

    while(1)
    {
        P0 = 0xFF;
        P1 = 0xFF;
        P2 = 0xFF;
        P3 = 0xFF;
        P4 = 0xFF;
        P5 = 0xFF;
        P6 = 0xFF;
        P7 = 0xFF;
        SYS_Delay(500);

        P0 = 0x00;
        P1 = 0x00;
        P2 = 0x00;
        P3 = 0x00;
        P4 = 0x00;
        P5 = 0x00;
        P6 = 0x00;
        P7 = 0x00;
        SYS_Delay(500);
    }
}
