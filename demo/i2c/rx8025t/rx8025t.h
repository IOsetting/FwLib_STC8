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

#ifndef __FW_RX8025T_H__
#define __FW_RX8025T_H__

#include "fw_hal.h"

#define RX8025T_I2C_ADDR                 0x64

/**
 * REGISTER TABLE
 * 
 * * RX-8025T is different from RX-8025 SA/NB
 */
#define RX8025T_REG_SECOND               0x00 // BCD value 00 -> 59
#define RX8025T_REG_MINUTE               0x01 // BCD value 00 -> 59
#define RX8025T_REG_HOUR                 0x02 // BCD value 00 -> 23
#define RX8025T_REG_WEEKDAY              0x03 // bit 0->6: sunday->saturday
#define RX8025T_REG_DAY                  0x04 // BCD value 01 -> 31
#define RX8025T_REG_MONTH                0x05 // BCD value 01 -> 12
#define RX8025T_REG_YEAR                 0x06 // BCD value 00 -> 99
#define RX8025T_REG_RAM                  0x07 // R/W accessible for any data in the range from 00 h to FF h

#define RX8025T_REG_ALARM_MIN            0x08 // BCD value 00 -> 59
#define RX8025T_REG_ALARM_HOUR           0x09 // BCD value 00 -> 23
#define RX8025T_REG_ALARM_W_OR_D         0x0A // WEEK: bit 0->6: sunday->saturday
                                              // DAY: BCD value

#define RX8025T_REG_TIMER_COUNTER0       0x0B // Fixed-cycle timer control registers to set the preset countdown value 
                                              // for the fixed-cycle timer interrupt. (COUNTER1, COUNTER0) = 12bit number
#define RX8025T_REG_TIMER_COUNTER1       0x0C // When control register changes from 001h to 000h, the /INT pin goes to
                                              // low level and "1" is set to the TF.

#define RX8025T_REG_EXTEN                0x0D
    #define RX8025T_EXTEN_TEST           0x80 // TEST bit. value should always be "0"
    #define RX8025T_EXTEN_WADA           0x40 // Week Alarm/Day Alarm bit. R/W to specify either WEEK or DAY 
                                              // as the target of the alarm interrupt function. 0:WEEK, 1:DAY
    #define RX8025T_EXTEN_USEL           0x20 // Update Interrupt Select bit. R/W specify either "second" 
                                              // or "minute" as update interrupt, 0:second update, 1:minute update
    #define RX8025T_EXTEN_TE             0x10 // Timer Enable bit. controls the start/stop setting for the fixed-cycle 
                                              // timer interrupt function. 1:start, 0:stop
    #define RX8025T_EXTEN_FSEL1          0x08 // FOUT frequency Select bits to set the FOUT frequency. (FSEL1, FSEL0)
    #define RX8025T_EXTEN_FSEL0          0x04 //    0,0:32.768KHz, 0,1:1024Hz, 1,0:1Hz, 1,1:32.768KHz
    #define RX8025T_EXTEN_TSEL1          0x02 // Timer Select bits to set the countdown period (source clock) for the 
                                              // fixed-cycle timer interrupt (TSEL1, TSEL0)
    #define RX8025T_EXTEN_TSEL0          0x01 //    0,0:4096Hz, 0,1:64Hz, 1,0:1Hz(per second), 1,1:1/60Hz(per minute)

#define RX8025T_REG_FLAG                 0x0E
    #define RX8025T_FLAG_UF              0x20 // Update Flag. 0 -> 1 when  a time update interrupt event has
                                              // occurred. 1 is retained until a 0 is written
    #define RX8025T_FLAG_TF              0x10 // Timer Flag. 0 -> 1 when a fixed-cycle timer interrupt 
                                              // event has occurred, 1 is retained until a 0 is written
    #define RX8025T_FLAG_AF              0x08 // Alarm Flag. 0 -> 1 when an alarm interrupt event has occurred
                                              // 1 is retained until a 0 is written
    #define RX8025T_FLAG_VLF             0x02 // Voltage Low Flag. 0 -> 1 when data loss occurs, e.g. a supply
                                              // voltage drop, 
    #define RX8025T_FLAG_VDET            0x01 // Voltage Detection Flag. 0 -> 1 when stop the temperature compensation
                                              // such as due to a supply voltage drop, 1 is retained until a 0 is written

#define RX8025T_REG_CONTROL              0x0F
    #define RX8025T_CONTR_CSEL1          0x80 // Compensation interval (CSEL1, CSEL0)
    #define RX8025T_CONTR_CSEL0          0x40 //    0,0:0.5s, 0,1:2s(default), 1,0:10s, 1,1:30s
    #define RX8025T_CONTR_UIE            0x20 // Update Interrupt Enable, 0:off, 1:on
    #define RX8025T_CONTR_TIE            0x10 // Timer Interrupt Enable
    #define RX8025T_CONTR_AIE            0x08 // Alarm Interrupt Enable
    #define RX8025T_CONTR_RESET          0x01 // Writing a "1" to this bit stops the counter operation and 
                                              // resets the RTC module's internal counter value when the 
                                              // value is less than one second.

uint8_t RX8025T_Init(void);
uint8_t RX8025T_GetTime(uint8_t* t);
uint8_t RX8025T_SetTime(uint8_t* t);

#endif
