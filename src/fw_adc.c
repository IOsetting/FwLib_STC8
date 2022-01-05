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

#include "fw_adc.h"


uint8_t ADC_Convert(void)
{
    ADC_Start();
    NOP();
    NOP();
    while (!ADC_SamplingFinished());
    ADC_ClearInterrupt();
    return ADC_RES;
}

uint16_t ADC_ConvertHP(void)
{
    int16_t res;
    ADC_Start();
    NOP();
    NOP();
    while (!ADC_SamplingFinished());
    ADC_ClearInterrupt();
    res = ADC_RES;
    return (res << 8) + ADC_RESL;
}