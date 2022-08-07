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
 * Demo:  Ci24R1 SOP8 2.4GHz RF
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
#include "ci24r1.h"

// 0:TX, 1:RX
#define CI24R1_MODE 1

__CODE uint8_t TX_ADDRESS[5]={0x34,0x43,0x10,0x10,0x01};
__CODE uint8_t RX_ADDRESS[5]={0x01,0x43,0x10,0x10,0x34};
extern uint8_t *xbuf_data;

void GPIO_Init(void)
{
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
    uint8_t i, j, status;

    SYS_SetClock();
    GPIO_Init();

    // UART1, baud 115200, baud source Timer1, 1T mode, no interrupt
    UART1_Config8bitUart(UART1_BaudSource_Timer1, HAL_State_ON, 115200);
    UART1_TxString("UART Initialized\r\n");

    while (CI24R1_SPI_Test() == HAL_ERROR)
    {
        UART1_TxString(" - check failed\r\n");
        SYS_Delay(1000);
    }
    UART1_TxString(" - check passed\r\n");

    CI24R1_Init();

    if (CI24R1_MODE == 0)
    {
        // TX
        CI24R1_SetChannel(60);
        CI24R1_SetTxMode();
        CI24R1_SetTxAddress(TX_ADDRESS);
        CI24R1_SetRxAddress(RX_ADDRESS);
        UART1_TxString("CI24R1 TX Initialized\r\n");

        while(1)
        {
            CI24R1_PrintStatus();
            CI24R1_Tx(tmp, CI24R1_PLOAD_WIDTH);
            SYS_Delay(500);
        }
    }
    else
    {
        // RX
        CI24R1_SetChannel(60);
        CI24R1_SetRxMode();
        CI24R1_SetTxAddress(RX_ADDRESS);
        CI24R1_SetRxAddress(TX_ADDRESS);
        UART1_TxString("CI24R1 RX Initialized\r\n");

        while(1)
        {
            CI24R1_PrintStatus();
            CI24R1_Rx();
            UART1_TxString("\r\n");
            SYS_Delay(10);
        }
    }
}
