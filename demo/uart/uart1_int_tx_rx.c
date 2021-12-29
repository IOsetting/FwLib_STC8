#include "fw_hal.h"

extern char UART1_RxBuffer[UART_RX_BUFF_SIZE];

INTERRUPT(UART1_Routine, EXTI_VectUART1)
{
    UART1_InterruptHandler();
}

void main(void)
{
    SYS_Init();
    UART1_ConfigMode1Dyn8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200, HAL_State_ON);
    UART1_SetRxState(HAL_State_ON);
    while(1)
    {
        UART1_IntTxChar('R');
        UART1_IntTxChar('X');
        UART1_IntTxChar(':');
        for (uint8_t i = 0; i < UART_RX_BUFF_SIZE; i++) UART1_IntTxChar(UART1_RxBuffer[i]);
        UART1_IntTxChar(' ');
        UART1_IntTxHex(0x41);
        UART1_IntTxHex('A');
        UART1_IntTxString(" string\r\n");
        SYS_Delay(1000);
    }
}