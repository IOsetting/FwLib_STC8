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

#ifndef ___FW_EXTI_H___
#define ___FW_EXTI_H___

#include "fw_conf.h"
#include "fw_types.h"

typedef enum
{
    EXTI_IntPriority_Lowest  = 0x00,
    EXTI_IntPriority_Low     = 0x01,
    EXTI_IntPriority_High    = 0x02,
    EXTI_IntPriority_Highest = 0x03,
} EXTI_IntPriority_t;

typedef enum
{
    EXTI_PortIntMode_Fall   = 0x00,
    EXTI_PortIntMode_Rise   = 0x01,
    EXTI_PortIntMode_Low    = 0x02,
    EXTI_PortIntMode_High   = 0x03,
} EXTI_PortIntMode_t;

#define EXTI_VectInt0       0
#define EXTI_VectTimer0     1
#define EXTI_VectInt1       2
#define EXTI_VectTimer1     3
#define EXTI_VectUART1      4
#define EXTI_VectADC        5
#define EXTI_VectLowVoltDect 6
#define EXTI_VectPCA        7
#define EXTI_VectUART2      8
#define EXTI_VectSPI        9
#define EXTI_VectInt2       10
#define EXTI_VectInt3       11
#define EXTI_VectTimer2     12
#define EXTI_VectInt4       16
#define EXTI_VectUART3      17
#define EXTI_VectUART4      18
#define EXTI_VectTimer3     19
#define EXTI_VectTimer4     20
#define EXTI_VectCMP        21
#define EXTI_VectPWM        22
#define EXTI_VectPWMFD      23
#define EXTI_VectI2C        24

#define EXTI_Global_SetIntState(__STATE__)  SBIT_ASSIGN(EA, __STATE__)
#define EXTI_Timer0_SetIntState(__STATE__)  SBIT_ASSIGN(ET0, __STATE__)
#define EXTI_Timer1_SetIntState(__STATE__)  SBIT_ASSIGN(ET1, __STATE__)
#define EXTI_ADC_SetIntState(__STATE__)     SBIT_ASSIGN(EADC, __STATE__)
#define EXTI_UART1_SetIntState(__STATE__)   SBIT_ASSIGN(ES, __STATE__)
#define EXTI_LowVoltDetect_SetIntState(__STATE__) SBIT_ASSIGN(ELVD, __STATE__)
#define EXTI_Int0_SetIntState(__STATE__)    SBIT_ASSIGN(EX0, __STATE__)
#define EXTI_Int1_SetIntState(__STATE__)    SBIT_ASSIGN(EX1, __STATE__)

#define EXTI_Int0_SetTrigByFall    SBIT_SET(IT0)      // Trigger by falling
#define EXTI_Int0_SetTrigByBoth    SBIT_RESET(IT0)    // Trigger by both rising and falling
#define EXTI_Int1_SetTrigByFall    SBIT_SET(IT1)      // Trigger by falling
#define EXTI_Int1_SetTrigByBoth    SBIT_RESET(IT1)    // Trigger by both rising and falling

#define EXTI_USB_SetIntState(__STATE__)     SFR_ASSIGN(IE2, 7, __STATE__)
#define EXTI_Timer4_SetIntState(__STATE__)  SFR_ASSIGN(IE2, 6, __STATE__)
#define EXTI_Timer3_SetIntState(__STATE__)  SFR_ASSIGN(IE2, 5, __STATE__)
#define EXTI_UART4_SetIntState(__STATE__)   SFR_ASSIGN(IE2, 4, __STATE__)
#define EXTI_UART3_SetIntState(__STATE__)   SFR_ASSIGN(IE2, 3, __STATE__)
#define EXTI_Timer2_SetIntState(__STATE__)  SFR_ASSIGN(IE2, 2, __STATE__)
#define EXTI_SPI_SetIntState(__STATE__)     SFR_ASSIGN(IE2, 1, __STATE__)
#define EXTI_UART2_SetIntState(__STATE__)   SFR_ASSIGN(IE2, 0, __STATE__)

#define EXTI_INT_Int4_ON            SFR_SET(INTCLKO, 6)
#define EXTI_INT_Int4_OFF           SFR_RESET(INTCLKO, 6)
#define EXTI_INT_Int3_ON            SFR_SET(INTCLKO, 5)
#define EXTI_INT_Int3_OFF           SFR_RESET(INTCLKO, 5)
#define EXTI_INT_Int2_ON            SFR_SET(INTCLKO, 4)
#define EXTI_INT_Int2_OFF           SFR_RESET(INTCLKO, 4)

