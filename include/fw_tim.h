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

#ifndef ___FW_TIM_H___
#define ___FW_TIM_H___

#include "fw_conf.h"
#include "fw_types.h"
#include "fw_exti.h"

typedef enum
{
    TIM_TimerMode_16BitAuto         = 0x00,   // 16-bit auto-reload from [TH0,TL0](Timer0), [TH1,TL1](Timer1)
    TIM_TimerMode_16Bit             = 0x01,   // 16-bit no-auto-reload
    TIM_TimerMode_8BitAuto          = 0x02,   // 8-bit auto-reload from TH0(Timer0), TH1(Timer1)
    TIM_TimerMode_16BitAutoNoInt    = 0x03    // Uninterruptable 16-bit auto-reload, Timer0 only
} TIM_TimerMode_t;

int16_t TIM_Timer0n1_CalculateInitValue(uint16_t frequency, HAL_State_t freq1t, uint16_t limit);

/***************************** /
 * Timer 0
*/
#define TIM_Timer0_SetRunState(__STATE__)   SBIT_ASSIGN(TR0, __STATE__)
#define TIM_Timer0_SetGateState(__STATE__)  SFR_ASSIGN(TMOD, 3, __STATE__)
#define TIM_Timer0_SetFuncCounter           SFR_SET(TMOD, 2)
#define TIM_Timer0_SetFuncTimer             SFR_RESET(TMOD, 2)
// ON:FOSC, OFF:FOSC/12
#define TIM_Timer0_Set1TMode(__STATE__)     SFR_ASSIGN(AUXR, 7, __STATE__)
// Enable output on P3.5, when counter overflow, P3.5 switch voltage level
#define TIM_Timer0_SetOutput(__STATE__)     SFR_ASSIGN(INTCLKO, 0, __STATE__)
#define TIM_Timer0_SetMode(__TIM_TIMER_MODE__)  (TMOD = TMOD & ~(0x03 << 0) | ((__TIM_TIMER_MODE__) << 0))
#define TIM_Timer0_SetInitValue(__TH__, __TL__)  do{ TH0 = (__TH__); TL0 = (__TL__); }while(0)

void TIM_Timer0_Config(HAL_State_t freq1t, TIM_TimerMode_t mode, uint16_t frequency);


/***************************** /
 * Timer 1
*/
#define TIM_Timer1_SetRunState(__STATE__)   SBIT_ASSIGN(TR1, __STATE__)
#define TIM_Timer1_SetGateState(__STATE__)  SFR_ASSIGN(TMOD, 7, __STATE__)
#define TIM_Timer1_FuncCounter              SFR_SET(TMOD, 6)
#define TIM_Timer1_FuncTimer                SFR_RESET(TMOD, 6)
// ON:FOSC, OFF:FOSC/12
#define TIM_Timer1_Set1TMode(__STATE__)     SFR_ASSIGN(AUXR, 6, __STATE__)
// Enable output on P3.4, when counter overflow, P3.4 switch voltage level
#define TIM_Timer1_SetOutput(__STATE__)     SFR_ASSIGN(INTCLKO, 1, __STATE__)
#define TIM_Timer1_SetMode(__TIM_TIMER_MODE__)  (TMOD = TMOD & ~(0x03 << 4) | ((__TIM_TIMER_MODE__) << 4))
#define TIM_Timer1_SetInitValue(__TH__, __TL__)  do{ TH1 = (__TH__); TL1 = (__TL__); }while(0)

void TIM_Timer1_Config(HAL_State_t freq1t, TIM_TimerMode_t mode, uint16_t frequency);


/***************************** /
 * Timer 2,3,4 (STC8H3K only)
 * 
 *                     ||=> 12T Mode => |
 *                     |                |   |Counter|                     |=> TxIF Interrupt
 *  SYSCLK => TMxPS => |                |=> |Timer  | => TxR => TxH|TxL =>|
 *                     |                |                                 |=> TxCLKO => Output
 *                     ||=>  1T Mode => |
*/
#define TIM_Timer2_SetRunState(__STATE__)   SFR_ASSIGN(AUXR, 4, __STATE__)
#define TIM_Timer2_FuncCounter              SFR_SET(AUXR, 3)
#define TIM_Timer2_FuncTimer                SFR_RESET(AUXR, 3)
// ON:FOSC, OFF:FOSC/12
#define TIM_Timer2_Set1TMode(__STATE__)     SFR_ASSIGN(AUXR, 2, __STATE__)
// Enable output on P1.3, when counter overflow, P1.3 switch voltage level
#define TIM_Timer2_SetOutput(__STATE__)     SFR_ASSIGN(INTCLKO, 2, __STATE__)
#define TIM_Timer2_SetInitValue(__TH__, __TL__)  do{ T2H = (__TH__); T2L = (__TL__); }while(0)
// Timer2 Prescaler: [0, 255]
#define TIM_Timer2_SetPreScaler(__PRE__)  do{SFRX_ON(); TM2PS = (__PRE__); SFRX_OFF();}while(0)

void TIM_Timer2_Config(HAL_State_t freq1t, uint8_t prescaler, uint16_t frequency);


/***************************** /
 * Timer 3
*/
#define TIM_Timer3_SetRunState(__STATE__)   SFR_ASSIGN(T4T3M, 3, __STATE__)
#define TIM_Timer3_FuncCounter              SFR_SET(T4T3M, 2)
#define TIM_Timer3_FuncTimer                SFR_RESET(T4T3M, 2)
// ON:FOSC, OFF:FOSC/12
#define TIM_Timer3_Set1TMode(__STATE__)     SFR_ASSIGN(T4T3M, 1, __STATE__)
// Enable output on P0.4
#define TIM_Timer3_SetOutput(__STATE__)     SFR_ASSIGN(T4T3M, 0, __STATE__)
#define TIM_Timer3_SetInitValue(__TH__, __TL__)  do{ T3H = (__TH__); T3L = (__TL__); }while(0)
// Timer3 Prescaler: [0, 255]
#define TIM_Timer3_SetPreScaler(__PRE__)  do{SFRX_ON(); TM3PS = (__PRE__); SFRX_OFF();}while(0)

void TIM_Timer3_Config(HAL_State_t freq1t, uint8_t prescaler, uint16_t frequency, HAL_State_t intState);


/***************************** /
 * Timer 4
*/
#define TIM_Timer4_SetRunState(__STATE__)   SFR_ASSIGN(T4T3M, 7, __STATE__)
#define TIM_Timer4_FuncCounter              SFR_SET(T4T3M, 6)
#define TIM_Timer4_FuncTimer                SFR_RESET(T4T3M, 6)
// ON:FOSC, OFF:FOSC/12
#define TIM_Timer4_Set1TMode(__STATE__)     SFR_ASSIGN(T4T3M, 5, __STATE__)
// Enable output on P0.7
#define TIM_Timer4_SetOutput(__STATE__)     SFR_ASSIGN(T4T3M, 4, __STATE__)
#define TIM_Timer4_SetInitValue(__TH__, __TL__)  do{ T4H = (__TH__); T4L = (__TL__); }while(0)
// Timer4 Prescaler: [0, 255]
#define TIM_Timer4_SetPreScaler(__PRE__)  do{SFRX_ON(); TM4PS = (__PRE__); SFRX_OFF();}while(0)

void TIM_Timer4_Config(HAL_State_t freq1t, uint8_t prescaler, uint16_t frequency, HAL_State_t intState);


#endif