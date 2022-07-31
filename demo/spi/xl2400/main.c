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

/***
 * Demo:  XL2400 / WL2400 SOP8 2.4GHz RF
 * 
 *    Pin connection:
 *    P35(SS, Ignored) => CSN
 *    P34(MOSI)        => DATA
 *    P32(SPCLK)       => SCK
 *                        VDD1     => 3.3V
 *                        XC1,XC2  => 16MHz OSC
 *                        GND      => GND
 * 
 * test-board: Minimum System; test-MCU: STC8H1K08,STC8H3K64S2
 */

#include "fw_hal.h"
#include "xl2400.h"

// 0:TX, 1:RX
#define XL2400_MODE 1

__CODE uint8_t TX_ADDRESS[5] = {0x11,0x33,0x33,0x33,0x11};
__CODE uint8_t RX_ADDRESS[5] = {0x33,0x55,0x33,0x44,0x33};
extern uint8_t *xbuf_data;

uint8_t XL2400_PrintStatus(void);

void SPI_Init(void)
{
    // SPI frequency
    SPI_SetClockPrescaler(SPI_ClockPreScaler_16);
    // Clock is low when idle
    SPI_SetClockPolarity(HAL_State_OFF);
    // Data transfer is driven by lower SS pin
    SPI_SetClockPhase(SPI_ClockPhase_LeadingEdge);
    // MSB first
    SPI_SetDataOrder(SPI_DataOrder_MSB);
    // Define the output pins
    SPI_SetPort(SPI_AlterPort_P35_P34_P33_P32);
    // Ignore SS pin, use MSTR to swith between master/slave mode
    SPI_IgnoreSlaveSelect(HAL_State_ON);
    // Master mode
    SPI_SetMasterMode(HAL_State_ON);
    // Start SPI
    SPI_SetEnabled(HAL_State_ON);
}

void GPIO_Init(void)
{
    // Configure GPIO pins before SPI and device
    // MISO(P33) MOSI(P34)
    GPIO_P3_SetMode(GPIO_Pin_4, GPIO_Mode_InOut_QBD);
    // SCLK(P32) CSN(P35) CE(P37)
    GPIO_P3_SetMode(GPIO_Pin_2|GPIO_Pin_5|GPIO_Pin_7, GPIO_Mode_Output_PP);
}

int main(void)
{
    __CODE uint8_t tmp[] = {
        0x1F, 0x80, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
        0x21, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x28,
        0x31, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x38,
        0x41, 0x12, 0x13, 0x14, 0x15, 0x16, 0x37, 0x48};
    uint8_t i, j, status;

    SYS_SetClock();
    GPIO_Init();

    // UART1, baud 115200, baud source Timer1, 1T mode, no interrupt
    UART1_Config8bitUart(UART1_BaudSource_Timer1, HAL_State_ON, 115200);
    UART1_TxString("UART Initialized\r\n");

    SPI_Init();
    UART1_TxString("SPI Initialized\r\n");

    while (XL2400_SPI_Test() == HAL_ERROR)
    {
        UART1_TxString(" - check failed\r\n");
        SYS_Delay(1000);
    }
    UART1_TxString(" - check passed\r\n");

    XL2400_Init();
    XL2400_SetPower(XL2400_RF_0DB);

    if (XL2400_MODE == 0)
    {
        // TX
        XL2400_SetChannel(78);
        XL2400_SetTxAddress(RX_ADDRESS);
        XL2400_SetRxAddress(TX_ADDRESS);
        XL2400_SetTxMode();
        UART1_TxString("XL2400 TX Initialized\r\n");

        while(1)
        {
            //XL2400_PrintStatus();
            XL2400_Tx(tmp, XL2400_PLOAD_WIDTH);
            SYS_Delay(100);
        }
    }
    else
    {
        // RX
        XL2400_SetChannel(77);
        XL2400_SetTxAddress(RX_ADDRESS);
        XL2400_SetRxAddress(TX_ADDRESS);
        UART1_TxString("XL2400 RX Initialized\r\n");

        while(1)
        {
            XL2400_WakeUp();
            XL2400_SetRxMode();
            while (--j)
            {
                status = XL2400_Rx();
                if (status & RX_DR_FLAG)
                {
                    UART1_TxString(" <\r\n");
                }
            }
            //XL2400_PrintStatus();
            XL2400_Sleep();
            SYS_Delay(10);
        }
    }
}
