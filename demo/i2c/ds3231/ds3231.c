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

#include "ds3231.h"
#include "string.h"


uint8_t DS3231_Write(uint8_t reg, uint8_t dat)
{
    return I2C_Write(DS3231_I2C_ADDR, reg, &dat, 1);
}

uint8_t DS3231_MultipleRead(uint8_t reg, uint8_t *buf, uint8_t len)
{
    return I2C_Read(DS3231_I2C_ADDR, reg, buf, len);
}

uint8_t DS3231_Hex2Bcd(uint8_t hex)
{
    uint8_t i, j, k;

    i = hex / 10;            /* get tens place */
    j = hex % 10;            /* get ones place */
    k = j + (i << 4);        /* set bcd */
    return k;                /* return bcd */
}

uint8_t DS3231_Bcd2Hex(uint8_t val)
{
    uint8_t temp;

    temp = val & 0x0F;              /* get ones place */
    val = (val >> 4) & 0x0F;        /* get tens place */
    val = val * 10;                 /* set tens place */
    temp = temp + val;              /* get hex */
    return temp;                    /* return hex */
}

uint8_t DS3231_Init(void)
{
    uint8_t res;
    uint8_t prev;

    res = DS3231_MultipleRead(DS3231_REG_STATUS, (uint8_t *)&prev, 1);              /* multiple_read */
    if (res != HAL_OK)                                                              /* check result */
    {
        return res;
    }
    prev &= ~(1 << 7);                                                              /* clear config */
    res = DS3231_Write(DS3231_REG_STATUS, prev);                                    /* write status */
    if (res != HAL_OK)                                                              /* check result */
    {
        return res;
    }
    return HAL_OK;
}

uint8_t DS3231_ReadAll(uint8_t *buf)
{
    return DS3231_MultipleRead(DS3231_REG_SECOND, buf, 19);
}

uint8_t DS3231_GetTime(DS3231_Time_t *t)
{
    uint8_t res;
    uint8_t buf[7];
    memset(buf, 0, sizeof(uint8_t) * 7);                                                /* clear the buffer */
    res = DS3231_MultipleRead(DS3231_REG_SECOND, (uint8_t *)buf, 7);                    /* multiple_read */
    if (res != HAL_OK)                                                                  /* check result */
    {
        return res;                                                                     /* return error */
    }
    t->year = DS3231_Bcd2Hex(buf[6]) + 1990 + ((buf[5] >> 7) & 0x01) * 100;             /* get year */
    t->month = DS3231_Bcd2Hex(buf[5]&0x1F);                                             /* get month */
    t->week = DS3231_Bcd2Hex(buf[3]);                                                   /* get week */
    t->date = DS3231_Bcd2Hex(buf[4]);                                                   /* get date */
    t->am_pm = (DS3231_AmPm_t)((buf[2] >> 5) & 0x01);                                   /* get am pm */
    t->format = (DS3231_HourFormat_t)((buf[2] >> 6) & 0x01);                            /* get format */
    if (t->format == DS3231_FORMAT_12H)                                                 /* if 12H */
    {
        t->hour = DS3231_Bcd2Hex(buf[2] & 0x1F);                                        /* get hour */
    }
    else
    {
        t->hour = DS3231_Bcd2Hex(buf[2] & 0x3F);                                        /* get hour */
    }
    t->minute = DS3231_Bcd2Hex(buf[1]);                                                 /* get minute */
    t->second = DS3231_Bcd2Hex(buf[0]);                                                 /* get second */
    return HAL_OK;                                                                      /* success return 0 */
}
