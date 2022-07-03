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

#include "fw_i2c.h"


uint8_t I2C_Write(uint8_t devAddr, uint8_t memAddr, uint8_t *dat, uint16_t size)
{
    SFRX_ON();
    I2C_MasterStart();
    I2C_MasterSendData(devAddr & 0xFE);
    I2C_MasterRxAck();
    I2C_MasterSendData(memAddr);
    I2C_MasterRxAck();
    while(size--)
    {
        I2C_MasterSendData(*dat++);
        I2C_MasterRxAck();
    }
    I2C_MasterStop();
    SFRX_OFF();
    return HAL_OK;
}

uint8_t I2C_Read(uint8_t devAddr, uint8_t memAddr, uint8_t *buf, uint16_t size)
{
    SFRX_ON();
    I2C_MasterStart();
    I2C_MasterSendData(devAddr & 0xFE);
    I2C_MasterRxAck();
    I2C_MasterSendData(memAddr);
    I2C_MasterRxAck();
    I2C_MasterStart();
    I2C_MasterSendData(devAddr | 0x01);
    I2C_MasterRxAck();
    while(size--)
    {
        I2C_SendMasterCmd(I2C_MasterCmd_Recv);
        *buf++ = I2CRXD;
        if (size == 0)
        {
            I2C_MasterNAck();
        }
        else
        {
            I2C_MasterAck();
        }
    }
    I2C_MasterStop();
    SFRX_OFF();
    return HAL_OK;
}

uint8_t I2C_Write16BitAddr(uint8_t devAddr, uint16_t memAddr, uint8_t *dat, uint16_t size)
{
    SFRX_ON();
    I2C_MasterStart();
    I2C_MasterSendData(devAddr & 0xFE);
    I2C_MasterRxAck();
    I2C_MasterSendData(memAddr >> 8);
    I2C_MasterRxAck();
    I2C_MasterSendData(memAddr & 0xFF);
    I2C_MasterRxAck();
    while(size--)
    {
        I2C_MasterSendData(*dat++);
        I2C_MasterRxAck();
    }
    I2C_MasterStop();
    SFRX_OFF();
    return HAL_OK;
}

uint8_t I2C_Read16BitAddr(uint8_t devAddr, uint16_t memAddr, uint8_t *buf, uint16_t size)
{
    SFRX_ON();
    I2C_MasterStart();
    I2C_MasterSendData(devAddr & 0xFE);
    I2C_MasterRxAck();
    I2C_MasterSendData(memAddr >> 8);
    I2C_MasterRxAck();
    I2C_MasterSendData(memAddr & 0xFF);
    I2C_MasterRxAck();
    I2C_MasterStart();
    I2C_MasterSendData(devAddr | 0x01);
    I2C_MasterRxAck();
    while(size--)
    {
        I2C_SendMasterCmd(I2C_MasterCmd_Recv);
        *buf++ = I2CRXD;
        if (size == 0)
        {
            I2C_MasterNAck();
        }
        else
        {
            I2C_MasterAck();
        }
    }
    I2C_MasterStop();
    SFRX_OFF();
    return HAL_OK;
}