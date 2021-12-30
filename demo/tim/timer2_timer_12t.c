#include "fw_hal.h"

INTERRUPT(Timer2_Routine, EXTI_VectTimer2)
{
	UART1_TxString("hello\r\n");
}

void main(void)
{
	SYS_SetClock();
	// UART1 configuration: baud 115200 with Timer1, 1T mode, no interrupt
    UART1_ConfigMode1Dyn8bitUart(UART1_BaudSource_Timer1, HAL_State_ON, 115200, HAL_State_OFF);
	// 12T mode, prescaler:255+1, frequency: 1, interrupt: ON
	TIM_Timer2_Config(HAL_State_OFF, 0xFF, 1);
	EXTI_Timer2_SetIntState(HAL_State_ON);
	EXTI_Global_SetIntState(HAL_State_ON);
	TIM_Timer2_SetRunState(HAL_State_ON);

    while(1);
}