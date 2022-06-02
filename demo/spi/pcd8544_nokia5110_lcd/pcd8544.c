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

#include "pcd8544.h"
#include <string.h>

/* PCD8544 data buffer */
uint8_t PCD8544_currentX = 0;
uint8_t PCD8544_currentY = 0;
static __XDATA uint8_t PCD8544_Buffer[PCD8544_WIDTH * PCD8544_HEIGHT / 8];

void PCD8544_WriteData(uint8_t dat)
{
    PCD8544_CS = 0;
    SPI_TxRx(dat);
    PCD8544_CS = 1;
}

void PCD8544_WriteSameData(uint8_t dat, uint32_t size)
{
    PCD8544_CS = 0;
    do
    {
        SPI_TxRx(dat);
    } while (--size);
    PCD8544_CS = 1;
}

void PCD8544_WriteCommand(uint8_t command)
{
    PCD8544_DC = 0;
    PCD8544_WriteData(command);
    PCD8544_DC = 1;
}

static void PCD8544_Transmit(const uint8_t *pDat, uint32_t size)
{
    PCD8544_CS = 0;
    do
    {
        SPI_TxRx(*pDat++);
    } while (--size);
    PCD8544_CS = 1;
}

void PCD8544_Reset(void)
{
    PCD8544_RES = 0;
    SYS_Delay(5);
    PCD8544_RES = 1;
}

void PCD8544_SetPowerDownMode(HAL_State_t state)
{
    if (state == HAL_State_ON)
        PCD8544_WriteCommand(PCD8544_FUNCTIONSET | PCD8544_POWERDOWN);
    else
        PCD8544_WriteCommand(PCD8544_FUNCTIONSET);
}

void PCD8544_clear(void)
{
    PCD8544_WriteCommand(0x0c);
    PCD8544_WriteCommand(0x80);
    PCD8544_WriteSameData(0x00, PCD8544_WIDTH * PCD8544_HEIGHT);
}

void PCD8544_SetBias(uint8_t val)
{
    val = val & 0x07;
    PCD8544_WriteCommand(PCD8544_FUNCTIONSET | PCD8544_EXT_INSTRUCTION);
    PCD8544_WriteCommand(PCD8544_SET_BIAS | val);
    PCD8544_WriteCommand(PCD8544_FUNCTIONSET);
}

void PCD8544_SetContrast(uint8_t bias, uint8_t val)
{
    bias = bias & 0x07;
    val = val & 0x7F;
    // Extended instruction set
    PCD8544_WriteCommand(PCD8544_FUNCTIONSET | PCD8544_EXT_INSTRUCTION);
    // Set Bias System, value can be [0x03, 0x07]
    PCD8544_WriteCommand(PCD8544_SET_BIAS | bias);
    // Set Vop, value can be [0x01, 0x7F]
    PCD8544_WriteCommand(PCD8544_SET_VOP | val);
    // Change back to basic instruction set
    PCD8544_WriteCommand(PCD8544_FUNCTIONSET);
}

void PCD8544_SetTemperatureCoef(uint8_t val)
{
    val = val & 0x03;
    PCD8544_WriteCommand(PCD8544_FUNCTIONSET | PCD8544_EXT_INSTRUCTION);
    PCD8544_WriteCommand(PCD8544_SET_TEMP | val);
    PCD8544_WriteCommand(PCD8544_FUNCTIONSET);
}

void PCD8544_SetDisplayAllOn(void)
{
    PCD8544_WriteCommand(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_ALLON);
}

void PCD8544_SetDisplayInverted(void)
{
    PCD8544_WriteCommand(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_INVERTED);
}

void PCD8544_SetDisplayBlank(void)
{
    PCD8544_WriteCommand(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_BLANK);
}

void PCD8544_SetDisplayNormal(void)
{
    PCD8544_WriteCommand(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_NORMAL);
}

void PCD8544_Init(void)
{
    PCD8544_Reset();
    PCD8544_SetContrast(0x06, 0x3F);
    PCD8544_SetDisplayNormal();
}

