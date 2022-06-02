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

#ifndef __FW_ST7567__
#define __FW_ST7567__

#include "fw_hal.h"

/**
 * ST7565, ST7567
 * 
 * Display Data RAM has a matrix of 65 by 132 bits. The address ranges are: 
 * X=0~131(83H) (column address), Y=0~8 (page address)
 * 
*/

#define ST7567_MODEL        ST7567_MODEL_ST7567

#define ST7567_CS           P35
#define ST7567_MOSI         P34
#define ST7567_SCK          P32
#define ST7567_RES          P37
#define ST7567_DC           P36
#define ST7567_BL           P12

// X width
#define ST7567_WIDTH  128
// Y height
#define ST7567_HEIGHT 64
// Display RAM Columns
#define ST7567_COLUMN_EXPAND  4
// Display RAM Pages (8x8bit + 1bit)
#define ST7567_PAGES 8
// X orientation
#define ST7567_X_ORIENT ST7567_SEG_DIRECTION_NORMAL
// Y orientation
#define ST7567_Y_ORIENT ST7567_COM_DIRECTION_NORMAL

#define ST7567_MODEL_ST7565                  0
#define ST7567_MODEL_ST7567                  1

/* ST7567 commands definitions */
#define ST7567_DISPLAY_OFF                   0xAE /* 0xae: Display OFF (sleep mode), default */
#define ST7567_DISPLAY_ON                    0xAF /* 0xaf: Display ON in normal mode */

#define ST7567_SET_START_LINE                0x40 /* 0x40-7f: Set display start line */
#define  ST7567_SET_START_LINE_MASK          0x3f

#define ST7567_SET_PAGE_ADDRESS              0xB0 /* 0xb0-b7: Set page start address, 0 - 8 */
#define  ST7567_SET_PAGE_ADDRESS_MASK        0x07

#define ST7567_SET_COLUMN_ADDRESS_MSB        0x10 /* 0x10-0x1f: Set 8bit column address - high 4 bits of 0 - 131 */
#define  ST7567_SET_COLUMN_ADDRESS_MSB_MASK  0x0F

#define ST7567_SET_COLUMN_ADDRESS_LSB        0x00 /* 0x00-0x0f: Set 8bit column address - low 4 bits of 0 - 131 */
#define  ST7567_SET_COLUMN_ADDRESS_LSB_MASK  0x0F

#define ST7567_SEG_DIRECTION_NORMAL          0xA0 /* 0xa0: Column address 0 is mapped to SEG0, default*/
#define ST7567_SEG_DIRECTION_REVERSE         0xA1 /* 0xa1: Column address 83H(131) is mapped to SEG0 */

#define ST7567_COM_DIRECTION_NORMAL          0xC0 /* 0xc0: Set COM output direction, normal mode */
#define ST7567_COM_DIRECTION_REVERSE         0xC8 /* 0xc8: Set COM output direction, reverse mode */

#define ST7567_INVERSE_DISPLAY_OFF           0xA6 /* 0xa6: Normal display */
#define ST7567_INVERSE_DISPLAY_ON            0xA7 /* 0xa7: Inverse display */

#define ST7567_ALL_PIXEL_ON                  0xA5 /* 0xa5: Entire display ON */
#define ST7567_ALL_PIXEL_NORMAL              0xA4 /* 0xa4: Resume to RAM content display */

                                                  /* LCD bias set */
#define ST7567_BIAS_1_9                      0xA2 /* 0xa2: Select BIAS setting 1/9 */
#define ST7567_BIAS_1_7                      0xA3 /* 0xa3: Select BIAS setting 1/7 */

#define ST7567_READ_MODIFY_WRITE_START       0xE0 /* 0xe0: Enter the Read Modify Write mode */
#define ST7567_READ_MODIFY_WRITE_END         0xEE /* 0xee: Leave the Read Modify Write mode */

#define ST7567_RESET                         0xE2 /* 0xe2: Software RESET */

/**
 * This instruction controls the built-in power circuits. 
 * Typically, these 3 flags are turned ON at the same time.
*/
#define ST7567_POWER_CONTROL                 0x28
#define ST7567_POWER_CONTROL_VF              0x01
#define ST7567_POWER_CONTROL_VR              0x02
#define ST7567_POWER_CONTROL_VB              0x04

/**
 * The operation voltage (V0) calculation formula is shown below: 
 * (RR comes from Regulation Ratio, EV comes from EV[5:0])
 * V0 = RR X [ 1 – (63 – EV) / 162 ] X 2.1, or 
 * V0 = RR X [ ( 99 + EV ) / 162 ] X 2.1
*/
#define ST7567_REGULATION_RATIO              0x20
#define ST7567_REGULATION_RATIO_3_0          0x00
#define ST7567_REGULATION_RATIO_3_5          0x01
#define ST7567_REGULATION_RATIO_4_0          0x02
#define ST7567_REGULATION_RATIO_4_5          0x03
#define ST7567_REGULATION_RATIO_5_0          0x04 /* Default */
#define ST7567_REGULATION_RATIO_5_5          0x05
#define ST7567_REGULATION_RATIO_6_0          0x06
#define ST7567_REGULATION_RATIO_6_5          0x07

