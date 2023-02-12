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

#ifndef ___FW_CMP_H___
#define ___FW_CMP_H___

#include "fw_conf.h"
#include "fw_types.h"

/**
 * STC8 MCU analog comparator
 * 
 * 2P: 2 positive input options
 * 4P: 4 positive input options
 * 
 * |                | 2P+2N | 4P+2N |
 * | STC8G1K08      |   Y   |       | 
 * | STC8G1K08-8Pin |   N   |       | 
 * | STC8G1K08A     |   N   |       | 
 * | STC8G2K64S4    |   Y   |       | 
 * | STC8G2K64S2    |   Y   |       | 
 * | STC8G1K08T     |   Y   |       | 
 * | STC15H2K64S4   |   Y   |       | 
 * | STC8H1K08      |   Y   |       | 
 * | STC8H1K28      |   Y   |       | 
 * | STC8H3K64S4    |   Y   |       | 
 * | STC8H3K64S2    |   Y   |       | 
 * | STC8H2K64T     |   Y   |       |      
 * | STC8H8K64U     |       |   Y   |      
 * | STC8H4K64TLR   |       |   Y   |      
 * | STC8H4K64TLCD  |       |   Y   |      
 * | STC8H4K64LCD   |       |   Y   |     
*/

typedef enum
{
    CMP_OLD_PositiveInput_P37   = 0x00,
    CMP_OLD_PositiveInput_ADC   = 0x01,
} CMP_OLD_PositiveInput_t;

typedef enum
{
    CMP_OLD_NegativeInput_RefV  = 0x00,
    CMP_OLD_NegativeInput_P36   = 0x01,
} CMP_OLD_NegativeInput_t;

typedef enum
{
    CMP_PositiveInput_P37   = 0x00,
    CMP_PositiveInput_P50   = 0x01,
    CMP_PositiveInput_P51   = 0x02,
    CMP_PositiveInput_ADC   = 0x03,
} CMP_PositiveInput_t;

typedef enum
{
    CMP_NegativeInput_P36   = 0x00,
    CMP_NegativeInput_RefV  = 0x01,
} CMP_NegativeInput_t;

typedef enum
{
    CMP_Hysteresis_0mV      = 0x00,
    CMP_Hysteresis_10mV     = 0x01,
    CMP_Hysteresis_20mV     = 0x02,
    CMP_Hysteresis_30mV     = 0x03,
} CMP_Hysteresis_t;

#define CMP_SetEnabled(__STATE__)           SFR_ASSIGN(CMPCR1, 7, __STATE__)
#define CMP_ClearInterrupt()                SFR_ASSIGN(CMPCR1, 6, 0)
/**
 * for 2P+2N series. 
 * Set positive input pin, 0:P36, 1:ADC
*/
#define CMP_OLD_SetPositiveInput(__INPUT__)     SFR_ASSIGN(CMPCR1, 3, __INPUT__)
/**
 * for 4P+2N series. 
 * Set positive input pin, 0:P36, 1:P50, 2:P51, 3:ADC
*/
#define CMP_SetPositiveInput(__INPUT__) do{ \
                                            SFRX_ON(); \
                                            CMPEXCFG = CMPEXCFG & ~(0x03) | (__INPUT__ & 0x03); \
                                            SFRX_OFF(); \
                                        } while(0)
/**
 * for 2P+2N series. 
 * Set negative input pin, 0:1.19V ref, 1:P36
*/
#define CMP_OLD_SetNegativeInput(__INPUT__) SFR_ASSIGN(CMPCR1, 2, __INPUT__)
/**
 * for 4P+2N series. 
 * Set negative input pin, 0:P36, 1:1.19Vref
*/
#define CMP_SetNegativeInput(__INPUT__)     SFRX_ASSIGN(CMPEXCFG, 2, __INPUT__)

/**
 * Result output
 * 0:no output, 1:output to P34 or P41 
*/
#define CMP_SetResultOutputState(__STATE__) SFR_ASSIGN(CMPCR1, 1, __STATE__)
#define CMP_ReadResultOutput()              (CMPCR1 & 0x01)
/**
 * 0: P34/P41 output high when result is 1
 * 1: P34/P41 output low when result is 1
*/
#define CMP_SetResultOutputInvert(__STATE__)    SFR_ASSIGN(CMPCR2, 7, __STATE__)
/**
 * 0: Enable 0.1us analog filter
 * 1: Disable 0.1us analog filter
*/
#define CMP_SetFilterDisabled(__STATE__)    SFR_ASSIGN(CMPCR2, 6, __STATE__)
/**
 * Comparator result will be delayed for (__CLOCKS__ + 2) clocks
*/
#define CMP_SetDebouncingClocks(__CLOCKS__) CMPCR2 = CMPCR2 & ~(0x3F) | (__CLOCKS__ & 0x3F)
/**
 * Set comparator hysteresis for producing stable switching behavior.
*/
#define CMP_SetHysteresis(__HYST__) do{ \
                                        SFRX_ON(); \
                                        CMPEXCFG = CMPEXCFG & ~(0x03 << 6) | (__HYST__ << 6); \
                                        SFRX_OFF(); \
                                    } while(0)

#endif
