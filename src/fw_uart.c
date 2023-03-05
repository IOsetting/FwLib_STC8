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

#include "fw_uart.h"
#include "fw_tim.h"
#include "fw_sys.h"


int16_t UART_Timer_InitValueCalculate(uint32_t sysclk, HAL_State_t _1TMode, uint32_t baudrate)
{
    uint32_t value;
    value = sysclk / (4 * baudrate);
    if (!_1TMode)
        value = value / 12;
    if (value > 0xFFFF)
        return 0;
    else
        return 0xFFFF - value + 1;
}

/**************************************************************************** /
 * UART1
*/

void _UART1_ConfigDynUart(UART1_BaudSource_t baudSource, HAL_State_t _1TMode, int16_t init)
{
    UART1_SetBaudSource(baudSource);
    // Timer1 configuration. Mode0 only, mode2 is covered by mode0 so it is unnecessary.
    if (baudSource == UART1_BaudSource_Timer1)
    {
        TIM_Timer1_Set1TMode(_1TMode);
        TIM_Timer1_SetMode(TIM_TimerMode_16BitAuto);
        TIM_Timer1_SetInitValue(init >> 8, init & 0xFF);
        TIM_Timer1_SetRunState(HAL_State_ON);
    }
    // Timer2 configuration
    else
    {
        // Timer2: 1T mode and initial value. prescaler is ignored, no interrupt.
        TIM_Timer2_Set1TMode(_1TMode);
        TIM_Timer2_SetInitValue(init >> 8, init & 0xFF);
        TIM_Timer2_SetRunState(HAL_State_ON);
    }
}
void UART1_Config8bitUart(UART1_BaudSource_t baudSource, HAL_State_t _1TMode, uint32_t baudrate)
{
    uint16_t init;
    SM0=0; SM1=1;
    init = UART_Timer_InitValueCalculate(__SYSCLOCK, _1TMode, baudrate);
    _UART1_ConfigDynUart(baudSource, _1TMode, init);
}

void UART1_Config9bitUart(UART1_BaudSource_t baudSource, HAL_State_t _1TMode, uint32_t baudrate)
{
    uint16_t init;
    SM0=1; SM1=1;
    init = UART_Timer_InitValueCalculate(__SYSCLOCK, _1TMode, baudrate);
    _UART1_ConfigDynUart(baudSource, _1TMode, init);
}

void UART1_TxChar(char dat)
{
    UART1_WriteBuffer(dat);
    while(!TI);
    UART1_ClearTxInterrupt();
}

void UART1_TxHex(uint8_t hex)
{
    UART1_TxChar(HEX_TABLE[hex >> 4]);
    UART1_TxChar(HEX_TABLE[hex & 0xF]);
}

void UART1_TxString(uint8_t *str)
{
    while (*str) UART1_TxChar(*str++);
}

int putchar(int dat) {
    UART1_WriteBuffer(dat);
    while(!TI);
    UART1_ClearTxInterrupt();
    return dat;
}


/**************************************************************************** /
 * UART2
*/

void UART2_Config(HAL_State_t _1TMode, uint32_t baudrate)
{
    uint16_t init;

    init = UART_Timer_InitValueCalculate(__SYSCLOCK, _1TMode, baudrate);
    // Timer2: 1T mode and initial value. prescaler is ignored, no interrupt.
    TIM_Timer2_Set1TMode(_1TMode);
    TIM_Timer2_SetInitValue(init >> 8, init & 0xFF);
    TIM_Timer2_SetRunState(HAL_State_ON);
}

void UART2_TxChar(char dat)
{
    UART2_WriteBuffer(dat);
    while(!UART2_TxFinished());
    UART2_ClearTxInterrupt();
}

void UART2_TxHex(uint8_t hex)
{
    UART2_TxChar(HEX_TABLE[hex >> 4]);
    UART2_TxChar(HEX_TABLE[hex & 0xF]);
}

void UART2_TxString(uint8_t *str)
{
    while (*str) UART2_TxChar(*str++);
}


/**************************************************************************** /
 * UART3
*/

void UART3_ConfigOnTimer2(HAL_State_t _1TMode, uint32_t baudrate)
{
    uint16_t init;

    UART3_SetBaudSource(0x00);
    init = UART_Timer_InitValueCalculate(__SYSCLOCK, _1TMode, baudrate);
    // Timer2: 1T mode and initial value. prescaler is ignored, no interrupt.
    TIM_Timer2_Set1TMode(_1TMode);
    TIM_Timer2_SetInitValue(init >> 8, init & 0xFF);
    TIM_Timer2_SetRunState(HAL_State_ON);
}

void UART3_ConfigOnTimer3(HAL_State_t _1TMode, uint32_t baudrate)
{
    uint16_t init;

    UART3_SetBaudSource(0x01);
    init = UART_Timer_InitValueCalculate(__SYSCLOCK, _1TMode, baudrate);
    // Timer3: 1T mode and initial value. prescaler is ignored, no interrupt.
    TIM_Timer3_Set1TMode(_1TMode);
    TIM_Timer3_SetInitValue(init >> 8, init & 0xFF);
    TIM_Timer3_SetRunState(HAL_State_ON);
}


/**************************************************************************** /
 * UART4
*/

void UART4_ConfigOnTimer2(HAL_State_t _1TMode, uint32_t baudrate)
{
    uint16_t init;

    UART4_SetBaudSource(0x00);
    init = UART_Timer_InitValueCalculate(__SYSCLOCK, _1TMode, baudrate);
    TIM_Timer2_Set1TMode(_1TMode);
    TIM_Timer2_SetInitValue(init >> 8, init & 0xFF);
    TIM_Timer2_SetRunState(HAL_State_ON);
}

void UART4_ConfigOnTimer4(HAL_State_t _1TMode, uint32_t baudrate)
{
    uint16_t init;

    UART4_SetBaudSource(0x01);
    init = UART_Timer_InitValueCalculate(__SYSCLOCK, _1TMode, baudrate);
    TIM_Timer4_Set1TMode(_1TMode);
    TIM_Timer4_SetInitValue(init >> 8, init & 0xFF);
    TIM_Timer4_SetRunState(HAL_State_ON);
}
