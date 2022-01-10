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

#ifndef ___FW_IAP_H___
#define ___FW_IAP_H___

#include "fw_conf.h"
#include "fw_types.h"

/**
 * EEPROM size and IAP address of different series
 * 
 * | LINE             | SIZE | ADDR START | ADDR END | 
 * | ---------        | --- | -----  | -----  | 
 * | STC8G1K08        | 4K  | 0x0000 | 0x0FFF |
 * | STC8G1K08-8Pin   | 4K  | 0x0000 | 0x0FFF |
 * | STC8G1K08A       | 4K  | 0x0000 | 0x0FFF |
 * | STC8G1K08T       | 4K  | 0x0000 | 0x0FFF |
 * | STC8G2K60S4      | 4K  | 0x0000 | 0x0FFF |
 * | STC8G2K60S2      | 4K  | 0x0000 | 0x0FFF |
 * | STC8H1K08        | 4K  | 0x0000 | 0x0FFF |
 * | STC8H1K24        | 4K  | 0x0000 | 0x0FFF |
 * | STC8H3K60S2      | 4K  | 0x0000 | 0x0FFF |
 * | STC8H3K60S4      | 4K  | 0x0000 | 0x0FFF |
 * | STC8H8K60U       | 4K  | 0x0000 | 0x0FFF |
 * | STC8G1K04        | 8K  | 0x0000 | 0x1FFF |
 * | STC8H1K16        | 12K | 0x0000 | 0x2FFF |
 * | STC8H3K48S2      | 16K | 0x0000 | 0x3FFF |
 * | STC8H3K48S4      | 16K | 0x0000 | 0x3FFF |
 * | STC8H8K48U       | 16K | 0x0000 | 0x3FFF |
 * | STC8G2K48S4      | 16K | 0x0000 | 0x3FFF |
 * | STC8G2K48S2      | 16K | 0x0000 | 0x3FFF |
 * | STC8H3K32S2      | 32K | 0x0000 | 0x7FFF |
 * | STC8H3K32S4      | 32K | 0x0000 | 0x7FFF |
 * | STC8H8K32U       | 32K | 0x0000 | 0x7FFF |
 * | STC8G2K32S4      | 32K | 0x0000 | 0x7FFF |
 * | STC8G2K32S2      | 32K | 0x0000 | 0x7FFF |
 * 
*/

typedef enum
{
    IAP_RestartFrom_UserCode    = 0x00,
    IAP_RestartFrom_ISPCode     = 0x01,
} IAP_RestartFrom_t;

#define IAP_SetWaitTime()           (IAP_TPS = (uint8_t)(__CONF_FOSC / 1000000UL))
#define IAP_ReadData()              (IAP_DATA)
#define IAP_WriteData(__BYTE__)     (IAP_DATA = (__BYTE__))

/**
 * Set cmd to idle
*/
#define IAP_SetIdle()               (IAP_CMD = IAP_CMD & ~(0x03))

/**
 * Read one byte
*/
#define IAP_CmdRead(__16BIT_ADDR__)   do{ \
                            EA = 0; \
                            IAP_ADDRH = ((__16BIT_ADDR__) >> 8); \
                            IAP_ADDRL = ((__16BIT_ADDR__) & 0xFF); \
                            IAP_CMD = IAP_CMD & ~(0x03) | 0x01; \
                            IAP_TRIG = 0x5A; \
                            IAP_TRIG = 0xA5; \
                            NOP();NOP(); \
                            IAP_SetIdle(); \
                            EA = 1; \
                        }while(0)
/**
 * Write one byte, 1->0 only
*/
#define IAP_CmdWrite(__16BIT_ADDR__)   do{ \
                            EA = 0; \
                            IAP_ADDRH = ((__16BIT_ADDR__) >> 8); \
                            IAP_ADDRL = ((__16BIT_ADDR__) & 0xFF); \
                            IAP_CMD = IAP_CMD & ~(0x03) | 0x02; \
                            IAP_TRIG = 0x5A; \
                            IAP_TRIG = 0xA5; \
                            NOP();NOP(); \
                            IAP_SetIdle(); \
                            EA = 1; \
                        }while(0)
/**
 * Erase one section (512 bytes), set all bytes to 0xFF
*/
#define IAP_CmdErase(__16BIT_ADDR__)   do{ \
                            EA = 0; \
                            IAP_ADDRH = ((__16BIT_ADDR__) >> 8); \
                            IAP_ADDRL = ((__16BIT_ADDR__) & 0xFF); \
                            IAP_CMD = IAP_CMD & ~(0x03) | 0x03; \
                            IAP_TRIG = 0x5A; \
                            IAP_TRIG = 0xA5; \
                            NOP();NOP(); \
                            IAP_SetIdle(); \
                            EA = 1; \
                        }while(0)

#define IAP_SetEnabled(__STATE__)       SFR_ASSIGN(IAP_CONTR, 7, __STATE__)
#define IAP_SetRestartFrom(__FROM__)    SFR_ASSIGN(IAP_CONTR, 6, __FROM__)
#define IAP_SoftReset()                 SFR_SET(IAP_CONTR, 5)
#define IAP_IsCmdFailed()               (IAP_CONTR & (0x01 << 4))
#define IAP_ClearCmdFailFlag()          SFR_RESET(IAP_CONTR, 4)


#endif
