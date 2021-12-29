#include "fw_hal.h"

void main(void)
{
    SYS_Init();
    UART1_ConfigMode1Dyn8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200, HAL_State_OFF);
    while(1)
    {
        UART1_TxChar('T');
        UART1_TxHex(0x41);
        UART1_TxString("U");
        UART1_TxString(" string\r\n");
        SYS_Delay(1000);
    }
}