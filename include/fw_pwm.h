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

#ifndef ___FW_PWM_H___
#define ___FW_PWM_H___

#include "fw_conf.h"
#include "fw_types.h"


typedef enum
{
    PWM_Pin_1       = B00000001,
    PWM_Pin_1N      = B00000010,
    PWM_Pin_2       = B00000100,
    PWM_Pin_2N      = B00001000,
    PWM_Pin_3       = B00010000,
    PWM_Pin_3N      = B00100000,
    PWM_Pin_4       = B01000000,
    PWM_Pin_4N      = B10000000,
    PWMA_Pin_All    = B11111111,
    PWMB_Pin_All    = B01010101,
} PWM_Pin_t;

/**
 * Trigger mode
 * Side Mode: 
 *  Depends on DIR
 * Center Mode: counter increasing then decreasing
 *  CenterDown: trigger interrupt when meet target in decreasing
 *  CenterUp:   trigger interrupt when meet target in increasing
 *  CenterBoth: trigger interrupt when meet target in both
*/
typedef enum
{
    PWM_EdgeAlignment_Side          = 0x00,
    PWM_EdgeAlignment_CenterDown    = 0x01,
    PWM_EdgeAlignment_CenterUp      = 0x10,
    PWM_EdgeAlignment_CenterBoth    = 0x11,
} PWM_EdgeAlignment_t;

typedef enum
{
    PWM_CounterDirection_Up     = 0x00,
    PWM_CounterDirection_Down   = 0x01,
} PWM_CounterDirection_t;

/**
 * Comparasion Output Mode: PWMx_CCRx vs PWMx_CNT => OCxREF
*/
typedef enum
{
    PWM_OutputMode_NoAction        = 0x00, // Fixed
    PWM_OutputMode_TriggerHigh     = 0x01, // OCxREF=1 when PWMA_CCR1=PWMA_CNT
    PWM_OutputMode_TriggerLow      = 0x02, // OCxREF=0 when PWMA_CCR1=PWMA_CNT
    PWM_OutputMode_TriggerToggle   = 0x03, // Toggle OCxREF when PWMA_CCR1=PWMA_CNT
    PWM_OutputMode_AlwaysLow       = 0x04, // OCxREF always low
    PWM_OutputMode_AlwaysHigh      = 0x05, // OCxREF always high
    PWM_OutputMode_PWM_HighIfLess  = 0x06, // OCxREF=1 when PWMA_CNT<PWMA_CCR1, in both counting direction
    PWM_OutputMode_PWM_LowIfLess   = 0x07, // OCxREF=0 when PWMA_CNT<PWMA_CCR1, in both counting direction
} PWM_OutputMode_t;


/**************************************************************************** /
 * PWMA
*/

/**
 * PWM clock prescaler and auto-reload period
 * 
 * side alignment:
 *      Fpwm = SYSCLK / (PWMx_PSCR + 1) / (PWMx_ARR + 1)
 * central alignment: 
 *      Fpwm = SYSCLK / (PWMx_PSCR + 1) / PWMx_ARR / 2
*/
#define PWMA_SetPrescaler(__16BIT_VAL__)     do {   \
                        SFRX_ON(); \
                        (PWMA_PSCRH = ((__16BIT_VAL__) >> 8)); \
                        (PWMA_PSCRL = ((__16BIT_VAL__) & 0xFF)); \
                        SFRX_OFF(); \
                    }while(0)

#define PWMA_SetPeriod(__16BIT_VAL__)        do {   \
                        SFRX_ON(); \
                        (PWMA_ARRH = ((__16BIT_VAL__) >> 8)); \
                        (PWMA_ARRL = ((__16BIT_VAL__) & 0xFF)); \
                        SFRX_OFF(); \
                    }while(0)

// PWMA all pins input/output OFF/ON
#define PWMA_SetOverallState(__STATE__)   SFRX_ASSIGN(PWMA_BKR, 7, (__STATE__))

// PWMA Pins Output OFF/ON
#define PWMA_SetPinOutputState(__PINS__, __STATE__) do {  \
                        SFRX_ON();                                                                   \
                        PWMA_ENO = PWMA_ENO & ~(__PINS__) | (((__STATE__) & 0x01)? (__PINS__) : 0x00);  \
                        SFRX_OFF();                                                                   \
                    } while(0)

