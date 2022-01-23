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

#ifndef ___FW_CONF_H___
#define ___FW_CONF_H___

#define MCU_MODEL_STC8A8K64D4       0x01

#define MCU_MODEL_STC8G1K04         0x02
#define MCU_MODEL_STC8G1K08         0x03
#define MCU_MODEL_STC8G1K12         0x04
#define MCU_MODEL_STC8G1K17         0x05
#define MCU_MODEL_STC8G2K16         0x06
#define MCU_MODEL_STC8G2K32         0x07
#define MCU_MODEL_STC8G2K48         0x08
#define MCU_MODEL_STC8G2K60         0x09
#define MCU_MODEL_STC8G2K64         0x0a

#define MCU_MODEL_STC8H1K08         0x10
#define MCU_MODEL_STC8H1K12         0x11
#define MCU_MODEL_STC8H1K16         0x12
#define MCU_MODEL_STC8H1K17         0x13
#define MCU_MODEL_STC8H1K24         0x14
#define MCU_MODEL_STC8H1K28         0x15
#define MCU_MODEL_STC8H1K33         0x16

#define MCU_MODEL_STC8H3K32S4       0x17
#define MCU_MODEL_STC8H3K32S2       0x18
#define MCU_MODEL_STC8H2K32T        0x19
#define MCU_MODEL_STC8H4K32TLR      0x1A
#define MCU_MODEL_STC8H4K32TLCD     0x1B
#define MCU_MODEL_STC8H4K32LCD      0x1C

#define MCU_MODEL_STC8H3K48S4       0x1D
#define MCU_MODEL_STC8H3K48S2       0x1E
#define MCU_MODEL_STC8H2K48T        0x1F
#define MCU_MODEL_STC8H4K48TLR      0x20
#define MCU_MODEL_STC8H4K48TLCD     0x21
#define MCU_MODEL_STC8H4K48LCD      0x22

#define MCU_MODEL_STC8H3K60S4       0x23
#define MCU_MODEL_STC8H3K60S2       0x24
#define MCU_MODEL_STC8H2K60T        0x25
#define MCU_MODEL_STC8H4K60TLR      0x26
#define MCU_MODEL_STC8H4K60TLCD     0x27
#define MCU_MODEL_STC8H4K60LCD      0x28

#define MCU_MODEL_STC8H3K64S4       0x29
#define MCU_MODEL_STC8H3K64S2       0x2A
#define MCU_MODEL_STC8H2K64T        0x2B
#define MCU_MODEL_STC8H4K64TLR      0x2C
#define MCU_MODEL_STC8H4K64TLCD     0x2D
#define MCU_MODEL_STC8H4K64LCD      0x2E

#define MCU_MODEL_STC8H8K32U        0x2F
#define MCU_MODEL_STC8H8K48U        0x30
#define MCU_MODEL_STC8H8K60U        0x31
#define MCU_MODEL_STC8H8K64U        0x32



#ifndef __CONF_FOSC
    #define __CONF_FOSC 24000000UL
#endif

#ifndef __CONF_CLKDIV
    #define __CONF_CLKDIV 0x00
#endif

#ifndef __CONF_IRCBAND
    #define __CONF_IRCBAND 0x00
#endif

#ifndef __CONF_VRTRIM
    #define __CONF_VRTRIM 0x00
#endif

#ifndef __CONF_IRTRIM
    #define __CONF_IRTRIM 0x00
#endif

#ifndef __CONF_LIRTRIM
    #define __CONF_LIRTRIM 0x00
#endif

#ifndef __CONF_MCU_MODEL
    #define __CONF_MCU_MODEL MCU_MODEL_STC8H1K08
#endif

#if (__CONF_MCU_MODEL == MCU_MODEL_STC8A8K64D4)
    #define __CONF_MCU_TYPE 1
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8G1K04   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8G1K08     ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8G1K12     ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8G1K17     ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8G2K16     ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8G2K32     ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8G2K48     ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8G2K60     ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8G2K64     )
    #define __CONF_MCU_TYPE 2

#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K08   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K12     ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K16     ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K17     ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K24     ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K28     ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K33     ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K32S4   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K32S2   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H2K32T    ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K32TLR  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K32TLCD ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K32LCD  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K48S4   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K48S2   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H2K48T    ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K48TLR  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K48TLCD ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K48LCD  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K60S4   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K60S2   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H2K60T    ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K60TLR  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K60TLCD ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K60LCD  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K64S4   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K64S2   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H2K64T    ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K64TLR  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K64TLCD ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K64LCD  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H8K32U    ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H8K48U    ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H8K60U    ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H8K64U    )
    #define __CONF_MCU_TYPE 3
#endif

#if (__CONF_MCU_TYPE == 1  )
    #include "fw_reg_stc8a8k64d4.h"
#elif (__CONF_MCU_TYPE == 2 )
    #include "fw_reg_stc8g.h"
    #include "fw_cid_stc8g.h"
#elif (__CONF_MCU_TYPE == 3  )
    #include "fw_reg_stc8h.h"
    #include "fw_cid_stc8h.h"
#endif

#endif
