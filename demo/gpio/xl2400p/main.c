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

/***
 * Demo:  XL2400P SOP8 2.4GHz RF, Emulate SPI on GPIO pins
 * 
 *    Pin connection:
 *    P35              => CSN
 *    P34              => DATA
 *    P32              => SCK
 *                        VDD1     => 3.3V
 *                        XC1,XC2  => 16MHz OSC
 *                        GND      => GND
 * 
 * test-board: Minimum System; test-MCU: STC8H1K08,STC8H3K64S2
 */

#include "main.h"
#include "xl2400p.h"

#define XL2400P_PLOAD_WIDTH       32   // Payload width

// 0:RX, 1:TX
#define XL2400P_MODE 1

__CODE uint8_t TEST_ADDRESS[5] = {0x11,0x33,0x33,0x33,0x11};

uint8_t XL2400_PrintStatus(void);

void GPIO_Init(void)
{
    GPIO_P3_SetMode(GPIO_Pin_4, GPIO_Mode_InOut_QBD);
    // SCLK(P32) CSN(P35)
    GPIO_P3_SetMode(GPIO_Pin_2|GPIO_Pin_5, GPIO_Mode_Output_PP);
}

int main(void)
{
    __CODE uint8_t tmp[] = {
        0x1F, 0x80, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
        0x21, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x28,
        0x31, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x38,
        0x41, 0x12, 0x13, 0x14, 0x15, 0x16, 0x37, 0x48};

    uint8_t i, status;

    SYS_SetClock();
    GPIO_Init();

    // UART1, baud 115200, baud source Timer1, 1T mode, no interrupt
    UART1_Config8bitUart(UART1_BaudSource_Timer1, HAL_State_ON, 115200);
    UART1_TxString("UART Initialized\r\n");

    UART1_TxString("XL2400P self-test ");
    while (XL2400P_SelfTest() == 1)
    {
        UART1_TxString(" - check failed\r\n");
        SYS_Delay(1000);
    }
    UART1_TxString(" - check passed\r\n");

    XL2400P_Init();
    XL2400P_SetPower(XL2400P_RF_0DB);

#if XL2400P_MODE == 1
    XL2400P_Reset();
    XL2400P_CE_High();
    XL2400P_SetChannel(78);
    XL2400P_SetTxMode();
    XL2400P_SetTxAddress(TEST_ADDRESS);
    XL2400P_SetRxAddress(0, TEST_ADDRESS);
    UART1_TxString("XL2400P TX Initialized\r\n");

    while(1)
    {
        status = XL2400P_Tx(tmp, XL2400P_PLOAD_WIDTH);
        UART1_TxHex(status);
        UART1_TxString("\r\n");
        SYS_Delay(500);
    }
#else
    uint8_t meta[] = {0, 0}, xbuff[128];

    // RX
    XL2400P_Reset();
    XL2400P_CE_High();
    XL2400P_SetChannel(77); // RX channel = TX channel - 1
    XL2400P_SetRxMode();
    XL2400P_SetTxAddress(TEST_ADDRESS);
    XL2400P_SetRxAddress(0, TEST_ADDRESS);
    UART1_TxString("XL2400P RX Initialized\r\n");

    while(1)
    {
        status = XL2400P_Rx(xbuff, meta);
        if (status & XL2400P_FLAG_RX_DR)
        {
            UART1_TxHex(meta[0]);
            UART1_TxHex(meta[1]);
            UART1_TxChar('>');
            for (i = 0; i < meta[1]; i++)
            {
                UART1_TxHex(*(xbuff + i));
            }
            UART1_TxString("\r\n");
        }
        SYS_Delay(1);
    }
#endif
}


/************* Methods for XL2400P interface ********************/

#define XL2400P_CSN  P35
#define XL2400P_SCK  P32
#define XL2400P_MOSI P34
#define XL2400P_DATA_OUT()        GPIO_P3_SetMode(GPIO_Pin_4, GPIO_Mode_Output_PP)
#define XL2400P_DATA_IN()         GPIO_P3_SetMode(GPIO_Pin_4, GPIO_Mode_Input_HIP)

void XL2400P_SetNssHigh(void)
{
  XL2400P_CSN = 1;
}

void XL2400P_SetNssLow(void)
{
  XL2400P_CSN = 0;
}

/**
 * Emulate SPI Write on GPIO pins
 */
void XL2400P_WriteByte(uint8_t value)
{
    uint8_t i = 0;
    XL2400P_SCK = 0;
    XL2400P_DATA_OUT();
    for (i = 0; i < 8; i++)
    {
        XL2400P_SCK = 0;
        if (value & 0x80)
        {
            XL2400P_MOSI = 1;
        }
        else
        {
            XL2400P_MOSI = 0;
        }
        XL2400P_SCK = 1;
        value = value << 1;
    }
    XL2400P_SCK = 0;
}

/**
 * Emulate SPI Read on GPIO pins
 */
uint8_t XL2400P_ReadByte(void)
{
    uint8_t i = 0, RxData = 0;

    XL2400P_DATA_IN();
    XL2400P_SCK = 0;
    for (i = 0; i < 8; i++)
    {
        RxData = RxData << 1;
        XL2400P_SCK = 1;
        if (XL2400P_MOSI)
        {
            RxData |= 0x01;
        }
        else
        {
            RxData &= 0xfe;
        }
        XL2400P_SCK = 0;
    }
    XL2400P_SCK = 0;
    return RxData;
}



