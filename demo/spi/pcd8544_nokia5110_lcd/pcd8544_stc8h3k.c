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
 * Demo:  PCD8544 - Nokia5110 84x48 LCD 
 * Board: STC8H3K32
 * 
 *              P37   -> RES, RESET
 *              P36   -> DC, A0
 *              P35   -> CE, Chip Select
 *              P32   -> SCK, SCL, CLK, Clock
 *              P12   -> BL, Backlight
 *              P34   -> MOSI, Din
 *              GND   -> GND
 *              3.3V  -> VCC
 */

#include "fw_hal.h"
#include "pcd8544.h"


void SPI_Init(void)
{
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
    uint8_t y1, y2;

    SYS_SetClock();
    GPIO_Init();
    SPI_Init();
    PCD8544_Init();

    while(1)
    {
        PCD8544_SetBackLightState(HAL_State_ON);
        SYS_Delay(500);
        PCD8544_SetDisplayAllOn();
        SYS_Delay(200);
        PCD8544_SetDisplayInverted();
        SYS_Delay(200);
        PCD8544_SetDisplayBlank();
        SYS_Delay(200);
        PCD8544_SetDisplayNormal();
        SYS_Delay(500);
        PCD8544_Fill(0);

        PCD8544_DrawLine(0,   0,  83,  0, 1);
        PCD8544_DrawLine(0,   0,   0, 47, 1);
        PCD8544_DrawLine(83,  0,  83, 47, 1);
        PCD8544_DrawLine(0,  47,  83, 47, 1);
        PCD8544_UpdateScreen();
        SYS_Delay(500);

        PCD8544_GotoXY(3, 3);
        PCD8544_Puts("LCD:PCD8544", &Font_5x7, 1);
        PCD8544_GotoXY(3, 11);
        PCD8544_Puts("STC8 FwLib", &Font_5x7, 1);
        PCD8544_GotoXY(3, 19);
        PCD8544_Puts("A demo of PCD8544", &Font_3x5, 1);
        PCD8544_GotoXY(3, 25);
        PCD8544_Puts("Font 3x5: 01234567890", &Font_3x5, 1);
        PCD8544_UpdateScreen();
        SYS_Delay(500);
        PCD8544_SetPowerDownMode(HAL_State_ON);
        SYS_Delay(1000);
        PCD8544_SetPowerDownMode(HAL_State_OFF);
        SYS_Delay(1000);
        PCD8544_SetDisplayInverted();
        SYS_Delay(1000);
        PCD8544_SetDisplayNormal();
        SYS_Delay(1000);

        for (y1 = 0x05; y1 < 0x08; y1++)
        {
            for (y2 = 0x00; y2 < 0x60; y2+=2)
            {
                PCD8544_GotoXY(3, 32);
                PCD8544_Putc(HEX_TABLE[y1 >> 4], &Font_5x7, 1);
                PCD8544_Putc(HEX_TABLE[y1 & 0x0F], &Font_5x7, 1);
                PCD8544_Putc(' ', &Font_5x7, 1);
                PCD8544_Putc(HEX_TABLE[y2 >> 4], &Font_5x7, 1);
                PCD8544_Putc(HEX_TABLE[y2 & 0x0F], &Font_5x7, 1);
                PCD8544_UpdateScreen();
                PCD8544_SetContrast(y1, y2);
                SYS_Delay(100);
            }
            SYS_Delay(1000);
        }
        PCD8544_SetContrast(0x06, 0x20);
        PCD8544_Fill(0);

        y1 = 47, y2 = 0;
        while (y1 < 0xF0)
        {
            PCD8544_DrawLine(0, y1, 83, y2, 1);
            PCD8544_UpdateScreen();
            y1 -= 2;
            y2 += 2;
            SYS_Delay(100);
        }
        SYS_Delay(1000);
        PCD8544_Fill(0);
        
        y1 = 83, y2 = 0;
        while (y1 < 0xF0)
        {
            PCD8544_DrawLine(y1, 0, y2, 47, 1);
            PCD8544_UpdateScreen();
            y1 -= 2;
            y2 += 2;
            SYS_Delay(100);
        }
        SYS_Delay(1000);

        PCD8544_Fill(0);
        PCD8544_UpdateScreen();
        SYS_Delay(1000);
        PCD8544_SetBackLightState(HAL_State_OFF);
        SYS_Delay(1000);
    }
}
