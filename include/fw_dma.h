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

#ifndef ___FW_DMA_H___
#define ___FW_DMA_H___

#include "fw_conf.h"
#include "fw_types.h"

typedef enum
{
    DMA_BusPriority_Lowest  = 0x00,
    DMA_BusPriority_Low     = 0x01,
    DMA_BusPriority_High    = 0x02,
    DMA_BusPriority_Highest = 0x03,
} DMA_BusPriority_t;

/**************************************************************************** /
 * DMA M2M
*/

#define DMA_M2M_SetSrcAddrIncrement(__STATE__)      SFRX_ASSIGN(DMA_M2M_CFG, 5, __STATE__)
#define DMA_M2M_SetDstAddrIncrement(__STATE__)      SFRX_ASSIGN(DMA_M2M_CFG, 4, __STATE__)
#define DMA_M2M_SetBusPriority(__PRI__)             SFRX_ASSIGN2BIT(DMA_M2M_CFG, 0, __PRI__)
#define DMA_M2M_SetEnabled(__STATE__)               SFRX_ASSIGN(DMA_M2M_CR, 7, __STATE__)
#define DMA_M2M_Start()                             SFRX_SET(DMA_M2M_CR, 6)
#define DMA_M2M_ClearInterrupt()                    SFRX_RESET(DMA_M2M_STA, 0)
/**
 * Transfer size = __LEN__ + 1
*/
#define DMA_M2M_SetTxLength(__LEN__)                do{SFRX_ON(); DMA_M2M_AMT = (__LEN__); SFRX_OFF();}while(0)
#define DMA_M2M_SetSrcAddr(__16BIT_ADDR__)          do{   \
                                                        SFRX_ON(); \
                                                        (DMA_M2M_TXAH = ((__16BIT_ADDR__) >> 8)); \
                                                        (DMA_M2M_TXAL = ((__16BIT_ADDR__) & 0xFF)); \
                                                        SFRX_OFF(); \
                                                    } while(0)
#define DMA_M2M_SetDstAddr(__16BIT_ADDR__)          do{   \
                                                        SFRX_ON(); \
                                                        (DMA_M2M_RXAH = ((__16BIT_ADDR__) >> 8)); \
                                                        (DMA_M2M_RXAL = ((__16BIT_ADDR__) & 0xFF)); \
                                                        SFRX_OFF(); \
                                                    } while(0)

/**************************************************************************** /
 * DMA ADC
*/

typedef enum
{
    DMA_ADC_ConvTimes_1     = 0x00,
    DMA_ADC_ConvTimes_2     = 0x08,
    DMA_ADC_ConvTimes_4     = 0x09,
    DMA_ADC_ConvTimes_8     = 0x0a,
    DMA_ADC_ConvTimes_16    = 0x0b,
    DMA_ADC_ConvTimes_32    = 0x0c,
    DMA_ADC_ConvTimes_64    = 0x0d,
    DMA_ADC_ConvTimes_128   = 0x0e,
    DMA_ADC_ConvTimes_256   = 0x0f,
} DMA_ADC_ConvTimes_t;

#define DMA_ADC_SetBusPriority(__PRI__)             SFRX_ASSIGN2BIT(DMA_ADC_CFG, 0, __PRI__)
#define DMA_ADC_SetEnabled(__STATE__)               SFRX_ASSIGN(DMA_ADC_CR, 7, __STATE__)
#define DMA_ADC_Start()                             SFRX_SET(DMA_ADC_CR, 6)
#define DMA_ADC_ClearInterrupt()                    SFRX_RESET(DMA_ADC_STA, 0)
#define DMA_ADC_SetDstAddr(__16BIT_ADDR__)          do{   \
                                                        SFRX_ON(); \
                                                        (DMA_ADC_RXAH = ((__16BIT_ADDR__) >> 8)); \
                                                        (DMA_ADC_RXAL = ((__16BIT_ADDR__) & 0xFF)); \
                                                        SFRX_OFF(); \
                                                    } while(0)
#define DMA_ADC_SetConvTimes(__TIMES__)             do{   \
                                                        SFRX_ON(); \
                                                        DMA_ADC_CFG2 = DMA_ADC_CFG2 & ~(0x0F) | ((__TIMES__) & 0x0F); \
                                                        SFRX_OFF(); \
                                                    } while(0)
/**
 * auto-scann channels. scanning always starts from lower number channels.
 * 
 * @param __16BIT_CHANNEL__: from high to low each bit stands for one ADC channel, 
 *                           start from ADC15 to ADC0, e.g. 0x11 means ADC8 and ADC0
*/
#define DMA_ADC_EnableChannels(__16BIT_CHANNEL__)   do{   \
                                                        SFRX_ON(); \
                                                        DMA_ADC_CHSW0 = (__CHANNEL__ >> 8) & 0xFF; \
                                                        DMA_ADC_CHSW1 = __CHANNEL__ & 0xFF; \
                                                        SFRX_OFF(); \
                                                    } while(0)



/**************************************************************************** /
 * DMA SPI
*/



#endif
