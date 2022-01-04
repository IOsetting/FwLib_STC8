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

/**
 * Demo: MAX7219 8x8 LED Matrix
 * Board: STC8H1K08
 * 
 * P1.3  -> DIN
 * P1.5  -> SCLK
 * P1.7  -> CS
*/

#include "fw_hal.h"

#define MAX7219_CS P17

#define DECODE_MODE  0x09
#define INTENSITY    0x0A
#define SCAN_LIMIT   0x0B
#define SHUT_DOWN    0x0C
#define DISPLAY_TEST 0x0F

const uint8_t numbers[]={
0x00,0x00,0x7C,0xC6,0xC6,0xCE,0xD6,0xD6,  // -0-.  
0xE6,0xC6,0xC6,0x7C,0x00,0x00,0x00,0x00,
0x00,0x00,0x18,0x38,0x78,0x18,0x18,0x18,  // -1-  
0x18,0x18,0x18,0x7E,0x00,0x00,0x00,0x00,  
0x00,0x00,0x7C,0xC6,0x06,0x0C,0x18,0x30,  // -2-  
0x60,0xC0,0xC6,0xFE,0x00,0x00,0x00,0x00,  
0x00,0x00,0x7C,0xC6,0x06,0x06,0x3C,0x06,  // -3-  
0x06,0x06,0xC6,0x7C,0x00,0x00,0x00,0x00,  
0x00,0x00,0x0C,0x1C,0x3C,0x6C,0xCC,0xFE,  // -4-  
0x0C,0x0C,0x0C,0x1E,0x00,0x00,0x00,0x00,  
0x00,0x00,0xFE,0xC0,0xC0,0xC0,0xFC,0x0E,  // -5-  
0x06,0x06,0xC6,0x7C,0x00,0x00,0x00,0x00,  
0x00,0x00,0x38,0x60,0xC0,0xC0,0xFC,0xC6,  // -6-  
0xC6,0xC6,0xC6,0x7C,0x00,0x00,0x00,0x00,  
0x00,0x00,0xFE,0xC6,0x06,0x06,0x0C,0x18,  // -7-  
0x30,0x30,0x30,0x30,0x00,0x00,0x00,0x00,  
0x00,0x00,0x7C,0xC6,0xC6,0xC6,0x7C,0xC6,  // -8-  
0xC6,0xC6,0xC6,0x7C,0x00,0x00,0x00,0x00, 
0x00,0x00,0x7C,0xC6,0xC6,0xC6,0x7E,0x06,  // -9-  
0x06,0x06,0x0C,0x78,0x00,0x00,0x00,0x00};

void MAX7219_write(uint8_t addr, uint8_t dat)
{
    MAX7219_CS = 0;
    SPI_TxRx(addr);
    SPI_TxRx(dat);
    MAX7219_CS = 1;
}

void MAX7219_init(void)
{
    MAX7219_write(SHUT_DOWN,    0x01);      // 0x00:shutdown, 0x01:normal
    MAX7219_write(DECODE_MODE,  0x00);      // Bypass code B decoder, no-decode operation
    MAX7219_write(SCAN_LIMIT,   0x07);      // Scan-limit, 0:1-digit, 1:2-digits, ... 7:8-digits
    MAX7219_write(INTENSITY,    0x01);      // 0x00:min, 0xFF:max
    MAX7219_write(DISPLAY_TEST, 0x00);      // 0x00:normal, 0x01:test mode
}

void SPI_init(void)
{
    // MAX7219 can work with frequency up to 20MHz
    SPI_SetClockPrescaler(SPI_ClockPreScaler_4);
    // Clock idles low
    SPI_SetClockPolarity(HAL_State_OFF);
    // Data transfer is driven by lower SS pin
    SPI_SetClockPhase(SPI_ClockPhase_LeadingEdge);
    // MSB first
    SPI_SetDataOrder(SPI_DataOrder_MSB);
    // Define the output pins
    SPI_SetPort(SPI_AlterPort_P12P54_P13_P14_P15);
    // Ignore SS pin, use MSTR to swith between master/slave mode
    SPI_IgnoreSlaveSelect(HAL_State_ON);
    // Master mode
    SPI_SetMasterMode(HAL_State_ON);
    // Start SPI
    SPI_SetEnabled(HAL_State_ON);
}

void main()
{
    uint8_t pos = 0, size = sizeof(numbers), i, j;

    SYS_SetClock();
    // Configure GPIO pins before SPI and device
    GPIO_P1_SetMode(GPIO_Pin_3, GPIO_Mode_InOut_QBD);
    GPIO_P1_SetMode(GPIO_Pin_5|GPIO_Pin_7, GPIO_Mode_Output_PP);
    // Configure SPI and device
    SPI_init();
    MAX7219_init();

    while(1)
    {
        for (i = 0; i < 8; i++)
        {
            j = (pos + i) % size;
            MAX7219_write(i + 1, numbers[j]);
        }
        pos = (pos + 1) % size;
        SYS_Delay(100);
    }
}