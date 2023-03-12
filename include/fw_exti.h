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
#define EXTI_VectUser       13  // 006BH, for Cx51 vector hack
#define EXTI_VectInt4       16
#define EXTI_VectUART3      17
#define EXTI_VectUART4      18
#define EXTI_VectTimer3     19
#define EXTI_VectTimer4     20
#define EXTI_VectCMP        21

#if (__CONF_MCU_TYPE == 1  ) || (__CONF_MCU_TYPE == 2  )
#define EXTI_VectPWM0       22
#define EXTI_VectPWM0FD     23
#endif

#define EXTI_VectI2C        24

#if (__CONF_MCU_TYPE == 3  )
#define EXTI_VectUSB        25
#define EXTI_VectPWMA       26
#define EXTI_VectPWMB       27
#endif

#if (__CONF_MCU_TYPE == 2  )
#define EXTI_VectPWM1       28
#define EXTI_VectPWM2       29
#define EXTI_VectPWM3       30
#define EXTI_VectPWM4       31
#define EXTI_VectPWM5       32  // 0103H
#define EXTI_VectPWM2FD     33  // 010BH
#define EXTI_VectPWM4FD     34  // 0113H
#endif

#if (__CONF_MCU_TYPE == 2  ) || (__CONF_MCU_TYPE == 3  )
#define EXTI_VectTKSU       35  // 011BH
#endif

#if (__CONF_MCU_TYPE == 3  )
#define EXTI_VectRTC        36  // 0123H
#endif

#if (__CONF_MCU_TYPE == 1  ) || (__CONF_MCU_TYPE == 3  )
#define EXTI_VectP0         37  // 012BH
#define EXTI_VectP1         38  // 0133H
#define EXTI_VectP2         39  // 013BH
#define EXTI_VectP3         40  // 0143H
#define EXTI_VectP4         41  // 014BH
#define EXTI_VectP5         42  // 0153H
#define EXTI_VectP6         43  // 015BH
#define EXTI_VectP7         44  // 0163H
#define EXTI_VectP8         45  // 016BH
#define EXTI_VectP9         46  // 0173H
#define EXTI_VectDMA_M2M    47
#define EXTI_VectDMA_ADC    48
#define EXTI_VectDMA_SPI    49
#define EXTI_VectDMA_UR1T   50
#define EXTI_VectDMA_UR1R   51
#define EXTI_VectDMA_UR2T   52
#define EXTI_VectDMA_UR2R   53
#define EXTI_VectDMA_UR3T   54
#define EXTI_VectDMA_UR3R   55
#define EXTI_VectDMA_UR4T   56
#define EXTI_VectDMA_UR4R   57
#define EXTI_VectDMA_LCM    58
#define EXTI_VectLCM        59
#endif

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

#define EXTI_Int4_SetIntState(__STATE__)    SFR_ASSIGN(INTCLKO, 6, __STATE__)
#define EXTI_Int3_SetIntState(__STATE__)    SFR_ASSIGN(INTCLKO, 5, __STATE__)
#define EXTI_Int2_SetIntState(__STATE__)    SFR_ASSIGN(INTCLKO, 4, __STATE__)

#define EXTI_CMP_SetRiseIntState(__STATE__) SFR_ASSIGN(CMPCR1, 5, __STATE__)
#define EXTI_CMP_SetFallIntState(__STATE__) SFR_ASSIGN(CMPCR1, 4, __STATE__)

#define EXTI_I2C_SetMstIntState(__STATE__)      SFRX_ASSIGN(I2CMSCR, 7, __STATE__)
#define EXTI_I2C_SetSlvStartIntState(__STATE__) SFRX_ASSIGN(I2CSLCR, 6, __STATE__)
#define EXTI_I2C_SetSlvRecvIntState(__STATE__)  SFRX_ASSIGN(I2CSLCR, 5, __STATE__)
#define EXTI_I2C_SetSlvSendIntState(__STATE__)  SFRX_ASSIGN(I2CSLCR, 4, __STATE__)
#define EXTI_I2C_SetSlvStopIntState(__STATE__)  SFRX_ASSIGN(I2CSLCR, 3, __STATE__)

