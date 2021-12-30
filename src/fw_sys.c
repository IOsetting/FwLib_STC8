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

#include "fw_sys.h"

static const uint16_t ticks_ms = (__CONF_FOSC / (float)1000 / 13 - 46);
static const uint8_t ticks_us = (__CONF_FOSC / (float)12100000UL);
static uint8_t clkdiv = 0x1;

/**
 * Change system clock
 * - invoke this in the beginning of code
 * - don't invoke this if the target frequency is already set by STC-ISP
*/
void SYS_SetClock(void)
{
    uint16_t i = 0; uint8_t j = 5;
    P_SW2 = 0x80;
    if (CLKDIV != (__CONF_CLKDIV))
    {
        CLKDIV = (__CONF_CLKDIV);
        do { // Wait a while after clock changed, or it may block the main process
            while (--i);
        } while (--j);
    }
    P_SW2 = 0x00;
    clkdiv = (__CONF_CLKDIV == 0)? 1 : __CONF_CLKDIV;
    SYS_SetFOSC(__CONF_IRCBAND, __CONF_VRTRIM, __CONF_IRTRIM, __CONF_LIRTRIM);
    while (--i); // Wait
}

void SYS_Delay(uint16_t t)
{
    uint16_t i;
    do
    {
        i = ticks_ms;
        while (--i);
    } while (--t);
}

void SYS_DelayUs(uint16_t t)
{
    uint8_t i;
    do
    {
        i = ticks_us;
        while (--i);
    } while (--t);
}

uint32_t SYS_GetSysClock(void)
{
    return ((uint32_t)__CONF_FOSC) / clkdiv;
}
