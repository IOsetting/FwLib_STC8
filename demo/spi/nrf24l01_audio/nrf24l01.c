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

#include "nrf24l01.h"

uint8_t __IDATA NRF24L01_xbuf[NRF24_PLOAD_WIDTH + 1];
uint8_t *NRF24L01_xbuf_data = NRF24L01_xbuf + 1;
uint16_t NRF24L01_rxsn = 0;
// T:0x22, R:0x65
const uint8_t RX_ADDRESS[NRF24_ADDR_WIDTH] = {0x32,0x4E,0x6F,0x64,0x22};
const uint8_t TX_ADDRESS[NRF24_ADDR_WIDTH] = {0x32,0x4E,0x6F,0x64,0x65};

void NRF24L01_WriteReg(uint8_t reg, uint8_t value)
{
    NRF_CSN = 0;
    NRF24L01_xbuf[0] = reg;
    NRF24L01_xbuf[1] = value;
    SPI_TxRxBytes(NRF24L01_xbuf, 2);
    NRF_CSN = 1;
}

uint8_t NRF24L01_ReadReg(uint8_t reg)
{
    NRF_CSN = 0;
    NRF24L01_xbuf[0] = reg;
    NRF24L01_xbuf[1] = NRF24_CMD_NOP;
    SPI_TxRxBytes(NRF24L01_xbuf, 2);
    NRF_CSN = 1;
    return NRF24L01_xbuf[1];
}

void NRF24L01_ReadToBuf(uint8_t reg, uint8_t len)
{
    NRF_CSN = 0;
    memset(NRF24L01_xbuf, NRF24_CMD_NOP, NRF24_PLOAD_WIDTH + 1);
    NRF24L01_xbuf[0] = reg;
    SPI_TxRxBytes(NRF24L01_xbuf, len + 1);
    NRF_CSN = 1;
}

void NRF24L01_WriteFromBuf(uint8_t reg, const uint8_t *pBuf, uint8_t len)
{
    NRF_CSN = 0;
    NRF24L01_xbuf[0] = reg;
    memcpy(NRF24L01_xbuf_data, pBuf, len);
    SPI_TxRxBytes(NRF24L01_xbuf, len + 1);
    NRF_CSN = 1;
}

void NRF24L01_PrintBuf(void)
{
    uint8_t i;
    for (i = 0; i < NRF24_PLOAD_WIDTH + 1; i++)
    {
        UART1_TxHex(NRF24L01_xbuf[i]);
    }
    UART1_TxString("\r\n");
}

/**
* Flush the RX FIFO
*/
void NRF24L01_FlushRX(void)
{
    NRF24L01_WriteReg(NRF24_CMD_FLUSH_RX, NRF24_CMD_NOP);
}

/**
* Flush the TX FIFO
*/
void NRF24L01_FlushTX(void)
{
    NRF24L01_WriteReg(NRF24_CMD_FLUSH_TX, NRF24_CMD_NOP);
}

void NRF24L01_CheckFlag(void)
{
    // Read the status & reset the flags
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER + NRF24_REG_STATUS, NRF24_FLAG_RX_DREADY|NRF24_FLAG_TX_DSENT|NRF24_FLAG_MAX_RT);
}

uint8_t NRF24L01_HandelIrqFlag(void)
{
    uint8_t status, tx_ds, max_rt, rx_dr, pipe_num;
    NRF24L01_CheckFlag();
    status = NRF24L01_xbuf[0];
    pipe_num = (status >> 1) & 0x07;
    if (pipe_num != 0x07) 
    {
        NRF24L01_ReadToBuf(NRF24_CMD_R_RX_PAYLOAD, NRF24_PLOAD_WIDTH);
        NRF24L01_rxsn++;
    }
    return status;
}

void NRF24L01_Tx(uint8_t *pBuf)
{
    NRF_CE = 0;
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER + NRF24_REG_CONFIG, 0x0E);
    NRF24L01_WriteFromBuf(NRF24_CMD_W_TX_PAYLOAD, pBuf, NRF24_PLOAD_WIDTH);
    NRF_CE = 1;
    SYS_Delay(10); // for reliable DS state when SETUP_RETR is 0x13
    NRF_CE = 0;
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER + NRF24_REG_CONFIG, 0x0F);
    NRF_CE = 1;
}

void NRF24L01_StartFastWrite(const void* pBuf)
{
    NRF24L01_WriteFromBuf(NRF24_CMD_W_TX_PAYLOAD, pBuf, NRF24_PLOAD_WIDTH);
    NRF_CE = 1;
}

uint8_t NRF24L01_WriteFast(const void* pBuf)
{
    //Blocking only if FIFO is full. This will loop and block until TX is successful or fail
    while ((NRF24L01_ReadReg(NRF24_REG_STATUS) & NRF24_FLAG_TX_FULL)) {
        if (NRF24L01_xbuf[0] & NRF24_FLAG_MAX_RT) {
            return 0;
        }
    }
    NRF24L01_StartFastWrite(pBuf);
    return 1;
}

void NRF24L01_ResetTX(void)
{
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER + NRF24_REG_STATUS, NRF24_FLAG_MAX_RT);//Clear max retry flag
    NRF_CE = 0;
    NRF_CE = 1;
}

uint8_t NRF24L01_Check(void)
{
    uint8_t i;
    const uint8_t *ptr = (const uint8_t *)NRF24_TEST_ADDR;
    NRF24L01_WriteFromBuf(NRF24_CMD_W_REGISTER | NRF24_REG_TX_ADDR, ptr, NRF24_ADDR_WIDTH);
    NRF24L01_ReadToBuf(NRF24_CMD_R_REGISTER | NRF24_REG_TX_ADDR, NRF24_ADDR_WIDTH);
    for (i = 0; i < NRF24_ADDR_WIDTH; i++) {
        UART1_TxHex(*(NRF24L01_xbuf_data + i));
        if (*(NRF24L01_xbuf_data + i) != *ptr++) return 1;
    }
    return 0;
}

void NRF24L01_Init(NRF24_MODE mode)
{
    NRF_CE = 0;
    NRF24L01_WriteFromBuf(NRF24_CMD_W_REGISTER + NRF24_REG_TX_ADDR, (uint8_t *)TX_ADDRESS, NRF24_ADDR_WIDTH);
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER + NRF24_REG_RX_PW_P0, NRF24_PLOAD_WIDTH);
    NRF24L01_WriteFromBuf(NRF24_CMD_W_REGISTER + NRF24_REG_RX_ADDR_P0, (uint8_t *)TX_ADDRESS, NRF24_ADDR_WIDTH);
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER + NRF24_REG_RX_PW_P1, NRF24_PLOAD_WIDTH);
    NRF24L01_WriteFromBuf(NRF24_CMD_W_REGISTER + NRF24_REG_RX_ADDR_P1, (uint8_t *)RX_ADDRESS, NRF24_ADDR_WIDTH);
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER + NRF24_REG_EN_AA, 0x3f);
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER + NRF24_REG_EN_RXADDR, 0x3f);
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER + NRF24_REG_SETUP_RETR, 0x13);
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER + NRF24_REG_RF_CH, 40);
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER + NRF24_REG_RF_SETUP, 0x07);
    switch (mode)
    {
        case NRF24_MODE_TX:
            NRF24L01_WriteReg(NRF24_CMD_W_REGISTER + NRF24_REG_CONFIG, 0x0E);
            break;
        case NRF24_MODE_RX:
        default:
            NRF24L01_WriteReg(NRF24_CMD_W_REGISTER + NRF24_REG_CONFIG, 0x0F);
            break;
    }
    NRF_CE = 1;
}