#define EXTI_INT_CompRise_ON        SFR_SET(CMPCR1, 5)
#define EXTI_INT_CompRise_OFF       SFR_RESET(CMPCR1, 5)
#define EXTI_INT_CompFall_ON        SFR_SET(CMPCR1, 4)
#define EXTI_INT_CompFall_OFF       SFR_RESET(CMPCR1, 4)

#define EXTI_INT_I2cMaster_ON       SFRX_SET(I2CMSCR, 7)
#define EXTI_INT_I2cMaster_OFF      SFRX_RESET(I2CMSCR, 7)
#define EXTI_INT_I2cSlvRxStart_ON   SFRX_SET(I2CSLCR, 6)
#define EXTI_INT_I2cSlvRxStart_OFF  SFRX_RESET(I2CSLCR, 6)
#define EXTI_INT_I2cSlvRxEnd_ON     SFRX_SET(I2CSLCR, 5)
#define EXTI_INT_I2cSlvRxEnd_OFF    SFRX_RESET(I2CSLCR, 5)
#define EXTI_INT_I2cSlvTxEnd_ON     SFRX_SET(I2CSLCR, 4)
#define EXTI_INT_I2cSlvTxEnd_OFF    SFRX_RESET(I2CSLCR, 4)
#define EXTI_INT_I2cSlvRxStop_ON    SFRX_SET(I2CSLCR, 3)
#define EXTI_INT_I2cSlvRxStop_OFF   SFRX_RESET(I2CSLCR, 3)

#define EXTI_INT_PWM1_Break_ON      SFRX_SET(PWM1_IER, 7)
#define EXTI_INT_PWM1_Break_OFF     SFRX_RESET(PWM1_IER, 7)
#define EXTI_INT_PWM1_Int_ON        SFRX_SET(PWM1_IER, 6)
#define EXTI_INT_PWM1_Int_OFF       SFRX_RESET(PWM1_IER, 6)
#define EXTI_INT_PWM1_Comp_ON       SFRX_SET(PWM1_IER, 5)
#define EXTI_INT_PWM1_Comp_OFF      SFRX_RESET(PWM1_IER, 5)
#define EXTI_INT_PWM1_CapCH4_ON     SFRX_SET(PWM1_IER, 4)
#define EXTI_INT_PWM1_CapCH4_OFF    SFRX_RESET(PWM1_IER, 4)
#define EXTI_INT_PWM1_CapCH3_ON     SFRX_SET(PWM1_IER, 3)
#define EXTI_INT_PWM1_CapCH3_OFF    SFRX_RESET(PWM1_IER, 3)
#define EXTI_INT_PWM1_CapCH2_ON     SFRX_SET(PWM1_IER, 2)
#define EXTI_INT_PWM1_CapCH2_OFF    SFRX_RESET(PWM1_IER, 2)
#define EXTI_INT_PWM1_CapCH1_OFF    SFRX_SET(PWM1_IER, 1)
#define EXTI_INT_PWM1_CapCH1_ON     SFRX_RESET(PWM1_IER, 1)
#define EXTI_INT_PWM1_Update_OFF    SFRX_SET(PWM1_IER, 0)
#define EXTI_INT_PWM1_Update_ON     SFRX_RESET(PWM1_IER, 0)

#define EXTI_INT_PWM2_Break_ON      SFRX_SET(PWM2_IER, 7)
#define EXTI_INT_PWM2_Break_OFF     SFRX_RESET(PWM2_IER, 7)
#define EXTI_INT_PWM2_Int_ON        SFRX_SET(PWM2_IER, 6)
#define EXTI_INT_PWM2_Int_OFF       SFRX_RESET(PWM2_IER, 6)
#define EXTI_INT_PWM2_Comp_ON       SFRX_SET(PWM2_IER, 5)
#define EXTI_INT_PWM2_Comp_OFF      SFRX_RESET(PWM2_IER, 5)
#define EXTI_INT_PWM2_CapCH4_ON     SFRX_SET(PWM2_IER, 4)
#define EXTI_INT_PWM2_CapCH4_OFF    SFRX_RESET(PWM2_IER, 4)
#define EXTI_INT_PWM2_CapCH3_ON     SFRX_SET(PWM2_IER, 3)
#define EXTI_INT_PWM2_CapCH3_OFF    SFRX_RESET(PWM2_IER, 3)
#define EXTI_INT_PWM2_CapCH2_ON     SFRX_SET(PWM2_IER, 2)
#define EXTI_INT_PWM2_CapCH2_OFF    SFRX_RESET(PWM2_IER, 2)
#define EXTI_INT_PWM2_CapCH1_OFF    SFRX_SET(PWM2_IER, 1)
#define EXTI_INT_PWM2_CapCH1_ON     SFRX_RESET(PWM2_IER, 1)
#define EXTI_INT_PWM2_Update_OFF    SFRX_SET(PWM2_IER, 0)
#define EXTI_INT_PWM2_Update_ON     SFRX_RESET(PWM2_IER, 0)