#define EXTI_RTC_SetAlarmIntState(__STATE__)    SFRX_ASSIGN(RTCIEN, 7, __STATE__)
#define EXTI_RTC_SetDayIntState(__STATE__)      SFRX_ASSIGN(RTCIEN, 6, __STATE__)
#define EXTI_RTC_SetHourIntState(__STATE__)     SFRX_ASSIGN(RTCIEN, 5, __STATE__)
#define EXTI_RTC_SetMinuteIntState(__STATE__)   SFRX_ASSIGN(RTCIEN, 4, __STATE__)
#define EXTI_RTC_SetSecondIntState(__STATE__)   SFRX_ASSIGN(RTCIEN, 3, __STATE__)
#define EXTI_RTC_SetSecondDiv2IntState(__STATE__)   SFRX_ASSIGN(RTCIEN, 2, __STATE__)
#define EXTI_RTC_SetSecondDiv8IntState(__STATE__)   SFRX_ASSIGN(RTCIEN, 1, __STATE__)
#define EXTI_RTC_SetSecondDiv32IntState(__STATE__)  SFRX_ASSIGN(RTCIEN, 0, __STATE__)

#define EXTI_DMA_M2M_SetIntState(__STATE__)     SFRX_ASSIGN(DMA_M2M_CFG, 7, __STATE__)
#define EXTI_DMA_ADC_SetIntState(__STATE__)     SFRX_ASSIGN(DMA_ADC_CFG, 7, __STATE__)
#define EXTI_DMA_SPI_SetIntState(__STATE__)     SFRX_ASSIGN(DMA_SPI_CFG, 7, __STATE__)
#define EXTI_DMA_UART1T_SetIntState(__STATE__)  SFRX_ASSIGN(DMA_UR1T_CFG, 7, __STATE__)
#define EXTI_DMA_UART1R_SetIntState(__STATE__)  SFRX_ASSIGN(DMA_UR1R_CFG, 7, __STATE__)
#define EXTI_DMA_UART2T_SetIntState(__STATE__)  SFRX_ASSIGN(DMA_UR2T_CFG, 7, __STATE__)
#define EXTI_DMA_UART2R_SetIntState(__STATE__)  SFRX_ASSIGN(DMA_UR2R_CFG, 7, __STATE__)
#define EXTI_DMA_UART3T_SetIntState(__STATE__)  SFRX_ASSIGN(DMA_UR3T_CFG, 7, __STATE__)
#define EXTI_DMA_UART3R_SetIntState(__STATE__)  SFRX_ASSIGN(DMA_UR3R_CFG, 7, __STATE__)
#define EXTI_DMA_UART4T_SetIntState(__STATE__)  SFRX_ASSIGN(DMA_UR4T_CFG, 7, __STATE__)
#define EXTI_DMA_UART4R_SetIntState(__STATE__)  SFRX_ASSIGN(DMA_UR4R_CFG, 7, __STATE__)
#define EXTI_DMA_LCM_SetIntState(__STATE__)     SFRX_ASSIGN(DMA_LCM_CFG, 7, __STATE__)

#define EXTI_INT_PWMA_Break_ON      SFRX_SET(PWMA_IER, 7)
#define EXTI_INT_PWMA_Break_OFF     SFRX_RESET(PWMA_IER, 7)
#define EXTI_INT_PWMA_Int_ON        SFRX_SET(PWMA_IER, 6)
#define EXTI_INT_PWMA_Int_OFF       SFRX_RESET(PWMA_IER, 6)
#define EXTI_INT_PWMA_Comp_ON       SFRX_SET(PWMA_IER, 5)
#define EXTI_INT_PWMA_Comp_OFF      SFRX_RESET(PWMA_IER, 5)
#define EXTI_INT_PWMA_CapCH4_ON     SFRX_SET(PWMA_IER, 4)
#define EXTI_INT_PWMA_CapCH4_OFF    SFRX_RESET(PWMA_IER, 4)
#define EXTI_INT_PWMA_CapCH3_ON     SFRX_SET(PWMA_IER, 3)
#define EXTI_INT_PWMA_CapCH3_OFF    SFRX_RESET(PWMA_IER, 3)
#define EXTI_INT_PWMA_CapCH2_ON     SFRX_SET(PWMA_IER, 2)
#define EXTI_INT_PWMA_CapCH2_OFF    SFRX_RESET(PWMA_IER, 2)
#define EXTI_INT_PWMA_CapCH1_OFF    SFRX_SET(PWMA_IER, 1)
#define EXTI_INT_PWMA_CapCH1_ON     SFRX_RESET(PWMA_IER, 1)
#define EXTI_INT_PWMA_Update_OFF    SFRX_SET(PWMA_IER, 0)
#define EXTI_INT_PWMA_Update_ON     SFRX_RESET(PWMA_IER, 0)

