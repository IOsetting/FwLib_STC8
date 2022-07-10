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

__XDATA uint8_t buff[7];

uint8_t DS3231_Write(uint8_t reg, uint8_t dat)
{
    return I2C_Write(DS3231_I2C_ADDR, reg, &dat, 1);
}

uint8_t DS3231_Hex2Bcd(uint8_t hex)
{
    return (hex % 10) + ((hex / 10) << 4);
}

uint8_t DS3231_Bcd2Hex(uint8_t bcd)
{
    return (bcd >> 4) * 10 + (bcd & 0x0F);
}

uint8_t DS3231_GetStatus(void)
{
    I2C_Read(DS3231_I2C_ADDR, DS3231_REG_STATUS, buff, 1);
    return buff[0];
}

uint8_t DS3231_GetTime(uint8_t *t)
{
    uint8_t res;
    res = I2C_Read(DS3231_I2C_ADDR, DS3231_REG_SECOND, buff, 7);
    if (res != HAL_OK)
    {
        return res;
    }
    t[0] = DS3231_Bcd2Hex(buff[6]) + ((buff[5] >> 7) & 0x01) * 100; // year
    t[1] = DS3231_Bcd2Hex(buff[5] & 0x1F);                          // month
    t[2] = DS3231_Bcd2Hex(buff[3]); // week
    t[3] = DS3231_Bcd2Hex(buff[4]); // date
    t[7] = (buff[2] >> 6) & 0x01; // 12h/24h
    t[8] = (buff[2] >> 5) & 0x01; // am/pm
    if (t[7] == DS3231_FORMAT_12H)
    {
        t[4] = DS3231_Bcd2Hex(buff[2] & 0x1F); // hour
    }
    else
    {
        t[4] = DS3231_Bcd2Hex(buff[2] & 0x3F); // hour
    }
    t[5] = DS3231_Bcd2Hex(buff[1]); // minute
    t[6] = DS3231_Bcd2Hex(buff[0]); // second
    return HAL_OK;
}

/**
    uint8_t year;
    uint8_t month;
    uint8_t week;
    uint8_t date;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    DS3231_HourFormat_t format;
    DS3231_AmPm_t am_pm;
 */
uint8_t DS3231_SetTime(uint8_t *t)
{
    uint8_t res, reg;

    // Time validation
    if (t[0] > 200) t[0] = 200; // year

    if (t[1] == 0) t[1] = 1; // month
    else if (t[1] > 12) t[1] = 12;

    if (t[2] == 0) t[2] = 1; // week
    else if (t[2] > 7) t[2] = 7;

    if (t[3] == 0) t[3] = 1; // date
    else if (t[3] > 31) t[3] = 31;

    if (t[7] == DS3231_FORMAT_12H)
    {
        if (t[4] > 12) t[4] = 12; // hour
    }
    else if (t[7] == DS3231_FORMAT_24H)
    {
        if (t[4] > 23) t[4] = 23; // hour
    }

    if (t[5] > 59) t[5] = 59; // minute
    if (t[6] > 59) t[6] = 59; // second

    res = DS3231_Write(DS3231_REG_SECOND, DS3231_Hex2Bcd(t[6]));
    if (res != HAL_OK) return res;

    res = DS3231_Write(DS3231_REG_MINUTE, DS3231_Hex2Bcd(t[5]));
    if (res != HAL_OK) return res;

    if (t[7] == DS3231_FORMAT_12H)
    {
        reg = (uint8_t)((1 << 6) | (t[8] << 5) | DS3231_Hex2Bcd(t[4]));
    }
    else
    {
        reg = (0 << 6) | DS3231_Hex2Bcd(t[4]);
    }
    res = DS3231_Write(DS3231_REG_HOUR, reg);
    if (res != HAL_OK) return res;

    res = DS3231_Write(DS3231_REG_WEEK, DS3231_Hex2Bcd(t[2]));
    if (res != HAL_OK) return res;

    res = DS3231_Write(DS3231_REG_DATE, DS3231_Hex2Bcd(t[3]));
    if (res != HAL_OK) return res;

    if (t[0] >= 100)
    {
        res = DS3231_Write(DS3231_REG_MONTH, DS3231_Hex2Bcd(t[1]) | (1 << 7));
        if (res != HAL_OK) return res;
        return DS3231_Write(DS3231_REG_YEAR, DS3231_Hex2Bcd(t[0] - 100));
    }
    else
    {
        res = DS3231_Write(DS3231_REG_MONTH, DS3231_Hex2Bcd(t[1]));
        if (res != HAL_OK) return res;
        return DS3231_Write(DS3231_REG_YEAR, DS3231_Hex2Bcd(t[0]));
    }
}

