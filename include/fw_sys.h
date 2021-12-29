#ifndef ___FW_SYS_H___
#define ___FW_SYS_H___

#include "fw_conf.h"
#include "fw_types.h"

#define SYS_SetFOSC(__IRCBAND__, __VRTRIM__, __IRTRIM__, __LIRTRIM__)  do {      \
                                     IRCBAND = ((__IRCBAND__) & 0x03);           \
                                     VRTRIM = (__VRTRIM__);                      \
                                     IRTRIM = (__IRTRIM__);                      \
                                     LIRTRIM = ((__LIRTRIM__) & 0x03);           \
                                 } while(0)

/**
 * STC8H Clock: 
 *  MCKSEL                     ||===> MCLKODIV ==> MCLKO_S => P1.6/P5.4
 *  00 Internal IRC    |       ||
 *  01 External OSC    |==> CLKDIV ==> SYSCLK
 *  10 External 32KHz  |
 *  11 Internal 32KHz  |
*/
HAL_StatusTypeDef SYS_Init(void);
void SYS_Delay(uint16_t t);
void SYS_DelayUs(uint16_t t);
void SYS_SetSysClkDiv(uint8_t div);
uint32_t SYS_GetSysClk(void);

#endif
