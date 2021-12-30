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
    RCC_IRCBand_20MHz   = 0x00, /* 20MHz RC osc band */
    RCC_IRCBand_35MHz   = 0x01, /* 35MHz RC osc band */
} RCC_IRCBand_t;

typedef enum
{
    RCC_LIRTrim_None    = 0x00, /* none */
    RCC_LIRTrim_001     = 0x01, /* +0.01% */
    RCC_LIRTrim_004     = 0x02, /* +0.04% */
    RCC_LIRTrim_010     = 0x03, /* +0.10% */
} RCC_LIRTrim_t;

typedef enum
{
    RCC_SoftwareReset_Code  = 0x00, /* restart from user code */
    RCC_SoftwareReset_ISP   = 0x01, /* restart from ISP */
} RCC_SoftwareReset_t;

typedef enum
{
    RCC_LowVoltResetPinAF_IO      = 0x00, /* P5.4 as GPIO */
    RCC_LowVoltResetPinAF_Reset   = 0x01, /* P5.4 as RESET */
} RCC_LowVoltResetPinAF_t;

typedef enum
{
    RCC_LowVoltDetectVolt_2V0   = 0x00, /* Detect at 2.0V */
    RCC_LowVoltDetectVolt_2V4   = 0x01, /* Detect at 2.4V */
    RCC_LowVoltDetectVolt_2V7   = 0x02, /* Detect at 2.7V */
    RCC_LowVoltDetectVolt_3V0   = 0x03, /* Detect at 3.0V */
} RCC_LowVoltDetectVolt_t;

void RCC_SetSYSCLKSource(RCC_SYSCLKSource_t SYSCLKSource);
void RCC_SetCLKDivider(uint8_t divider);
void RCC_SetIRC(RCC_IRCBand_t IRCBand, uint8_t IRTrim, RCC_LIRTrim_t LIRTrim);
void RCC_SoftwareReset(RCC_SoftwareReset_t SoftwareReset);
void RCC_ConfigLowVoltReset(
    HAL_State_t HAL_State, 
    RCC_LowVoltResetPinAF_t LowVoltResetPinAF,
    RCC_LowVoltDetectVolt_t LowVoltDetectVolt);

void RCC_SetPowerDownWakeupTimer(HAL_State_t HAL_State, uint16_t countdown);
void RCC_SetPowerDownMode(HAL_State_t HAL_State);
void RCC_SetIdleMode(HAL_State_t HAL_State);

#endif
