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

#ifndef ___FW_UTIL_H___
#define ___FW_UTIL_H___

#include "fw_conf.h"
#include "fw_types.h"

void UTIL_Uart1_24M_9600_Init(void);
void UTIL_Uart1_24M_115200_Init(void);
void UTIL_Uart1_33M1776_9600_Init(void);
void UTIL_Uart1_33M1776_115200_Init(void);
void UTIL_Uart1_35M_9600_Init(void);
void UTIL_Uart1_36M864_9600_Init(void);
void UTIL_Uart1_36M864_115200_Init(void);

#endif
