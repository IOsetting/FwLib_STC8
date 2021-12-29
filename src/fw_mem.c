#include "fw_mem.h"

void MEM_SelectWorkRegGroup(MEM_WorkRegGroup_t WorkRegGroup)
{
	RS0 = WorkRegGroup & B00000001;
	RS1 = (WorkRegGroup >> 1) & B00000001;
}

void MEM_SetOnchipExtRAM(HAL_State_t HAL_State)
{
	AUXR = AUXR & ~B00000010 | (HAL_State << 1);
}