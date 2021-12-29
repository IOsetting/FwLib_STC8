#include "fw_uart.h"
#include "fw_tim.h"
#include "fw_sys.h"

static const char hexTable[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
char wptr, rptr, UART1_RxBuffer[UART_RX_BUFF_SIZE];
__bit busy;

/***************************** /
 * UART1
*/
int16_t _UART1_Timer_InitValueCalculate(HAL_State_t freq1t, uint32_t baudrate)
{
    uint32_t value, sysclk = SYS_GetSysClk();
    value = sysclk / (4 * baudrate);
    if (!freq1t)
        value = value / 12;
    if (value > 0xFFFF)
        return 0;
    else
        return 0xFFFF - value + 1;
}

void _UART1_ConfigDynUart(UART1_BaudSource_t baudSource, HAL_State_t freq1t, uint32_t baudrate, HAL_State_t enableInterrupt)
{
    uint16_t init = _UART1_Timer_InitValueCalculate(freq1t, baudrate);
    UART1_SetBaudSource(baudSource);
    // Timer1 configuration. Mode0 only, mode2 is covered by mode0 so it is unnecessary.
    if (baudSource == UART1_BaudSource_Timer1)
    {
        TIM_Timer1_Set1TMode(freq1t);
        TIM_Timer1_SetMode(TIM_TimerMode_16BitAuto);
        TIM_Timer1_SetInitValue(init >> 8, init & 0xFF);
        TIM_Timer1_SetRunState(HAL_State_ON);
    }
    // Timer2 configuration
    else
    {
        // Timer2: 1T mode and initial value. prescaler is ignored, no interrupt.
        TIM_Timer2_Set1TMode(freq1t);
        TIM_Timer2_SetInitValue(init >> 8, init & 0xFF);
        TIM_Timer2_SetRunState(HAL_State_ON);
    }
    if (enableInterrupt)
    {
        // Enable UART1 interrupt
        EXTI_Global_SetIntState(HAL_State_ON);
        EXTI_UART1_SetIntState(HAL_State_ON);
        EXTI_UART1_SetIntPriority(EXTI_IntPriority_Highest);
    }
}

void UART1_ConfigMode1Dyn8bitUart(
    UART1_BaudSource_t baudSource, HAL_State_t freq1t, uint32_t baudrate, HAL_State_t enableInterrupt)
{
    SM0=0; SM1=1;
    _UART1_ConfigDynUart(baudSource, freq1t, baudrate, enableInterrupt);
}

void UART1_ConfigMode3Dyn9bitUart(
    UART1_BaudSource_t baudSource, HAL_State_t freq1t, uint32_t baudrate, HAL_State_t enableInterrupt)
{
    SM0=1; SM1=1;
    _UART1_ConfigDynUart(baudSource, freq1t, baudrate, enableInterrupt);
}

void UART1_InterruptHandler(void)
{
    if (TI)
    {
        TI = 0;
        busy = 0;
    }
    if (RI)
    {
        RI = 0;
        UART1_RxBuffer[rptr++] = SBUF;
        rptr = rptr % UART_RX_BUFF_SIZE;
    }
}

void UART1_IntTxChar(char dat)
{
    while (busy);
    busy = 1;
    SBUF = dat;
}

void UART1_IntTxHex(uint8_t hex)
{
    UART1_IntTxChar(hexTable[hex >> 4]);
    UART1_IntTxChar(hexTable[hex & 0xF]);
}

void UART1_IntTxString(uint8_t *str)
{
    while (*str) UART1_IntTxChar(*str++);
}

void UART1_TxChar(char dat)
{
    SBUF = dat;
    while(!TI);
    SBIT_RESET(TI);
}

void UART1_TxHex(uint8_t hex)
{
    UART1_TxChar(hexTable[hex >> 4]);
    UART1_TxChar(hexTable[hex & 0xF]);
}

void UART1_TxString(uint8_t *str)
{
    while (*str) UART1_TxChar(*str++);
}


/***************************** /
 * UART2
*/

void _UART2_ConfigDynUart(HAL_State_t freq1t, uint32_t baudrate, HAL_State_t enableInterrupt)
{
    uint16_t init = _UART1_Timer_InitValueCalculate(freq1t, baudrate);
    // Timer2: 1T mode and initial value. prescaler is ignored, no interrupt.
    TIM_Timer2_Set1TMode(freq1t);
    TIM_Timer2_SetInitValue(init >> 8, init & 0xFF);
    TIM_Timer2_SetRunState(HAL_State_ON);
    if (enableInterrupt)
    {
        // Enable UART1 interrupt
        EXTI_Global_SetIntState(HAL_State_ON);
        EXTI_UART2_SetIntState(HAL_State_ON);
        EXTI_UART2_SetIntPriority(EXTI_IntPriority_Highest);
    }
}

void UART2_ConfigMode0Dyn8bitUart(
    HAL_State_t freq1t, uint32_t baudrate, HAL_State_t enableInterrupt)
{
    SFR_RESET(S2CON, 7);
    _UART2_ConfigDynUart(freq1t, baudrate, enableInterrupt);
}
/**
 * Mode1: 9-bit UART, dynamic baud-rate, provided by Timer2
*/
void UART2_ConfigMode1Dyn9bitUart(
    HAL_State_t freq1t, uint32_t baudrate, HAL_State_t enableInterrupt)
{
    SFR_SET(S2CON, 7);
    _UART2_ConfigDynUart(freq1t, baudrate, enableInterrupt);
}

void UART2_TxChar(char dat)
{
    S2BUF = dat;
    while(!(S2CON & B00000010));
    SFR_RESET(S2CON, 1);
}

void UART2_TxHex(uint8_t hex)
{
    UART2_TxChar(hexTable[hex >> 4]);
    UART2_TxChar(hexTable[hex & 0xF]);
}

void UART2_TxString(uint8_t *str)
{
    while (*str) UART2_TxChar(*str++);
}