// Enable/Disable PWMB_BKR Control on Pins
#define PWMA_SetPinBrakeControl(__PINS__, __STATE__) do {  \
                        SFRX_ON();                                                                   \
                        PWMA_IOAUX = PWMA_IOAUX & ~(__PINS__) | (((__STATE__) & 0x01)? (__PINS__) : 0x00);  \
                        SFRX_OFF();                                                                   \
                    } while(0)

/**
 * 0: New period will be written to [PWMA_ARRH,PWMA_ARRL] and take effect immediately
 * 1: New period will be written to shadow register and loaded to [PWMA_ARRH,PWMA_ARRL] on next update event
*/
#define PWMA_SetAutoReloadPreload(__STATE__)    SFRX_ASSIGN(PWMA_CR1, 7, (__STATE__))

/**
 * Turn off counter (call PWMA_SetCounterState()) before changing to different alignment
*/
#define PWMA_SetEdgeAlignment(__ALIGN__)        do{   \
                        SFRX_ON();(PWMA_CR1 = PWMA_CR1 & ~(0x03 << 5) | ((__ALIGN__) << 5));SFRX_OFF();  \
                    }while(0)

/**
 * 0: count from 0 to [PWMA_ARRH,PWMA_ARRL], then send an event and restart from 0
 * 1: count from [PWMA_ARRH,PWMA_ARRL] to 0, then send an event and restart from [PWMA_ARRH,PWMA_ARRL]
*/
#define PWMA_SetCounterDirection(__DIR__)       SFRX_ASSIGN(PWMA_CR1, 4, (__DIR__))
/**
 * 0: counter continues when update event occurs
 * 1: counter stops(reset CEN) when update event occurs
*/
#define PWMA_SetCounterOnePulse(__STATE__)      SFRX_ASSIGN(PWMA_CR1, 3, (__STATE__))
/**
 * Work only when update events are enabled
 * 0: An interrupt will be triggered by these events: counter overflow(upwards or downwards), soft set UG, timer/controller updates
 * 1: An interrupt will be triggered(and set UIF=1) by counter overflow(upwards or downwards)
*/
#define PWMA_SetUpdateEventSource(__STATE__)    SFRX_ASSIGN(PWMA_CR1, 2, (__STATE__))
/**
 * 0:enable update events, 1:disable update events
*/
#define PWMA_SetNonUpdateEvent(__STATE__)       SFRX_ASSIGN(PWMA_CR1, 1, (__STATE__))
/**
 * 0:stop counter, 1:start counter
*/
#define PWMA_SetCounterState(__STATE__)         SFRX_ASSIGN(PWMA_CR1, 0, (__STATE__))

/**
 * PWMA.1 - PWMA.4 io polar and on/off state
*/
#define PWMA_PWM1_SetPortState(__STATE__)          SFRX_ASSIGN(PWMA_CCER1, 0, (__STATE__))
#define PWMA_PWM1_SetPortPolar(__POLAR__)          SFRX_ASSIGN(PWMA_CCER1, 1, (__POLAR__))
#define PWMA_PWM1N_SetPortState(__STATE__)         SFRX_ASSIGN(PWMA_CCER1, 2, (__STATE__))
#define PWMA_PWM1N_SetPortPolar(__POLAR__)         SFRX_ASSIGN(PWMA_CCER1, 3, (__POLAR__))

#define PWMA_PWM2_SetPortState(__STATE__)          SFRX_ASSIGN(PWMA_CCER1, 4, (__STATE__))
#define PWMA_PWM2_SetPortPolar(__POLAR__)          SFRX_ASSIGN(PWMA_CCER1, 5, (__POLAR__))
#define PWMA_PWM2N_SetPortState(__STATE__)         SFRX_ASSIGN(PWMA_CCER1, 6, (__STATE__))
#define PWMA_PWM2N_SetPortPolar(__POLAR__)         SFRX_ASSIGN(PWMA_CCER1, 7, (__POLAR__))

#define PWMA_PWM3_SetPortState(__STATE__)          SFRX_ASSIGN(PWMA_CCER2, 0, (__STATE__))
#define PWMA_PWM3_SetPortPolar(__POLAR__)          SFRX_ASSIGN(PWMA_CCER2, 1, (__POLAR__))
#define PWMA_PWM3N_SetPortState(__STATE__)         SFRX_ASSIGN(PWMA_CCER2, 2, (__STATE__))
#define PWMA_PWM3N_SetPortPolar(__POLAR__)         SFRX_ASSIGN(PWMA_CCER2, 3, (__POLAR__))