#define EXTI_INT_PWMB_Break_ON      SFRX_SET(PWMB_IER, 7)
#define EXTI_INT_PWMB_Break_OFF     SFRX_RESET(PWMB_IER, 7)
#define EXTI_INT_PWMB_Int_ON        SFRX_SET(PWMB_IER, 6)
#define EXTI_INT_PWMB_Int_OFF       SFRX_RESET(PWMB_IER, 6)
#define EXTI_INT_PWMB_Comp_ON       SFRX_SET(PWMB_IER, 5)
#define EXTI_INT_PWMB_Comp_OFF      SFRX_RESET(PWMB_IER, 5)
#define EXTI_INT_PWMB_CapCH4_ON     SFRX_SET(PWMB_IER, 4)
#define EXTI_INT_PWMB_CapCH4_OFF    SFRX_RESET(PWMB_IER, 4)
#define EXTI_INT_PWMB_CapCH3_ON     SFRX_SET(PWMB_IER, 3)
#define EXTI_INT_PWMB_CapCH3_OFF    SFRX_RESET(PWMB_IER, 3)
#define EXTI_INT_PWMB_CapCH2_ON     SFRX_SET(PWMB_IER, 2)
#define EXTI_INT_PWMB_CapCH2_OFF    SFRX_RESET(PWMB_IER, 2)
#define EXTI_INT_PWMB_CapCH1_OFF    SFRX_SET(PWMB_IER, 1)
#define EXTI_INT_PWMB_CapCH1_ON     SFRX_RESET(PWMB_IER, 1)
#define EXTI_INT_PWMB_Update_OFF    SFRX_SET(PWMB_IER, 0)
#define EXTI_INT_PWMB_Update_ON     SFRX_RESET(PWMB_IER, 0)

#define EXTI_INT_LCM_ON             SFRX_SET(LCMIFCFG, 7)
#define EXTI_INT_LCM_OFF            SFRX_RESET(LCMIFCFG, 7)

#define EXTI_Port_SetInterrupt_ON(__PORT__, __PINS__)  do {SFRX_ON(); SFRX(PxINTE + (__PORT__)) |=  (__PINS__); SFRX_OFF();} while(0)
#define EXTI_Port_SetInterrupt_OFF(__PORT__, __PINS__) do {SFRX_ON(); SFRX(PxINTE + (__PORT__)) &= ~(__PINS__); SFRX_OFF();} while(0)

#define EXTI_Int0_SetIntPriority(__PRIORITY__)     SFR_DUAL_SET(IP, IPH, 0, __PRIORITY__)
#define EXTI_Timer0_SetIntPriority(__PRIORITY__)   SFR_DUAL_SET(IP, IPH, 1, __PRIORITY__)
#define EXTI_Int1_SetIntPriority(__PRIORITY__)     SFR_DUAL_SET(IP, IPH, 2, __PRIORITY__)
#define EXTI_Timer1_SetIntPriority(__PRIORITY__)   SFR_DUAL_SET(IP, IPH, 3, __PRIORITY__)
#define EXTI_UART1_SetIntPriority(__PRIORITY__)    SFR_DUAL_SET(IP, IPH, 4, __PRIORITY__)
#define EXTI_ADC_SetIntPriority(__PRIORITY__)      SFR_DUAL_SET(IP, IPH, 5, __PRIORITY__)
#define EXTI_LowVoltDetect_SetIntPriority(__PRIORITY__)    SFR_DUAL_SET(IP, IPH, 6, __PRIORITY__)

