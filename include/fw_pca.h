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

#ifndef ___FW_PCA_H___
#define ___FW_PCA_H___

#include "fw_conf.h"
#include "fw_types.h"

typedef enum
{
    PCA_ClockSource_SysClkDiv12     = 0x00,
    PCA_ClockSource_SysClkDiv2      = 0x01,
    PCA_ClockSource_Timer0Overflow  = 0x02,
    PCA_ClockSource_ExtClock        = 0x03,
    PCA_ClockSource_SysClk          = 0x04,
    PCA_ClockSource_SysClkDiv4      = 0x05,
    PCA_ClockSource_SysClkDiv6      = 0x06,
    PCA_ClockSource_SysClkDiv8      = 0x07,
} PCA_ClockSource_t;

typedef enum
{
    PCA_WorkMode_None               = 0x00, // n/a
    PCA_WorkMode_PWM_NonInterrupt   = 0x42, // 6/7/8/10-bit PWM, no interrupt
    PCA_WorkMode_PWM_RiseInterrupt  = 0x63, // 6/7/8/10-bit PWM, rising interrupt
    PCA_WorkMode_PWM_FallInterrupt  = 0x53, // 6/7/8/10-bit PWM, falling interrupt
    PCA_WorkMode_PWM_EdgeInterrupt  = 0x73, // 6/7/8/10-bit PWM, both edge interrupt
    PCA_WorkMode_CAP_16bitRising    = 0x20, // 16-bit Capture Mode, capture triggered by rising edge on CCPn/PCAn 
    PCA_WorkMode_CAP_16bitFalling   = 0x10, // 16-bit Capture Mode, capture triggered by falling edge on CCPn/PCAn 
    PCA_WorkMode_CAP_16bitEdge      = 0x30, // 16-bit Capture Mode, capture triggered by both edge on CCPn/PCAn 
    PCA_WorkMode_CAP_16bitTimer     = 0x48, // 16-bit software timer
    PCA_WorkMode_CAP_16bitPulseOut  = 0x4C, // 16-bit high-speed pulse output
} PCA_WorkMode_t;

typedef enum
{
    PCA_PWM_BitWidth_8      = 0x00, // {EPCnH, CCAPnH[7:0]} {EPCnL, CCAPnL[7:0]}
    PCA_PWM_BitWidth_7      = 0x01, // {EPCnH, CCAPnH[6:0]} {EPCnL, CCAPnL[6:0]}
    PCA_PWM_BitWidth_6      = 0x02, // {EPCnH, CCAPnH[5:0]} {EPCnL, CCAPnL[5:0]}
    PCA_PWM_BitWidth_10     = 0x03, // {EPCnH, XCCAPnH[1:0], CCAPnH[7:0]} {EPCnL, XCCAPnL[1:0], CCAPnL[7:0]}
} PCA_PWM_Bitwidth_t;

typedef enum
{
    //           ECI CCP0 CCP1 CCP2
    PCA_AlterPort_P12_P11_P10_P37 = 0x00,
    PCA_AlterPort_P34_P35_P36_P37 = 0x01,
    PCA_AlterPort_P24_P25_P26_P27 = 0x10,
} PCA_AlterPort_t;

typedef enum
{
    //                  ECI CCP0 CCP1 CCP2
    PCA_AlterPort_G1K08A_P55_P32_P33_P54 = 0x00,
    PCA_AlterPort_G1K08A_P55_P31_P33_P54 = 0x01,
    PCA_AlterPort_G1K08A_P31_P32_P33_P55 = 0x10,
} PCA_AlterPort_G1K08A_t;

typedef enum
{
    //                   ECI CCP0 CCP1 CCP2
    PCA_AlterPort_G1K08T_P13_P11_P10_P37 = 0x00,
    PCA_AlterPort_G1K08T_P34_P35_P36_P37 = 0x01,
    PCA_AlterPort_G1K08T_P54_P13_P14_P15 = 0x10,
} PCA_AlterPort_G1K08T_t;


#define PCA_SetCounterState(__STATE__)      SBIT_ASSIGN(CR, __STATE__)
#define PCA_ClearCounterOverflowInterrupt() SBIT_RESET(CF)
#define PCA_PCA0_ClearInterrupt()           SBIT_RESET(CCF0)
#define PCA_PCA1_ClearInterrupt()           SBIT_RESET(CCF1)
#define PCA_PCA2_ClearInterrupt()           SBIT_RESET(CCF2)

#define PCA_SetStopCounterInIdle(__STATE__) SFR_ASSIGN(CMOD, 7, __STATE__)
#define PCA_SetClockSource(__SOURCE___)     (CMOD = CMOD & ~(0x07 << 1) | ((__SOURCE___) << 1))
#define PCA_EnableCounterOverflowInterrupt(__STATE__)   SFR_ASSIGN(CMOD, 0, __STATE__)

