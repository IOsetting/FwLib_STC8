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

#ifndef ___FW_WDT_H___
#define ___FW_WDT_H___

#include "fw_conf.h"
#include "fw_types.h"

/********************************************************
 * STC8 watchdog behavior is different from STC15
 * 
 * STC8 watchdog will ALWAYS reset chip from ISP code region inspite of the 
 * setting of SWBS in IAP_CONTR
 * 
*/

/**
 * Start watchdog. 
 * It cannot be stopped in code once it is started
*/
#define WDT_StartWatchDog()         SFR_SET(WDT_CONTR, 5)
/**
 * Reset watchdog counter to avoid reset
*/
#define WDT_ResetCounter()          SFR_SET(WDT_CONTR, 4)
/**
 * Enable or disable watchdog counter in idle mode
*/
#define WDT_EnableCounterWhenIdle(__STATE__)    SFR_ASSIGN(WDT_CONTR, 3, __STATE__)
/**
 * Set counter prescaler. The higher this value is, the longer counter overflow will take place
 * 
 * Toverflow (in seconds) = 12 * 32768 * 2^(__PRE_SCALER__ + 1) / SYSCLK
*/
#define WDT_SetCounterPrescaler(__PRE_SCALER__) (WDT_CONTR = WDT_CONTR & ~0x07 | (__PRE_SCALER__ & 0x07))

#endif