#define PWMA_PWM4_SetPortState(__STATE__)          SFRX_ASSIGN(PWMA_CCER2, 4, (__STATE__))
#define PWMA_PWM4_SetPortPolar(__POLAR__)          SFRX_ASSIGN(PWMA_CCER2, 5, (__POLAR__))
#define PWMA_PWM4N_SetPortState(__STATE__)         SFRX_ASSIGN(PWMA_CCER2, 6, (__STATE__))
#define PWMA_PWM4N_SetPortPolar(__POLAR__)         SFRX_ASSIGN(PWMA_CCER2, 7, (__POLAR__))

/**
 * Configurate PWMA.1 - PWMA.4 port direction
*/
typedef enum
{
    PWMA_PortDirOut       = 0x00,
    PWMA_PortDirIn_TI1FP1_TI2FP2_TI3FP3_TI4FP4  = 0x01,
    PWMA_PortDirIn_TI2FP1_TI1FP2_TI4FP3_TI3FP4  = 0x10,
    PWMA_PortDirInTRC     = 0x11,
} PWMA_PortDirection_t;

#define PWMA_PWM1_SetPortDirection(__PORT_DIR__)    do{   \
                        SFRX_ON();(PWMA_CCMR1 = PWMA_CCMR1 & ~(0x03 << 0) | ((__PORT_DIR__) << 0)); SFRX_OFF(); \
                    }while(0)
#define PWMA_PWM2_SetPortDirection(__PORT_DIR__)    do{   \
                        SFRX_ON();(PWMA_CCMR2 = PWMA_CCMR2 & ~(0x03 << 0) | ((__PORT_DIR__) << 0)); SFRX_OFF(); \
                    }while(0)
#define PWMA_PWM3_SetPortDirection(__PORT_DIR__)    do{   \
                        SFRX_ON();(PWMA_CCMR3 = PWMA_CCMR3 & ~(0x03 << 0) | ((__PORT_DIR__) << 0)); SFRX_OFF(); \
                    }while(0)
#define PWMA_PWM4_SetPortDirection(__PORT_DIR__)    do{   \
                        SFRX_ON();(PWMA_CCMR4 = PWMA_CCMR4 & ~(0x03 << 0) | ((__PORT_DIR__) << 0)); SFRX_OFF(); \
                    }while(0)

/**
 * PWMA.1 - PWMA.4 comparison value preload OFF/ON
 *   0: New values will be written to PWMx_CCRx and take effect immediately
 *   1: New values will be written to shadow register and loaded to PWMx_CCRx on next update event
*/
#define PWMA_PWM1_SetComparePreload(__STATE__)      SFRX_ASSIGN(PWMA_CCMR1, 3, (__STATE__))
#define PWMA_PWM2_SetComparePreload(__STATE__)      SFRX_ASSIGN(PWMA_CCMR2, 3, (__STATE__))
#define PWMA_PWM3_SetComparePreload(__STATE__)      SFRX_ASSIGN(PWMA_CCMR3, 3, (__STATE__))
#define PWMA_PWM4_SetComparePreload(__STATE__)      SFRX_ASSIGN(PWMA_CCMR4, 3, (__STATE__))

/**
 * Configurate PWMA.1 - PWMA.4 out mode 
*/
#define PWMA_PWM1_ConfigOutputMode(__MODE__) do{   \
                        SFRX_ON();(PWMA_CCMR1 = PWMA_CCMR1 & ~(0x07 << 4) | ((__MODE__) << 4)); SFRX_OFF(); \
                    }while(0)
#define PWMA_PWM2_ConfigOutputMode(__MODE__) do{   \
                        SFRX_ON();(PWMA_CCMR2 = PWMA_CCMR2 & ~(0x07 << 4) | ((__MODE__) << 4)); SFRX_OFF(); \
                    }while(0)
#define PWMA_PWM3_ConfigOutputMode(__MODE__) do{   \
                        SFRX_ON();(PWMA_CCMR3 = PWMA_CCMR3 & ~(0x07 << 4) | ((__MODE__) << 4)); SFRX_OFF(); \
                    }while(0)
#define PWMA_PWM4_ConfigOutputMode(__MODE__) do{   \
                        SFRX_ON();(PWMA_CCMR4 = PWMA_CCMR4 & ~(0x07 << 4) | ((__MODE__) << 4)); SFRX_OFF(); \
                    }while(0)

