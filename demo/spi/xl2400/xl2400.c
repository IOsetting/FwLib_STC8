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

#include "xl2400.h"

__IDATA uint8_t cbuf[2], xbuf[XL2400_PL_WIDTH_MAX + 1];
uint8_t *xbuf_data = xbuf + 1;

void XL2400_WriteReg(uint8_t reg, uint8_t value)
{
    XL2400_CSN = 0;
    cbuf[0] = reg;
    cbuf[1] = value;
    SPI_TxRxBytes(cbuf, 2);
    XL2400_CSN = 1;
}

uint8_t XL2400_ReadReg(uint8_t reg)
{
    XL2400_CSN = 0;
    cbuf[0] = reg;
    cbuf[1] = XL2400_CMD_NOP;
    SPI_TxRxBytes(cbuf, 2);
    XL2400_CSN = 1;
    return cbuf[1];
}

void XL2400_WriteFromBuf(uint8_t reg, const uint8_t *pBuf, uint8_t len)
{
    XL2400_CSN = 0;
    xbuf[0] = reg;
    memcpy(xbuf_data, pBuf, len);
    SPI_TxRxBytes(xbuf, len + 1);
    XL2400_CSN = 1;
}

void XL2400_ReadToBuf(uint8_t reg, uint8_t len)
{
    XL2400_CSN = 0;
    memset(xbuf, XL2400_CMD_NOP, XL2400_PL_WIDTH_MAX + 1);
    xbuf[0] = reg;
    SPI_TxRxBytes(xbuf, len + 1);
    XL2400_CSN = 1;
}

void XL2400_WriteBack(uint8_t reg, uint8_t len)
{
    XL2400_CSN = 0;
    xbuf[0] = reg;
    SPI_TxRxBytes(xbuf, len + 1);
    XL2400_CSN = 1;
}

void XL2400_CE_Low(void)
{
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_CFG_TOP, 2);
    *(xbuf_data + 1) &= 0xBF;
    XL2400_WriteBack(XL2400_CMD_W_REGISTER | XL2400_REG_CFG_TOP, 2);
}

void XL2400_CE_High(void)
{
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_CFG_TOP, 2);
    *(xbuf_data + 1) |= 0x40;
    XL2400_WriteBack(XL2400_CMD_W_REGISTER | XL2400_REG_CFG_TOP, 2);
}

uint8_t XL2400_SPI_Test(void)
{
    uint8_t i;
    const uint8_t *ptr = (const uint8_t *)XL2400_TEST_ADDR;
    XL2400_WriteFromBuf(XL2400_CMD_W_REGISTER | XL2400_REG_TX_ADDR, ptr, 5);
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_TX_ADDR, 5);
    for (i = 0; i < 5; i++) {
        UART1_TxHex(*(xbuf_data + i));
        if (*(xbuf_data + i) != *ptr++) return HAL_ERROR;
    }
    return HAL_OK;
}

void XL2400_Init(void)
{
    // Analog config
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_ANALOG_CFG0, 13);
    *(xbuf_data + 4) &= ~0x04;
    *(xbuf_data + 12) |= 0x40;
    XL2400_WriteBack(XL2400_CMD_W_REGISTER | XL2400_REG_ANALOG_CFG0, 13);
    // Switch to software CE control, wake up RF
    XL2400_WakeUp();
    // Enable Auto ACK Pipe 0
    XL2400_WriteReg(XL2400_CMD_W_REGISTER | XL2400_REG_EN_AA, 0x3F);
    // Enable Pipe 0
    XL2400_WriteReg(XL2400_CMD_W_REGISTER | XL2400_REG_EN_RXADDR, 0x3F);
    // Address Width, 5 bytes
    XL2400_WriteReg(XL2400_CMD_W_REGISTER | XL2400_REG_SETUP_AW, 0xAF);
    // Retries and interval
    XL2400_WriteReg(XL2400_CMD_W_REGISTER | XL2400_REG_SETUP_RETR, 0x33);
    // RF Data Rate 1Mbps
    XL2400_WriteReg(XL2400_CMD_W_REGISTER | XL2400_REG_RF_SETUP, 0x22);
    // Number of bytes in RX payload, pipe 0 and pipe 1
    *(xbuf_data + 0) = XL2400_PLOAD_WIDTH;
    *(xbuf_data + 1) = XL2400_PLOAD_WIDTH;
    XL2400_WriteBack(XL2400_CMD_W_REGISTER | XL2400_REG_RX_PW_PX, 2);
    // Dynamic payload width: off
    XL2400_WriteReg(XL2400_CMD_W_REGISTER | XL2400_REG_DYNPD, 0x00);
    // Other features
    //bit7&6=00 return status when send register address
    //bit5=0 long data pack off
    //bit4=1 FEC off
    //bit3=1 FEATURE on
    //bit2=0 Dynamic length off
    //bit1=0 ACK without payload
    //bit0=0 W_TX_PAYLOAD_NOACK off
    XL2400_WriteReg(XL2400_CMD_W_REGISTER | XL2400_REG_FEATURE, 0x18);
    // Enable RSSI
    *(xbuf_data + 0) = 0x10;
    *(xbuf_data + 1) = 0x00;
    XL2400_WriteBack(XL2400_CMD_W_REGISTER | XL2400_REG_RSSI, 2);
}

