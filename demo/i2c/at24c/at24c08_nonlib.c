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
 * Demo: AT24C08 write and read with raw registers
 * Board: STC8H3K32
 * 
 *              P32   -> SCL
 *              P33   -> SDA
 *              GND   -> GND, A2
 *              3.3V  -> VCC
 */

#include "fw_hal.h"

#define AT24C_ADDR  0xA0


void Wait()
{
    while (!(I2CMSST & 0x40));
    I2CMSST &= ~0x40;
}

void Start()
{
    I2CMSCR = 0x01;
    Wait();
}

void SendData(char dat)
{
    I2CTXD = dat;
    I2CMSCR = 0x02;
    Wait();
}

void RecvACK()
{
    I2CMSCR = 0x03;
    Wait();
}

char RecvData()
{
    I2CMSCR = 0x04;
    Wait();
    return I2CRXD;
}

void SendACK()
{
    I2CMSST = 0x00;
    I2CMSCR = 0x05;
    Wait();
}

void SendNAK()
{
    I2CMSST = 0x01;
    I2CMSCR = 0x05;
    Wait();
}

void Stop()
{
    I2CMSCR = 0x06;
    Wait();
}

void I2C_Init(void)
{
    // Master mode
    I2C_SetWorkMode(I2C_WorkMode_Master);
    /**
     * I2C clock = FOSC / 2 / (__prescaler__ * 2 + 4)
    */
    I2C_SetClockPrescaler(0x20);
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
    uint8_t i, buf[20];

    SYS_SetClock();
    // UART1 configuration: baud 115200 with Timer2, 1T mode, no interrupt
    UART1_Config8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200);

    GPIO_Init();
    I2C_Init();

    P_SW2 |= 0x80;
    
    Start();
    SendData(AT24C_ADDR);
    RecvACK();
    SendData(0x00);
    RecvACK();
    SendData(0xAF);
    RecvACK();
    SendData(0xBF);
    RecvACK();
    SendData(0xCF);
    RecvACK();
    SendData(0xDF);
    RecvACK();
    SendData(0xEF);
    RecvACK();
    SendData(0xFF);
    RecvACK();
    Stop(); 
    SYS_Delay(50);

    while (1)
    {
        Start();
        SendData(AT24C_ADDR);
        RecvACK();
        SendData(0x00);
        RecvACK();
        Start();
        SendData(AT24C_ADDR|0x01);
        RecvACK();
        buf[0] = RecvData();
        SendACK();
        buf[1] = RecvData();
        SendNAK();
        Stop();
        UART1_TxHex(buf[0]);
        UART1_TxChar(':');
        UART1_TxHex(buf[1]);
        UART1_TxChar(' ');

        Start();
        SendData(AT24C_ADDR);
        RecvACK();
        SendData(0x01);
        RecvACK();
        Start();
        SendData(AT24C_ADDR|0x01);
        RecvACK();
        buf[0] = RecvData();
        SendACK();
        buf[1] = RecvData();
        SendNAK();
        Stop();
        UART1_TxHex(buf[0]);
        UART1_TxChar(':');
        UART1_TxHex(buf[1]);
        UART1_TxChar(' ');

        Start();
        SendData(AT24C_ADDR);
        RecvACK();
        SendData(0x02);
        RecvACK();
        Start();
        SendData(AT24C_ADDR|0x01);
        RecvACK();
        buf[0] = RecvData();
        SendACK();
        buf[1] = RecvData();
        SendNAK();
        Stop();
        UART1_TxHex(buf[0]);
        UART1_TxChar(':');
        UART1_TxHex(buf[1]);
        UART1_TxChar(' ');

        SYS_Delay(200);
    }
}
