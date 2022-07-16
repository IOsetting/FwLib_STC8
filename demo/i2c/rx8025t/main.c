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
 * Demo:  RX8025T I2C RTC/TCXO
 * Board: STC8H3K32
 * 
 *              P32   -> SCL
 *              P33   -> SDA
 *              GND   -> GND
 *              3.3V  -> VCC
 */

#include "fw_hal.h"
#include "rx8025t.h"

#define BUFF_SIZE 16

__XDATA uint8_t time[BUFF_SIZE];

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
    uint8_t i;
    SYS_SetClock();
    // UART1 configuration: baud 115200 with Timer2, 1T mode, no interrupt
    UART1_Config8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200);

    GPIO_Init();
    I2C_Init();
    RX8025T_Init();
    time[0] = 0x10; // second
    time[1] = 0x10; // minute
    time[2] = 0x10; // hour
    time[3] = 0x40; // week day
    time[4] = 0x16; // day
    time[5] = 0x07; // month
    time[6] = 0x22; // year
    RX8025T_SetTime(time);

    while(1)
    {
        RX8025T_GetTime(time);
        for (i = 0; i < BUFF_SIZE; i++)
        {
            UART1_TxHex(time[i]);
            UART1_TxChar('-');
        }
        UART1_TxString("\r\n");
        SYS_Delay(1000);
    }
}
