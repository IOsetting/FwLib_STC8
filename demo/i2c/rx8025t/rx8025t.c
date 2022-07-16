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

#include "rx8025t.h"

__XDATA uint8_t buff[7];

uint8_t RX8025T_Write(uint8_t reg, uint8_t dat)
{
    return I2C_Write(RX8025T_I2C_ADDR, reg, &dat, 1);
}

uint8_t RX8025T_Init(void)
{
    // Reset all flags
    RX8025T_Write(RX8025T_REG_FLAG, 0x00);
    // Default , turn off all interrupts
    RX8025T_Write(RX8025T_REG_CONTROL, 0x40);
    return HAL_OK;
}

uint8_t RX8025T_GetTime(uint8_t *t)
{
    I2C_Read(RX8025T_I2C_ADDR, RX8025T_REG_SECOND, t, 16);
    return HAL_OK;
}

uint8_t RX8025T_SetTime(uint8_t *t)
{
    RX8025T_Write(RX8025T_REG_SECOND, t[0]);
    RX8025T_Write(RX8025T_REG_MINUTE, t[1]);
    RX8025T_Write(RX8025T_REG_HOUR, t[2]);
    
    RX8025T_Write(RX8025T_REG_WEEKDAY, t[3]);
    RX8025T_Write(RX8025T_REG_DAY, t[4]);
    RX8025T_Write(RX8025T_REG_MONTH, t[5]);
    RX8025T_Write(RX8025T_REG_YEAR, t[6]);
    return HAL_OK;
}