uint8_t DS3231_GetPin(DS3231_PinType_t *pin)
{
    uint8_t res;
    res = I2C_Read(DS3231_I2C_ADDR, DS3231_REG_CONTROL, buff, 1);
    if (res != HAL_OK) return res;

    *pin = (DS3231_PinType_t)((buff[0] >> 2) & 0x01);
    return HAL_OK;
}

uint8_t DS3231_SetPin(DS3231_PinType_t *pin)
{
    uint8_t res;
    res = I2C_Read(DS3231_I2C_ADDR, DS3231_REG_CONTROL, buff, 1);
    if (res != HAL_OK) return res;
    buff[0] &= ~(1 << 2);
    buff[0] |= (*pin) << 2;
    return DS3231_Write(DS3231_REG_CONTROL, buff[0]);
}

uint8_t ds3231_GetSquareOutputState(HAL_State_t *state)
{
    uint8_t res;
    res = I2C_Read(DS3231_I2C_ADDR, DS3231_REG_CONTROL, buff, 1);
    if (res != HAL_OK) return res;
    *state = (HAL_State_t)((buff[0] >> 6) & 0x01);
    return HAL_OK;
}

uint8_t DS3231_SetSquareOutputState(HAL_State_t state)
{
    uint8_t res;
    res = I2C_Read(DS3231_I2C_ADDR, DS3231_REG_CONTROL, buff, 1);
    if (res != HAL_OK) return res;
    buff[0] &= ~(1 << 6);
    buff[0] |= state << 6;
    return DS3231_Write(DS3231_REG_CONTROL, buff[0]);
}

uint8_t DS3231_GetAlarmInterrupt(DS3231_Alarm_t alarm, HAL_State_t *state)
{
    uint8_t res;
    res = I2C_Read(DS3231_I2C_ADDR, DS3231_REG_CONTROL, buff, 1);
    if (res != HAL_OK) return res;
    *state = (HAL_State_t)((buff[0] >> alarm) & 0x01);
    return HAL_OK;  
}

uint8_t DS3231_SetAlarmInterrupt(DS3231_Alarm_t alarm, HAL_State_t state)
{
    uint8_t res;
    res = I2C_Read(DS3231_I2C_ADDR, DS3231_REG_CONTROL, buff, 1);
    if (res != HAL_OK) return res;
    buff[0] &= ~(1 << alarm);
    buff[0] |= state << alarm;
    return DS3231_Write(DS3231_REG_CONTROL, buff[0]);
}

uint8_t DS3231_GetAlarm1(uint8_t *t, DS3231_Alarm1Mode_t *mode)
{
    uint8_t res;

    res = I2C_Read(DS3231_I2C_ADDR, DS3231_REG_ALARM1_SECOND, buff, 4);
    if (res != HAL_OK) return res;
    t[0] = 0; // year
    t[1] = 0; // month
    if (((buff[3] >> 6) & 0x01) != 0) // if week
    {
        t[2] = DS3231_Bcd2Hex(buff[3] & 0x0F); // week
        t[3] = 0; // date
    }
    else // if date
    {
        t[2] = 0; // week
        t[3] = DS3231_Bcd2Hex(buff[3] & 0x3F); // date
    }
    t[8] = ((buff[2] >> 5) & 0x01); // am/pm
    t[7] = ((buff[2] >> 6) & 0x01); // 12h/24h
    if (t[7] == DS3231_FORMAT_12H)
    {
        t[4] = DS3231_Bcd2Hex(buff[2]&0x1F);
    }
    else
    {
        t[4] = DS3231_Bcd2Hex(buff[2]&0x3F);
    }
    t[5] = DS3231_Bcd2Hex(buff[1] & 0x7F);
    t[6] = DS3231_Bcd2Hex(buff[0] & 0x7F);
    *mode = (DS3231_Alarm1Mode_t)(
        ((buff[0]>>7)&0x01)<<0 | 
        ((buff[1]>>7)&0x01)<<1 | 
        ((buff[2]>>7)&0x01)<<2 | 
        ((buff[3]>>7)&0x01)<<3 | 
        ((buff[3]>>6)&0x01)<<4
    );
    return HAL_OK;
}

