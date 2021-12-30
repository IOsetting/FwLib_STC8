// Copyright 2021 IOsetting <iosetting@outlook.com>
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

#include "fw_rcc.h"

void RCC_SetSYSCLKSource(RCC_SYSCLKSource_t SYSCLKSource)
{
    P_SW2 = 0x80;
	if (SYSCLKSource == RCC_SYSCLKSource_HSI)
	{
		// Enable internal high speed rc osc 
		HIRCCR |= B10000000;
		while(!(HIRCCR & B00000001));
	}
	else if (SYSCLKSource == RCC_SYSCLKSource_HSE)
	{
		// Enable external high speed osc 
		XOSCCR |= B10000000;
		while(!(XOSCCR & B00000001));
	}
	else if (SYSCLKSource == RCC_SYSCLKSource_LSE)
	{
		// Enable external 32khz osc 
		X32KCR |= B10000000;
		while(!(X32KCR & B00000001));
	}
	else if (SYSCLKSource == RCC_SYSCLKSource_LSI)
	{
		// Enable internal 32khz rc osc 
		IRC32KCR |= B10000000;
		while(!(IRC32KCR & B00000001));
	}
	CKSEL = CKSEL & ~(B00000011) | SYSCLKSource;
	P_SW2 = 0x00;
}

void RCC_SetCLKDivider(uint8_t divider)
{
	P_SW2 = 0x80;
	CLKDIV = divider;
	P_SW2 = 0x00;
}

void RCC_SetIRC(RCC_IRCBand_t IRCBand, uint8_t IRTrim, RCC_LIRTrim_t LIRTrim)
{
	IRCBAND = IRCBAND & ~(B00000001) | IRCBand;
	IRTRIM = IRTrim;
	LIRTRIM = LIRTRIM & ~(B00000011) | LIRTrim;
}

void RCC_SoftwareReset(RCC_SoftwareReset_t SoftwareReset)
{
	/* IAP_CONTR = IAP_CONTR & ~(B0011 << 5) | (((SoftwareReset << 1) | B0001) << 5);*/
	IAP_CONTR |= ((SoftwareReset << 1) | B00000001) << 5;
}

void RCC_ConfigLowVoltReset(
    HAL_State_t HAL_State, 
    RCC_LowVoltResetPinAF_t LowVoltResetPinAF,
    RCC_LowVoltDetectVolt_t LowVoltDetectVolt)
{
	RSTCFG = RSTCFG 
		& ~(B01000000 | B00010000 | B00000011)
		| ((HAL_State << 6)|(LowVoltResetPinAF << 4)|(LowVoltDetectVolt));
}

void RCC_SetPowerDownWakeupTimer(HAL_State_t HAL_State, uint16_t countdown)
{
	WKTCH = WKTCH & ~B10000000 | (HAL_State << 7);
	WKTCH = WKTCH & ~B01111111 | ((countdown >> 8) & B01111111);
	WKTCL = countdown & 0xFF;
}

void RCC_SetPowerDownMode(HAL_State_t HAL_State)
{
	PCON |= (HAL_State << 1);
}

void RCC_SetIdleMode(HAL_State_t HAL_State)
{
	PCON |= (HAL_State);
}
