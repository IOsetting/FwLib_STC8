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
 * Demo: MPU6050, 3-axis gyroscope + 3-axis accelerometer + Digital Motion Processor™ (DMP™)
 * Board: STC8H8K64U
 * 
 *              P32   -> SCL
 *              P33   -> SDA
 *              GND   -> GND
 *              3.3V  -> VCC
 */
#include "fw_hal.h"
#include "mpu6050.h"
#include <stdio.h>

void I2C_Init(void)
{
    // Master mode
    I2C_SetWorkMode(I2C_WorkMode_Master);
    /**
     * I2C clock = SYSCLK / 2 / (__prescaler__ * 2 + 4)
     * MPU6050 works with i2c clock up to 400KHz
     * 
     * 44.2368 / 2 / (26 * 2 + 4) = 0.39 MHz
    */
    I2C_SetClockPrescaler(0x1A);
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
    uint16_t buf[7];

    SYS_SetClock();
    GPIO_Init();
    UART1_Config8bitUart(UART1_BaudSource_Timer1, HAL_State_ON, 115200);
    I2C_Init();
    MPU6050_Init();

    while(1)
    {
        for (i = 0; i < 100; i++)
        {
            if (i == 0)
            {
                MPU6050_EnableLowPowerMode(MPU6050_Wakeup_Freq_1p25Hz);
            }
            else if (i == 50)
            {
                MPU6050_DisableLowPowerMode();
            }
            MPU6050_ReadAll(buf);
            printf("ax:%6d, ay:%6d, az:%6d, tp:%6d, gx:%6d, gy:%6d, gz:%6d\r\n", 
                buf[0], buf[1], buf[2], (int16_t)buf[3] / 34 + 365, buf[4], buf[5], buf[6]);
            SYS_Delay(100);
        }
    }
}