void XL2400_SetChannel(uint8_t channel)
{
    if (channel > 80) channel = 80;
    // AFC reset
    XL2400_WriteReg(XL2400_CMD_W_REGISTER | XL2400_REG_ANALOG_CFG0, 0x06);
    // AFC on
    XL2400_WriteReg(XL2400_CMD_W_REGISTER | XL2400_REG_ANALOG_CFG0, 0x0E);
    // Frequency(MHz) 2400:0x960 -> 2480:0x9B0
    *(xbuf_data + 0) = 0x60 + channel;
    *(xbuf_data + 1) = 0x09;
    XL2400_WriteBack(XL2400_CMD_W_REGISTER | XL2400_REG_RF_CH, 2);
    // AFC Locked
    *(xbuf_data + 1) |= 0x20;
    XL2400_WriteBack(XL2400_CMD_W_REGISTER | XL2400_REG_RF_CH, 2);
}

void XL2400_SetTxAddress(uint8_t *address)
{
    XL2400_WriteFromBuf(XL2400_CMD_W_REGISTER | XL2400_REG_TX_ADDR, address, 5);
    XL2400_WriteFromBuf(XL2400_CMD_W_REGISTER | XL2400_REG_RX_ADDR_P0, address, 5);
}

void XL2400_SetRxAddress(uint8_t *address)
{
    XL2400_WriteFromBuf(XL2400_CMD_W_REGISTER | XL2400_REG_RX_ADDR_P1, address, 5);
}

void XL2400_SetPower(uint8_t power)
{
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_RF_CH, 3);
    *(xbuf_data + 2) = power;
    XL2400_WriteBack(XL2400_CMD_W_REGISTER | XL2400_REG_RF_CH, 3);
}

void XL2400_Sleep(void)
{
    XL2400_CE_Low();
    XL2400_ClearStatus();

    *(xbuf_data + 0) = 0x7C;
    *(xbuf_data + 1) = 0x82;
    *(xbuf_data + 2) = 0x03;
    XL2400_WriteBack(XL2400_CMD_W_REGISTER | XL2400_REG_CFG_TOP, 3);
}

void XL2400_WakeUp(void)
{
    *(xbuf_data + 0) = 0x7E;
    *(xbuf_data + 1) = 0x82;
    *(xbuf_data + 2) = 0x0B;
    XL2400_WriteBack(XL2400_CMD_W_REGISTER | XL2400_REG_CFG_TOP, 3);
    XL2400_CE_Low();
    XL2400_ClearStatus();
}