#define EXTI_UART2_SetIntPriority(__PRIORITY__)    SFR_DUAL_SET(IP2, IP2H, 0, __PRIORITY__)
#define EXTI_SPI_SetIntPriority(__PRIORITY__)      SFR_DUAL_SET(IP2, IP2H, 1, __PRIORITY__)
#define EXTI_PWMA_SetIntPriority(__PRIORITY__)     SFR_DUAL_SET(IP2, IP2H, 2, __PRIORITY__)
#define EXTI_PWMB_SetIntPriority(__PRIORITY__)     SFR_DUAL_SET(IP2, IP2H, 3, __PRIORITY__)
#define EXTI_Int4_SetIntPriority(__PRIORITY__)     SFR_DUAL_SET(IP2, IP2H, 4, __PRIORITY__)
#define EXTI_CMP_SetIntPriority(__PRIORITY__)      SFR_DUAL_SET(IP2, IP2H, 5, __PRIORITY__)
#define EXTI_I2c_SetIntPriority(__PRIORITY__)      SFR_DUAL_SET(IP2, IP2H, 6, __PRIORITY__)
#define EXTI_USB_SetIntPriority(__PRIORITY__)      SFR_DUAL_SET(IP2, IP2H, 7, __PRIORITY__)

#define EXTI_UART3_SetIntPriority(__PRIORITY__)    SFR_DUAL_SET(IP3, IP3H, 0, __PRIORITY__)
#define EXTI_UART4_SetIntPriority(__PRIORITY__)    SFR_DUAL_SET(IP3, IP3H, 1, __PRIORITY__)
#define EXTI_RTC_SetIntPriority(__PRIORITY__)      SFR_DUAL_SET(IP3, IP3H, 2, __PRIORITY__)

#define EXTI_DMA_M2M_SetIntPriority(__PRIORITY__)  SFRX_ASSIGN2BIT(DMA_M2M_CFG, 2, __PRIORITY__)
#define EXTI_DMA_ADC_SetIntPriority(__PRIORITY__)  SFRX_ASSIGN2BIT(DMA_ADC_CFG, 2, __PRIORITY__)
#define EXTI_DMA_SPI_SetIntPriority(__PRIORITY__)  SFRX_ASSIGN2BIT(DMA_SPI_CFG, 2, __PRIORITY__)
#define EXTI_DMA_UART1T_SetIntPriority(__PRIORITY__)  SFRX_ASSIGN2BIT(DMA_UR1T_CFG, 2, __PRIORITY__)
#define EXTI_DMA_UART1R_SetIntPriority(__PRIORITY__)  SFRX_ASSIGN2BIT(DMA_UR1R_CFG, 2, __PRIORITY__)
#define EXTI_DMA_UART2T_SetIntPriority(__PRIORITY__)  SFRX_ASSIGN2BIT(DMA_UR2T_CFG, 2, __PRIORITY__)
#define EXTI_DMA_UART2R_SetIntPriority(__PRIORITY__)  SFRX_ASSIGN2BIT(DMA_UR2R_CFG, 2, __PRIORITY__)
#define EXTI_DMA_UART3T_SetIntPriority(__PRIORITY__)  SFRX_ASSIGN2BIT(DMA_UR3T_CFG, 2, __PRIORITY__)
#define EXTI_DMA_UART3R_SetIntPriority(__PRIORITY__)  SFRX_ASSIGN2BIT(DMA_UR3R_CFG, 2, __PRIORITY__)
#define EXTI_DMA_UART4T_SetIntPriority(__PRIORITY__)  SFRX_ASSIGN2BIT(DMA_UR4T_CFG, 2, __PRIORITY__)
#define EXTI_DMA_UART4R_SetIntPriority(__PRIORITY__)  SFRX_ASSIGN2BIT(DMA_UR4R_CFG, 2, __PRIORITY__)
#define EXTI_DMA_LCM_SetIntPriority(__PRIORITY__)  SFRX_ASSIGN2BIT(DMA_LCM_CFG, 2, __PRIORITY__)

#define EXTI_Port_SetIntPriority(__PORT__, __PRIORITY__)    SFRX_DUAL_SET(PIN_IP, PIN_IPH, __PORT__, __PRIORITY__)

#define EXTI_Port_SetIntMode(__PORT__, __PINS__, __PORT_INT_MODE__) do { SFRX_ON();                                          \
            SFRX(PxIM0 + (__PORT__)) = SFRX(PxIM0 + (__PORT__)) & ~(__PINS__) | (((__PORT_INT_MODE__) & 0x01)? (__PINS__) : 0x00);  \
            SFRX(PxIM1 + (__PORT__)) = SFRX(PxIM1 + (__PORT__)) & ~(__PINS__) | (((__PORT_INT_MODE__) & 0x02)? (__PINS__) : 0x00);  \
        SFRX_OFF(); } while(0)

#endif