#define EXTI_INT_LCM_ON             SFRX_SET(LCMIFCFG, 7)
#define EXTI_INT_LCM_OFF            SFRX_RESET(LCMIFCFG, 7)

#define EXTI_Port_SetInterrupt_ON(__PORT__, __PINS__)  do {P_SW2 = 0x80; SFRX(PxINTE + (__PORT__)) |=  (__PINS__); P_SW2 = 0x00;} while(0)
#define EXTI_Port_SetInterrupt_OFF(__PORT__, __PINS__) do {P_SW2 = 0x80; SFRX(PxINTE + (__PORT__)) &= ~(__PINS__); P_SW2 = 0x00;} while(0)

#define EXTI_Int0_SetIntPriority(__PRIORITY__)     SFR_DUAL_SET(IP, IPH, 0, __PRIORITY__)
#define EXTI_Timer0_SetIntPriority(__PRIORITY__)   SFR_DUAL_SET(IP, IPH, 1, __PRIORITY__)
#define EXTI_Int1_SetIntPriority(__PRIORITY__)     SFR_DUAL_SET(IP, IPH, 2, __PRIORITY__)
#define EXTI_Timer1_SetIntPriority(__PRIORITY__)   SFR_DUAL_SET(IP, IPH, 3, __PRIORITY__)
#define EXTI_UART1_SetIntPriority(__PRIORITY__)    SFR_DUAL_SET(IP, IPH, 4, __PRIORITY__)
#define EXTI_ADC_SetIntPriority(__PRIORITY__)      SFR_DUAL_SET(IP, IPH, 5, __PRIORITY__)
#define EXTI_LowVoltDetect_SetIntPriority(__PRIORITY__)    SFR_DUAL_SET(IP, IPH, 6, __PRIORITY__)

#define EXTI_UART2_SetIntPriority(__PRIORITY__)    SFR_DUAL_SET(IP2, IP2H, 0, __PRIORITY__)
#define EXTI_SPI_SetIntPriority(__PRIORITY__)      SFR_DUAL_SET(IP2, IP2H, 1, __PRIORITY__)
#define EXTI_PWM1_SetIntPriority(__PRIORITY__)     SFR_DUAL_SET(IP2, IP2H, 2, __PRIORITY__)
#define EXTI_PWM2_SetIntPriority(__PRIORITY__)     SFR_DUAL_SET(IP2, IP2H, 3, __PRIORITY__)
#define EXTI_Int4_SetIntPriority(__PRIORITY__)     SFR_DUAL_SET(IP2, IP2H, 4, __PRIORITY__)
#define EXTI_CMP_SetIntPriority(__PRIORITY__)      SFR_DUAL_SET(IP2, IP2H, 5, __PRIORITY__)
#define EXTI_I2c_SetIntPriority(__PRIORITY__)      SFR_DUAL_SET(IP2, IP2H, 6, __PRIORITY__)
#define EXTI_USB_SetIntPriority(__PRIORITY__)      SFR_DUAL_SET(IP2, IP2H, 7, __PRIORITY__)

#define EXTI_UART3_SetIntPriority(__PRIORITY__)    SFR_DUAL_SET(IP3, IP3H, 0, __PRIORITY__)
#define EXTI_UART4_SetIntPriority(__PRIORITY__)    SFR_DUAL_SET(IP3, IP3H, 1, __PRIORITY__)
#define EXTI_RTC_SetIntPriority(__PRIORITY__)      SFR_DUAL_SET(IP3, IP3H, 2, __PRIORITY__)

#define EXTI_Port_SetIntPriority(__PORT__, __PRIORITY__)    SFRX_DUAL_SET(PIN_IP, PIN_IPH, __PORT__, __PRIORITY__)

#define EXTI_Port_SetIntMode(__PORT__, __PINS__, __PORT_INT_MODE__) do { P_SW2 = 0x80;                                          \
            SFRX(PxIM0 + (__PORT__)) = SFRX(PxIM0 + (__PORT__)) & ~(__PINS__) | (((__PORT_INT_MODE__) & 0x01)? (__PINS__) : 0x00);  \
            SFRX(PxIM1 + (__PORT__)) = SFRX(PxIM1 + (__PORT__)) & ~(__PINS__) | (((__PORT_INT_MODE__) & 0x02)? (__PINS__) : 0x00);  \
        P_SW2 = 0x00; } while(0)

#endif