uint8_t DS3231_SetAlarm1(uint8_t *t, DS3231_Alarm1Mode_t mode)
{
    uint8_t res;
    uint8_t reg;

    res = DS3231_Write(DS3231_REG_ALARM1_SECOND, DS3231_Hex2Bcd(t[6]) | ((mode & 0x01) << 7));
    if (res != HAL_OK) return res;

    res = DS3231_Write(DS3231_REG_ALARM1_MINUTE, DS3231_Hex2Bcd(t[5]) | (((mode >> 1) & 0x01) << 7));
    if (res != HAL_OK) return res;

    if (t[7] == DS3231_FORMAT_12H)
    {
        reg = (uint8_t)((((mode >> 2) & 0x01) << 7) | (1 << 6) | (t[8] << 5) | DS3231_Hex2Bcd(t[4]));
    }
    else
    {
        reg = (((mode >> 2) & 0x01) << 7) | DS3231_Hex2Bcd(t[4]);
    }
    res = DS3231_Write(DS3231_REG_ALARM1_HOUR, reg);
    if (res != HAL_OK) return res;

    if (mode >= DS3231_ALARM1_MODE_WEEK_HOUR_MINUTE_SECOND_MATCH)
    {
        reg = (((mode >> 3) & 0x01) << 7) | (1 << 6) | DS3231_Hex2Bcd(t[2]);
    }
    else
    {
        reg = (((mode >> 3) & 0x01) << 7) | DS3231_Hex2Bcd(t[3]);
    }
    return DS3231_Write(DS3231_REG_ALARM1_WEEK, reg);
}

uint8_t DS3231_GetAlarm2(uint8_t *t, DS3231_Alarm2Mode_t *mode)
{
    uint8_t res;

    res = I2C_Read(DS3231_I2C_ADDR, DS3231_REG_ALARM2_MINUTE, buff, 3);
    if (res != HAL_OK) return res;
    t[0] = 0; // year
    t[1] = 0; // month
    if (((buff[2] >> 6) & 0x01) != 0) // if week
    {
        t[2] = DS3231_Bcd2Hex(buff[2] & 0x0F);
        t[3] = 0;
    }
    else // if date
    {
        t[2] = 0;
        t[3] = DS3231_Bcd2Hex(buff[2] & 0x3F);
    }
    t[8] = ((buff[1] >> 5) & 0x01); // am/pm
    t[7] = ((buff[1] >> 6) & 0x01); // 12h/24h


    if (t[7] == DS3231_FORMAT_12H)
    {
        t[4] = DS3231_Bcd2Hex(buff[1]&0x1F);
    }
    else
    {
        t[4] = DS3231_Bcd2Hex(buff[1]&0x3F);
    }
    t[5] = DS3231_Bcd2Hex(buff[0] & 0x7F);
    t[6] = 0;

    *mode = (DS3231_Alarm2Mode_t)(
        ((buff[0]>>7)&0x01)<<0 | 
        ((buff[1]>>7)&0x01)<<1 | 
        ((buff[2]>>7)&0x01)<<2 | 
        ((buff[2]>>6)&0x01)<<4
    );
    return HAL_OK;
}

uint8_t DS3231_SetAlarm2(uint8_t *t, DS3231_Alarm2Mode_t mode)
{
    uint8_t res;
    uint8_t reg;

    res = DS3231_Write(DS3231_REG_ALARM2_MINUTE, DS3231_Hex2Bcd(t[5]) | (((mode >> 0) & 0x01) << 7));
    if (res != HAL_OK) return res;

    if (t[7] == DS3231_FORMAT_12H)
    {
        reg = (uint8_t)((((mode >> 1) & 0x01) << 7) | (1 << 6) | (t[8] << 5) | DS3231_Hex2Bcd(t[4]));
    }
    else
    {
        reg = (((mode >> 1) & 0x01) << 7) | DS3231_Hex2Bcd(t[4]);
    }
    res = DS3231_Write(DS3231_REG_ALARM2_HOUR, reg);
    if (res != HAL_OK) return res;

    if (mode >= DS3231_ALARM2_MODE_WEEK_HOUR_MINUTE_MATCH)
    {
        reg = (((mode >> 2) & 0x01) << 7) | (1 << 6) | DS3231_Hex2Bcd(t[2]);
    }
    else
    {
        reg = (((mode >> 2) & 0x01) << 7) | DS3231_Hex2Bcd(t[3]);
    }
    return DS3231_Write(DS3231_REG_ALARM2_WEEK, reg);
}

uint8_t DS3231_ClearAlarm(DS3231_Alarm_t alarm)
{
    uint8_t res;

    res = I2C_Read(DS3231_I2C_ADDR, DS3231_REG_STATUS, buff, 1);
    if (res != HAL_OK) return res;

    buff[0] &= ~(1 << alarm);
    return DS3231_Write(DS3231_REG_STATUS, buff[0]);
}