/**
 * This is double byte instruction. The first byte set ST7567 into EV 
 * adjust mode and the following instruction will change the EV setting. 
 * That means these 2 bytes must be used together. They control the electronic 
 * volume to adjust a suitable V0 voltage for the LCD.
*/
#define ST7567_SET_EV                        0x81
#define ST7567_SET_EV_MASK                   0x3F

#if (ST7567_MODEL == ST7567_MODEL_ST7565)
    #define ST7567_MODE_SLEEP                0xAC
    #define ST7567_MODE_NORMAL               0xAD
#endif

#define ST7567_SET_BOOSTER                   0xF8 /* Set booster level */
#define ST7567_SET_BOOSTER_4X                0x00
#define ST7567_SET_BOOSTER_5X                0x01
#define ST7567_SET_BOOSTER_6X                0x11

#define ST7567_NOP                           0xE3
#define ST7567_TEST                          0xFE


#ifndef ST7567_TIMEOUT
#define ST7567_TIMEOUT					20000
#endif

/** Front color */
#define ST7567_COLOR_FRONT 1U
/** Background color */
#define ST7567_COLOR_BACK  0U


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
 * @brief  Write a single byte data to ST7567
 * @param  dat: data
 * @retval None
 */
void ST7567_WriteData(uint8_t dat);
void ST7567_WriteSameData(uint8_t dat, uint32_t size);

/**
 * @brief  Write a single byte command to ST7567
 * @param  command: command
 * @retval None
 */
void ST7567_WriteCommand(uint8_t command);

/**
 * @brief  Hardware reset ST7567 LCD
 * @param  None
 * @retval None
 */
void ST7567_Reset(void);

/**
 * @brief  Initializes ST7567 LCD
 * @param  None
 * @retval None
 */
void ST7567_Init(void);

/**
 * @brief  Powersave mode control
 * @param  state HAL_State_ON:powersave mode, HAL_State_OFF:work mode
 * @retval None
 */
void ST7567_SetPowerSaveMode(HAL_State_t state);


/**
 * @brief  Turn ST7567 LCD backlight on or off
 * @param  state HAL_State_ON:on, HAL_State_OFF:off
 * @retval None
 */
void ST7567_SetBackLightState(HAL_State_t state);

/**
 * @brief  Turn ST7567 LCD backlight off
 * @param  val: value between 0x00 ~ 0x3F
 * @retval None
 */
void ST7567_SetContrast(uint8_t val);

/** 
 * @brief  Update LCD display with buffer changes
 * @note   Call this function each time when display is changed
 * @param  None
 * @retval None
 */
void ST7567_UpdateScreen(void);

/**
 * @brief  Toggles pixels invertion inside internal RAM
 * @note   @ref ST7567_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  None
 * @retval None
 */
void ST7567_ToggleInvert(void);

/** 
 * @brief  Fills entire LCD with specified color
 * @note   @ref ST7567_UpdateScreen() must be called after that in order to see updates
 * @param  Color: Color to be used for screen fill, ST7567_COLOR_FRONT or ST7567_COLOR_BACK
 * @retval None
 */
void ST7567_Fill(uint8_t Color);

/**
 * @brief  Draws pixel at desired location
 * @note   @ref ST7567_UpdateScreen() must called after that in order to see updates
 * @param  x: X location. This parameter can be a value between 0 and ST7567_WIDTH - 1
 * @param  y: Y location. This parameter can be a value between 0 and ST7567_HEIGHT - 1
 * @param  color: Color to be used for screen fill. This parameter can be a value of @ref ST7567_COLOR_t enumeration
 * @retval None
 */
void ST7567_DrawPixel(uint8_t x, uint8_t y, uint8_t color);

/**
 * @brief  Sets cursor pointer to desired location for strings
 * @param  x: X location. This parameter can be a value between 0 and ST7567_WIDTH - 1
 * @param  y: Y location. This parameter can be a value between 0 and ST7567_HEIGHT - 1
 * @retval None
 */
void ST7567_GotoXY(uint16_t x, uint16_t y);

/**
 * @brief  Puts character to internal RAM
 * @note   @ref ST7567_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  ch: Character to be written
 * @param  *Font: Pointer to @ref FontDef_t structure with used font
 * @param  color: Color used for drawing. This parameter can be a value of @ref ST7567_COLOR_t enumeration
 * @retval Character written
 */
char ST7567_Putc(char ch, FontDef_t* Font, uint8_t color);

/**
 * @brief  Puts string to internal RAM
 * @note   @ref ST7567_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  *str: String to be written
 * @param  *Font: Pointer to @ref FontDef_t structure with used font
 * @param  color: Color used for drawing. This parameter can be a value of @ref ST7567_COLOR_t enumeration
 * @retval Zero on success or character value when function failed
 */
char ST7567_Puts(char* str, FontDef_t* Font, uint8_t color);

/**
 * @brief  Draws line on LCD
 * @note   @ref ST7567_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x0: Line X start point. Valid input is 0 to ST7567_WIDTH - 1
 * @param  y0: Line Y start point. Valid input is 0 to ST7567_HEIGHT - 1
 * @param  x1: Line X end point. Valid input is 0 to ST7567_WIDTH - 1
 * @param  y1: Line Y end point. Valid input is 0 to ST7567_HEIGHT - 1
 * @param  c: Color to be used. This parameter can be a value of @ref ST7567_COLOR_t enumeration
 * @retval None
 */
void ST7567_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t c);

#endif // __ST7567_H_
