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

#ifndef __FW_PCD8544__
#define __FW_PCD8544__

#include "fw_hal.h"

/**
 * PCD8544
 * 
 * Philips – PCD8544 is a single-chip low-power CMOS LCD driver controller
 * The chip is designed to drive a graphic display of 84×48 pixels with SPI interface.
 * Display Data RAM = 6 banks x 84 segments x 8 bits = 4032 bits = 504 bytes
 *   Each bank contains 84 columns/segments (from 0 to 83)
 *   Each column can store 8 bits of data (from 0 to 7)
*/

#define PCD8544_CS           P35
#define PCD8544_MOSI         P34
#define PCD8544_SCK          P32
#define PCD8544_RES          P37
#define PCD8544_DC           P36
#define PCD8544_BL           P12

// X width
#define PCD8544_WIDTH  84
// Y height
#define PCD8544_HEIGHT 48
// Display RAM Pages
#define PCD8544_PAGES  6

#define PCD8544_FUNCTIONSET         0x20 // Function set
#define  PCD8544_POWERDOWN          0x04 // Function set, power down mode
#define  PCD8544_ENTRYMODE          0x02 // Function set, entry mode (vertical addressing)
#define  PCD8544_EXT_INSTRUCTION    0x01 // Function set, extended instruction set control

#define PCD8544_DISPLAY_CONTROL     0x08 // Basic instruction set - Set display configuration
#define  PCD8544_DISPLAY_BLANK      0x00 // Display control, blank
#define  PCD8544_DISPLAY_NORMAL     0x04 // Display control, normal mode
#define  PCD8544_DISPLAY_ALLON      0x01 // Display control, all segments on
#define  PCD8544_DISPLAY_INVERTED   0x05 // Display control, inverse mode

#define PCD8544_SET_YADDR           0x40 // Basic instruction set - Set Y address of RAM, 0 <= Y <= 5
#define PCD8544_SET_XADDR           0x80 // Basic instruction set - Set X address of RAM, 0 <= X <= 83

#define PCD8544_SET_TEMP            0x04 // Extended instruction set - Set temperature coefficient
#define PCD8544_SET_BIAS            0x10 // Extended instruction set - Set bias system
#define PCD8544_SET_VOP             0x80 // Extended instruction set - Write Vop to register

typedef struct {
    uint8_t width;
    uint8_t height;
    uint8_t order;
    uint8_t bytes;
    const uint8_t *dat;
} FontDef_t;

extern __CODE FontDef_t Font_3x5;
extern __CODE FontDef_t Font_5x7;

/**
 * @brief  Turn PCD8544 LCD backlight on or off
 * @param  state HAL_State_ON:on, HAL_State_OFF:off
 * @retval None
 */
void PCD8544_SetBackLightState(HAL_State_t state);

/**
 * @brief  Writes single byte data to PCD8544
 * @param  dat: data to be written
 * @retval None
 */
void PCD8544_WriteData(uint8_t dat);
void PCD8544_WriteSameData(uint8_t dat, uint32_t size);

/**
 * @brief  Write a single byte command to PCD8544
 * @param  command: command to be written
 * @retval None
 */
void PCD8544_WriteCommand(uint8_t command);

/**
 * @brief  Hardware reset PCD8544 LCD
 * @param  None
 * @retval None
 */
void PCD8544_Reset(void);

/**
 * @brief  Powerdown mode control
 * @param  state HAL_State_ON:powerdown mode, HAL_State_OFF:work mode
 * @retval None
 */
void PCD8544_SetPowerDownMode(HAL_State_t state);

/**
 * @brief  Set bias system level
 * @param  val bias value, [0x00,0x07], small value may lead to totally blank display
 * @retval None
 */
void PCD8544_SetBias(uint8_t val);

/**
 * @brief  Set TCx (temperature coefficient)
 * @param  val TCx value, [0x00, 0x03]
 * @retval None
 */
