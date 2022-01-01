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

#ifndef __FW_CID_STC8H_H__
#define __FW_CID_STC8H_H__

#include "fw_reg_base.h"

#if (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K08   )
    #define __CID_ADDR     0x1FE7
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K12 )
    #define __CID_ADDR     0x2FE7
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K16 )
    #define __CID_ADDR     0x3FE7
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K17 )
    #define __CID_ADDR     0x43E7
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K24 )
    #define __CID_ADDR     0x5FE7
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K28 )
    #define __CID_ADDR     0x6FE7
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K33 )
    #define __CID_ADDR     0x83E7
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K32S4 ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K32S2   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H2K32T    ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K32TLR  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K32TLCD ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K32LCD  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H8K32U    )
    #define __CID_ADDR     0x7FE7
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K48S4 ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K48S2   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H2K48T    ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K48TLR  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K48TLCD ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K48LCD  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H8K48U    )
    #define __CID_ADDR     0xBFE7
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K60S4 ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K60S2   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H2K60T    ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K60TLR  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K60TLCD ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K60LCD  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H8K60U    )
    #define __CID_ADDR     0xEFE7
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K64S4 ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K64S2   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H2K64T    ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K64TLR  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K64TLCD ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K64LCD  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H8K64U    )
    #define __CID_ADDR     0xFDE7
#endif

#define ID_ROMADDR        ( (unsigned char __CODE *)(__CID_ADDR + 18)) // MCU ID 7 bytes
#define VREF_ROMADDR      (*(unsigned int  __CODE *)(__CID_ADDR + 16)) //1.19Vref
#define F32K_ROMADDR      (*(unsigned int  __CODE *)(__CID_ADDR + 14)) //32kHz frequency
#define T22M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 13)) //22.1184MHz (20M)
#define T24M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 12)) //24MHz (20M)
#define T20M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 11)) //20MHz (20M)
#define T27M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 10)) //27MHz (35M)
#define T30M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 9)) //30MHz (35M)
#define T33M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 8)) //33.1776MHz (35M)
#define T35M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 7)) //35MHz (35M)
#define T36M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 6)) //36.864MHz (35M)
#define T40M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 5)) //
#define T45M_ROMADDR      (*(unsigned char __CODE *)(__CID_ADDR + 4)) //
#define VRT20M_ROMADDR    (*(unsigned char __CODE *)(__CID_ADDR + 3)) //VRTRIM of IRCBAND 0
#define VRT35M_ROMADDR    (*(unsigned char __CODE *)(__CID_ADDR + 2)) //VRTRIM of IRCBAND 1
#define VRT24M_ROMADDR    (*(unsigned char __CODE *)(__CID_ADDR + 1)) //VRTRIM of IRCBAND 2
#define VRT40M_ROMADDR    (*(unsigned char __CODE *)(__CID_ADDR + 0)) //VRTRIM of IRCBAND 3

#endif
