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
 * Demo: MAX7219 8x8 LED Matrix 4 in 1
 * Board: STC8H1K08
 * 
 * P1.3  -> DIN
 * P1.5  -> SCLK
 * P1.7  -> CS
*/

/**
 * 
 * PlatformIO configuration example

[env:stc8g1k08]
platform = intel_mcs51
board = stc8g1k08
build_flags =
    -D__CONF_FOSC=36864000UL
    -D__CONF_MCU_MODEL=MCU_MODEL_STC8G1K08
    -D__CONF_CLKDIV=0x00
    -D__CONF_IRCBAND=0x01
    -D__CONF_VRTRIM=0x20
    -D__CONF_IRTRIM=0xA3
    -D__CONF_LIRTRIM=0x03
upload_protocol = custom
upload_port = /dev/ttyUSB0
upload_speed = 115200
upload_flags =
    -p$UPLOAD_PORT
    -s$UPLOAD_SPEED
    -e
upload_command = ${platformio.packages_dir}/tool-stc8prog/stc8prog $UPLOAD_FLAGS -f $SOURCE

*/

#include "fw_hal.h"

#define MAX7219_CS P17
#define MAX7219_BLOCKS       4

#define DECODE_MODE  0x09
#define INTENSITY    0x0A
#define SCAN_LIMIT   0x0B
#define SHUT_DOWN    0x0C
#define DISPLAY_TEST 0x0F

const uint8_t numbers[]={
  0x3e,0x63,0x63,0x7f,0x63,0x63,0x63,0x63, //A
  0x7e,0x63,0x63,0x7e,0x63,0x63,0x63,0x7e, //B
  0x3e,0x63,0x63,0x60,0x60,0x63,0x63,0x3e, //C
  0x7e,0x63,0x63,0x63,0x63,0x63,0x63,0x7e, //D
  0x7f,0x60,0x60,0x7f,0x60,0x60,0x60,0x7f, //E
  0x7f,0x60,0x60,0x7e,0x60,0x60,0x60,0x60, //F
  0x3e,0x63,0x63,0x60,0x67,0x63,0x63,0x3e, //G
  0x63,0x63,0x63,0x7f,0x63,0x63,0x63,0x63, //H
  0x3f,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x3f, //I
  0x1f,0x06,0x06,0x06,0x06,0x66,0x66,0x3c, //J
  0x63,0x66,0x6c,0x78,0x6c,0x66,0x63,0x61, //K
  0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x7f, //L
  0x63,0x77,0x7f,0x6b,0x63,0x63,0x63,0x63, //M
  0x63,0x63,0x73,0x7b,0x6f,0x67,0x63,0x63, //N
  0x3e,0x63,0x63,0x63,0x63,0x63,0x63,0x3e, //O
  0x7e,0x63,0x63,0x63,0x7e,0x60,0x60,0x60, //P
  0x3c,0x66,0x66,0x66,0x66,0x6e,0x66,0x3f, //Q
  0x7e,0x63,0x63,0x63,0x7e,0x6c,0x66,0x63, //R
  0x3e,0x63,0x63,0x60,0x3e,0x03,0x63,0x3e, //S
  0x3f,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c, //T
  0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x3e, //U
  0x63,0x63,0x63,0x63,0x63,0x36,0x1c,0x08, //V
  0x63,0x63,0x63,0x63,0x6b,0x7f,0x77,0x63, //W
  0x63,0x63,0x36,0x1c,0x1c,0x36,0x63,0x63, //X
  0x33,0x33,0x33,0x33,0x1e,0x0c,0x0c,0x0c, //Y
  0x7f,0x03,0x06,0x0c,0x18,0x30,0x60,0x7f, //Z
  0x3e,0x63,0x73,0x6b,0x67,0x63,0x63,0x3e, //0
  0x0c,0x1c,0x3c,0x0c,0x0c,0x0c,0x0c,0x3f, //1
  0x3e,0x63,0x63,0x06,0x0c,0x18,0x30,0x7f, //2
  0x3e,0x63,0x63,0x0e,0x03,0x63,0x63,0x3e, //3
  0x06,0x0e,0x1e,0x36,0x66,0x7f,0x06,0x06, //4
  0x7f,0x60,0x60,0x7e,0x03,0x03,0x03,0x7e, //5
  0x3e,0x63,0x60,0x7e,0x63,0x63,0x63,0x3e, //6
  0x7f,0x03,0x03,0x06,0x0c,0x18,0x18,0x18, //7
  0x3e,0x63,0x63,0x3e,0x63,0x63,0x63,0x3e, //8
  0x3e,0x63,0x63,0x63,0x3f,0x03,0x63,0x3e, //9
};

