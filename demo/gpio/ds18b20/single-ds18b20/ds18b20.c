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
    /* Pull up 2 seconds for possible capacitor charging */
    DS18B20_DQ_PULLUP();
    DS18B20_DQ_OUTPUT();
    DS18B20_DQ = SET;
    SYS_Delay(1000);
    DS18B20_DQ = RESET;
    SYS_Delay(1);
    DS18B20_DQ = SET;
    SYS_Delay(1000);
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
        if (DS18B20_ReadBit())
        {
            byte |= 0x80;
        }
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

void DS18B20_ReadScratchpad(uint8_t *buf)
{
    uint8_t i = 0;
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
        *buf++ = DS18B20_ReadByte();
    }
}

uint8_t DS18B20_Crc(uint8_t *addr, uint8_t len)
{
    uint8_t crc = 0, inbyte, i, mix;

    while (len--) 
    {
        inbyte = *addr++;
        for (i = 8; i; i--) 
        {
            mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if (mix) 
            {
                crc ^= 0x8C;
            }
            inbyte >>= 1;
        }
    }
    /* Return calculated CRC */
    return crc;
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

void DS18B20_ReadRom(uint8_t *buf)
{
    uint8_t i = 0;
    /* Reset pulse */
    DS18B20_Reset();
    /* Read rom */
    DS18B20_WriteByte(ONEWIRE_CMD_READROM);
    /* Get data */
    for (i = 0; i < 8; i++) 
    {
        /* Read byte by byte */
        *buf++ = DS18B20_ReadByte();
    }
}

void DS18B20_Select(const uint8_t* addr)
{
    uint8_t len = 8;
    DS18B20_WriteByte(ONEWIRE_CMD_MATCHROM);
    while (len--)
    {
        DS18B20_WriteByte(*addr++);
    }
}

void DS18B20_Start(const uint8_t *addr)
{
	/* Reset pulse */
    DS18B20_Reset();
	/* Select ROM number */
	DS18B20_Select(addr);
    /* Start conversion on selected device */
    DS18B20_WriteByte(DS18B20_CMD_CONVERTTEMP);
}

void DS18B20_ReadScratchpadFromAddr(const uint8_t *addr, uint8_t *buf)
{
    uint8_t i = 0;
    /* Reset line */
    DS18B20_Reset();
    /* Select ROM number */
	DS18B20_Select(addr);
    /* Read scratchpad command by onewire protocol */
    DS18B20_WriteByte(ONEWIRE_CMD_RSCRATCHPAD);

    /* Get data */
    for (i = 0; i < 9; i++) 
    {
        /* Read byte by byte */
        *buf++ = DS18B20_ReadByte();
    }
}

uint8_t DS18B20_Search(uint8_t *buff, uint8_t *stack, uint8_t split_point)
{
    uint8_t len = 64, pos = 0;
    /* Start from deepest point */
    split_point = (split_point == 0x00)? 0xFF : split_point;
    /* Reset line */
    DS18B20_Reset();
    /* Start searching */
    DS18B20_WriteByte(ONEWIRE_CMD_SEARCHROM);

    while (len--)
    {
        // Read the value and its complement value of this bit
        __BIT pb = DS18B20_ReadBit();
        __BIT cb = DS18B20_ReadBit();
        if (pb && cb) // no device
        {
            return 0;
        }
        else if (pb) // bit = 1
        {
            *(buff + pos / 8) |= 0x01 << (pos % 8);
            DS18B20_WriteBit(SET);
            // confirm: set this bit to 1
            *(stack + pos / 8) |= 0x01 << (pos % 8);
        }
        else if (cb) // bit = 0
        {
            *(buff + pos / 8) &= ~(0x01 << (pos % 8));
            DS18B20_WriteBit(RESET);
            // confirm: set this bit to 1
            *(stack + pos / 8) |= 0x01 << (pos % 8);
        }
        else // bit can be 0 or 1, possible split point
        {
            if (split_point == 0xFF || pos > split_point)
            {
                // new split point, try 0
                *(buff + pos / 8) &= ~(0x01 << (pos % 8));
                DS18B20_WriteBit(RESET);
                // unconfirm: set this bit to 0
                *(stack + pos / 8) &= ~(0x01 << (pos % 8));
                // record this new split point
                split_point = pos;
            }
            else if (pos == split_point)
            {
                // reach split point, try 1
                *(buff + pos / 8) |= 0x01 << (pos % 8);
                DS18B20_WriteBit(SET);
                // confirm: set this bit to 1
                *(stack + pos / 8) |= 0x01 << (pos % 8);
            }
            else // middle point, use existing bit
            {
                DS18B20_WriteBit(*(buff + pos / 8) >> (pos % 8) & 0x01);
            }
        }
        pos++;
    }
    // Relocate split point, move it to the last *unconfirmed* bit of stack
    while (split_point > 0 && *(stack + split_point / 8) >> (split_point % 8) & 0x01 == 0x01) split_point--;
    return split_point;
}