uint8_t XL2400_RxCalibrate(void)
{
    uint8_t i, j;
    for (i = 0; i < 10; i++)
    {
        SYS_Delay(2);
        XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_ANALOG_CFG3, 2);
        *(xbuf_data + 1) |= 0x90;
        *(xbuf_data + 1) &= ~0x20;
        XL2400_WriteBack(XL2400_CMD_W_REGISTER | XL2400_REG_ANALOG_CFG3, 2);
        *(xbuf_data + 1) |= 0x40;
        XL2400_WriteBack(XL2400_CMD_W_REGISTER | XL2400_REG_ANALOG_CFG3, 2);
        SYS_Delay(1);
        XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_FIFO_STATUS, 2);

        if (*(xbuf_data + 1) & 0x20)
        {
            j = *(xbuf_data + 1) << 3;
            XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_ANALOG_CFG3, 2);
            *(xbuf_data + 1) &= 0x8F;
            *(xbuf_data + 1) |= 0x20;
            *(xbuf_data + 0) &= 0x07;
            *(xbuf_data + 0) |= j;
            XL2400_WriteBack(XL2400_CMD_W_REGISTER | XL2400_REG_ANALOG_CFG3, 2);
            return HAL_OK;
        }
    }
    return HAL_ERROR;
}

void XL2400_SetTxMode(void)
{
    XL2400_CE_Low();
    XL2400_ClearStatus();
    XL2400_WriteReg(XL2400_CMD_W_REGISTER | XL2400_REG_CFG_TOP, 0x7E);
    XL2400_RxCalibrate();
    SYS_Delay(2);
}

void XL2400_SetRxMode(void)
{
    XL2400_CE_Low();
    XL2400_ClearStatus();
    XL2400_WriteReg(XL2400_CMD_W_REGISTER | XL2400_REG_CFG_TOP, 0x7F);
    XL2400_RxCalibrate();
    XL2400_CE_High();
    SYS_Delay(1);
}

uint8_t XL2400_Tx(uint8_t *ucPayload, uint8_t length)
{
    uint8_t y = 100, status = 0;
    XL2400_ClearStatus();
    XL2400_WriteFromBuf(XL2400_CMD_W_TX_PAYLOAD, ucPayload, length);
    XL2400_CE_High();
    SYS_DelayUs(100);
    // Retry until timeout
    while (y--)
    {
        SYS_DelayUs(100);
        status = XL2400_ReadStatus();
        // If TX successful or retry timeout, exit
        if ((status & (MAX_RT_FLAG | TX_DS_FLAG)) != 0)
        {
            break;
        }
    }
    XL2400_CE_Low();
    return status;
}

uint8_t XL2400_Rx(void)
{
    uint8_t i, status, rxplWidth;
    status = XL2400_ReadStatus();
    if (status & RX_DR_FLAG)
    {
        XL2400_CE_Low();
        rxplWidth = XL2400_ReadReg(XL2400_CMD_R_RX_PL_WID);
        XL2400_ReadToBuf(XL2400_CMD_R_RX_PAYLOAD, rxplWidth);
        XL2400_ClearStatus();
        UART1_TxChar('>');
        for (i = 0; i < rxplWidth; i++)
        {
            UART1_TxHex(*(xbuf_data + i));
        }
    }
    return status;
}

uint8_t XL2400_ReadStatus(void)
{
    return XL2400_ReadReg(XL2400_CMD_R_REGISTER | XL2400_REG_STATUS);
}

void XL2400_ClearStatus(void)
{
    XL2400_WriteReg(XL2400_CMD_FLUSH_TX, XL2400_CMD_NOP);
    XL2400_WriteReg(XL2400_CMD_FLUSH_RX, XL2400_CMD_NOP);
    XL2400_WriteReg(XL2400_CMD_W_REGISTER | XL2400_REG_STATUS, 0x70);
}

void XL2400_FlushRxTX(void)
{
    XL2400_WriteReg(XL2400_CMD_FLUSH_TX, XL2400_CMD_NOP);
    XL2400_WriteReg(XL2400_CMD_FLUSH_RX, XL2400_CMD_NOP);
}

void XL2400_CarrierTest(void)
{
    XL2400_CE_Low();
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_ANALOG_CFG0, 13);
    *(xbuf_data + 12) |= 0x40;
    *(xbuf_data + 4) &= ~0x04;
    XL2400_WriteBack(XL2400_CMD_W_REGISTER | XL2400_REG_ANALOG_CFG0, 13);
    XL2400_WriteReg(XL2400_CMD_W_REGISTER | XL2400_REG_TXPROC_CFG, 0x00);
    *(xbuf_data + 0) = 0x01;
    *(xbuf_data + 1) = 0x00;
    XL2400_WriteBack(XL2400_CMD_W_REGISTER | XL2400_REG_RF_SETUP, 2);
    XL2400_ClearStatus();
}

