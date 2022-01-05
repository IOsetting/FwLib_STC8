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

uint8_t __IDATA xbuf[NRF24_PLOAD_WIDTH + 1];
uint8_t *xbuf_data = xbuf + 1;
uint16_t NRF24L01_rxsn = 0;

const uint8_t TX_ADDRESS[NRF24_ADDR_WIDTH] = {0x32,0x4E,0x6F,0x64,0x22};
const uint8_t RX_ADDRESS[NRF24_ADDR_WIDTH] = {0x32,0x4E,0x6F,0x64,0x65};

void NRF24L01_WriteReg(uint8_t reg, uint8_t value)
{
    NRF_CSN = 0;
    xbuf[0] = reg;
    xbuf[1] = value;
    SPI_TxRxBytes(xbuf, 2);
    NRF_CSN = 1;
}

uint8_t NRF24L01_ReadReg(uint8_t reg)
{
    NRF_CSN = 0;
    xbuf[0] = reg;
    xbuf[1] = NRF24_CMD_NOP;
    SPI_TxRxBytes(xbuf, 2);
    NRF_CSN = 1;
    return xbuf[1];
}

void NRF24L01_ReadToBuf(uint8_t reg, uint8_t len)
{
    NRF_CSN = 0;
    memset(xbuf, NRF24_CMD_NOP, NRF24_PLOAD_WIDTH + 1);
    xbuf[0] = reg;
    SPI_TxRxBytes(xbuf, len + 1);
    NRF_CSN = 1;
}

void NRF24L01_WriteFromBuf(uint8_t reg, const uint8_t *pBuf, uint8_t len)
{
    NRF_CSN = 0;
    xbuf[0] = reg;
    memcpy(xbuf_data, pBuf, len);
    SPI_TxRxBytes(xbuf, len + 1);
    NRF_CSN = 1;
}

void NRF24L01_PrintBuf(void)
{
    uint8_t i;
    for (i = 0; i < NRF24_PLOAD_WIDTH + 1; i++)
    {
        UART1_TxHex(xbuf[i]);
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

void NRF24L01_CheckFlag(uint8_t *tx_ds, uint8_t *max_rt, uint8_t *rx_dr)
{
    // Read the status & reset the status in one easy call
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER + NRF24_REG_STATUS, NRF24_FLAG_RX_DREADY|NRF24_FLAG_TX_DSENT|NRF24_FLAG_MAX_RT);
    // Report to the user what happened
    *tx_ds = xbuf[0] & NRF24_FLAG_TX_DSENT;
    *max_rt = xbuf[0] & NRF24_FLAG_MAX_RT;
    *rx_dr = xbuf[0] & NRF24_FLAG_RX_DREADY;
}

uint8_t NRF24L01_RxAvailable(uint8_t *pipe_num)
{
    uint8_t pipe;
    NRF24L01_ReadReg(NRF24_REG_STATUS);
    pipe = (xbuf[0] >> 1) & 0x07;
    if (pipe > 5)
        return 0;
    // If the caller wants the pipe number, include that
    if (pipe_num)
        *pipe_num = pipe;

    return 1;
}

void NRF24L01_HandelIrqFlag(void)
{
    uint8_t tx_ds, max_rt, rx_dr, pipe_num;
    NRF24L01_CheckFlag(&tx_ds, &max_rt, &rx_dr);
    if (NRF24L01_RxAvailable(&pipe_num) == 1) 
    {
        NRF24L01_ReadToBuf(NRF24_CMD_R_RX_PAYLOAD, NRF24_PLOAD_WIDTH);
        NRF24L01_rxsn++;
    }
    UART1_TxHex(tx_ds);
    UART1_TxChar(' ');
    UART1_TxHex(max_rt);
    UART1_TxChar(' ');
    UART1_TxHex(rx_dr);
    UART1_TxChar(' ');
    UART1_TxHex(pipe_num);
    UART1_TxString("\r\n");
    NRF24L01_PrintBuf();
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
        if (xbuf[0] & NRF24_FLAG_MAX_RT) {
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
        UART1_TxHex(*(xbuf_data + i));
        if (*(xbuf_data + i) != *ptr++) return 1;
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