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
 * Demo: 2-channel complementary output
 * 
 * P1.0  -> 1k Ω resistor -> LED1+
 * P1.1  -> 1k Ω resistor -> LED2+
 * GND   -> LED1-
 * GND   -> LED2-
*/
#include "fw_hal.h"


void main(void)
{
    __BIT dir = SET;
    uint8_t dc = 0; 

    SYS_SetClock();
    // UART1, baud 115200, baud source Timer2, 1T mode
    UART1_Config8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200);

    // Set GPIO pins output mode
    GPIO_P1_SetMode(GPIO_Pin_0|GPIO_Pin_1, GPIO_Mode_Output_PP);
    // Turn off PWMA.1 before change its mode
    PWMA_PWM1_SetPortState(HAL_State_OFF);
    PWMA_PWM1N_SetPortState(HAL_State_OFF);
    // Set PWMA.1 port direction output
    PWMA_PWM1_SetPortDirection(PWMB_PortDirOut);
    // Set PWMA.1 output low voltage when counter is less than target value
    PWMA_PWM1_ConfigOutputMode(PWM_OutputMode_PWM_LowIfLess);
    // Enable comparison value preload to make duty cycle changing smooth
    PWMA_PWM1_SetComparePreload(HAL_State_ON);
    // Turn on PWMA.1
    PWMA_PWM1_SetPortState(HAL_State_ON);
    // Turn on PWMA.1 complementary output
    PWMA_PWM1N_SetPortState(HAL_State_ON);
    // Set highest PWM clock
    PWMA_SetPrescaler(0);
    // PWM width = Period + 1 (side alignment), or AutoReloadPeriod * 2 (center alignment)
    PWMA_SetPeriod(0xFF);
    // Counter direction, down:from [PWMA_ARRH,PWMA_ARRL] to 0
    PWMA_SetCounterDirection(PWM_CounterDirection_Down);
    // Enable preload on reload-period
    PWMA_SetAutoReloadPreload(HAL_State_ON);
    // Enable output on PWMA.1P, PWMA.1N
    PWMA_SetPinOutputState(PWM_Pin_1|PWM_Pin_1N, HAL_State_ON);
    // Set PWMA.1 alternative ports to P1.0 and P1.1
    PWMA_PWM1_SetPort(PWMA_PWM1_AlterPort_P10_P11);
    // Enable overall output
    PWMA_SetOverallState(HAL_State_ON);
    // Start counter
    PWMA_SetCounterState(HAL_State_ON);

    while(1)
    {
        PWMA_PWM1_SetCaptureCompareValue(dc);
        UART1_TxHex(0xFF);
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
        UART1_TxString("\r\n");
        SYS_Delay(10);
    }
}