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
 * Demo: STC8H1K08 P5.4 PWM output, duty cycle updated by TIM2 interrupt
 * 
 * P5.4  -> 1k Ω resistor -> LED1+
 * GND   -> LED1-
 * 
 * Note: PWM6 = PWMB_PWM2
*/
#include "fw_hal.h"

__BIT dir = SET;
uint8_t dc = 0;

INTERRUPT(Timer2_Routine, EXTI_VectTimer2)
{
    PWMB_PWM2_SetCaptureCompareValue(dc);
    UART1_TxHex(dc);
    UART1_TxString("\r\n");
    if (dir)
    {
        dc++;
        if (dc == 0xFF) dir = !dir;
    }
    else
    {
        dc--;
        if (dc == 0) dir = !dir;
    }
}

void main(void)
{
    SYS_SetClock();
    // UART1, baud 115200, baud source Timer1, 1T mode
    UART1_Config8bitUart(UART1_BaudSource_Timer1, HAL_State_ON, 115200);

    // Set GPIO pins output mode
    GPIO_P5_SetMode(GPIO_Pin_4, GPIO_Mode_Output_PP);
    // Turn off PWMB.2 before change its mode
    PWMB_PWM2_SetPortState(HAL_State_OFF);
    // Set PWMB.2 port direction output
    PWMB_PWM2_SetPortDirection(PWMB_PortDirOut);
    // Set PWMB.2 output low voltage when counter is less than target value
    PWMB_PWM2_ConfigOutputMode(PWM_OutputMode_PWM_LowIfLess);
    // Enable comparison value preload to make duty cycle changing smooth
    PWMB_PWM2_SetComparePreload(HAL_State_ON);
    // Turn on PWMB.2
    PWMB_PWM2_SetPortState(HAL_State_ON);

    // Set highest PWM clock
    PWMB_SetPrescaler(0);
    // PWM width = Period + 1 (side alignment), or AutoReloadPeriod * 2 (center alignment)
    PWMB_SetPeriod(0xFF);
    // Counter direction, down:from [PWMA_ARRH,PWMA_ARRL] to 0
    PWMB_SetCounterDirection(PWM_CounterDirection_Down);
    // Enable preload on reload-period
    PWMB_SetAutoReloadPreload(HAL_State_ON);
    // Enable output on PWMB.2
    PWMB_SetPinOutputState(PWM_Pin_2, HAL_State_ON);
    // Set PWMB.2 alternative ports to P5.4
    PWMB_PWM2_SetPort(PWMB_PWM6_AlterPort_P54);
    // Enable overall output
    PWMB_SetOverallState(HAL_State_ON);
    // Start counter
    PWMB_SetCounterState(HAL_State_ON);

    // 1T mode, prescaler:255+1, frequency: 100
    TIM_Timer2_Config(HAL_State_ON, 0xFF, 100);
    // Timer2 interrupt: ON
    EXTI_Timer2_SetIntState(HAL_State_ON);
    EXTI_Global_SetIntState(HAL_State_ON);
    TIM_Timer2_SetRunState(HAL_State_ON);

    while(1);
}