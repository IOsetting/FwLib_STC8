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

#ifndef ___FW_UART_H___
#define ___FW_UART_H___

#include "fw_conf.h"
#include "fw_types.h"
#include "fw_exti.h"

extern __CODE char HEX_TABLE[16];

int16_t UART_Timer_InitValueCalculate(uint32_t sysclk, HAL_State_t _1TMode, uint32_t baudrate);


/**************************************************************************** /
 * UART1
*/

typedef enum
{
    UART1_BaudSource_Timer1 = 0x00,
    UART1_BaudSource_Timer2 = 0x01,
} UART1_BaudSource_t;

/**
 * Alternative ports
 * 
 * The ports for STC8G1K08-8Pin and STC8G1K08A are different:
 * 00 - P3.0 P3.1, 01 - P3.2 P3.3, 10 - P5.4 P5.5, 11 - n/a
*/
typedef enum
{
    UART1_AlterPort_P30_P31      = 0x00,
    UART1_AlterPort_P36_P37      = 0x01,
    UART1_AlterPort_P16_P17      = 0x10,
    UART1_AlterPort_P43_P44      = 0x11,
} UART1_AlterPort_t;

#define UART1_SetRxState(__STATE__)         SBIT_ASSIGN(REN, __STATE__)
#define UART1_ClearTxInterrupt()            SBIT_RESET(TI)
#define UART1_ClearRxInterrupt()            SBIT_RESET(RI)
#define UART1_WriteBuffer(__DATA__)         (SBUF = (__DATA__))
#define UART1_SetFrameErrDetect(__STATE__)  SFR_ASSIGN(PCON, 6, __STATE__)
#define UART1_SetBaudSource(__BAUD_SRC__)   SFR_ASSIGN(AUXR, 0, __BAUD_SRC__)
/**
 * Mode0: Synchronous shift serial mode, baudrate is fixed, provided by SYSCLK
 * Baud = (UART_M0x6 = 0)? (SYSCLK/12) : (SYSCLK/2)
*/
#define UART1_ConfigMode0FixedSyncSerial(__STATE__)        do{ SM0=0; SM1=0; SFR_ASSIGN(AUXR, 5, __STATE__);}while(0)
#define UART1_SetMode0Baudx6(__STATE__)     SFR_ASSIGN(AUXR, 5, __STATE__)
/**
 * Mode2: 9-bit UART mode, baudrate is fixed, provided by SYSCLK
 * Baud = (SMOD = 0)? (SYSCLK/64) : (SYSCLK/32)
*/
#define UART1_ConfigMode2Fixed9bitUart(__STATE__)            do{ SM0=1; SM1=0; SFR_ASSIGN(PCON, 7, __STATE__);}while(0)
#define UART1_SetTimer1Mode2Baudx2(__STATE__)   SFR_ASSIGN(PCON, 7, __STATE__)
/**
 * Alternative port selection: P30/P31, P36/P37, P16/P17, P43/P44
*/
#define UART1_SwitchPort(__ALTER_PORT__)    (P_SW1 = P_SW1 & ~(0x03 << 6) | ((__ALTER_PORT__) << 6))
/**
 * Mode1:
 *   8-bit UART; 
 *   dynamic baud-rate; 
 *   10-bit frame: 1 start, 8 data(lsb), 1 stop; 
 *   clocked by Timer1 or Timer2
 * 
*/
void UART1_Config8bitUart(UART1_BaudSource_t baudSource, HAL_State_t _1TMode, uint32_t baudrate);
/**
 * Mode3: 
 *   9-bit UART;
 *   dynamic baud-rate;
 *   11-bit frame: 1 start, 8 data(lsb), 1 programmable, 1 stop; 
 *   clocked by Timer1 or Timer2
*/
void UART1_Config9bitUart(UART1_BaudSource_t baudSource, HAL_State_t _1TMode, uint32_t baudrate);

/**
 * FIXME: If place this in first with following TXString(), sending may not work. didn't find the reason
*/
void UART1_TxChar(char dat);
void UART1_TxHex(uint8_t hex);
void UART1_TxString(uint8_t *str);


/**************************************************************************** /
 * UART2
*/

#define UART2_SetRxState(__STATE__)         SFR_ASSIGN(S2CON, 4, __STATE__)
#define UART2_ClearTxInterrupt()            SFR_RESET(S2CON, 1)
#define UART2_ClearRxInterrupt()            SFR_RESET(S2CON, 0)
#define UART2_WriteBuffer(__DATA__)         (S2BUF = (__DATA__))
#define UART2_TxFinished()                  (S2CON & (0x01 << 1))
#define UART2_Set8bitUART()                 SFR_RESET(S2CON, 7)
#define UART2_Set9bitUART()                 SFR_SET(S2CON, 7)
/**
 * Dynamic baud-rate, provided by Timer2
*/
void UART2_Config(HAL_State_t _1TMode, uint32_t baudrate);


void UART2_TxChar(char dat);
void UART2_TxHex(uint8_t hex);
void UART2_TxString(uint8_t *str);


/**************************************************************************** /
 * UART3
*/

#define UART3_SetBaudSource(__BAUD_SRC__)   SFR_ASSIGN(S3CON, 6, __BAUD_SRC__)
#define UART3_SetRxState(__STATE__)         SFR_ASSIGN(S3CON, 4, __STATE__)
#define UART3_Set8bitUART()                 SFR_RESET(S3CON, 7)
#define UART3_Set9bitUART()                 SFR_SET(S3CON, 7)
#define UART3_ClearTxInterrupt()            SFR_RESET(S3CON, 1)
#define UART3_ClearRxInterrupt()            SFR_RESET(S3CON, 0)
#define UART3_WriteBuffer(__DATA__)         (S3BUF = (__DATA__))

/**
 * dynamic baud-rate from timer2 or timer3
*/
void UART3_ConfigOnTimer2(HAL_State_t _1TMode, uint32_t baudrate);
void UART3_ConfigOnTimer3(HAL_State_t _1TMode, uint32_t baudrate);


/**************************************************************************** /
 * UART4
*/

#define UART4_SetBaudSource(__BAUD_SRC__)   SFR_ASSIGN(S4CON, 6, __BAUD_SRC__)
#define UART4_SetRxState(__STATE__)         SFR_ASSIGN(S4CON, 4, __STATE__)
#define UART4_Set8bitUART()                 SFR_RESET(S4CON, 7)
#define UART4_Set9bitUART()                 SFR_SET(S4CON, 7)
#define UART4_ClearTxInterrupt()            SFR_RESET(S4CON, 1)
#define UART4_ClearRxInterrupt()            SFR_RESET(S4CON, 0)
#define UART4_WriteBuffer(__DATA__)         (S4BUF = (__DATA__))

/**
 * dynamic baud-rate from timer2 or timer4
*/
void UART4_ConfigOnTimer2(HAL_State_t _1TMode, uint32_t baudrate);
void UART4_ConfigOnTimer4(HAL_State_t _1TMode, uint32_t baudrate);


#endif