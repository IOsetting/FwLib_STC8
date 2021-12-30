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

#ifndef __FW_CID_STC8G_H__
#define __FW_CID_STC8G_H__

#include "fw_reg_base.h"


#if   (__CONF_MCU_MODEL == MCU_MODEL_STC8G1K04 )
    #define __CID_ADDR     0x0FE9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8G1K08 )
    #define __CID_ADDR     0x1FE9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8G1K12 )
    #define __CID_ADDR     0x2FE9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8G2K16 )
    #define __CID_ADDR     0x3FE9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8G1K17 )
    #define __CID_ADDR     0x43E9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8G2K32 )
    #define __CID_ADDR     0x7FE9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8G2K48 )
    #define __CID_ADDR     0xBFE9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8G2K60 )
    #define __CID_ADDR     0xEFE9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8G2K64 )
    #define __CID_ADDR     0xFDE9
#endif

#define ID_ROMADDR        ( (unsigned char __CODE *)(__CID_ADDR + 15)) // MCU ID 7 bytes
#define VREF_ROMADDR      (*(unsigned int  __CODE *)(__CID_ADDR + 13))
#define F32K_ROMADDR      (*(unsigned int  __CODE *)(__CID_ADDR + 11))
#define T22M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 10)) //22.1184MHz (20M)
#define T24M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 9)) //24MHz (20M)
#define T20M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 8)) //20MHz (20M)
#define T27M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 7)) //27MHz (35M)
#define T30M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 6)) //30MHz (35M)
#define T33M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 5)) //33.1776MHz (35M)
#define T35M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 4)) //35MHz (35M)
#define T36M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 3)) //36.864MHz (35M)
#define VRT20M_ROMADDR    (*(unsigned char __CODE *)(__CID_ADDR + 1)) //VRTRIM of 20M
#define VRT35M_ROMADDR    (*(unsigned char __CODE *)(__CID_ADDR + 0)) //VRTRIM of 35M

#endif
