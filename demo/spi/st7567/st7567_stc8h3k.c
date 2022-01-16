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
 * Demo: ST7567 12864 LCD
 * Board: STC8H3K32
 * 
 *              P37   -> RES, RESET              7   - 18
 *              P36   -> DC, A0                  8   - 17
 *              P35   -> CSB, Chip Select        6   - 16
 *              P32   -> SCK, SCL, CLK, Clock    9   - 13
 *              P12   -> LED-A, Backlight        3   - 19
 *              P34   -> MOSI, SDA               10  - 15
 *              GND   -> GND
 *              3.3V  -> VCC
 */

#include "fw_hal.h"
#include "st7567.h"


void SPI_Init(void)
{
    // ST7567 doesn't work if SPI frequency is too high
    SPI_SetClockPrescaler(SPI_ClockPreScaler_16);
    // Clock is low when idle
    SPI_SetClockPolarity(HAL_State_OFF);
    // Data transfer is driven by lower SS pin
    SPI_SetClockPhase(SPI_ClockPhase_LeadingEdge);
    // MSB first
    SPI_SetDataOrder(SPI_DataOrder_MSB);
    // Define the output pins
    SPI_SetPort(SPI_AlterPort_P35_P34_P33_P32);
    // Ignore SS pin, use MSTR to swith between master/slave mode
    SPI_IgnoreSlaveSelect(HAL_State_ON);
    // Master mode
    SPI_SetMasterMode(HAL_State_ON);
    // Start SPI
    SPI_SetEnabled(HAL_State_ON);
}

void GPIO_Init(void)
{
    // Configure GPIO pins before SPI and device
    // DIN(P34)
    GPIO_P3_SetMode(GPIO_Pin_4, GPIO_Mode_InOut_QBD);
    // SCLK(P32)
    GPIO_P3_SetMode(GPIO_Pin_2|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7, GPIO_Mode_Output_PP);
    GPIO_P1_SetMode(GPIO_Pin_2, GPIO_Mode_Output_PP);
}

int main(void)
{
    int y1, y2;
    uint8_t d1, d2;

    SYS_SetClock();
    GPIO_Init();
    SPI_Init();
    ST7567_Init();

    while(1)
    {
        ST7567_DrawLine(0,   0, 127,  0, 1);
        ST7567_DrawLine(0,   0,   0, 63, 1);
        ST7567_DrawLine(127, 0, 127, 63, 1);
        ST7567_DrawLine(0,  63, 127, 63, 1);

        ST7567_GotoXY(3, 5);
        ST7567_Puts("LCD:ST7567", &Font_5x7, 1);
        ST7567_GotoXY(3, 13);
        ST7567_Puts("STC8 FwLib Demo", &Font_5x7, 1);
        ST7567_GotoXY(3, 21);
        ST7567_Puts("It's a demo of ST7567 12864 LCD", &Font_3x5, 1);
        ST7567_GotoXY(3, 27);
        ST7567_Puts("Font size 3x5, nums:01234567890", &Font_3x5, 1);
        ST7567_GotoXY(5, 52);
        ST7567_Puts("Font size: 5x7", &Font_5x7, 1);
        ST7567_UpdateScreen(); 
        SYS_Delay(2000);

        y1 = 10;
        while (y1 <= 0x30)
        {
            ST7567_SetContrast(y1++);
            SYS_Delay(100);
        }
        while (y1 >= 10)
        {
            ST7567_SetContrast(y1--);
            SYS_Delay(100);
        }
        while (y1 <= 0x20)
        {
            ST7567_SetContrast(y1++);
            SYS_Delay(100);
        }
        SYS_Delay(2000);

        ST7567_ToggleInvert();
        ST7567_UpdateScreen();
        SYS_Delay(2000);

        ST7567_ToggleInvert();
        ST7567_UpdateScreen();
        SYS_Delay(2000);

        ST7567_Fill(0);
        y1 = 64, y2 = 0;
        while (y1 > 0)
        {
            ST7567_DrawLine(0, y1, 127, y2, 1);
            ST7567_UpdateScreen();
            y1 -= 2;
            y2 += 2;
            SYS_Delay(100);
        }
        SYS_Delay(1000);

        ST7567_Fill(0);
        y1 = 127, y2 = 0;
        while (y1 > 0)
        {
            ST7567_DrawLine(y1, 0, y2, 63, 1);
            ST7567_UpdateScreen();
            y1 -= 2;
            y2 += 2;
            SYS_Delay(100);
        }
        SYS_Delay(1000);

        ST7567_Fill(0);
        ST7567_UpdateScreen();
        SYS_Delay(2000);
    }
}
