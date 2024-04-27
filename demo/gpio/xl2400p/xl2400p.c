// Copyright 2024 IOsetting <iosetting(at)outlook.com>
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

#include "xl2400p.h"


/* Address for SPI interface test */
const uint8_t XL2400P_TestAddress[5] = {0xCC,0x31,0x21,0x46,0x33};


void XL2400P_WriteReg(uint8_t reg, uint8_t value)
{
  XL2400P_SetNssLow();
  XL2400P_WriteByte(reg);
  XL2400P_WriteByte(value);
  XL2400P_SetNssHigh();
}

uint8_t XL2400P_ReadReg(uint8_t reg)
{
  uint8_t reg_val;
  XL2400P_SetNssLow();
  XL2400P_WriteByte(reg);
  reg_val = XL2400P_ReadByte();
  XL2400P_SetNssHigh();
  return reg_val;
}

void XL2400P_WriteFromBuf(uint8_t reg, const uint8_t *pBuf, uint8_t len)
{
  uint8_t ctr;
  XL2400P_SetNssLow();
  XL2400P_WriteByte(reg);
  for (ctr = 0; ctr < len; ctr++)
  {
    XL2400P_WriteByte(*pBuf++);
  }
  XL2400P_SetNssHigh();
}

void XL2400P_ReadToBuf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
  uint8_t ctr;
  XL2400P_SetNssLow();
  XL2400P_WriteByte(reg);
  for (ctr = 0; ctr < len; ctr++)
  {
    pBuf[ctr] = XL2400P_ReadByte();
  }
  XL2400P_SetNssHigh();
}

void XL2400P_CE_High(void)
{
  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_CFG_TOP, 0xEF);
}

void XL2400P_CE_Low(void)
{
  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_CFG_TOP, 0xEE);
}

uint8_t XL2400P_SelfTest(void)
{
    uint8_t i, xbuf[6];

    // Turn it into work mode otherwise SPI write won't succeed
    XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_CFG_TOP, 0x02);
    SYS_Delay(2);
    XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_CFG_TOP, 0x3E);
    SYS_Delay(2);
    XL2400P_ReadToBuf(XL2400P_CMD_R_REGISTER | XL2400P_REG_ANALOG_CFG3, xbuf, 6);
    xbuf[5] = (xbuf[5] | 0x6d);
    XL2400P_WriteFromBuf(XL2400P_CMD_W_REGISTER | XL2400P_REG_ANALOG_CFG3, xbuf, 6);

    // Write test address
    XL2400P_WriteFromBuf(XL2400P_CMD_W_REGISTER | XL2400P_REG_TX_ADDR, XL2400P_TestAddress, 5);
    // Read back and check
    XL2400P_ReadToBuf(XL2400P_CMD_R_REGISTER | XL2400P_REG_TX_ADDR, xbuf, 5);
    for (i = 0; i < 5; i++) {
        UART1_TxHex(*(xbuf + i));
        if (*(xbuf + i) != *(XL2400P_TestAddress + i)) return 1;
    }
    return 0;
}

void XL2400P_Init(void)
{
	uint8_t buff[16]={0};

  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_CFG_TOP, 0x02);
  SYS_Delay(2);

  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_CFG_TOP, 0x3E);
  SYS_Delay(2);

  XL2400P_ReadToBuf(XL2400P_REG_ANALOG_CFG3, buff, 6);
  buff[5] = (buff[5] | 0x6D);
  XL2400P_WriteFromBuf(XL2400P_CMD_W_REGISTER | XL2400P_REG_ANALOG_CFG3, buff, 6);

  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_EN_AA, 0x3F);         // 0x00:no ack, 0x3F:all ack
  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_EN_RXADDR, 0x3F);
  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_SETUP_AW, 0xaf);      // Address width
  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_SETUP_RETR, 0x33);    // retries and interval
  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_RF_SETUP, XL2400P_RF_DR_250K); // speed rate

  // buff[0] = RF_PACKET_SIZE;
  // buff[1] = RF_PACKET_SIZE;
  // XL2400P_WriteFromBuf(XL2400P_CMD_W_REGISTER+RX_PW_PX, buff, 2);

  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_DYNPD, 0x3f); // Use dynamic length

  //bit7&6=00 Return status when send register address
  //bit5=0 Disable long-pack
  //bit4=1 FEC off
  //bit3=1 FEATURE on
  //bit2=0 Dynamic length off
  //bit1=0 ACK without payload
  //bit0=0 Disable W_TX_PAYLOAD_NOACK mode
  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_FEATURE, 0x1C);
}

void XL2400P_ClearBuffer(void)
{
  XL2400P_WriteReg(XL2400P_CMD_FLUSH_TX, XL2400P_CMD_NOP);
  XL2400P_WriteReg(XL2400P_CMD_FLUSH_RX, XL2400P_CMD_NOP);
  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_STATUS, XL2400P_FLAG_RX_DR
                                                           | XL2400P_FLAG_TX_DS
                                                           | XL2400P_FLAG_MAX_RT);
}

