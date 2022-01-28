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
 * Example code of wireless audio transer with NRF24L01 module
 * 
 * Pin connection:
 *    8H3K32S2/8H1K08  NRF24L01
 *    P35(SS, Ignored) => CSN    16
 *    P34(MOSI)        => MOSI   15
 *    P33(MISO)        => MISO   14
 *    P32(SPCLK)       => CLK    13
 *    P36(INT2)        => IRQ    17
 *    P37(IO)          => CE     18
 * 
 * TX: STC8H3K32S2     MAX9814
 *    P11(ADC1)        => MIC
 *    3.3V             => VDD
 *    3.3V             => GAIN
 *    GND              => A/R
 *    GND              => GND
 * 
 * RX: STC8H1K08       PAM8403
 *    P10(PWM1P)       => 200R => L or R Input
 *    GND              => _|_ Input
 *    Ext 3.3V/5V      => VCC
 *    Ext GND          => GND
 * 
 *    Note: 
 *    1. Use individual power supply for PAM8403
 *    2. Switch RX_ADDRESS and TX_ADDRESS in nrf24l01.c for RX and TX
 */

#include "nrf24l01.h"
//#include "voice.h"
#include <stdio.h>

#define BUFF_UNITS    8
#define BUFF_SIZE     (BUFF_UNITS * NRF24_PLOAD_WIDTH)

const NRF24_SCEN CURRENT_SCEN = NRF24_SCEN_TX;
extern uint16_t NRF24L01_rxsn;
extern uint8_t *NRF24L01_xbuf_data;

__XDATA uint8_t MAIN_buf[2][BUFF_SIZE] = {{0}};
uint8_t MAIN_buf_index = 0, MAIN_buf_pos = 0, 
        MAIN_ready_index = 0xFF, 
        MAIN_txrx_index, MAIN_txrx_pos = 0;

//uint16_t voice_pos = 0, voice_size = 10665;

void ADC_Init(void)
{
    // Set ADC1(GPIO P1.1) HIP
    GPIO_P1_SetMode(GPIO_Pin_1, GPIO_Mode_Input_HIP);

    // Channel: ADC1
    ADC_SetChannel(0x01);
    // ADC Clock = SYSCLK / 2 / (1+2) = SYSCLK / 6
    ADC_SetClockPrescaler(0x02);
    // Left alignment, high 8-bit in ADC_RES
    ADC_SetResultAlignmentLeft();
    // Enable interrupts
    EXTI_Global_SetIntState(HAL_State_ON);
    EXTI_ADC_SetIntState(HAL_State_ON);
    // Turn on ADC power
    ADC_SetPowerState(HAL_State_ON);
}

