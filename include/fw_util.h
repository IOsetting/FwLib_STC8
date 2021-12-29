#ifndef ___FW_UTIL_H___
#define ___FW_UTIL_H___

#include "fw_conf.h"
#include "fw_types.h"

void UTIL_Uart1_24M_9600_Init(void);
void UTIL_Uart1_24M_115200_Init(void);
void UTIL_Uart1_33M1776_9600_Init(void);
void UTIL_Uart1_33M1776_115200_Init(void);
void UTIL_Uart1_35M_9600_Init(void);
void UTIL_Uart1_36M864_9600_Init(void);
void UTIL_Uart1_36M864_115200_Init(void);
void UTIL_ItrimScan(uint8_t ircband, uint8_t *str);

#endif