uint8_t XL2400_PrintStatus(void)
{
    uint8_t i, status;

    UART1_TxString("Bytes from low to high: 0,1,2,3,...\r\n[Config]");
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_CFG_TOP, 3);
    for (i = 0; i < 3; i++) {
        UART1_TxHex(*(xbuf_data + i));
    }

    UART1_TxString("  [EN_AA]");
    UART1_TxHex(XL2400_ReadReg(XL2400_CMD_R_REGISTER | XL2400_REG_EN_AA));

    UART1_TxString("  [EN_RxAddr]");
    UART1_TxHex(XL2400_ReadReg(XL2400_CMD_R_REGISTER | XL2400_REG_EN_RXADDR));

    UART1_TxString("  [AddrWidth]");
    UART1_TxHex(XL2400_ReadReg(XL2400_CMD_R_REGISTER | XL2400_REG_SETUP_AW));

    UART1_TxString("  [Retry]");
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_SETUP_RETR, 4);
    for (i = 0; i < 4; i++) {
        UART1_TxHex(*(xbuf_data + i));
    }

    UART1_TxString("\r\n[RF_Channel]");
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_RF_CH, 3);
    for (i = 0; i < 3; i++) {
        UART1_TxHex(*(xbuf_data + i));
    }

    UART1_TxString("  [RF_Setup]");
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_RF_SETUP, 2);
    for (i = 0; i < 2; i++) {
        UART1_TxHex(*(xbuf_data + i));
    }

    UART1_TxString("  [Observe_Tx]");
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_OBSERVE_TX, 4);
    for (i = 0; i < 4; i++) {
        UART1_TxHex(*(xbuf_data + i));
    }

    UART1_TxString("  [RSSI]");
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_RSSI, 2);
    for (i = 0; i < 2; i++) {
        UART1_TxHex(*(xbuf_data + i));
    }

    UART1_TxString("\r\n[TxAddr]  ");
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_TX_ADDR, 5);
    for (i = 0; i < 5; i++) {
        UART1_TxHex(*(xbuf_data + i));
    }

    UART1_TxString("\r\n[RxAddrP0]");
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_RX_ADDR_P0, 5);
    for (i = 0; i < 5; i++) {
        UART1_TxHex(*(xbuf_data + i));
    }
    UART1_TxString(" [RxAddrP1]");
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_RX_ADDR_P1, 5);
    for (i = 0; i < 5; i++) {
        UART1_TxHex(*(xbuf_data + i));
    }
    UART1_TxString(" [RxAddrP2-P5]");
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_RX_ADDR_P2_P5, 4);
    for (i = 0; i < 4; i++) {
        UART1_TxHex(*(xbuf_data + i));
    }

    UART1_TxString("\r\n[RxPloadWidth_P0-P5]");
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_RX_PW_PX, 6);
    for (i = 0; i < 6; i++) {
        UART1_TxHex(*(xbuf_data + i));
    }

    UART1_TxString("\r\n[FIFO_Status]");
    XL2400_ReadToBuf(XL2400_CMD_R_REGISTER | XL2400_REG_FIFO_STATUS, 3);
    for (i = 0; i < 3; i++) {
        UART1_TxHex(*(xbuf_data + i));
    }
    UART1_TxString("  [DynPloadWidth]");
    UART1_TxHex(XL2400_ReadReg(XL2400_CMD_R_REGISTER | XL2400_REG_DYNPD));
    UART1_TxString("  [Feature]");
    UART1_TxHex(XL2400_ReadReg(XL2400_CMD_R_REGISTER | XL2400_REG_FEATURE));

    status = XL2400_ReadStatus();
    UART1_TxString("\r\n[Status]");
    UART1_TxHex(status);
    UART1_TxString("\r\n\r\n");
    return status;
}
