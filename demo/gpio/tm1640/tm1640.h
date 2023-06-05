#ifndef __TM1640_H
#define __TM1640_H

#include "fw_hal.h"
#include "string.h"

#define TM1640_SCK          P32
#define TM1640_DIN          P35

#define TM1640_SCK_HIGH     P32 = 1
#define TM1640_SCK_LOW      P32 = 0
#define TM1640_DIN_HIGH     P35 = 1
#define TM1640_DIN_LOW      P35 = 0


#define TM1640_ADDR_INCR    0x40 // auto-increment address
#define TM1640_ADDR_FIEXD   0x44 // fixed address

#define TM1640_ADDR_MASK    0xC0 // address command, adding grid from 0x00 to 0x0F

#define TM1640_DISPLAY_OFF  0x80 // display off
#define TM1640_DISPLAY_ON   0x88 // display on, adding brightness from 0x00 to 0x07
#define TM1640_BRIGHT_0     0x00
#define TM1640_BRIGHT_1     0x01
#define TM1640_BRIGHT_2     0x02
#define TM1640_BRIGHT_3     0x03
#define TM1640_BRIGHT_4     0x04
#define TM1640_BRIGHT_5     0x05
#define TM1640_BRIGHT_6     0x06
#define TM1640_BRIGHT_7     0x07



void TM1640_ResetAll(uint8_t data);
void TM1640_WriteCommand(uint8_t command);
void TM1640_SetAddrFixedMode(void);
void TM1640_SetAddrIncrMode(void);
void TM1640_WriteOneGrid(uint8_t addr, uint8_t data);
void TM1640_WriteRange(uint8_t addr, uint8_t *data, uint8_t len);

#endif