/**
 * Configurate PWMA.1 - PWMA.4 capture/comparison value, this will affect duty cycle
*/
#define PWMA_PWM1_SetCaptureCompareValue(__16BIT_VAL__)        do{   \
                        SFRX_ON(); \
                        (PWMA_CCR1H = ((__16BIT_VAL__) >> 8)); \
                        (PWMA_CCR1L = ((__16BIT_VAL__) & 0xFF)); \
                        SFRX_OFF(); \
                    }while(0)
#define PWMA_PWM2_SetCaptureCompareValue(__16BIT_VAL__)        do{   \
                        SFRX_ON(); \
                        (PWMA_CCR2H = ((__16BIT_VAL__) >> 8)); \
                        (PWMA_CCR2L = ((__16BIT_VAL__) & 0xFF)); \
                        SFRX_OFF(); \
                    }while(0)
#define PWMA_PWM3_SetCaptureCompareValue(__16BIT_VAL__)        do{   \
                        SFRX_ON(); \
                        (PWMA_CCR3H = ((__16BIT_VAL__) >> 8)); \
                        (PWMA_CCR3L = ((__16BIT_VAL__) & 0xFF)); \
                        SFRX_OFF(); \
                    }while(0)
#define PWMA_PWM4_SetCaptureCompareValue(__16BIT_VAL__)        do{   \
                        SFRX_ON(); \
                        (PWMA_CCR4H = ((__16BIT_VAL__) >> 8)); \
                        (PWMA_CCR4L = ((__16BIT_VAL__) & 0xFF)); \
                        SFRX_OFF(); \
                    }while(0)

/**
 * PWM1 - PWM4 alternative ports
*/
typedef enum
{
    //                PWM1P   PWM1N
    PWMA_PWM1_AlterPort_P10_P11 = 0x00,
    PWMA_PWM1_AlterPort_P20_P21 = 0x01,
    PWMA_PWM1_AlterPort_P60_P61 = 0x10,
} PWMA_PWM1_AlterPort_t;

typedef enum
{
    PWMA_PWM2_AlterPort_P12P54_P13 = 0x00,
    PWMA_PWM2_AlterPort_P22_P23 = 0x01,
    PWMA_PWM2_AlterPort_P62_P63 = 0x10,
} PWMA_PWM2_AlterPort_t;

typedef enum
{
    PWMA_PWM3_AlterPort_P14_P15 = 0x00,
    PWMA_PWM3_AlterPort_P24_P25 = 0x01,
    PWMA_PWM3_AlterPort_P64_P65 = 0x10,
} PWMA_PWM3_AlterPort_t;

typedef enum
{
    PWMA_PWM4_AlterPort_P16_P17 = 0x00,
    PWMA_PWM4_AlterPort_P26_P27 = 0x01,
    PWMA_PWM4_AlterPort_P66_P67 = 0x10,
    PWMA_PWM4_AlterPort_P34_P33 = 0x11,
} PWMA_PWM4_AlterPort_t;

// Alternative port selection
#define PWMA_PWM1_SetPort(__ALTER_PORT__)    do{   \
                        SFRX_ON();(PWMA_PS = PWMA_PS & ~(0x03 << 0) | ((__ALTER_PORT__) << 0)); SFRX_OFF(); \
                    }while(0)
#define PWMA_PWM2_SetPort(__ALTER_PORT__)    do{   \
                        SFRX_ON();(PWMA_PS = PWMA_PS & ~(0x03 << 2) | ((__ALTER_PORT__) << 2)); SFRX_OFF(); \
                    }while(0)
#define PWMA_PWM3_SetPort(__ALTER_PORT__)    do{   \
                        SFRX_ON();(PWMA_PS = PWMA_PS & ~(0x03 << 4) | ((__ALTER_PORT__) << 4)); SFRX_OFF(); \
                    }while(0)
#define PWMA_PWM4_SetPort(__ALTER_PORT__)    do{   \
                        SFRX_ON();(PWMA_PS = PWMA_PS & ~(0x03 << 6) | ((__ALTER_PORT__) << 6)); SFRX_OFF(); \
                    }while(0)



/**************************************************************************** /
 * PWMB
*/

