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
 * Demo: SSD1306/SSD1315 12864 OLED
 * Board: STC8H3K32
 * 
 *              P32   -> SCL
 *              P33   -> SDA
 *              GND   -> GND
 *              3.3V  -> VCC
 */

#include "fw_hal.h"
#include "ssd1306.h"

void I2C_Init(void)
{
    // Master mode
    I2C_SetWorkMode(I2C_WorkMode_Master);
    /**
     * I2C clock = FOSC / 2 / (__prescaler__ * 2 + 4)
     * SSD1306 works with i2c clock up to 1.3 MHz, beyond this value, display may fail.
    */
    I2C_SetClockPrescaler(0x10);
    // Switch alternative port
    I2C_SetPort(I2C_AlterPort_P32_P33);
    // Start I2C
    I2C_SetEnabled(HAL_State_ON);
}

void GPIO_Init(void)
{
    // SDA
    GPIO_P3_SetMode(GPIO_Pin_3, GPIO_Mode_InOut_QBD);
    // SCL
    GPIO_P3_SetMode(GPIO_Pin_2, GPIO_Mode_Output_PP);
}

int main(void)
{
    int y1, y2;
    uint8_t d1, d2;

    SYS_SetClock();
    GPIO_Init();
    I2C_Init();
    SSD1306_Init();

    while(1)
    {
        SSD1306_DrawLine(0,   0, 127,  0, 1);
        SSD1306_DrawLine(0,   0,   0, 63, 1);
        SSD1306_DrawLine(127, 0, 127, 63, 1);
        SSD1306_DrawLine(0,  63, 127, 63, 1);
        SSD1306_UpdateScreen(); // display
        SYS_Delay(1000);

        SSD1306_Fill(0);

        SSD1306_ToggleInvert(); // Invert display
        SSD1306_UpdateScreen();
        SYS_Delay(1000);

        SSD1306_ToggleInvert(); // Invert display
        SSD1306_UpdateScreen();
        SYS_Delay(1000);

        y1 = 64, y2 = 0;
        while (y1 > 0)
        {
            SSD1306_DrawLine(0, y1, 127, y2, 1);
            SSD1306_UpdateScreen();
            y1 -= 2;
            y2 += 2;
        }
        SYS_Delay(1000);

        SSD1306_Fill(0);
        y1 = 127, y2 = 0;
        while (y1 > 0)
        {
            SSD1306_DrawLine(y1, 0, y2, 63, 1);
            SSD1306_UpdateScreen();
            y1 -= 2;
            y2 += 2;
        }
        SYS_Delay(1000);
    }
}
