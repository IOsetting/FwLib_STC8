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

#ifndef ___FW_ADC_H___
#define ___FW_ADC_H___

#include "fw_conf.h"
#include "fw_types.h"

#define ADC_SetPowerState(__STATE__)        SFR_ASSIGN(ADC_CONTR, 7, __STATE__)
#define ADC_Start()                         SFR_SET(ADC_CONTR, 6)
#define ADC_SamplingFinished()              (ADC_CONTR & (0x01 << 5))
#define ADC_ClearInterrupt()                SFR_RESET(ADC_CONTR, 5)
#define ADC_SetPWMTriggerState(__STATE__)   SFR_ASSIGN(ADC_CONTR, 4, __STATE__)

/**
 * ADC input channels selection
 *   Set PxM0/PxM1 to high-impedance input for selected I/O port, and set PxIE
 *   to shutdown digital input if you want to enable ADC in powerdown mode
 * 
 *                                                         STC8H8K64U                                                       
 *                                         STC8H3K64S4     STC8H2K64T       STC8H4K64TLCD               STC8G1K08     STC8G2K64S4        
 * STC8H1K28:             STC8H1K08        STC8H3K64S2     STC8H4K64TLR     STC8H4K64LCD    STC8G1K08A  STC8G1K08T    STC8G2K64S2                   
 *  0000 P1.0/ADC0         P1.0/ADC0        P1.0/ADC0       P1.0/ADC0        P1.0/ADC0       P3.0/ADC0   P1.0/ADC0     P1.0/ADC0                      
 *  0001 P1.1/ADC1         P1.1/ADC1        P1.1/ADC1       P1.1/ADC1        P1.1/ADC1       P3.1/ADC1   P1.1/ADC1     P1.1/ADC1                      
 *  0010 P1.2/ADC2         N/A              P1.2/ADC2       P5.4/ADC2        P5.4/ADC2       P3.2/ADC2   P1.2/ADC2     P1.2/ADC2                
 *  0011 P1.3/ADC3         N/A              N/A             P1.3/ADC3        P1.3/ADC3       P3.3/ADC3   P1.3/ADC3     P1.3/ADC3                  
 *  0100 P1.4/ADC4         N/A              N/A             P1.4/ADC4        P1.4/ADC4       P5.4/ADC4   P1.4/ADC4     P1.4/ADC4                   
 *  0101 P1.5/ADC5         N/A              N/A             P1.5/ADC5        P1.5/ADC5       P5.5/ADC5   P1.5/ADC5     P1.5/ADC5                     
 *  0110 P1.6/ADC6         N/A              P1.6/ADC6       P1.6/ADC6        P6.2/ADC6       N/A         P1.6/ADC6     P1.6/ADC6          
 *  0111 P1.7/ADC7         N/A              P1.7/ADC7       P1.7/ADC7        P6.3/ADC7       N/A         P1.7/ADC7     P1.7/ADC7          
 *  1000 P0.0/ADC8         P3.0/ADC8        P0.0/ADC8       P0.0/ADC8        P0.0/ADC8       N/A         P3.0/ADC8     P0.0/ADC8                
 *  1001 P0.1/ADC9         P3.1/ADC9        P0.1/ADC9       P0.1/ADC9        P0.1/ADC9       N/A         P3.1/ADC9     P0.1/ADC9                
 *  1010 P0.2/ADC10        P3.2/ADC10       P0.2/ADC10      P0.2/ADC10       P0.2/ADC10      N/A         P3.2/ADC10    P0.2/ADC10                      
 *  1011 P0.3/ADC11        P3.3/ADC11       P0.3/ADC11      P0.3/ADC11       P0.3/ADC11      N/A         P3.3/ADC11    P0.3/ADC11                      
 *  1100 N/A               P3.4/ADC12       P0.4/ADC12      P0.4/ADC12       P0.4/ADC12      N/A         P3.4/ADC12    P0.4/ADC12               
 *  1101 N/A               P3.5/ADC13       P0.5/ADC13      P0.5/ADC13       P0.5/ADC13      N/A         P3.5/ADC13    P0.5/ADC13               
 *  1110 N/A               P3.6/ADC14       P0.6/ADC14      P0.6/ADC14       P0.6/ADC14      N/A         P3.6/ADC14    P0.6/ADC14               
 *  1111 Internal 1.19V voltage reference 
*/
#define ADC_SetChannel(__CHANNEL__)         (ADC_CONTR = ADC_CONTR & ~0x0F | ((__CHANNEL__ & 0x0F) << 0))

/**
 * 10-bit in [ADC_RES,ADC_RESL]: STC8H1K28,STC8H1K08
 * 12-bit in [ADC_RES,ADC_RESL]: STC8H3K64S4,STC8H3K64S2,STC8H8K64U,STC8H2K64T,STC8H4K64TLR,STC8H4K64TLCD,STC8H4K64LCD
*/
#define ADC_SetResultAlignmentLeft()        SFR_RESET(ADCCFG, 5)
#define ADC_SetResultAlignmentRight()       SFR_SET(ADCCFG, 5)

/**
 * Time of one complete ADC conversion:
 *   10-bit ADC: (Switch + 1) + (Hold + 1) + (Sample + 1) + 10
 *   12-bit ADC: (Switch + 1) + (Hold + 1) + (Sample + 1) + 12
 * 
 * ADC conversion frequency:
 *   10-bit ADC Frequency ＝ SYSCLK / 2 / (__PRESCALER__ + 1) / [(Switch + 1) + (Hold + 1) + (Sample + 1) + 10]
 *   12-bit ADC Frequency ＝ SYSCLK / 2 / (__PRESCALER__ + 1) / [(Switch + 1) + (Hold + 1) + (Sample + 1) + 12]
 * 
*/

/**
 * ADC clock = SYSclk/2/(__PRESCALER__+1)
*/
#define ADC_SetClockPrescaler(__PRESCALER__)    (ADCCFG = ADCCFG & ~0x0F | ((__PRESCALER__) << 0))

/**
 * Channel switch time, 
 *  0: 1 ADC clock; 
 *  1: 2 ADC clocks
*/
#define ADC_SetChannelSwitchTime(__CLKS_1OR2__) SFR_ASSIGN(ADCTIM, 7, __CLKS_1OR2__)
/**
 * Channel hold time, 
 * 0x00: 1 ADC clock; 
 * 0x01: 2 ADC clocks
 * 0x02: 3 ADC clocks
 * 0x03: 4 ADC clocks
*/
#define ADC_SetChannelHoldTime(__CLKS_1TO4__)   (ADCTIM = ADCTIM & ~(0x03 << 5) | ((__CLKS_1TO4__) << 5))
/**
 * Sample time
 *   value should be equal or larger than 10
 * 0x00: 1 ADC clock; 
 * 0x01: 2 ADC clocks
 * ...
 * 0x1F: 32 ADC clocks
*/
#define ADC_SetSampleTime(__CLKS_1TO32__)       (ADCTIM = ADCTIM & ~(0x1F << 0) | ((__CLKS_1TO32__) << 0))

/**
 * Start ADC conversion, and return 8-bit result
*/
uint8_t ADC_Convert(void);

/**
 * Start ADC conversion, and return 16-bit high precision result
*/
uint16_t ADC_ConvertHP(void);

#endif
