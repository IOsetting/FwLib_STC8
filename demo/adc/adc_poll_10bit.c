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
 * STC8H3K64S2
 *   AGrnd   -> GND
 *   AVcc    -> VCC
 *   AVref   -> VCC 
 *   Vcc     -> VCC
 *   Gnd     -> GND
 *   ADC1    -> Test voltage
 * 
 * STC8H1K08
 *   AVref   -> VCC 
 *   Vcc     -> VCC
 *   Gnd     -> GND
 *   ADC1    -> Test voltage
*/
#include "fw_hal.h"

void main(void)
{
    uint16_t res;
    SYS_SetClock();
    // For debug print
    UART1_Config8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200);
    // Set ADC1(GPIO P1.1) HIP
    GPIO_P1_SetMode(GPIO_Pin_1, GPIO_Mode_Input_HIP);
    // Channel: ADC1
    ADC_SetChannel(0x01);
    // ADC Clock = SYSCLK / 2 / (1+1) = SYSCLK / 4
    ADC_SetClockPrescaler(0x01);
    // Right alignment, high 2-bit/4-bit in ADC_RES, low 8-bit in ADC_RESL
    ADC_SetResultAlignmentRight();
    // Turn on ADC power
    ADC_SetPowerState(HAL_State_ON);

    while(1)
    {
        ADC_Start();
        NOP();
        NOP();
        while (!ADC_SamplingFinished());
        ADC_ClearInterrupt();
        /*
        res = ADC_RESL;
        res |= (ADC_RES & 0x0F) << 8;
        */
        UART1_TxHex(ADC_RES);
        UART1_TxHex(ADC_RESL);
        UART1_TxString("\r\n");
        SYS_Delay(100);
    }
}