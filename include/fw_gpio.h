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

#ifndef ___FW_GPIO_H___
#define ___FW_GPIO_H___

#include "fw_conf.h"
#include "fw_types.h"

typedef enum
{
    GPIO_Mode_InOut_QBD  = 0x00, /* quasi-bidirectional(be compatible with classical 8051 MCUs) */
    GPIO_Mode_Output_PP  = 0x01, /* push-pull output */
    GPIO_Mode_Input_HIP  = 0x02, /* high-impedance input */
    GPIO_Mode_InOut_OD   = 0x03, /* open drain output */
} GPIO_Mode_t;

typedef enum
{
    GPIO_Port_0     = 0U,
    GPIO_Port_1     = 1U,
    GPIO_Port_2     = 2U,
    GPIO_Port_3     = 3U,
    GPIO_Port_4     = 4U,
    GPIO_Port_5     = 5U,
#if (__CONF_MCU_TYPE == 1  ) || (__CONF_MCU_TYPE == 3  )
    GPIO_Port_6     = 6U,
    GPIO_Port_7     = 7U,
#endif
} GPIO_Port_t;

typedef enum
{
    GPIO_Pin_0      = B00000001,
    GPIO_Pin_1      = B00000010,
    GPIO_Pin_2      = B00000100,
    GPIO_Pin_3      = B00001000,
    GPIO_Pin_4      = B00010000,
    GPIO_Pin_5      = B00100000,
    GPIO_Pin_6      = B01000000,
    GPIO_Pin_7      = B10000000,
    GPIO_Pin_All    = B11111111,
} GPIO_Pin_t;

typedef enum
{
    GPIO_SchmittTrigger_ON  = 0x00,
    GPIO_SchmittTrigger_OFF = 0x01,
} GPIO_SchmittTrigger_t;

typedef enum
{
    GPIO_SwitchSpeed_High   = 0x00,
    GPIO_SwitchSpeed_Low    = 0x01,
} GPIO_SwitchSpeed_t;

typedef enum
{
    GPIO_DriveCapability_High      = 0x00,
    GPIO_DriveCapability_Normal    = 0x01,
} GPIO_DriveCapability_t;

#define GPIO_P0_SetMode(__PINS__, __MODE__) do {  \
                            P0M0 = P0M0 & ~(__PINS__) | (((__MODE__) & 0x01)? (__PINS__) : 0x00); \
                            P0M1 = P0M1 & ~(__PINS__) | (((__MODE__) & 0x02)? (__PINS__) : 0x00); \
                        } while(0)

#define GPIO_P1_SetMode(__PINS__, __MODE__) do {  \
                            P1M0 = P1M0 & ~(__PINS__) | (((__MODE__) & 0x01)? (__PINS__) : 0x00); \
                            P1M1 = P1M1 & ~(__PINS__) | (((__MODE__) & 0x02)? (__PINS__) : 0x00); \
                        } while(0)

#define GPIO_P2_SetMode(__PINS__, __MODE__) do {  \
                            P2M0 = P2M0 & ~(__PINS__) | (((__MODE__) & 0x01)? (__PINS__) : 0x00); \
                            P2M1 = P2M1 & ~(__PINS__) | (((__MODE__) & 0x02)? (__PINS__) : 0x00); \
                        } while(0)

#define GPIO_P3_SetMode(__PINS__, __MODE__) do {  \
                            P3M0 = P3M0 & ~(__PINS__) | (((__MODE__) & 0x01)? (__PINS__) : 0x00); \
                            P3M1 = P3M1 & ~(__PINS__) | (((__MODE__) & 0x02)? (__PINS__) : 0x00); \
                        } while(0)

#define GPIO_P4_SetMode(__PINS__, __MODE__) do {  \
                            P4M0 = P4M0 & ~(__PINS__) | (((__MODE__) & 0x01)? (__PINS__) : 0x00); \
                            P4M1 = P4M1 & ~(__PINS__) | (((__MODE__) & 0x02)? (__PINS__) : 0x00); \
                        } while(0)

#define GPIO_P5_SetMode(__PINS__, __MODE__) do {  \
                            P5M0 = P5M0 & ~(__PINS__) | (((__MODE__) & 0x01)? (__PINS__) : 0x00); \
                            P5M1 = P5M1 & ~(__PINS__) | (((__MODE__) & 0x02)? (__PINS__) : 0x00); \
                        } while(0)

#if (__CONF_MCU_TYPE == 1  ) || (__CONF_MCU_TYPE == 3  )
#define GPIO_P6_SetMode(__PINS__, __MODE__) do {  \
                            P6M0 = P6M0 & ~(__PINS__) | (((__MODE__) & 0x01)? (__PINS__) : 0x00); \
                            P6M1 = P6M1 & ~(__PINS__) | (((__MODE__) & 0x02)? (__PINS__) : 0x00); \
                        } while(0)

#define GPIO_P7_SetMode(__PINS__, __MODE__) do {  \
                            P7M0 = P7M0 & ~(__PINS__) | (((__MODE__) & 0x01)? (__PINS__) : 0x00); \
                            P7M1 = P7M1 & ~(__PINS__) | (((__MODE__) & 0x02)? (__PINS__) : 0x00); \
                        } while(0)
#endif

#define GPIO_SetPullUp(__PORT__, __PINS__, __STATE__) do { \
                            SFRX_ON();                                                           \
                            SFRX(PxPU + (__PORT__)) = SFRX(PxPU + (__PORT__))                       \
                                & ~(__PINS__) | (((__STATE__) & 0x01)? (__PINS__) : 0x00);          \
                            SFRX_OFF();                                                           \
                        } while(0)

#define GPIO_SetSchmittTrigger(__PORT__, __PINS__, __STATE__) do { \
                            SFRX_ON();                                                           \
                            SFRX(PxNCS + (__PORT__)) = SFRX(PxNCS + (__PORT__))                     \
                                & ~(__PINS__) | (((__STATE__) & 0x01)? (__PINS__) : 0x00);          \
                            SFRX_OFF();                                                           \
                        } while(0)

#define GPIO_SetSwitchSpeed(__PORT__, __PINS__, __STATE__) do { \
                            SFRX_ON();                                                           \
                            SFRX(PxSR + (__PORT__)) = SFRX(PxSR + (__PORT__))                       \
                                & ~(__PINS__) | (((__STATE__) & 0x01)? (__PINS__) : 0x00);          \
                            SFRX_OFF();                                                           \
                        } while(0)

#define GPIO_SetDriveCapability(__PORT__, __PINS__, __STATE__) do { \
                            SFRX_ON();                                                           \
                            SFRX(PxDR + (__PORT__)) = SFRX(PxDR + (__PORT__))                       \
                                & ~(__PINS__) | (((__STATE__) & 0x01)? (__PINS__) : 0x00);          \
                            SFRX_OFF();                                                           \
                        } while(0)

#define GPIO_SetDigitalInput(__PORT__, __PINS__, __STATE__) do { \
                            SFRX_ON();                                                           \
                            SFRX(PxIE + (__PORT__)) = SFRX(PxIE + (__PORT__))                       \
                                & ~(__PINS__) | (((__STATE__) & 0x01)? (__PINS__) : 0x00);          \
                            SFRX_OFF();                                                           \
                        } while(0)


#endif
