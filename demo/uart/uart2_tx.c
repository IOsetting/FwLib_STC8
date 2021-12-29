#include "fw_hal.h"

void main(void)
{
    SYS_Init();
    UART2_ConfigMode0Dyn8bitUart(HAL_State_ON, 115200, HAL_State_OFF);
    while(1)
    {
        UART2_TxChar('T');
        UART2_TxHex(0x41);
        UART2_TxString("U");
        UART2_TxString(" string\r\n");
        SYS_Delay(1000);
    }
}