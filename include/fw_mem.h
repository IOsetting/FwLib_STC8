#ifndef ___FW_MEM_H___
#define ___FW_MEM_H___

#include "fw_conf.h"
#include "fw_types.h"

typedef enum
{
    MEM_WorkRegGroup_00H_07H    = 0x00,
    MEM_WorkRegGroup_08H_0FH    = 0x01,
    MEM_WorkRegGroup_10H_17H    = 0x02,
    MEM_WorkRegGroup_18H_1FH    = 0x03,
} MEM_WorkRegGroup_t;

void MEM_SelectWorkRegGroup(MEM_WorkRegGroup_t WorkRegGroup);
void MEM_SetOnchipExtRAM(HAL_State_t HAL_State);

#endif
