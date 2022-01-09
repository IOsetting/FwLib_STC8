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

#ifndef ___FW_RTC_H___
#define ___FW_RTC_H___

#include "fw_conf.h"
#include "fw_types.h"

typedef enum
{
    RTC_ClockSource_External    = 0x00,
    RTC_ClockSource_Internal    = 0x01,
} RTC_ClockSource_t;

#define RTC_SetRunState(__STATE__)          SFRX_ASSIGN(RTCCR, 0, (__STATE__))
#define RTC_SetClockSource(__SOURCE__)      SFRX_ASSIGN(RTCCFG, 1, (__SOURCE__))
#define RTC_ConfigClockApply()              SFRX_SET(RTCCFG, 0)

/**
 * Call SFRX_ON(); before calling following macros
*/
#define RTC_ClearAllInterrupts()            (RTCIF = 0x00)
#define RTC_IsAlarmInterrupt()              (RTCIF & 0x80)
#define RTC_ClearAlarmInterrupt()           (RTCIF &= ~0x80)
#define RTC_IsDayInterrupt()                (RTCIF & 0x40)
#define RTC_ClearDayInterrupt()             (RTCIF &= ~0x40)
#define RTC_IsHourInterrupt()               (RTCIF & 0x20)
#define RTC_ClearHourInterrupt()            (RTCIF &= ~0x20)
#define RTC_IsMinuteInterrupt()             (RTCIF & 0x10)
#define RTC_ClearMinuteInterrupt()          (RTCIF &= ~0x10)
#define RTC_IsSecondInterrupt()             (RTCIF & 0x08)
#define RTC_ClearSecondInterrupt()          (RTCIF &= ~0x08)
#define RTC_IsSecondDiv2Interrupt()         (RTCIF & 0x04)
#define RTC_ClearSecondDiv2Interrupt()      (RTCIF &= ~0x04)
#define RTC_IsSecondDiv8Interrupt()         (RTCIF & 0x02)
#define RTC_ClearSecondDiv8Interrupt()      (RTCIF &= ~0x02)
#define RTC_IsSecondDiv32Interrupt()        (RTCIF & 0x01)
#define RTC_ClearSecondDiv32Interrupt()     (RTCIF &= ~0x01)

/**
 * Set Alarm 
*/
#define RTC_ConfigAlarm(__HOUR__, __MIN__, __SEC__, __SSEC__) do { \
                                            SFRX_ON(); \
                                            ALAHOUR = (__HOUR__ & 0x1F); \
                                            ALAMIN  = (__MIN__ & 0x3F); \
                                            ALASEC  = (__SEC__ & 0x3F); \
                                            ALASSEC = (__SSEC__ & 0x7F); \
                                            SFRX_OFF();  \
                                        } while(0)
/**
 * Set clock initial value
*/
#define RTC_ConfigClock(__YEAR__, __MON__, __DAY__, __HOUR__, __MIN__, __SEC__, __SSEC__) do { \
                                            SFRX_ON(); \
                                            INIYEAR = (__YEAR__ & 0x7F); \
                                            INIMONTH = (__MON__ & 0x0F); \
                                            INIDAY = (__DAY__ & 0x1F); \
                                            INIHOUR = (__HOUR__ & 0x1F); \
                                            INIMIN  = (__MIN__ & 0x3F); \
                                            INISEC  = (__SEC__ & 0x3F); \
                                            INISSEC = (__SSEC__ & 0x7F); \
                                            SFRX_OFF();  \
                                        } while(0)


#endif