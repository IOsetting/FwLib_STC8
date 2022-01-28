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

/**
 * Demo: DAC voice output simulation
 * Board: STC8H3K32 (types with flash size >= 32KB)
 * 
 *  P1.0  -> 200R -> Speaker +
 *  GND           -> Speaker -
*/
#include "fw_hal.h"
#include "voice.h"

uint8_t dc = 0;
uint16_t voice_pos = 0, voice_size = 27451;

void PWM_Init()
{
    // Set GPIO pins output mode P10 -> PWMA.1P
    GPIO_P1_SetMode(GPIO_Pin_0, GPIO_Mode_Output_PP);
    // Turn off PWMA.1 before change its mode
    PWMA_PWM1_SetPortState(HAL_State_OFF);
    PWMA_PWM1N_SetPortState(HAL_State_OFF);
    // Set PWMA.1 port direction output
    PWMA_PWM1_SetPortDirection(PWMB_PortDirOut);
    // Set PWMA.1 output low voltage when counter is less than target value
    PWMA_PWM1_ConfigOutputMode(PWM_OutputMode_PWM_HighIfLess);
    // Enable comparison value preload to make duty cycle changing smooth
    PWMA_PWM1_SetComparePreload(HAL_State_ON);
    // Turn on PWMA.1
    PWMA_PWM1_SetPortState(HAL_State_ON);

    // Set PWM frequency to 16kHz, Fpwm = SYSCLK / (PWMx_PSCR + 1) / (PWMx_ARR + 1)
    // You will hear obvious noise if PWM frequency is less than 12kHz
    PWMA_SetPrescaler(8);
    // PWM width = Period + 1 (side alignment), or AutoReloadPeriod * 2 (center alignment)
    PWMA_SetPeriod(0xFF);
    // Counter direction, down:from [PWMA_ARRH,PWMA_ARRL] to 0
    PWMA_SetCounterDirection(PWM_CounterDirection_Down);
    // Enable preload on reload-period
    PWMA_SetAutoReloadPreload(HAL_State_ON);
    // Enable output on PWMA.1P
    PWMA_SetPinOutputState(PWM_Pin_1, HAL_State_ON);
    // Set PWMA.1 alternative ports to P1.0 and P1.1
    PWMA_PWM1_SetPort(PWMA_PWM1_AlterPort_P10_P11);
    // Enable overall output
    PWMA_SetOverallState(HAL_State_ON);
    // Start counter
    PWMA_SetCounterState(HAL_State_ON);
}

void Timer0_Init()
{
    TIM_Timer0_Config(HAL_State_ON, TIM_TimerMode_16BitAuto, 8000);
    EXTI_Timer0_SetIntState(HAL_State_ON);
    EXTI_Timer0_SetIntPriority(EXTI_IntPriority_High);
    EXTI_Global_SetIntState(HAL_State_ON);
    TIM_Timer0_SetRunState(HAL_State_ON);
}

INTERRUPT(Timer0_Routine, EXTI_VectTimer0)
{
    uint8_t dc;
    dc = voice_bulk[voice_pos++];
    PWMA_PWM1_SetCaptureCompareValue(dc);
    if (voice_pos == voice_size) voice_pos = 0;
}

void main(void)
{
    SYS_SetClock();
    PWM_Init();
    Timer0_Init();

    while(1);
}