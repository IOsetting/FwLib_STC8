// Copyright 2021 IOsetting <iosetting@outlook.com>
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

typedef enum
{
    MEM_WorkRegGroup_00H_07H    = 0x00,
    MEM_WorkRegGroup_08H_0FH    = 0x01,
    MEM_WorkRegGroup_10H_17H    = 0x02,
    MEM_WorkRegGroup_18H_1FH    = 0x03,
} MEM_WorkRegGroup_t;

void MEM_SelectWorkRegGroup(MEM_WorkRegGroup_t WorkRegGroup);
void MEM_SetOnchipExtRAM(HAL_State_t HAL_State);

#endif
