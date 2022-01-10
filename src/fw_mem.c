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

#include "fw_mem.h"

void MEM_SelectWorkRegGroup(MEM_WorkRegGroup_t WorkRegGroup)
{
	RS0 = WorkRegGroup & 0x01;
	RS1 = (WorkRegGroup >> 1) & 0x01;
}

void MEM_SetOnchipExtRAM(HAL_State_t HAL_State)
{
	AUXR = AUXR & ~(0x01 << 1) | (HAL_State << 1);
}

#if (__CONF_MCU_TYPE == 3  )
void MEM_ReadChipID(uint8_t *buff)
{
    uint8_t i;
	P_SW2 = 0x80;
	for (i = 0; i < 32; i++)
	{
		*(buff + i) = MEM_ReadXDATA(CHIPIDxx + i);
	}
	P_SW2 = 0x00;
}
#endif
