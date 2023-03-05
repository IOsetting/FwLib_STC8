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

#ifndef ___FW_SYS_H___
#define ___FW_SYS_H___

#include "fw_conf.h"
#include "fw_types.h"

typedef enum
{
    SYS_ExternalOSC_Clock       = 0x00,
    SYS_ExternalOSC_Crystal     = 0x01,
} SYS_ExternalOSC_t;

typedef enum
{
    SYS_SysClkOutputPort_P54    = 0x00,
    SYS_SysClkOutputPort_P16    = 0x01,
} SYS_SysClkOutputPort_t;

/**
 * STC8H Clock: 
 *  MCKSEL                     ||===> MCLKODIV ==> MCLKO_S => P1.6/P5.4
 *  00 Internal IRC    |       ||
 *  01 External OSC    |==> CLKDIV ==> SYSCLK
 *  10 External 32KHz  |
 *  11 Internal 32KHz  |
*/

/**
 * Precompute system clock based on __CONF_FOSC and __CONF_CLKDIV
*/
#define __SYSCLOCK          (__CONF_FOSC / ((__CONF_CLKDIV == 0) ? 1 : __CONF_CLKDIV))

#define SYS_SetFOSC(__IRCBAND__, __VRTRIM__, __IRTRIM__, __LIRTRIM__)  do {      \
                                     IRCBAND = ((__IRCBAND__) & 0x03);           \
                                     VRTRIM = (__VRTRIM__);                      \
                                     IRTRIM = (__IRTRIM__);                      \
                                     LIRTRIM = ((__LIRTRIM__) & 0x03);           \
                                 } while(0)

/**
 * Enable high speed internal oscillator
*/
#define SYS_EnableOscillatorHSI()   do {                                            \
                                        SFRX_ON();                                  \
                                        (HIRCCR) =  (HIRCCR) | (0x01 << 7);         \
                                        while (!(HIRCCR & 0x01));                   \
                                        SFRX_OFF();                                 \
                                    } while(0)
/**
 * Disable high speed internal oscillator
*/
#define SYS_DisableOscillatorHSI()  do {                                            \
                                        SFRX_ON();                                  \
                                        (HIRCCR) =  (HIRCCR) & ~(0x01 << 7);        \
                                        SFRX_OFF();                                 \
                                    } while(0)

/**
 * Enable low speed internal oscillator
*/
#define SYS_EnableOscillatorLSI()   do {                                            \
                                        SFRX_ON();                                  \
                                        (IRC32KCR) =  (IRC32KCR) | (0x01 << 7);     \
                                        while (!(IRC32KCR & 0x01));                 \
                                        SFRX_OFF();                                 \
                                    } while(0)
/**
 * Disable low speed internal oscillator
*/
#define SYS_DisableOscillatorLSI()  do {                                            \
                                        SFRX_ON();                                  \
                                        (IRC32KCR) =  (IRC32KCR) & ~(0x01 << 7);    \
                                        SFRX_OFF();                                 \
                                    } while(0)

/**
 * Enable high speed external oscillator
*/
#define SYS_EnableOscillatorHSE()   do {                                            \
                                        SFRX_ON();                                  \
                                        (XOSCCR) =  (XOSCCR) | (0x01 << 7);         \
                                        while (!(HIRCCR & 0x01));                   \
                                        SFRX_OFF();                                 \
                                    } while(0)
/**
 * Disable high speed external oscillator
*/
#define SYS_DisableOscillatorHSE()  do {                                            \
                                        SFRX_ON();                                  \
                                        (XOSCCR) =  (XOSCCR) & ~(0x01 << 7);        \
                                        SFRX_OFF();                                 \
                                    } while(0)
/**
 * Set high speed external oscillator type
*/
#define SYS_SetExternalOscType(__TYPE__)        SFRX_ASSIGN(XOSCCR, 6, (__TYPE__))

/**
 * Enable low speed external oscillator
*/
#define SYS_EnableOscillatorLSE()   do {                                            \
                                        SFRX_ON();                                  \
                                        (X32KCR) =  (X32KCR) | (0x01 << 7);         \
                                        while (!(X32KCR & 0x01));                   \
                                        SFRX_OFF();                                 \
                                    } while(0)
/**
 * Disable low speed external oscillator
*/
#define SYS_DisableOscillatorLSE()  do {                                            \
                                        SFRX_ON();                                  \
                                        (X32KCR) =  (X32KCR) & ~(0x01 << 7);        \
                                        SFRX_OFF();                                 \
                                    } while(0)
/**
 * Set low speed external oscillator gain
*/
#define SYS_SetExternal32kHighGain(__STATE__)   SFRX_ASSIGN(X32KCR, 6, (__STATE__))

/**
 * System clock output
 * 0:No output, Foutput = SYSCLK / __DIV__
*/
#define SYS_SetSysClockOutputDivider(__DIV__)   do {                                    \
                                        SFRX_ON();                                      \
                                        (MCLKOCR) =  (MCLKOCR) & ~(0x7F) | (__DIV__);   \
                                        SFRX_OFF();                                     \
                                    } while(0)

/**
 * System clock output pin
 * 0:P5.4, 1:P1.6
*/
#define SYS_SetClockOutputPin(__PORT__)    SFRX_ASSIGN(MCLKOCR, 7, (__STATE__))

/**
 * Enable 48MHz USB OSC
*/
#define SYS_EnableOscillator48M()   do {                                            \
                                        SFRX_ON();                                  \
                                        RSTFLAG = 0x07;                             \
                                        (IRC48MCR) =  (IRC48MCR) | (0x01 << 7);     \
                                        while (!(IRC48MCR & 0x01));                 \
                                        SFRX_OFF();                                 \
                                    } while(0)
/**
 * Disable 48MHz USB OSC
*/
#define SYS_DisableOscillator48M()  do {                                            \
                                        SFRX_ON();                                  \
                                        (IRC48MCR) =  (IRC48MCR) & ~(0x01 << 7);    \
                                        SFRX_OFF();                                 \
                                    } while(0)

void SYS_SetClock(void);
void SYS_TrimClock(uint8_t vrtrim, uint8_t irtrim);
void SYS_Delay(uint16_t t);
void SYS_DelayUs(uint16_t t);

#endif