void PCD8544_SetBackLightState(HAL_State_t state)
{
    PCD8544_BL = (state == HAL_State_ON)? SET : RESET;
}

void PCD8544_Fill(uint8_t color)
{
    /* Set memory */
    memset((uint8_t *)PCD8544_Buffer, (color == 0x00) ? 0x00 : 0xFF, sizeof(PCD8544_Buffer));
}

void PCD8544_UpdateScreen(void)
{
    uint8_t i = 0, *pt = PCD8544_Buffer;
    for (i = 0; i < PCD8544_PAGES; i++)
    {
        PCD8544_WriteCommand(PCD8544_SET_YADDR | i);
        PCD8544_WriteCommand(PCD8544_SET_XADDR);
        PCD8544_Transmit(pt + (PCD8544_WIDTH * i), PCD8544_WIDTH);
    }
    PCD8544_WriteCommand(PCD8544_SET_YADDR);
}

void PCD8544_DrawPixel(uint8_t x, uint8_t y, uint8_t color)
{
    if (x >= PCD8544_WIDTH || y >= PCD8544_HEIGHT)
    {
        /* Error */
        return;
    }

    if (color == 0x01)
    {
        PCD8544_Buffer[x + (y / 8) * PCD8544_WIDTH] |= 1 << (y % 8);
    }
    else
    {
        PCD8544_Buffer[x + (y / 8) * PCD8544_WIDTH] &= ~(1 << (y % 8));
    }
}