#define PCA_PCA0_SetWorkMode(__MODE__)          (CCAPM0 = (__MODE__))
#define PCA_PCA1_SetWorkMode(__MODE__)          (CCAPM1 = (__MODE__))
#define PCA_PCA2_SetWorkMode(__MODE__)          (CCAPM2 = (__MODE__))

#define PCA_PWM0_SetBitWidth(__BIT_WIDTH__) (PCA_PWM0 = PCA_PWM0 & ~(0x03 << 6) | ((__BIT_WIDTH__) << 6))
#define PCA_PWM1_SetBitWidth(__BIT_WIDTH__) (PCA_PWM1 = PCA_PWM1 & ~(0x03 << 6) | ((__BIT_WIDTH__) << 6))
#define PCA_PWM2_SetBitWidth(__BIT_WIDTH__) (PCA_PWM2 = PCA_PWM2 & ~(0x03 << 6) | ((__BIT_WIDTH__) << 6))
/**
 * Set initiale comparison value
*/
#define PCA_PCA0_SetCompareValue(__VALUE__)     do{CCAP0H = (__VALUE__); CCAP0L = (__VALUE__);}while(0)
#define PCA_PCA1_SetCompareValue(__VALUE__)     do{CCAP1H = (__VALUE__); CCAP1L = (__VALUE__);}while(0)
#define PCA_PCA2_SetCompareValue(__VALUE__)     do{CCAP2H = (__VALUE__); CCAP2L = (__VALUE__);}while(0)
/**
 * Change comparison value when running
*/
#define PCA_PCA0_ChangeCompareValue(__VALUE__)  (CCAP0H = (__VALUE__))
#define PCA_PCA1_ChangeCompareValue(__VALUE__)  (CCAP1H = (__VALUE__))
#define PCA_PCA2_ChangeCompareValue(__VALUE__)  (CCAP2H = (__VALUE__))

/**
 * Set initiale comparison value
*/
#define PCA_PCA0_SetCompareValue10bit(__VALUE__) do{ \
                        PCA_PWM0 = PCA_PWM0 & ~(0x0F << 2) | (((__VALUE__) >> 4) & 0x30) | (((__VALUE__) >> 6) & 0x0C); \
                        CCAP0H = ((__VALUE__) & 0xFF); CCAP0L = ((__VALUE__) & 0xFF);  \
                    }while(0)
#define PCA_PCA1_SetCompareValue10bit(__VALUE__) do{ \
                        PCA_PWM1 = PCA_PWM1 & ~(0x0F << 2) | (((__VALUE__) >> 4) & 0x30) | (((__VALUE__) >> 6) & 0x0C); \
                        CCAP1H = ((__VALUE__) & 0xFF); CCAP1L = ((__VALUE__) & 0xFF);  \
                    }while(0)
#define PCA_PCA2_SetCompareValue10bit(__VALUE__) do{ \
                        PCA_PWM2 = PCA_PWM2 & ~(0x0F << 2) | (((__VALUE__) >> 4) & 0x30) | (((__VALUE__) >> 6) & 0x0C); \
                        CCAP2H = ((__VALUE__) & 0xFF); CCAP2L = ((__VALUE__) & 0xFF);  \
                    }while(0)

/**
 * Change comparison value in running mode
 * Note: set high 2bit first, then low 8bit, the hardware will make sure new 10bit be loaded as a whole number.
 * If you write low bits first, it will introduce glitchnoise.
*/
#define PCA_PCA0_ChangeCompareValue10bit(__VALUE__) do{ \
                        PCA_PWM0 = PCA_PWM0 & ~(0x03 << 4) | (((__VALUE__) >> 4) & 0x30); \
                        CCAP0H = ((__VALUE__) & 0xFF);  \
                    }while(0)
#define PCA_PCA1_ChangeCompareValue10bit(__VALUE__) do{ \
                        PCA_PWM1 = PCA_PWM1 & ~(0x03 << 4) | (((__VALUE__) >> 4) & 0x30); \
                        CCAP1H = ((__VALUE__) & 0xFF);  \
                    }while(0)
#define PCA_PCA2_ChangeCompareValue10bit(__VALUE__) do{ \
                        PCA_PWM2 = PCA_PWM2 & ~(0x03 << 4) | (((__VALUE__) >> 4) & 0x30); \
                        CCAP2H = ((__VALUE__) & 0xFF);  \
                    }while(0)

/**
 * Alternative port selection
*/
#define PCA_SetPort(__ALTER_PORT__)         (P_SW1 = P_SW1 & ~(0x03 << 4) | ((__ALTER_PORT__) << 4))

#endif
