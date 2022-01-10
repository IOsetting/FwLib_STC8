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

#ifndef ___FW_TYPES_H___
#define ___FW_TYPES_H___

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef uint32_t uint64_t[2];

typedef signed char int8_t;
typedef short int16_t;
typedef long int32_t;
typedef int32_t int64_t[2];


#define B00000000   0x00
#define B00000001   0x01
#define B00000010   0x02
#define B00000011   0x03
#define B00000100   0x04
#define B00000110   0x06
#define B00000111   0x07
#define B00001000   0x08
#define B00001100   0x0C
#define B00001110   0x0E
#define B00001111   0x0F
#define B00010000   0x10
#define B00011000   0x18
#define B00011100   0x1C
#define B00011110   0x1E
#define B00011111   0x1F
#define B00100000   0x20
#define B00110000   0x30
#define B00111000   0x38
#define B00111100   0x3C
#define B00111110   0x3E
#define B00111111   0x3F
#define B01000000   0x40
#define B01100000   0x60
#define B01110000   0x70
#define B01111000   0x78
#define B01111100   0x7C
#define B01111110   0x7E
#define B01111111   0x7F
#define B10000000   0x80
#define B11000000   0xC0
#define B11100000   0xE0
#define B11110000   0xF0
#define B11111000   0xF8
#define B11111100   0xFC
#define B11111110   0xFE
#define B11111111   0xFF
#define B01010101   0x55

typedef enum
{
    HAL_State_OFF   = 0x00,
    HAL_State_ON    = 0x01,
} HAL_State_t;

typedef enum
{
    HAL_OK      = 0x00U,
    HAL_ERROR   = 0x01U,
    HAL_BUSY    = 0x02U,
    HAL_TIMEOUT = 0x03U
} HAL_StatusTypeDef;

typedef enum
{
    RESET = 0x0,
    SET = !RESET
} FlagStatus;

/**
 * sbit operations
 */
#define SBIT_SET(__BIT__)                       ((__BIT__) = SET)
#define SBIT_RESET(__BIT__)                     ((__BIT__) = RESET)
#define SBIT_ASSIGN(__BIT__, __VAL__)           ((__BIT__) = (__VAL__))

/**
 * sfr bit operations
 */
#define SFR_SET(__SFR__, __POS__)               ((__SFR__) |=  (0x01 << (__POS__)))
#define SFR_RESET(__SFR__, __POS__)             ((__SFR__) &= ~(0x01 << (__POS__)))
#define SFR_ASSIGN(__SFR__, __POS__, __VAL__)   ((__SFR__) = (__SFR__) & ~(0x01 << (__POS__)) | ((__VAL__) << (__POS__)))
#define SFR_ASSIGN2BIT(__SFR__, __POS__, __VAL__)   ((__SFR__) = (__SFR__) & ~(0x03 << (__POS__)) | ((__VAL__ & 0x03) << (__POS__)))
#define SFR_ASSIGN3BIT(__SFR__, __POS__, __VAL__)   ((__SFR__) = (__SFR__) & ~(0x07 << (__POS__)) | ((__VAL__ & 0x07) << (__POS__)))
// For dual sfr bit (one for each) operation
#define SFR_DUAL_SET(__SFR0__, __SFR1__, __POS__, __VAL__)  do {                                        \
    (__SFR0__) = (__SFR0__) & ~(0x01 << (__POS__)) | (((__VAL__) & 0x01)? (0x01 << (__POS__)) : 0x00);  \
    (__SFR1__) = (__SFR1__) & ~(0x01 << (__POS__)) | (((__VAL__) & 0x02)? (0x01 << (__POS__)) : 0x00);  \
} while(0)

/**
 * xdata sfr address switch
*/
#define SFRX_ON()             (P_SW2 |= 0x80)
#define SFRX_OFF()            (P_SW2 &= ~0x80)

/**
 * xdata sfr operations
 */
#define SFRX_SET(__SFR__, __POS__)     do {SFRX_ON(); (__SFR__) |=  (0x01 << (__POS__)); SFRX_OFF();} while(0)
#define SFRX_RESET(__SFR__, __POS__)   do {SFRX_ON(); (__SFR__) &= ~(0x01 << (__POS__)); SFRX_OFF();} while(0)
#define SFRX_ASSIGN(__SFR__, __POS__, __VAL__)  do {                                                    \
                            SFRX_ON();                                                                  \
                            (__SFR__) =  (__SFR__) & ~(0x01 << (__POS__)) | ((__VAL__) << (__POS__));   \
                            SFRX_OFF();                                                                 \
                        } while(0)
#define SFRX_ASSIGN2BIT(__SFR__, __POS__, __VAL__)  do {                                                    \
                            SFRX_ON();                                                                      \
                            (__SFR__) =  (__SFR__) & ~(0x03 << (__POS__)) | ((__VAL__ & 0x03) << (__POS__));\
                            SFRX_OFF();                                                                     \
                        } while(0)
#define SFRX_ASSIGN3BIT(__SFR__, __POS__, __VAL__)  do {                                                    \
                            SFRX_ON();                                                                      \
                            (__SFR__) =  (__SFR__) & ~(0x07 << (__POS__)) | ((__VAL__ & 0x07) << (__POS__));\
                            SFRX_OFF();                                                                     \
                        } while(0)
// For dual xdata sfr bit (one for each) operation
#define SFRX_DUAL_SET(__SFR0__, __SFR1__, __POS__, __VAL__)  do {                                           \
        SFRX_ON();                                                                                          \
        (__SFR0__) = (__SFR0__) & ~(0x01 << (__POS__)) | (((__VAL__) & 0x01)? (0x01 << (__POS__)) : 0x00);  \
        (__SFR1__) = (__SFR1__) & ~(0x01 << (__POS__)) | (((__VAL__) & 0x02)? (0x01 << (__POS__)) : 0x00);  \
        SFRX_OFF();                                                                                         \
    } while(0)

#endif
