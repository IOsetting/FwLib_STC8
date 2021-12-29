#ifndef __FW_CID_STC8H_H__
#define __FW_CID_STC8H_H__

#include "fw_reg_base.h"

#if (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K08   )
    #define __CID_ADDR     0x1FE9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K12 )
    #define __CID_ADDR     0x2FE9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K16 )
    #define __CID_ADDR     0x3FE9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K17 )
    #define __CID_ADDR     0x43E9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K24 )
    #define __CID_ADDR     0x5FE9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K28 )
    #define __CID_ADDR     0x6FE9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H1K33 )
    #define __CID_ADDR     0x83E9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K32S4 ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K32S2   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H2K32T    ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K32TLR  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K32TLCD ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K32LCD  )
    #define __CID_ADDR     0x7FE7
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K48S4 ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K48S2   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H2K48T    ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K48TLR  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K48TLCD ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K48LCD  )
    #define __CID_ADDR     0xBFE9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K60S4 ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K60S2   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H2K60T    ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K60TLR  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K60TLCD ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K60LCD  )
    #define __CID_ADDR     0xEFE9
#elif (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K64S4 ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H3K64S2   ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H2K64T    ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K64TLR  ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K64TLCD ) || \
    (__CONF_MCU_MODEL == MCU_MODEL_STC8H4K64LCD  )
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