void XL2400P_Reset(void)
{
  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_CFG_TOP, 0xEA);
  SYS_Delay(1);
  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_CFG_TOP, 0xEE);
  SYS_Delay(1);
}

/**
 * ch: range [0, 80]
*/
void XL2400P_SetChannel(uint8_t ch)
{
  uint8_t bak = XL2400P_ReadReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_EN_AA);
  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_EN_AA, bak & ~0x40);
  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_RF_CH, 0x60 + ch);
  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_EN_AA, bak | 0x40);
}

void XL2400P_SetTxAddress(const uint8_t *addr)
{
  XL2400P_WriteFromBuf(XL2400P_CMD_W_REGISTER | XL2400P_REG_TX_ADDR, addr, 5);
}

void XL2400P_SetRxAddress(const uint8_t pipe, const uint8_t *addr)
{
  uint8_t buff[4];
  switch (pipe)
  {
  case 0:
    XL2400P_WriteFromBuf(XL2400P_CMD_W_REGISTER | XL2400P_REG_RX_ADDR_P0, addr, 5);
    break;
  case 1:
    XL2400P_WriteFromBuf(XL2400P_CMD_W_REGISTER | XL2400P_REG_RX_ADDR_P1, addr, 5);
    break;
  case 2: // P2 ~ P5 only accept 1 byte for each
  case 3:
  case 4:
  case 5:
    XL2400P_ReadToBuf(XL2400P_CMD_R_REGISTER | XL2400P_REG_RX_ADDR_P2_P5, buff, 4);
    *(buff + (pipe - 2)) = *addr;
    XL2400P_WriteFromBuf(XL2400P_CMD_W_REGISTER | XL2400P_REG_RX_ADDR_P2_P5, buff, 4);
    break;
  }
}

void XL2400P_SetPower(uint8_t power)
{
  uint8_t buff[2];
  XL2400P_ReadToBuf(XL2400P_CMD_R_REGISTER | XL2400P_REG_RF_SETUP, buff, 2);
  buff[1] = power;
  XL2400P_WriteFromBuf(XL2400P_CMD_W_REGISTER | XL2400P_REG_RF_SETUP, buff, 2);
}

void XL2400P_Sleep(void)
{
  XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_CFG_TOP, 0x00);
}

void XL2400P_SetTxMode(void)
{
  uint8_t buff[2];
  buff[0] = 0xee;
  buff[1] = 0x80;
  XL2400P_WriteFromBuf(XL2400P_CMD_W_REGISTER | XL2400P_REG_CFG_TOP, buff, 2);
  XL2400P_ClearBuffer();
  SYS_Delay(1);
}

void XL2400P_SetRxMode(void)
{
  uint8_t buff[2];
  buff[0] = 0xee;
  buff[1] = 0xc0;
  XL2400P_WriteFromBuf(XL2400P_CMD_W_REGISTER | XL2400P_REG_CFG_TOP, buff, 2);
  XL2400P_ClearBuffer();
  XL2400P_CE_High();
  SYS_Delay(1);
}

uint8_t XL2400P_Rx(uint8_t *pBuff, uint8_t *meta)
{
  uint8_t status;

  status = XL2400P_ReadReg(XL2400P_REG_STATUS);
  if (status & XL2400P_FLAG_RX_DR)
  {
    *meta = (status & 0x0E) >> 1;
    if (*meta < 6)
    {
      *(meta + 1) = XL2400P_ReadReg(XL2400P_CMD_R_RX_PL_WID);
      XL2400P_ReadToBuf(XL2400P_CMD_R_RX_PAYLOAD, pBuff, *(meta + 1));
    }
    XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_STATUS, status);
  }
  return status;
}

uint8_t XL2400P_Tx(uint8_t *pBuff , uint8_t len)
{
  uint8_t status = 0, timeout = 200;

  XL2400P_CE_High();
  XL2400P_WriteReg(XL2400P_CMD_FLUSH_TX, XL2400P_CMD_NOP);
  XL2400P_WriteFromBuf(XL2400P_CMD_W_TX_PAYLOAD, pBuff, len);
  while (timeout--)
  {
    SYS_Delay(1);
    status = XL2400P_ReadReg(XL2400P_CMD_R_REGISTER | XL2400P_REG_STATUS);
    if ((status & (XL2400P_FLAG_TX_DS | XL2400P_FLAG_MAX_RT)) != 0)
    {
      //DEBUG_PRINTF("%d: %02X\r\n", timeout, status);
      XL2400P_WriteReg(XL2400P_CMD_W_REGISTER | XL2400P_REG_STATUS, status);
      break;
    }
  }
  return status;
}