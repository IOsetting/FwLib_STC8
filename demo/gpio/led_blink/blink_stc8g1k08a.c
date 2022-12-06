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
 * Demo:  STC8G1K08A LED Blink
 * 
 *   Pin connection:
 * 
 *                   ___
 *            P5.4 -|   |- P3.3  <-- LED --> 4.7KR -> GND
 *   3.3V ->   VCC -|   |- P3.2  <-- LED --> 4.7KR -> GND
 *            P5.5 -|   |- TX
 *    GND ->   GND -|___|- RX   
 * 
 * 
 * test-board: Minimum System; test-MCU: STC8G1K08A
 */

#include "fw_hal.h"

void GPIO_Init(void)
{
    // P3.2, P3.3
    GPIO_P3_SetMode(GPIO_Pin_2|GPIO_Pin_3, GPIO_Mode_Output_PP);
}

int main(void)
{
    GPIO_Init();

    while(1)
    {
        /* Set by bit, P32 outputs high and P33 outputs low */
        P32 = SET;
        P33 = RESET;
        /**
         * Or set by byte
         * P3 = P3 & 0xF3 | 0x08;
        */
        SYS_Delay(500);

        /* Set by bit, P32 outputs low and P33 outputs high */
        P32 = RESET;
        P33 = SET;
        /**
         * Or set by byte
         * P3 = P3 & 0xF3 | 0x04;
        */
        SYS_Delay(500);
    }
}
