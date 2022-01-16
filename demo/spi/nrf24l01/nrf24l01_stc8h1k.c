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

/** 
 * Example code of SPI driving NRF24L01 module
 * 
 *    Pin connection:
 *    P35(SS, Ignored) => CSN
 *    P34(MOSI)        => MOSI
 *    P33(MISO)        => MISO
 *    P32(SPCLK)       => CLK
 *    P36(INT2)        => IRQ
 *    P37(IO)          => CE
 * 
 * test-board: Minimum System; test-MCU: STC8H1K08,STC8H3K32S2
 */

#include "nrf24l01.h"
#include <stdio.h>

const NRF24_SCEN CURRENT_SCEN = NRF24_SCEN_HALF_DUPLEX;
extern uint8_t __IDATA xbuf[NRF24_PLOAD_WIDTH + 1];

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
    // IRQ(P36)
    GPIO_P3_SetMode(GPIO_Pin_6, GPIO_Mode_Input_HIP);
}

void INT_Init()
{
    EXTI_Int2_SetIntState(HAL_State_ON);
    EXTI_Global_SetIntState(HAL_State_ON);
}

INTERRUPT(Int2_Routine, EXTI_VectInt2)
{
    NRF24L01_HandelIrqFlag();
}

void main(void)
{
    uint8_t __CODE tmp[] = {
        0x1F, 0x80, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
        0x21, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x28,
        0x31, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x38,
        0x41, 0x12, 0x13, 0x14, 0x15, 0x16, 0x37, 0x48};
    uint8_t succ = 0, err = 0;

    SYS_SetClock();

    GPIO_Init();
    // UART1, baud 115200, baud source Timer1, 1T mode, no interrupt
    UART1_Config8bitUart(UART1_BaudSource_Timer1, HAL_State_ON, 115200);
    UART1_TxString("UART Initialized\r\n");

    SPI_Init();
    UART1_TxString("SPI Initialized\r\n");

    while (NRF24L01_Check() == 1)
    {
        UART1_TxString("Check failed\r\n");
        SYS_Delay(1000);
    }
    UART1_TxString("NRF24L01 Checked\r\n");

    switch (CURRENT_SCEN)
    {
    case NRF24_SCEN_TX:
        NRF24L01_Init(NRF24_MODE_TX);
        UART1_TxString("NRF24L01 Initialized\r\n");
        while (1)
        {
            if (NRF24L01_WriteFast(tmp) == 0)
            {
                NRF24L01_ResetTX();
                err++;
            }
            else
            {
                succ++;
            }
            if (err >= 255 || succ >= 255)
            {
                UART1_TxHex(err);
                UART1_TxHex(succ);
                UART1_TxChar('.');
                err = 0;
                succ = 0;
            }
            SYS_Delay(50);
        }
        break;

    case NRF24_SCEN_RX:
        NRF24L01_Init(NRF24_MODE_RX);
        INT_Init();
        while (1);
        break;

    case NRF24_SCEN_HALF_DUPLEX:
        NRF24L01_Init(NRF24_MODE_RX);
        INT_Init();
        while (1)
        {
            NRF24L01_Tx(tmp);
            SYS_Delay(1000);
        }
        break;

    default:
        UART1_TxString("Unknown scen\r\n");
        break;
    }
}