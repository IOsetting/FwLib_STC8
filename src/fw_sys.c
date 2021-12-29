#include "fw_sys.h"

static const uint16_t ticks_ms = (__CONF_FOSC / (float)1000 / 13 - 46);
static const uint8_t ticks_us = (__CONF_FOSC / (float)12100000UL);
static uint8_t clkdiv = 0x1;

HAL_StatusTypeDef SYS_Init(void)
{
    SYS_SetSysClkDiv(0);
    SYS_SetFOSC(__CONF_IRCBAND, __CONF_VRTRIM, __CONF_IRTRIM, __CONF_LIRTRIM);
    // Wait a while till sysclk stable, or it may block the main process
    uint16_t i = ticks_ms;
    while (--i);
    return HAL_OK;
}

void SYS_Delay(uint16_t t)
{
    uint16_t i;
    do
    {
        i = ticks_ms;
        while (--i);
    } while (--t);
}

void SYS_DelayUs(uint16_t t)
{
    uint8_t i;
    do
    {
        i = ticks_us;
        while (--i);
    } while (--t);
}

void SYS_SetSysClkDiv(uint8_t div)
{
    P_SW2 = 0x80;
	CLKDIV = div;
	P_SW2 = 0x00;
    clkdiv = (div == 0)? 1 : div;
}

uint32_t SYS_GetSysClk(void)
{
    return ((uint32_t)__CONF_FOSC) / clkdiv;
}