void PCD8544_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color)
{
    int16_t dx, dy, sx, sy, err, e2, i, tmp; 
    
    /* Check for overflow */
    if (x0 >= PCD8544_WIDTH)
    {
        x0 = PCD8544_WIDTH - 1;
    }
    if (x1 >= PCD8544_WIDTH)
    {
        x1 = PCD8544_WIDTH - 1;
    }
    if (y0 >= PCD8544_HEIGHT)
    {
        y0 = PCD8544_HEIGHT - 1;
    }
    if (y1 >= PCD8544_HEIGHT)
    {
        y1 = PCD8544_HEIGHT - 1;
    }
    
    dx = (x0 < x1) ? (x1 - x0) : (x0 - x1); 
    dy = (y0 < y1) ? (y1 - y0) : (y0 - y1); 
    sx = (x0 < x1) ? 1 : -1; 
    sy = (y0 < y1) ? 1 : -1; 
    err = ((dx > dy) ? dx : -dy) / 2; 

    if (dx == 0)
    {
        if (y1 < y0)
        {
            tmp = y1;
            y1 = y0;
            y0 = tmp;
        }
        
        if (x1 < x0)
        {
            tmp = x1;
            x1 = x0;
            x0 = tmp;
        }
        
        /* Vertical line */
        for (i = y0; i <= y1; i++)
        {
            PCD8544_DrawPixel(x0, i, color);
        }
        return;
    }
    
    if (dy == 0)
    {
        if (y1 < y0)
        {
            tmp = y1;
            y1 = y0;
            y0 = tmp;
        }
        
        if (x1 < x0)
        {
            tmp = x1;
            x1 = x0;
            x0 = tmp;
        }
        
        /* Horizontal line */
        for (i = x0; i <= x1; i++)
        {
            PCD8544_DrawPixel(i, y0, color);
        }
        return;
    }

    while (1)
    {
        PCD8544_DrawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1)
        {
            break;
        }
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void PCD8544_GotoXY(uint8_t x, uint8_t y)
{
    /* Set write pointers */
    PCD8544_currentX = x;
    PCD8544_currentY = y;
}

char PCD8544_Putc(char ch, FontDef_t* font, uint8_t color)
{
    uint32_t i, b, j, k;

    for (i = 0; i < font->height; i++)
    {
        for (j = 0; j < font->bytes; j++)
        {
            b = font->dat[((ch - 32) * font->height + i) * font->bytes + j];
            if (font->order == 0)
            {
                for (k = 0; k < 8 && k < font->width - j * 8; k++)
                {
                    if ((b << k) & 0x80)
                    {
                        PCD8544_DrawPixel(PCD8544_currentX + (j * 8) + k, (PCD8544_currentY + i), (uint8_t) color);
                    }
                    else
                    {
                        PCD8544_DrawPixel(PCD8544_currentX + (j * 8) + k, (PCD8544_currentY + i), (uint8_t) !color);
                    }
                }
            }
            else
            {
                for (k = 0; k < 8 && k < font->width - j * 8; k++)
                {
                    if (b & (0x0001 << k))
                    {
                        PCD8544_DrawPixel(PCD8544_currentX + (j * 8) + k, (PCD8544_currentY + i), (uint8_t) color);
                    }
                    else
                    {
                        PCD8544_DrawPixel(PCD8544_currentX + (j * 8) + k, (PCD8544_currentY + i), (uint8_t) !color);
                    }
                }
            }
        }
    }

    /* Increase pointer */
    PCD8544_currentX += font->width + 1;

    /* Return character written */
    return ch;
}

char PCD8544_Puts(char* str, FontDef_t* Font, uint8_t color)
{
    /* Write characters */
    while (*str)
    {
        /* Write character by character */
        if (PCD8544_Putc(*str, Font, color) != *str)
        {
            /* Return error */
            return *str;
        }
        
        /* Increase string pointer */
        str++;
    }
    
    /* Everything OK, zero should be returned */
    return *str;
}


static __CODE uint8_t Font3x5 [] = {
0x00, 0x00, 0x00, 0x00, 0x00,   // SP
0x02, 0x02, 0x02, 0x00, 0x02,   // !
0x05, 0x05, 0x00, 0x00, 0x00,   // "
0x05, 0x07, 0x05, 0x07, 0x05,   // #
0x06, 0x03, 0x06, 0x03, 0x02,   // $
0x01, 0x04, 0x02, 0x01, 0x04,   // %
0x03, 0x03, 0x07, 0x05, 0x06,   // &
0x02, 0x02, 0x00, 0x00, 0x00,   // '
0x04, 0x02, 0x02, 0x02, 0x04,   // (
0x01, 0x02, 0x02, 0x02, 0x01,   // )
0x05, 0x02, 0x05, 0x00, 0x00,   // *
0x00, 0x02, 0x07, 0x02, 0x00,   // +
0x00, 0x00, 0x00, 0x02, 0x01,   // ,
0x00, 0x00, 0x07, 0x00, 0x00,   // -
0x00, 0x00, 0x00, 0x00, 0x02,   // .
0x00, 0x04, 0x02, 0x01, 0x00,   // /
0x07, 0x05, 0x05, 0x05, 0x07,   // 0
0x02, 0x03, 0x02, 0x02, 0x07,   // 1
0x07, 0x04, 0x07, 0x01, 0x07,   // 2
0x07, 0x04, 0x06, 0x04, 0x07,   // 3
0x05, 0x05, 0x07, 0x04, 0x04,   // 4
0x07, 0x01, 0x07, 0x04, 0x07,   // 5
0x07, 0x01, 0x07, 0x05, 0x07,   // 6
0x07, 0x04, 0x04, 0x04, 0x04,   // 7
0x07, 0x05, 0x07, 0x05, 0x07,   // 8
0x07, 0x05, 0x07, 0x04, 0x07,   // 9
0x00, 0x02, 0x00, 0x02, 0x00,   // :
0x00, 0x02, 0x00, 0x02, 0x01,   // ;
0x04, 0x02, 0x01, 0x02, 0x04,   // <
0x00, 0x07, 0x00, 0x07, 0x00,   // =
0x01, 0x02, 0x04, 0x02, 0x01,   // >
0x07, 0x04, 0x02, 0x00, 0x02,   // ?
0x02, 0x05, 0x07, 0x01, 0x06,   // @
0x02, 0x05, 0x07, 0x05, 0x05,   // A
0x03, 0x05, 0x03, 0x05, 0x03,   // B
0x06, 0x01, 0x01, 0x01, 0x06,   // C
0x03, 0x05, 0x05, 0x05, 0x03,   // D
0x07, 0x01, 0x07, 0x01, 0x07,   // E
0x07, 0x01, 0x07, 0x01, 0x01,   // F
0x06, 0x01, 0x07, 0x05, 0x06,   // G
0x05, 0x05, 0x07, 0x05, 0x05,   // H
0x07, 0x02, 0x02, 0x02, 0x07,   // I
0x04, 0x04, 0x04, 0x05, 0x02,   // J
0x05, 0x05, 0x03, 0x05, 0x05,   // K
0x01, 0x01, 0x01, 0x01, 0x07,   // L
0x05, 0x07, 0x07, 0x05, 0x05,   // M
0x05, 0x07, 0x07, 0x07, 0x05,   // N
0x02, 0x05, 0x05, 0x05, 0x02,   // O
0x03, 0x05, 0x03, 0x01, 0x01,   // P
0x02, 0x05, 0x05, 0x05, 0x06,   // Q
0x03, 0x05, 0x07, 0x03, 0x05,   // R
0x06, 0x01, 0x02, 0x04, 0x03,   // S
0x07, 0x02, 0x02, 0x02, 0x02,   // T
0x05, 0x05, 0x05, 0x05, 0x02,   // U
0x05, 0x05, 0x05, 0x02, 0x02,   // V
0x05, 0x05, 0x07, 0x07, 0x05,   // W
0x05, 0x05, 0x02, 0x05, 0x05,   // X
0x05, 0x05, 0x02, 0x02, 0x02,   // Y
0x07, 0x04, 0x02, 0x01, 0x07,   // Z
0x03, 0x01, 0x01, 0x01, 0x03,   // [
0x00, 0x01, 0x02, 0x04, 0x00,   /* \ */
0x06, 0x04, 0x04, 0x04, 0x06,   // ]
0x02, 0x05, 0x00, 0x00, 0x00,   // ^
0x00, 0x00, 0x00, 0x00, 0x07,   // _
0x01, 0x02, 0x00, 0x00, 0x00,   // `
0x00, 0x03, 0x06, 0x05, 0x07,   // a
0x01, 0x03, 0x05, 0x05, 0x03,   // b
0x00, 0x06, 0x01, 0x01, 0x06,   // c
0x04, 0x06, 0x05, 0x05, 0x06,   // d
0x00, 0x06, 0x05, 0x03, 0x06,   // e
0x04, 0x02, 0x07, 0x02, 0x02,   // f
0x06, 0x05, 0x07, 0x04, 0x02,   // g
0x01, 0x03, 0x05, 0x05, 0x05,   // h
0x02, 0x00, 0x02, 0x02, 0x02,   // i
0x04, 0x00, 0x04, 0x04, 0x03,   // j
0x01, 0x05, 0x03, 0x03, 0x05,   // k
0x03, 0x02, 0x02, 0x02, 0x07,   // l
0x00, 0x07, 0x07, 0x07, 0x05,   // m
0x00, 0x03, 0x05, 0x05, 0x05,   // n
0x00, 0x02, 0x05, 0x05, 0x02,   // o
0x00, 0x03, 0x05, 0x03, 0x01,   // p
0x00, 0x06, 0x05, 0x06, 0x04,   // q
0x00, 0x06, 0x01, 0x01, 0x01,   // r
0x00, 0x06, 0x03, 0x06, 0x03,   // s
0x02, 0x07, 0x02, 0x02, 0x06,   // t
0x00, 0x05, 0x05, 0x05, 0x06,   // u
0x00, 0x05, 0x05, 0x05, 0x02,   // v
0x00, 0x05, 0x07, 0x07, 0x07,   // w
0x00, 0x05, 0x02, 0x02, 0x05,   // x
0x00, 0x05, 0x06, 0x04, 0x06,   // y
0x00, 0x07, 0x06, 0x03, 0x07,   // z
0x06, 0x02, 0x01, 0x02, 0x06,   // {
0x02, 0x02, 0x02, 0x02, 0x02,   // |
0x03, 0x02, 0x04, 0x02, 0x03,   // }
0x00, 0x06, 0x03, 0x00, 0x00,   // ~
0x07, 0x07, 0x07, 0x07, 0x07,   // DEL
};

static __CODE uint8_t Font5x7 [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   //  
0x04, 0x04, 0x04, 0x04, 0x00, 0x04, 0x00,   // !
0x0a, 0x0a, 0x0a, 0x00, 0x00, 0x00, 0x00,   // "
0x0a, 0x0a, 0x1f, 0x0a, 0x1f, 0x0a, 0x0a,   // #
0x04, 0x1e, 0x05, 0x0e, 0x14, 0x0f, 0x04,   // $
0x00, 0x19, 0x1a, 0x04, 0x0b, 0x13, 0x00,   // %
0x06, 0x09, 0x05, 0x02, 0x15, 0x09, 0x16,   // &
0x06, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00,   // '
0x08, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08,   // (
0x02, 0x04, 0x08, 0x08, 0x08, 0x04, 0x02,   // )
0x00, 0x04, 0x15, 0x0e, 0x15, 0x04, 0x00,   // *
0x00, 0x04, 0x04, 0x1f, 0x04, 0x04, 0x00,   // +
0x00, 0x00, 0x00, 0x00, 0x0c, 0x08, 0x04,   // ,
0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00,   // -
0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06,   // .
0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00,   // /
0x0e, 0x11, 0x19, 0x15, 0x13, 0x11, 0x0e,   // 0
0x04, 0x06, 0x04, 0x04, 0x04, 0x04, 0x0e,   // 1
0x0e, 0x11, 0x10, 0x08, 0x04, 0x02, 0x1f,   // 2
0x1f, 0x08, 0x04, 0x08, 0x10, 0x11, 0x0e,   // 3
0x08, 0x0c, 0x0a, 0x09, 0x1f, 0x08, 0x08,   // 4
0x1f, 0x01, 0x0f, 0x10, 0x10, 0x11, 0x0e,   // 5
0x0c, 0x02, 0x01, 0x0f, 0x11, 0x11, 0x0e,   // 6
0x1f, 0x10, 0x08, 0x04, 0x02, 0x02, 0x02,   // 7
0x0e, 0x11, 0x11, 0x0e, 0x11, 0x11, 0x0e,   // 8
0x0e, 0x11, 0x11, 0x1e, 0x10, 0x08, 0x06,   // 9
0x00, 0x06, 0x06, 0x00, 0x06, 0x06, 0x00,   // :
0x00, 0x06, 0x06, 0x00, 0x06, 0x04, 0x02,   // ;
0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08,   // <
0x00, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x00,   // =
0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02,   // >
0x0e, 0x11, 0x10, 0x08, 0x04, 0x00, 0x04,   // ?
0x0e, 0x11, 0x10, 0x16, 0x1d, 0x11, 0x0e,   // @
0x0e, 0x11, 0x11, 0x11, 0x1f, 0x11, 0x11,   // A
0x0f, 0x11, 0x11, 0x0f, 0x11, 0x11, 0x0f,   // B
0x0e, 0x11, 0x01, 0x01, 0x01, 0x11, 0x0e,   // C
0x07, 0x09, 0x11, 0x11, 0x11, 0x09, 0x07,   // D
0x1f, 0x01, 0x01, 0x0f, 0x01, 0x01, 0x1f,   // E
0x1f, 0x01, 0x01, 0x0f, 0x01, 0x01, 0x01,   // F
0x0e, 0x11, 0x01, 0x1d, 0x11, 0x11, 0x1e,   // G
0x11, 0x11, 0x11, 0x1f, 0x11, 0x11, 0x11,   // H
0x0e, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0e,   // I
0x1c, 0x08, 0x08, 0x08, 0x08, 0x09, 0x06,   // J
0x11, 0x09, 0x05, 0x03, 0x05, 0x09, 0x11,   // K
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x1f,   // L
0x11, 0x1b, 0x15, 0x15, 0x11, 0x11, 0x11,   // M
0x11, 0x11, 0x13, 0x15, 0x19, 0x11, 0x11,   // N
0x0e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e,   // O
0x0f, 0x11, 0x11, 0x0f, 0x01, 0x01, 0x01,   // P
0x0e, 0x11, 0x11, 0x11, 0x15, 0x09, 0x16,   // Q
0x0f, 0x11, 0x11, 0x0f, 0x05, 0x09, 0x11,   // R
0x1e, 0x01, 0x01, 0x0e, 0x10, 0x10, 0x0f,   // S
0x1f, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,   // T
0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e,   // U
0x11, 0x11, 0x11, 0x11, 0x11, 0x0a, 0x04,   // V
0x11, 0x11, 0x11, 0x15, 0x15, 0x15, 0x0a,   // W
0x11, 0x11, 0x0a, 0x04, 0x0a, 0x11, 0x11,   // X
0x11, 0x11, 0x11, 0x0a, 0x04, 0x04, 0x04,   // Y
0x1f, 0x10, 0x08, 0x04, 0x02, 0x01, 0x1f,   // Z
0x0e, 0x02, 0x02, 0x02, 0x02, 0x02, 0x0e,   // [
0x15, 0x0a, 0x15, 0x0a, 0x15, 0x0a, 0x15,   /* \ */
0x0e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0e,   // ]
0x04, 0x0a, 0x11, 0x00, 0x00, 0x00, 0x00,   // ^
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,   // _
0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00,   // `
0x00, 0x00, 0x0e, 0x10, 0x1e, 0x11, 0x1e,   // a
0x01, 0x01, 0x0d, 0x13, 0x11, 0x11, 0x0f,   // b
0x00, 0x00, 0x0e, 0x01, 0x01, 0x11, 0x0e,   // c
0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x1e,   // d
0x00, 0x00, 0x0e, 0x11, 0x1f, 0x01, 0x0e,   // e
0x0c, 0x12, 0x02, 0x07, 0x02, 0x02, 0x02,   // f
0x00, 0x1e, 0x11, 0x11, 0x1e, 0x10, 0x0e,   // g
0x01, 0x01, 0x0d, 0x13, 0x11, 0x11, 0x11,   // h
0x04, 0x00, 0x06, 0x04, 0x04, 0x04, 0x0e,   // i
0x08, 0x00, 0x0c, 0x08, 0x08, 0x09, 0x06,   // j
0x01, 0x01, 0x09, 0x05, 0x03, 0x05, 0x09,   // k
0x06, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0e,   // l
0x00, 0x00, 0x0b, 0x15, 0x15, 0x11, 0x11,   // m
0x00, 0x00, 0x0d, 0x13, 0x11, 0x11, 0x11,   // n
0x00, 0x00, 0x0e, 0x11, 0x11, 0x11, 0x0e,   // o
0x00, 0x00, 0x0f, 0x11, 0x0f, 0x01, 0x01,   // p
0x00, 0x00, 0x16, 0x19, 0x1e, 0x10, 0x10,   // q
0x00, 0x00, 0x0d, 0x13, 0x01, 0x01, 0x01,   // r
0x00, 0x00, 0x0e, 0x01, 0x0e, 0x10, 0x0f,   // s
0x02, 0x02, 0x07, 0x02, 0x02, 0x12, 0x0c,   // t
0x00, 0x00, 0x11, 0x11, 0x11, 0x19, 0x16,   // u
0x00, 0x00, 0x11, 0x11, 0x11, 0x0a, 0x04,   // v
0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0a,   // w
0x00, 0x00, 0x11, 0x0a, 0x04, 0x0a, 0x11,   // x
0x00, 0x00, 0x11, 0x11, 0x1e, 0x10, 0x0e,   // y
0x00, 0x00, 0x1f, 0x08, 0x04, 0x02, 0x1f,   // z
0x08, 0x04, 0x04, 0x02, 0x04, 0x04, 0x08,   // { 
0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,   // |
0x02, 0x04, 0x04, 0x08, 0x04, 0x04, 0x02,   // }
0x00, 0x00, 0x02, 0x15, 0x08, 0x00, 0x00,   // ~
0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00,   // 
};

__CODE FontDef_t Font_3x5 = {3, 5, 1, 1, Font3x5};
__CODE FontDef_t Font_5x7 = {5, 7, 1, 1, Font5x7};