uint8_t val[MAX7219_BLOCKS];
uint8_t character_len = sizeof(numbers) / 8;

void MAX7219_singeWrite(uint8_t index, uint8_t addr, uint8_t dat)
{
    index = index % MAX7219_BLOCKS;
    MAX7219_CS = 0;
    SPI_TxRx(addr);
    SPI_TxRx(dat);
    while(index--)
    {
        SPI_TxRx(addr);
        SPI_TxRx(dat);
    }
    MAX7219_CS = 1;
}

void MAX7219_multiWrite(uint8_t addr, uint8_t len, uint8_t* dat)
{
    MAX7219_CS = 0;
    while (len--)
    {
        SPI_TxRx(addr);
        SPI_TxRx(*dat++);
    }
    MAX7219_CS = 1;
}

void MAX7219_init(void)
{
    for (uint8_t i = 0; i < MAX7219_BLOCKS; i++)
    {
        MAX7219_singeWrite(i, SHUT_DOWN, 0x01);    // 0x00:shutdown, 0x01:normal
        MAX7219_singeWrite(i, DECODE_MODE, 0x00);  // Bypass code B decoder, no-decode operation
        MAX7219_singeWrite(i, SCAN_LIMIT, 0x07);   // Scan-limit, 0:1-digit, 1:2-digits, ..., 7:8-digits
        MAX7219_singeWrite(i, INTENSITY, 0x00);    // 0x00:min, 0xFF:max
        MAX7219_singeWrite(i, DISPLAY_TEST, 0x00); // 0x00:normal, 0x01:test mode
    }
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
    /**
     *    ________________________
     *    |                       |
     *    |_______________________|
     *    A                       B
     * 
     * pos: point to the bit for boundary A
     * lpos: point to the bit for boundary B
    */
    uint16_t pos = 0, lpos = 0;
    uint8_t i, j, cpos = 0, bpos = 0, tcpos = 0;

    SYS_SetClock();
    // Configure GPIO pins before SPI and device
    // DIN(P13)
    GPIO_P1_SetMode(GPIO_Pin_3, GPIO_Mode_InOut_QBD);
    // SCLK(P15), CS(P17) 
    GPIO_P1_SetMode(GPIO_Pin_5|GPIO_Pin_7, GPIO_Mode_Output_PP);
    // Configure SPI and device
    SPI_init();
    MAX7219_init();

    while(1)
    {
        lpos = pos + sizeof(numbers) - MAX7219_BLOCKS * 8;
        cpos = lpos / 8;        // char position
        bpos = lpos % 8;        // bit position
        for (i = 0; i < 8; i++) // fill each line
        {
            for (j = 0; j < MAX7219_BLOCKS; j++)
            {
                tcpos = (cpos + j) % character_len;
                val[j] = numbers[tcpos * 8 + i] << bpos;
                tcpos = (cpos + j + 1) % character_len;
                val[j] |= numbers[tcpos * 8 + i] >> (8 - bpos);
            }
            MAX7219_multiWrite(i + 1, MAX7219_BLOCKS, val);
        }
        pos = (pos + 1) % sizeof(numbers);
        SYS_Delay(50);
    }
}