void SPI_Init(void)
{
    // MISO(P33) MOSI(P34)
    GPIO_P3_SetMode(GPIO_Pin_4, GPIO_Mode_InOut_QBD);
    // SCLK(P32) CSN(P35) CE(P37)
    GPIO_P3_SetMode(GPIO_Pin_2|GPIO_Pin_5|GPIO_Pin_7, GPIO_Mode_Output_PP);
    // IRQ(P36)
    GPIO_P3_SetMode(GPIO_Pin_6, GPIO_Mode_Input_HIP);

    // ST7567 doesn't work if SPI frequency is too high
    SPI_SetClockPrescaler(SPI_ClockPreScaler_16);
    // Clock idles low
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

void PWM_Init()
{
    // Set GPIO pins output mode P10 -> PWMA.1P
    GPIO_P1_SetMode(GPIO_Pin_0, GPIO_Mode_Output_PP);
    // Turn off PWMA.1 before change its mode
    PWMA_PWM1_SetPortState(HAL_State_OFF);
    PWMA_PWM1N_SetPortState(HAL_State_OFF);
    // Set PWMA.1 port direction output
    PWMA_PWM1_SetPortDirection(PWMB_PortDirOut);
    // Set PWMA.1 output low voltage when counter is less than target value
    PWMA_PWM1_ConfigOutputMode(PWM_OutputMode_PWM_HighIfLess);
    // Enable comparison value preload to make duty cycle changing smooth
    PWMA_PWM1_SetComparePreload(HAL_State_ON);
    // Turn on PWMA.1
    PWMA_PWM1_SetPortState(HAL_State_ON);

    // Set PWM frequency to 16kHz, Fpwm = SYSCLK / (PWMx_PSCR + 1) / (PWMx_ARR + 1)
    PWMA_SetPrescaler(8);
    // PWM width = Period + 1 (side alignment), or AutoReloadPeriod * 2 (center alignment)
    PWMA_SetPeriod(0xFF);
    // Counter direction, down:from [PWMA_ARRH,PWMA_ARRL] to 0
    PWMA_SetCounterDirection(PWM_CounterDirection_Down);
    // Enable preload on reload-period
    PWMA_SetAutoReloadPreload(HAL_State_ON);
    // Enable output on PWMA.1P
    PWMA_SetPinOutputState(PWM_Pin_1, HAL_State_ON);
    // Set PWMA.1 alternative ports to P1.0 and P1.1
    PWMA_PWM1_SetPort(PWMA_PWM1_AlterPort_P10_P11);
    // Enable overall output
    PWMA_SetOverallState(HAL_State_ON);
    // Start counter
    PWMA_SetCounterState(HAL_State_ON);
}

void Timer0_Init()
{
    TIM_Timer0_Config(HAL_State_ON, TIM_TimerMode_16BitAuto, 8000);
    EXTI_Timer0_SetIntState(HAL_State_ON);
    EXTI_Timer0_SetIntPriority(EXTI_IntPriority_High);
    EXTI_Global_SetIntState(HAL_State_ON);
    TIM_Timer0_SetRunState(HAL_State_ON);
}

void INT_Init()
{
    EXTI_Int2_SetIntState(HAL_State_ON);
    EXTI_Global_SetIntState(HAL_State_ON);
}

INTERRUPT(ADC_Routine, EXTI_VectADC)
{
    ADC_ClearInterrupt();
    MAIN_buf[MAIN_buf_index][MAIN_buf_pos] = ADC_RES;
    if (MAIN_buf_pos == BUFF_SIZE - 1)
    {
        MAIN_buf_pos = 0;
        MAIN_ready_index = MAIN_buf_index;
        MAIN_buf_index = 1 - MAIN_buf_index;
    }
    else
    {
        MAIN_buf_pos++;
    }
}

INTERRUPT(Timer0_Routine, EXTI_VectTimer0)
{
    uint8_t dc;
    if (CURRENT_SCEN == NRF24_SCEN_TX)
    {
        ADC_Start();
        // MAIN_buf[MAIN_buf_index][MAIN_buf_pos] = voice_bulk[voice_pos++];
        // if (MAIN_buf_pos == BUFF_SIZE - 1)
        // {
        //     MAIN_buf_pos = 0;
        //     MAIN_ready_index = MAIN_buf_index;
        //     MAIN_buf_index = 1 - MAIN_buf_index;
        // }
        // else
        // {
        //     MAIN_buf_pos++;
        // }
        // if (voice_pos == voice_size) voice_pos = 0;
    }
    else if (CURRENT_SCEN == NRF24_SCEN_RX)
    {
        if (MAIN_txrx_index == 0xFF)
        {
            if (MAIN_ready_index != 0xFF)
            {
                MAIN_txrx_index = MAIN_ready_index;
                MAIN_ready_index = 0xFF;
                MAIN_txrx_pos = 0;
            }
        }
        if (MAIN_txrx_index != 0xFF)
        {
            dc = MAIN_buf[MAIN_txrx_index][MAIN_txrx_pos];
            PWMA_PWM1_SetCaptureCompareValue(dc);
            // UART1_TxHex(dc);
            // if (MAIN_txrx_pos % 32 == 0)
            // {
            //     UART1_TxString("\r\n");
            // }
            if (MAIN_txrx_pos == BUFF_SIZE - 1)
            {
                MAIN_txrx_index = 0xFF;
                if (MAIN_ready_index != 0xFF)
                {
                    MAIN_txrx_index = MAIN_ready_index;
                    MAIN_ready_index = 0xFF;
                    MAIN_txrx_pos = 0;
                }
            }
            else
            {
                MAIN_txrx_pos++;
            }
        }
    }
}

INTERRUPT(Int2_Routine, EXTI_VectInt2)
{
    uint8_t pipe_num, status, i, *j;
    status = NRF24L01_HandelIrqFlag();
    pipe_num = (status >> 1) & 0x07;
    if (pipe_num != 0x07)
    {
        i = NRF24_PLOAD_WIDTH;
        j = NRF24L01_xbuf_data;
        while (i--)
        {
            MAIN_buf[MAIN_buf_index][MAIN_buf_pos++] = *j++;
        }
        //UART1_TxHex(MAIN_buf_pos);
        if (MAIN_buf_pos == 0)
        {
            MAIN_ready_index = MAIN_buf_index;
            MAIN_buf_index = 1 - MAIN_buf_index;
        }
    }
}

void main(void)
{
    uint8_t *tmp;
    uint8_t pos = 0, succ = 0, err = 0, i;

    SYS_SetClock();

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
        ADC_Init();
        UART1_TxString("ADC Initialized\r\n");

        Timer0_Init();
        UART1_TxString("Timer0 Initialized\r\n");

        NRF24L01_Init(NRF24_MODE_TX);
        UART1_TxString("NRF24L01 Initialized\r\n");
        while (1)
        {
            if (MAIN_ready_index != 0xFF)
            {
                MAIN_txrx_index = MAIN_ready_index;
                MAIN_ready_index = 0xFF;
                for (pos = 0; pos < BUFF_UNITS; pos++)
                {
                    tmp = (uint8_t *)MAIN_buf[MAIN_txrx_index] + (pos * NRF24_PLOAD_WIDTH);
                    // for (i = 0; i < 32; i++)
                    // {
                    //     UART1_TxHex(*(tmp + i));
                    // }
                    // UART1_TxString("\r\n");
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
                        UART1_TxString("\r\n");
                        err = 0;
                        succ = 0;
                    }
                    //SYS_Delay(1);
                }
                
            }
        }
        break;

    case NRF24_SCEN_RX:
        INT_Init();
        PWM_Init();
        Timer0_Init();
        UART1_TxString("Timer0 Initialized\r\n");
        NRF24L01_Init(NRF24_MODE_RX);
        while (1)
        {
            UART1_TxHex(NRF24L01_rxsn >> 8);
            UART1_TxHex(NRF24L01_rxsn & 0xFF);
            UART1_TxString("\r\n");
            SYS_Delay(1000);
        }
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