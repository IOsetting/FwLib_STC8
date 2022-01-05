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
 * 
 * The ports for STC8G1K08-8Pin, STC8G1K08A are different:
 *      SS   MO   MI   SCLK
 * 00 - P5.5 P5.4 P3.3 P3.2,  01/10/11 - n/a
*/
typedef enum
{
    //            SS MOSI MISO SCLK
    SPI_AlterPort_P12P54_P13_P14_P15    = 0x00,
    SPI_AlterPort_P22_P23_P24_P25       = 0x01,
    SPI_AlterPort_P54_P40_P41_P43       = 0x02,
    SPI_AlterPort_P35_P34_P33_P32       = 0x03,
    SPI_AlterPort_8G1K08_8Pin           = 0x00,
} SPI_AlterPort_t;

typedef enum
{
    SPI_ClockPreScaler_4       = 0x00,
    SPI_ClockPreScaler_8       = 0x01,
    SPI_ClockPreScaler_16      = 0x02,
    SPI_ClockPreScaler_32or2   = 0x03,
} SPI_ClockPreScaler_t;

typedef enum
{
    SPI_ClockPhase_LeadingEdge  = 0x00, // Bits are sampled on the leading edge of SCLK
    SPI_ClockPhase_TrailingEdge = 0x01, // Bits are sampled on the trailing edge of SCLK
} SPI_ClockPhase_t;

typedef enum
{
    SPI_DataOrder_MSB       = 0x00, // High bits first
    SPI_DataOrder_LSB       = 0x01, // Low bits first
} SPI_DataOrder_t;

#define SPI_RxTxFinished()                  (SPSTAT & 0x80)
#define SPI_ClearInterrupt()                SFR_SET(SPSTAT, 7)
#define SPI_ClearWriteConflictInterrupt()   SFR_SET(SPSTAT, 6)
#define SPI_ClearInterrupts()               (SPSTAT |= 0xC0)

#define SPI_IgnoreSlaveSelect(__STATE__)    SFR_ASSIGN(SPCTL, 7, __STATE__)
#define SPI_SetEnabled(__STATE__)           SFR_ASSIGN(SPCTL, 6, __STATE__)
#define SPI_SetDataOrder(__ORDER__)         SFR_ASSIGN(SPCTL, 5, __ORDER__)
#define SPI_SetMasterMode(__STATE__)        SFR_ASSIGN(SPCTL, 4, __STATE__)

/**
 * Clock Polarity, CPOL
 *  0: clock line idles low
 *  1: clock line idles high
*/
#define SPI_SetClockPolarity(__STATE__)        SFR_ASSIGN(SPCTL, 3, __STATE__)
/**
 * Clock Phase (CPHA)
 *  0: bits are sampled on the leading clock edge
 *  1: bits are sampled on the trailing clock edge
*/
#define SPI_SetClockPhase(__PHASE__)        SFR_ASSIGN(SPCTL, 2, __PHASE__)
/**
 * SPI Clock
*/
#define SPI_SetClockPrescaler(__PRE_SCALER__) (SPCTL = SPCTL & ~0x03 | ((__PRE_SCALER__) << 0))
/**
 * Alternative ports
*/
#define SPI_SetPort(__ALTER_PORT__)    (P_SW1 = P_SW1 & ~(0x03 << 2) | ((__ALTER_PORT__) << 2))

uint8_t SPI_TxRx(uint8_t dat);
void SPI_TxRxBytes(uint8_t *pBuf, uint8_t len);

#endif
