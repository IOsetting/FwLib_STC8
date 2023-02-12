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

#ifndef ___FW_RCC_H___
#define ___FW_RCC_H___

#include "fw_conf.h"
#include "fw_types.h"

typedef enum
{
    RCC_SYSCLKSource_HSI = 0x00, /* Internal high speed RC osc */
    RCC_SYSCLKSource_HSE = 0x01, /* External high speed osc */
    RCC_SYSCLKSource_LSE = 0x02, /* External 32KHz osc */
    RCC_SYSCLKSource_LSI = 0x03, /* Internal 32KHz RC osc */
} RCC_SYSCLKSource_t;

typedef enum
{
    RCC_LowVoltResetPinAF_IO      = 0x00, /* P5.4 as GPIO */
    RCC_LowVoltResetPinAF_Reset   = 0x01, /* P5.4 as RESET */
} RCC_LowVoltResetPinAF_t;

/**
 * Low voltage threshold 
 * 
 * |    | STC8H8K64U | Other      |
 * | -- | ---------- | ---------- |
 * | 00 | 1.9V       | 2.0V       |
 * | 01 | 2.3V       | 2.4V       |
 * | 10 | 2.8V       | 2.7V       |
 * | 11 | 3.7V       | 3.0V       |
*/
typedef enum
{
    RCC_LowVoltThreshold_Lowest     = 0x00,
    RCC_LowVoltThreshold_Low        = 0x01,
    RCC_LowVoltThreshold_High       = 0x02,
    RCC_LowVoltThreshold_Highest    = 0x03,
} RCC_LowVoltThreshold_t;

#define RCC_SetSYSCLKSource(__SOURCE__)     do {  \
            SFRX_ON();                              \
            (CKSEL) =  (CKSEL) & ~(0x03) | (__SOURCE__); \
            SFRX_OFF();                              \
        } while(0)

#define RCC_SetCLKDivider(__DIV__)          do {SFRX_ON(); CLKDIV = (__DIV__ & 0xFF); SFRX_OFF();} while(0)
#define RCC_SetPowerDownMode(__STATE__)     SFR_ASSIGN(PCON, 1, __STATE__)
#define RCC_SetIdleMode(__STATE__)          SFR_ASSIGN(PCON, 0, __STATE__)
#define RCC_SetPowerDownWakeupTimerState(__STATE__)     SFR_ASSIGN(WKTCH, 7, __STATE__)
#define RCC_SetPowerDownWakeupTimerCountdown(__15BIT_COUNT__) do { \
                            WKTCH = WKTCH & ~(0x7F) | (__15BIT_COUNT__ >> 8); \
                            WKTCL = (__15BIT_COUNT__ & 0xFF); \
                        }while(0)

#define RCC_SetLowVoltResetState(__STATE__) SFR_ASSIGN(RSTCFG, 6, __STATE__)
#define RCC_SetLowVoltResetPinAF(__PIN_AF__) SFR_ASSIGN(RSTCFG, 4, __PIN_AF__)
#define RCC_SetLowVoltResetThreshold(__THRESHOLD__) (RSTCFG = RSTCFG & ~(0x03) | (__THRESHOLD__))


#endif
