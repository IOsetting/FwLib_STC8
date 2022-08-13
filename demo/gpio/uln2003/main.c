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
 * Demo:  28BYJ-48 Stepper Motor with ULN2003 Driver
 * 
 *    Pin connection:
 *    MCU          ULN2003       External Power Supply
 *    P10           => IN1
 *    P11           => IN2
 *    P12           => IN3
 *    P13           => IN4       
 *                     VCC   =>  5V ~ 12V
 *                     GND   =>  GND
 * 
 * test-board: Minimum System; test-MCU: STC8H1K08,STC8H3K64S2
 */

#include "fw_hal.h"

// Clockwise, 8 steps
uint8_t cw[8]={
    0B00001001,
    0B00000001,
    0B00000011,
    0B00000010,
    0B00000110,
    0B00000100,
    0B00001100,
    0B00001000
};

void GPIO_Init(void)
{
    // P10, P11, P12, P13
    GPIO_P1_SetMode(GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3, GPIO_Mode_Output_PP);
}

int main(void)
{
    uint8_t step;
    uint16_t pos;
    SYS_SetClock();
    GPIO_Init();

    while(1)
    {
        for (pos = 0; pos < 640; pos++)
        {
            step = 8;
            while (step--)
            {
                P1 = P1 & 0xF0 | cw[7 - step];
                SYS_Delay(5);
            }
        }
        SYS_Delay(500);
        for (pos = 0; pos < 640; pos++)
        {
            step = 8;
            while (step--)
            {
                P1 = P1 & 0xF0 | cw[step];
                SYS_Delay(5);
            }
        }
        SYS_Delay(500);
    }
}