void PCD8544_SetTemperatureCoef(uint8_t val);

/**
 * @brief  Set the contrast level by adjusting Vlcd
 * @param  bias, bias value, [0x00,0x07], small value may lead to totally blank display
 * @param  val contrast level, [0x00, 0x7F]
 * @retval None
 */
void PCD8544_SetContrast(uint8_t bias, uint8_t val);

/**
 * @brief  Set PCD8544 To Turn On All Segments
 * @param  None
 * @retval None
 */
void PCD8544_SetDisplayAllOn(void);

/**
 * @brief  Set PCD8544 Display Mode to Inverted
 * @param  None
 * @retval None
 */
void PCD8544_SetDisplayInverted(void);

/**
 * @brief  Set PCD8544 Display Mode to Blank
 * @param  None
 * @retval None
 */
void PCD8544_SetDisplayBlank(void);

/**
 * @brief  Set PCD8544 Display Mode to Normal
 * @param  None
 * @retval None
 */
void PCD8544_SetDisplayNormal(void);

/**
 * @brief  Initializes PCD8544 Display
 * @param  None
 * @retval None
 */
void PCD8544_Init(void);

/** 
 * @brief  Fills entire LCD with specified color
 * @note   @ref PCD8544_UpdateScreen() must be called after that in order to see updates
 * @param  Color: Color to be used for screen fill, 0x00 or 0x01
 * @retval None
 */
void PCD8544_Fill(uint8_t color);

/** 
 * @brief  Update LCD display with changes
 * @note   Call this function each time when display is changed
 * @param  None
 * @retval None
 */
void PCD8544_UpdateScreen(void);

/**
 * @brief  Draws pixel at desired location
 * @note   @ref PCD8544_UpdateScreen() must called after that in order to show updates
 * @param  x: X location, value between [0, PCD8544_WIDTH)
 * @param  y: Y location, value between [0, PCD8544_HEIGHT)
 * @param  color: Color to be used for screen fill, 0x00 or 0x01
 * @retval None
 */
void PCD8544_DrawPixel(uint8_t x, uint8_t y, uint8_t color);

/**
 * @brief  Draws line on LCD
 * @note   @ref PCD8544_UpdateScreen() must be called after that in order to show updates
 * @param  x0: Line X start point, value between [0, PCD8544_WIDTH)
 * @param  y0: Line Y start point, value between [0, PCD8544_HEIGHT)
 * @param  x1: Line X end point, value between [0, PCD8544_WIDTH)
 * @param  y1: Line Y end point, value between [0, PCD8544_HEIGHT)
 * @param  color: Color to be used. 0x00 or 0x01
 * @retval None
 */
void PCD8544_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color);

/**
 * @brief  Sets cursor pointer to desired location for strings
 * @param  x: X location, value between [0, PCD8544_WIDTH)
 * @param  y: Y location, value between [0, PCD8544_HEIGHT)
 * @retval None
 */
void PCD8544_GotoXY(uint8_t x, uint8_t y);

/**
 * @brief  Put one character to internal RAM
 * @note   @ref PCD8544_UpdateScreen() must be called after that in order to show updates
 * @param  ch: Character to be written
 * @param  *Font: Pointer to @ref FontDef_t structure with used font
 * @param  color: Color used for drawing. 0x00 or 0x01
 * @retval value of ch
 */
char PCD8544_Putc(char ch, FontDef_t* font, uint8_t color);

/**
 * @brief  Puts string to internal RAM
 * @note   @ref PCD8544_UpdateScreen() must be called after that in order to show updates
 * @param  *str: String to be written
 * @param  *Font: Pointer to @ref FontDef_t structure with used font
 * @param  color: Color used for drawing. 0x00 or 0x01
 * @retval Zero on success or character value when function failed
 */
char PCD8544_Puts(char* str, FontDef_t* Font, uint8_t color);

#endif // __PCD8544_H_
