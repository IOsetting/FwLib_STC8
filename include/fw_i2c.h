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

#ifndef ___FW_I2C_H___
#define ___FW_I2C_H___

#include "fw_conf.h"
#include "fw_types.h"

typedef enum
{
    I2C_WorkMode_Slave              = 0x00,
    I2C_WorkMode_Master             = 0x01,
} I2C_WorkMode_t;

typedef enum
{
    I2C_MasterCmd_Wait          = 0x00, // Wait, idle
    I2C_MasterCmd_Start         = 0x01, // START
    I2C_MasterCmd_Send          = 0x02, /* Send data. This command will generate 8 clocks on SCL, and 
                                           send I2CTXD to SDA bit by bit from MSB */
    I2C_MasterCmd_RxAck         = 0x03, /* Recive Ack. This command will generate 1 clock on SCL, and
                                           save the received bit to MSACKI（I2CMSST.1) */
    I2C_MasterCmd_Recv          = 0x04, // Recive data
    I2C_MasterCmd_TxAck         = 0x05, /* Send Ack. This command will generate 1 clock on SCL, and 
                                           write the bit value of MSACKO（I2CMSST.0） to SDA */
    I2C_MasterCmd_Stop          = 0x06, // STOP. This command will send STOP signal, and reset MSBUSY flag
    I2C_MasterCmd_StartSendRxAck = 0x09, // START + Send data + RxAck
    I2C_MasterCmd_SendRxAck     = 0x0A, // Send data + RxAck
    I2C_MasterCmd_RecvTxAck0    = 0x0B, // Receive data + TxAck(0)
    I2C_MasterCmd_RecvNAck      = 0x0C, // Receive data + NAck
} I2C_MasterCmd_t;

typedef enum
{
    //           SCL  SDA
    I2C_AlterPort_P15_P14       = 0x00,
    I2C_AlterPort_P25_P24       = 0x01,
    I2C_AlterPort_P77_P76       = 0x02,
    I2C_AlterPort_P32_P33       = 0x03,
} I2C_AlterPort_t;

/**
 * I2C bus clock = FOSC / 2 / (prescaler * 2 + 4)
 * prescaler range is [0, 63]
 */

/* Compute i2c prescaler given frequency. If the result exceeds 63, i2c might not work as expeted */
#define I2C_PRESCALER_COMPUTE(__FREQ__) ((((__SYSCLOCK / __FREQ__) / 2U) - 4U) / 2U)
/* Compute i2c frequency given prescaler */
#define I2C_FREQUENCY_COMPUTE(__PRESCALER__) ((__SYSCLOCK / 2U) / (((__PRESCALER__) * 2U) + 4U))

#define I2C_SetEnabled(__STATE__)           SFRX_ASSIGN(I2CCFG, 7, __STATE__)
#define I2C_SetWorkMode(__MODE__)           SFRX_ASSIGN(I2CCFG, 6, __MODE__)

/**
 * I2C bus clock = FOSC / 2 / (__DIV__ * 2 + 4)
 * __DIV__ range [0, 63]
*/
#define I2C_SetClockPrescaler(__DIV__) do {                             \
                SFRX_ON();                                              \
                (I2CCFG) =  (I2CCFG) & ~(0x3F) | ((__DIV__) & 0x3F);    \
                SFRX_OFF();                                             \
            } while(0)

#define I2C_SendMasterCmd(__CMD__) {                                    \
                (I2CMSCR) =  (I2CMSCR) & ~(0x0F) | ((__CMD__) & 0x0F);  \
                while (!(I2CMSST & 0x40));                              \
                I2CMSST &= ~0x40;                                       \
            }

#define I2C_MasterStart()               I2C_SendMasterCmd(I2C_MasterCmd_Start)
#define I2C_MasterSendData(__DATA__)    do{I2CTXD = (__DATA__); I2C_SendMasterCmd(I2C_MasterCmd_Send);}while(0)
#define I2C_MasterRxAck()               I2C_SendMasterCmd(I2C_MasterCmd_RxAck)
#define I2C_MasterAck()                 do{I2CMSST &= ~(0x01); I2C_SendMasterCmd(I2C_MasterCmd_TxAck);}while(0)
#define I2C_MasterNAck()                do{I2CMSST |= 0x01; I2C_SendMasterCmd(I2C_MasterCmd_TxAck);}while(0)
#define I2C_MasterStop()                I2C_SendMasterCmd(I2C_MasterCmd_Stop)

/**
 * If enabled, `Send Data`+`RxAck` will be executed automatically after write operation on I2CTXD
*/
#define I2C_SetMasterAutoSend(__STATE__)    SFRX_ASSIGN(I2CMSAUX, 0, __STATE__)
/**
 * Call P_SW2=0x80 before invoking this
*/
#define I2C_IsMasterBusy()                  (I2CMSST & 0x80)
#define I2C_ClearMasterCmdInterrupt()       do {SFRX_ON(); I2CMSST &=  ~(0x01 << 6); SFRX_OFF();} while(0)

#define I2C_ResetSlaveMode()                SFRX_SET(I2CSLCR, 0)
/**
 * Call SFRX_ON() before invoking these
*/
#define I2C_IsSlaveBusy()                   (I2CSLST & (0x01 << 7))
#define I2C_IsSlaveStartInterrupt()         (I2CSLST & (0x01 << 6))
#define I2C_ClearSlaveStartInterrupt()      (I2CSLST &=  ~(0x01 << 6))
#define I2C_IsSlaveRecvInterrupt()          (I2CSLST & (0x01 << 5))
#define I2C_ClearSlaveRecvInterrupt()       (I2CSLST &=  ~(0x01 << 5))
#define I2C_IsSlaveSendInterrupt()          (I2CSLST & (0x01 << 4))
#define I2C_ClearSlaveSendInterrupt()       (I2CSLST &=  ~(0x01 << 4))
#define I2C_IsSlaveStopInterrupt()          (I2CSLST & (0x01 << 3))
#define I2C_ClearSlaveStopInterrupt()       (I2CSLST &=  ~(0x01 << 3))
#define I2C_ReadSlaveAckIn()                (I2CSLST & (0x01 << 1))
#define I2C_ReadSlaveAckOut()               (I2CSLST & (0x01 << 0))
#define I2C_ClearAllSlaveInterrupts()       (I2CSLST = 0x00)

#define I2C_SetSlaveAddrControl(__STATE__)  SFRX_ASSIGN(I2CSLADR, 0, __STATE__)
/**
 * Alternative ports
*/
#define I2C_SetPort(__ALTER_PORT__)    (P_SW2 = P_SW2 & ~(0x03 << 4) | ((__ALTER_PORT__) << 4))


uint8_t I2C_Write(uint8_t devAddr, uint8_t memAddr, uint8_t *dat, uint16_t size);
uint8_t I2C_Read(uint8_t devAddr, uint8_t memAddr, uint8_t *buf, uint16_t size);
uint8_t I2C_Write16BitAddr(uint8_t devAddr, uint16_t memAddr, uint8_t *dat, uint16_t size);
uint8_t I2C_Read16BitAddr(uint8_t devAddr, uint16_t memAddr, uint8_t *buf, uint16_t size);

#endif