/**
 * PWM clock prescaler
 * 
 * side alignment:
 *      Fpwm = SYSCLK / (PWMx_PSCR + 1) / (PWMx_ARR + 1)
 * central alignment: 
 *      Fpwm = SYSCLK / (PWMx_PSCR + 1) / PWMx_ARR / 2
*/
#define PWMB_SetPrescaler(__16BIT_VAL__)     do {   \
                        SFRX_ON(); \
                        (PWMB_PSCRH = ((__16BIT_VAL__) >> 8)); \
                        (PWMB_PSCRL = ((__16BIT_VAL__) & 0xFF)); \
                        SFRX_OFF(); \
                    }while(0)

#define PWMB_SetPeriod(__16BIT_VAL__)        do {   \
                        SFRX_ON(); \
                        (PWMB_ARRH = ((__16BIT_VAL__) >> 8)); \
                        (PWMB_ARRL = ((__16BIT_VAL__) & 0xFF)); \
                        SFRX_OFF(); \
                    }while(0)

// PWMA all pins input/output OFF/ON
#define PWMB_SetOverallState(__STATE__)   SFRX_ASSIGN(PWMB_BKR, 7, (__STATE__))

// PWMB Pins Output OFF/ON
#define PWMB_SetPinOutputState(__PINS__, __STATE__) do {  \
                        SFRX_ON();                                                                   \
                        PWMB_ENO = PWMB_ENO & ~(__PINS__) | (((__STATE__) & 0x01)? (__PINS__) : 0x00);  \
                        SFRX_OFF();                                                                   \
                    } while(0)

// Enable/Disable PWMB_BKR Control on Pins
#define PWMB_SetPinBrakeControl(__PINS__, __STATE__) do {  \
                        SFRX_ON();                                                                   \
                        PWMB_IOAUX = PWMB_IOAUX & ~(__PINS__) | (((__STATE__) & 0x01)? (__PINS__) : 0x00);  \
                        SFRX_OFF();                                                                   \
                    } while(0)

/**
 * 0: New period will be written to [PWMB_ARRH,PWMB_ARRL] and take effect immediately
 * 1: New period will be written to shadow register and loaded to [PWMB_ARRH,PWMB_ARRL] on next update event
*/
#define PWMB_SetAutoReloadPreload(__STATE__)    SFRX_ASSIGN(PWMB_CR1, 7, (__STATE__))

/**
 * Turn off counter (call PWMB_SetCounterState()) before changing to different alignment
*/
#define PWMB_SetEdgeAlignment(__ALIGN__)        do{   \
                        SFRX_ON();(PWMB_CR1 = PWMB_CR1 & ~(0x03 << 5) | ((__ALIGN__) << 5));SFRX_OFF();  \
                    }while(0)

/**
 * 0: count from 0 to [PWMB_ARRH,PWMB_ARRL], then send an event and restart from 0
 * 1: count from [PWMB_ARRH,PWMB_ARRL] to 0, then send an event and restart from [PWMB_ARRH,PWMB_ARRL]
*/
#define PWMB_SetCounterDirection(__DIR__)       SFRX_ASSIGN(PWMB_CR1, 4, (__DIR__))
/**
 * 0: counter continues when update event occurs
 * 1: counter stops(reset CEN) when update event occurs
*/
#define PWMB_SetCounterOnePulse(__STATE__)      SFRX_ASSIGN(PWMB_CR1, 3, (__STATE__))
/**
 * Work only when update events are enabled
 * 0: An interrupt will be triggered by these events: counter overflow(upwards or downwards), soft set UG, timer/controller updates
 * 1: An interrupt will be triggered(and set UIF=1) by counter overflow(upwards or downwards)
*/
#define PWMB_SetUpdateEventSource(__STATE__)    SFRX_ASSIGN(PWMB_CR1, 2, (__STATE__))
/**
 * 0:enable update events, 1:disable update events
*/
#define PWMB_SetNonUpdateEvent(__STATE__)       SFRX_ASSIGN(PWMB_CR1, 1, (__STATE__))
/**
 * 0:stop counter, 1:start counter
*/
#define PWMB_SetCounterState(__STATE__)         SFRX_ASSIGN(PWMB_CR1, 0, (__STATE__))

/**
 * PWMB.1(PWM5) - PWMB.4(PWM8) io polar and on/off state
*/
#define PWMB_PWM1_SetPortState(__STATE__)         SFRX_ASSIGN(PWMB_CCER1, 0, (__STATE__))
#define PWMB_PWM1_SetPortPolar(__POLAR__)         SFRX_ASSIGN(PWMB_CCER1, 1, (__POLAR__))

