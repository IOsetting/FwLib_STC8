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
 * Demo: AT24C32
 * Board: STC8H3K32
 * 
 *              P32   -> SCL
 *              P33   -> SDA
 *              GND   -> GND, A0, A1, A2
 *              3.3V  -> VCC
 */

#include "fw_hal.h"

// AT24C device address, change according to the voltage level of A0/A1/A2
#define AT24C_ADDR  0xA0
// Test data
__CODE int8_t dat[20] = {0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB};

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
    uint8_t offset, i, buf[20];

    SYS_SetClock();
    // UART1 configuration: baud 115200 with Timer2, 1T mode, no interrupt
    UART1_Config8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200);

    GPIO_Init();
    I2C_Init();
    I2C_Write16BitAddr(AT24C_ADDR, 0x0000, dat, 12);

    while(1)
    {
        for (offset = 0; offset < 4; offset++)
        {
            I2C_Read16BitAddr(AT24C_ADDR, 0x0000|offset, buf, 6);
            for (i = 0; i < 6; i++)
            {
                UART1_TxHex(buf[i]);
                UART1_TxChar(':');
            }
            UART1_TxString("  ");
            SYS_Delay(10);
        }
        UART1_TxString("\r\n");
        SYS_Delay(1000);
    }
}
