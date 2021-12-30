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

#ifndef ___FW_SPI_H___
#define ___FW_SPI_H___

#include "fw_conf.h"
#include "fw_types.h"

/**
 * STC8H1K08(TSSOP20)  STC8H3K32S2(TSSOP20)
 *            #1 #4     #1 #3 #4
 * SPI SS   -> 1 16     19  7 16(P35)
 * SPI MOSI -> 2 15           15(P34)
 * SPI MISO -> 3 14           14(P33)
 * SPI CLK  -> 4 13           13(P32)
*/
typedef enum
{
    //            SS MOSI MISO SCLK
    SPI_AlterPort_P12P54_P13_P14_P15    = 0x00,
    SPI_AlterPort_P22_P23_P24_P25       = 0x01,
    SPI_AlterPort_P54_P40_P41_P43       = 0x10,
    SPI_AlterPort_P35_P34_P33_P32       = 0x11,
} SPI_AlterPort_t;

typedef enum
{
    SPI_ClockPreScaler_4       = 0x00,
    SPI_ClockPreScaler_8       = 0x01,
    SPI_ClockPreScaler_16      = 0x02,
    SPI_ClockPreScaler_32or2   = 0x03,
} SPI_ClockPreScaler_t;

#define SPI_RxTxFinished()                  (SPSTAT & (0x01 << 7))
#define SPI_ClearInterrupt()                SFR_RESET(SPSTAT, 7)
#define SPI_ClearWriteConflictInterrupt()   SFR_RESET(SPSTAT, 6)

#define SPI_IgnoreSlaveSelect(__STATE__)    SFR_ASSIGN(SPCTL, 7, __STATE__)
#define SPI_SetEnableState(__STATE__)       SFR_ASSIGN(SPCTL, 6, __STATE__)
#define SPI_SetDataOrderLSB(__STATE__)      SFR_ASSIGN(SPCTL, 5, __STATE__)
#define SPI_SetMasterMode(__STATE__)        SFR_ASSIGN(SPCTL, 4, __STATE__)
// CPOL, 0:idle low, 1:idl high
#define SPI_SetClockPolarHigh(__STATE__)    SFR_ASSIGN(SPCTL, 3, __STATE__)
// CPHA, 0:SS low drive, 1:SCLK front edge drive
#define SPI_SetClockFrontEdgeDrive(__STATE__) SFR_ASSIGN(SPCTL, 2, __STATE__)
/**
 * SPI Clock
*/
#define SPI_SetClockPrescaler(__PRE_SCALER__) (SPCTL = SPCTL & ~0x03 | ((__PRE_SCALER__) << 0))
/**
 * Alternative port selection
*/
#define SPI_SwitchPort(__ALTER_PORT__)    (P_SW1 = P_SW1 & ~(0x03 << 2) | ((__ALTER_PORT__) << 2))

#endif