#define PWMB_PWM2_SetPortState(__STATE__)         SFRX_ASSIGN(PWMB_CCER1, 4, (__STATE__))
#define PWMB_PWM2_SetPortPolar(__POLAR__)         SFRX_ASSIGN(PWMB_CCER1, 5, (__POLAR__))

#define PWMB_PWM3_SetPortState(__STATE__)         SFRX_ASSIGN(PWMB_CCER2, 0, (__STATE__))
#define PWMB_PWM3_SetPortPolar(__POLAR__)         SFRX_ASSIGN(PWMB_CCER2, 1, (__POLAR__))

#define PWMB_PWM4_SetPortState(__STATE__)         SFRX_ASSIGN(PWMB_CCER2, 4, (__STATE__))
#define PWMB_PWM4_SetPortPolar(__POLAR__)         SFRX_ASSIGN(PWMB_CCER2, 5, (__POLAR__))

/**
 * Configurate PWMB.1(PWM5) - PWMB.4(PWM8) port direction
*/
typedef enum
{
    PWMB_PortDirOut       = 0x00,
    PWMB_PortDirIn_TI5FP5_TI6FP6_TI7FP7_TI8FP8  = 0x01,
    PWMB_PortDirIn_TI6FP5_TI5FP6_TI8FP7_TI7FP8  = 0x10,
    PWMB_PortDirInTRC     = 0x11,
} PWMB_PortDirection_t;

#define PWMB_PWM1_SetPortDirection(__PORT_DIR__)    do{   \
                        SFRX_ON();(PWMB_CCMR1 = PWMB_CCMR1 & ~(0x03 << 0) | ((__PORT_DIR__) << 0)); SFRX_OFF(); \
                    }while(0)
#define PWMB_PWM2_SetPortDirection(__PORT_DIR__)    do{   \
                        SFRX_ON();(PWMB_CCMR2 = PWMB_CCMR2 & ~(0x03 << 0) | ((__PORT_DIR__) << 0)); SFRX_OFF(); \
                    }while(0)
#define PWMB_PWM3_SetPortDirection(__PORT_DIR__)    do{   \
                        SFRX_ON();(PWMB_CCMR3 = PWMB_CCMR3 & ~(0x03 << 0) | ((__PORT_DIR__) << 0)); SFRX_OFF(); \
                    }while(0)
#define PWMB_PWM4_SetPortDirection(__PORT_DIR__)    do{   \
                        SFRX_ON();(PWMB_CCMR4 = PWMB_CCMR4 & ~(0x03 << 0) | ((__PORT_DIR__) << 0)); SFRX_OFF(); \
                    }while(0)

/**
 * PWMB.1 - PWMB.4 comparison value preload OFF/ON
 *   0: New values will be written to PWMx_CCRx and take effect immediately
 *   1: New values will be written to shadow register and loaded to PWMx_CCRx on next update event
*/
#define PWMB_PWM1_SetComparePreload(__STATE__)      SFRX_ASSIGN(PWMB_CCMR1, 3, (__STATE__))
#define PWMB_PWM2_SetComparePreload(__STATE__)      SFRX_ASSIGN(PWMB_CCMR2, 3, (__STATE__))
#define PWMB_PWM3_SetComparePreload(__STATE__)      SFRX_ASSIGN(PWMB_CCMR3, 3, (__STATE__))
#define PWMB_PWM4_SetComparePreload(__STATE__)      SFRX_ASSIGN(PWMB_CCMR4, 3, (__STATE__))

/**
 * Configurate PWMB.1(PWM5) - PWMB.4(PWM8) output mode 
*/
#define PWMB_PWM1_ConfigOutputMode(__MODE__) do{   \
                        SFRX_ON();(PWMB_CCMR1 = PWMB_CCMR1 & ~(0x07 << 4) | ((__MODE__) << 4)); SFRX_OFF(); \
                    }while(0)
#define PWMB_PWM2_ConfigOutputMode(__MODE__) do{   \
                        SFRX_ON();(PWMB_CCMR2 = PWMB_CCMR2 & ~(0x07 << 4) | ((__MODE__) << 4)); SFRX_OFF(); \
                    }while(0)
#define PWMB_PWM3_ConfigOutputMode(__MODE__) do{   \
                        SFRX_ON();(PWMB_CCMR3 = PWMB_CCMR3 & ~(0x07 << 4) | ((__MODE__) << 4)); SFRX_OFF(); \
                    }while(0)
