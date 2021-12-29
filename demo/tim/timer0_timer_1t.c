#include "fw_hal.h"

static uint16_t counter = 0;

INTERRUPT(Timer0_Routine, EXTI_VectTimer0)
{
	counter++;
	if (counter == 1000)
	{
		counter = 0;
		UART1_TxString("hello\r\n");
	}
}

void main(void)
{
	SYS_Init();
	// UART1 configuration: baud 115200 with Timer1, 1T mode, no interrupt
    UART1_ConfigMode1Dyn8bitUart(UART1_BaudSource_Timer1, HAL_State_ON, 115200, HAL_State_OFF);
	EXTI_Global_SetIntState(HAL_State_ON);
	TIM_Timer0_Config(
		HAL_State_ON, 
		TIM_TimerMode_16BitAuto, 
		1000, 
		HAL_State_ON, 
		EXTI_IntPriority_High);
	TIM_Timer0_SetRunState(HAL_State_ON);

    while(1);
}