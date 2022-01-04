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

#ifndef ___FW_MEM_H___
#define ___FW_MEM_H___

#include "fw_conf.h"
#include "fw_types.h"

#define MEM_ReadCODE(__ADDR__)      (*(unsigned char volatile __CODE *)(__ADDR__))
// Set SFRX_ON() before using this macro
#define MEM_ReadXDATA(__ADDR__)     (*(unsigned char volatile __XDATA *)(__ADDR__))

typedef enum
{
    MEM_WorkRegGroup_00H_07H    = 0x00,
    MEM_WorkRegGroup_08H_0FH    = 0x01,
    MEM_WorkRegGroup_10H_17H    = 0x02,
    MEM_WorkRegGroup_18H_1FH    = 0x03,
} MEM_WorkRegGroup_t;

void MEM_SelectWorkRegGroup(MEM_WorkRegGroup_t WorkRegGroup);
void MEM_SetOnchipExtRAM(HAL_State_t HAL_State);

#if (__CONF_MCU_TYPE == 3  )
void MEM_ReadChipID(uint8_t *buff);
#endif

#endif