#define PWMB_PWM4_ConfigOutputMode(__MODE__) do{   \
                        SFRX_ON();(PWMB_CCMR4 = PWMB_CCMR4 & ~(0x07 << 4) | ((__MODE__) << 4)); SFRX_OFF(); \
                    }while(0)

/**
 * Configurate PWMB.1(PWM5) - PWMB.4(PWM8) capture/comparison value, this will affect duty cycle
*/
#define PWMB_PWM1_SetCaptureCompareValue(__16BIT_VAL__)        do{   \
                        SFRX_ON(); \
                        (PWMB_CCR5H = ((__16BIT_VAL__) >> 8)); \
                        (PWMB_CCR5L = ((__16BIT_VAL__) & 0xFF)); \
                        SFRX_OFF(); \
                    }while(0)
#define PWMB_PWM2_SetCaptureCompareValue(__16BIT_VAL__)        do{   \
                        SFRX_ON(); \
                        (PWMB_CCR6H = ((__16BIT_VAL__) >> 8)); \
                        (PWMB_CCR6L = ((__16BIT_VAL__) & 0xFF)); \
                        SFRX_OFF(); \
                    }while(0)
#define PWMB_PWM3_SetCaptureCompareValue(__16BIT_VAL__)        do{   \
                        SFRX_ON(); \
                        (PWMB_CCR7H = ((__16BIT_VAL__) >> 8)); \
                        (PWMB_CCR7L = ((__16BIT_VAL__) & 0xFF)); \
                        SFRX_OFF(); \
                    }while(0)
#define PWMB_PWM4_SetCaptureCompareValue(__16BIT_VAL__)        do{   \
                        SFRX_ON(); \
                        (PWMB_CCR8H = ((__16BIT_VAL__) >> 8)); \
                        (PWMB_CCR8L = ((__16BIT_VAL__) & 0xFF)); \
                        SFRX_OFF(); \
                    }while(0)

typedef enum
{
    PWMB_PWM5_AlterPort_P20 = 0x00,
    PWMB_PWM5_AlterPort_P17 = 0x01,
    PWMB_PWM5_AlterPort_P00 = 0x10,
    PWMB_PWM5_AlterPort_P74 = 0x11,
} PWMB_PWM5_AlterPort_t;

typedef enum
{
    PWMB_PWM6_AlterPort_P21 = 0x00,
    PWMB_PWM6_AlterPort_P54 = 0x01,
    PWMB_PWM6_AlterPort_P01 = 0x10,
    PWMB_PWM6_AlterPort_P75 = 0x11,
} PWMB_PWM6_AlterPort_t;

typedef enum
{
    PWMB_PWM7_AlterPort_P22 = 0x00,
    PWMB_PWM7_AlterPort_P33 = 0x01,
    PWMB_PWM7_AlterPort_P02 = 0x10,
    PWMB_PWM7_AlterPort_P76 = 0x11,
} PWMB_PWM7_AlterPort_t;

typedef enum
{
    PWMB_PWM8_AlterPort_P23 = 0x00,
    PWMB_PWM8_AlterPort_P34 = 0x01,
    PWMB_PWM8_AlterPort_P03 = 0x10,
    PWMB_PWM8_AlterPort_P77 = 0x11,
} PWMB_PWM8_AlterPort_t;

// Alternative port selection
#define PWMB_PWM1_SetPort(__ALTER_PORT__)    do{   \
                        SFRX_ON();(PWMB_PS = PWMB_PS & ~(0x03 << 0) | ((__ALTER_PORT__) << 0)); SFRX_OFF(); \
                    }while(0)
#define PWMB_PWM2_SetPort(__ALTER_PORT__)    do{   \
                        SFRX_ON();(PWMB_PS = PWMB_PS & ~(0x03 << 2) | ((__ALTER_PORT__) << 2)); SFRX_OFF(); \
                    }while(0)
#define PWMB_PWM3_SetPort(__ALTER_PORT__)    do{   \
                        SFRX_ON();(PWMB_PS = PWMB_PS & ~(0x03 << 4) | ((__ALTER_PORT__) << 4)); SFRX_OFF(); \
                    }while(0)
#define PWMB_PWM4_SetPort(__ALTER_PORT__)    do{   \
                        SFRX_ON();(PWMB_PS = PWMB_PS & ~(0x03 << 6) | ((__ALTER_PORT__) << 6)); SFRX_OFF(); \
                    }while(0)


#endif
