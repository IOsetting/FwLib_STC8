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

#include "ds18b20.h"

void DS18B20_Init(void)
{
    DS18B20_DQ_PULLUP();
    DS18B20_DQ_OUTPUT();
    DS18B20_DQ = SET;
    SYS_DelayUs(1000);
    DS18B20_DQ = RESET;
    SYS_DelayUs(1000);
    DS18B20_DQ = SET;
    SYS_DelayUs(2000);
}

__BIT DS18B20_Reset(void)
{
    __BIT b;

    /* Line low, and wait 480us */
    DS18B20_DQ = RESET;
    DS18B20_DQ_OUTPUT();
    SYS_DelayUs(500);
    /* Release line and wait for 70us */
    DS18B20_DQ_INPUT();
    SYS_DelayUs(70);
    /* Check bit value, success if low */
    b = DS18B20_DQ;
    /* Delay for 410 us */
    SYS_DelayUs(410);
    /* Return value of presence pulse, 0 = OK, 1 = ERROR */
    return b;
}

__BIT DS18B20_ReadBit(void)
{
    __BIT b = RESET;

    /* Line low */
    DS18B20_DQ = RESET;
    DS18B20_DQ_OUTPUT();
    SYS_DelayUs(2);

    /* Release line */
    DS18B20_DQ_INPUT();
    SYS_DelayUs(10);

    /* Read line value */
    if (DS18B20_DQ) {
        /* Bit is HIGH */
        b = SET;
    }

    /* Wait 50us to complete 60us period */
    SYS_DelayUs(50);
    
    /* Return bit value */
    return b;
}

uint8_t DS18B20_ReadByte(void)
{
    uint8_t i = 8, byte = 0;
    while (i--) 
    {
        byte >>= 1;
        byte |= (DS18B20_ReadBit() << 7);
    }
    return byte;
}

void DS18B20_WriteBit(__BIT b)
{
    if (b)
    {
        /* Set line low */
        DS18B20_DQ = RESET;
        DS18B20_DQ_OUTPUT();
        SYS_DelayUs(10);

        /* Bit high */
        DS18B20_DQ_INPUT();
        
        /* Wait for 55 us and release the line */
        SYS_DelayUs(55);
        DS18B20_DQ_INPUT();
    } 
    else 
    {
        /* Set line low */
        DS18B20_DQ = RESET;
        DS18B20_DQ_OUTPUT();
        SYS_DelayUs(65);
        
        /* Bit high */
        DS18B20_DQ_INPUT();
        
        /* Wait for 5 us and release the line */
        SYS_DelayUs(5);
        DS18B20_DQ_INPUT();
    }

}

void DS18B20_WriteByte(uint8_t byte)
{
    uint8_t i = 8;
    /* Write 8 bits */
    while (i--) 
    {
        /* LSB bit is first */
        DS18B20_WriteBit(byte & 0x01);
        byte >>= 1;
    }
}

void DS18B20_StartAll(void)
{
    /* Reset pulse */
    DS18B20_Reset();
    /* Skip rom */
    DS18B20_WriteByte(ONEWIRE_CMD_SKIPROM);
    /* Start conversion on all connected devices */
    DS18B20_WriteByte(DS18B20_CMD_CONVERTTEMP);
}

__BIT DS18B20_AllDone(void)
{
    /* If read bit is low, then device is not finished yet with calculation temperature */
    return DS18B20_ReadBit();
}

uint16_t DS18B20_ReadTemperature(void)
{
    uint16_t temperature;
    uint8_t i = 0;
    uint8_t data[9];

    /* Reset line */
    DS18B20_Reset();
    /* Skip ROM */
    DS18B20_WriteByte(ONEWIRE_CMD_SKIPROM);
    /* Read scratchpad command by onewire protocol */
    DS18B20_WriteByte(ONEWIRE_CMD_RSCRATCHPAD);

    /* Get data */
    for (i = 0; i < 9; i++) 
    {
        /* Read byte by byte */
        data[i] = DS18B20_ReadByte();
    }
    temperature = data[1];
    temperature = temperature << 8 | data[0];
    return temperature;
}
