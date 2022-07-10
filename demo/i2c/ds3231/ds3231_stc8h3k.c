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

/***
 * Demo: ZS-042, DS3231 I2C RTC/TCXO/Crystal
 * Board: STC8H3K32
 * 
 *              P32   -> SCL
 *              P33   -> SDA
 *              GND   -> GND
 *              3.3V  -> VCC
 */

#include "fw_hal.h"
#include "ds3231.h"

__XDATA uint8_t time[9];

void I2C_Init(void)
{
    // Master mode
    I2C_SetWorkMode(I2C_WorkMode_Master);
    /**
     * I2C clock = FOSC / 2 / (__prescaler__ * 2 + 4)
    */
    I2C_SetClockPrescaler(0x3F);
    // Switch alternative port
    I2C_SetPort(I2C_AlterPort_P32_P33);
    // Start I2C
    I2C_SetEnabled(HAL_State_ON);
}

void GPIO_Init(void)
{
    // SDA
    GPIO_P3_SetMode(GPIO_Pin_3, GPIO_Mode_InOut_QBD);
    // SCL
    GPIO_P3_SetMode(GPIO_Pin_2, GPIO_Mode_Output_PP);
}

int main(void)
{
    SYS_SetClock();
    // UART1 configuration: baud 115200 with Timer2, 1T mode, no interrupt
    UART1_Config8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200);

    GPIO_Init();
    I2C_Init();
    time[0] = DS3231_GetStatus();
    UART1_TxString("Status:");
    UART1_TxHex(time[0]);
    UART1_TxString("\r\n");
    // Set time
    time[7] = DS3231_FORMAT_24H;
    time[0] = 2022 - 1990; // year
    time[1] = 7; // month
    time[2] = 7; // week day
    time[3] = 10; // date
    time[4] = 14; // hour
    time[5] = 21; // minute
    time[6] = 10; // second
    DS3231_SetTime(time);

    while(1)
    {
        DS3231_GetTime(time);
        UART1_TxHex(time[0]);
        UART1_TxChar('-');
        UART1_TxHex(time[1]);
        UART1_TxChar('-');
        UART1_TxHex(time[3]);
        UART1_TxChar(' ');
        UART1_TxHex(time[4]);
        UART1_TxChar(':');
        UART1_TxHex(time[5]);
        UART1_TxChar(':');
        UART1_TxHex(time[6]);
        UART1_TxChar(' ');
        UART1_TxHex(time[7]);
        UART1_TxChar(' ');
        UART1_TxHex(time[8]);
        UART1_TxString("\r\n");
        SYS_Delay(1000);
    }
}
