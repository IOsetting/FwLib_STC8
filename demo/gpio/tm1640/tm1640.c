#include "tm1640.h"


/**
 * Set SCK and DIN to low before transfer starts
*/
void TM1640_StartCommand(void)
{
    TM1640_SCK_HIGH;
    TM1640_DIN_HIGH;
    TM1640_DIN_LOW;
    TM1640_SCK_LOW;
}

/**
 * Set SCK and DIN to high after transfer ends
*/
void TM1640_EndCommand(void)
{
    TM1640_DIN_LOW;
    TM1640_SCK_HIGH;
    TM1640_DIN_HIGH;
}

/**
 * In each clock, input bit will be sampled when SCK is high
*/
void TM1640_WriteByte(uint8_t data)
{
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        TM1640_SCK_LOW;
        if (data & 0x01)
        {
            TM1640_DIN_HIGH;
        }
        else
        {
            TM1640_DIN_LOW;
        }
        TM1640_SCK_HIGH;
        data = data >> 1;
    }
}

void TM1640_WriteCommand(uint8_t command)
{
    TM1640_StartCommand();
    TM1640_WriteByte(command);
    TM1640_EndCommand();
}

void TM1640_SetAddrFixedMode(void)
{
    TM1640_WriteCommand(TM1640_ADDR_FIEXD);
}

void TM1640_SetAddrIncrMode(void)
{
    TM1640_WriteCommand(TM1640_ADDR_INCR);
}

void TM1640_WriteOneGrid(uint8_t addr, uint8_t data)
{
    TM1640_StartCommand();
    TM1640_WriteByte(TM1640_ADDR_MASK | addr);
    TM1640_WriteByte(data);
    TM1640_EndCommand();
}

void TM1640_WriteRange(uint8_t addr, uint8_t *data, uint8_t len)
{
    TM1640_StartCommand();
    TM1640_WriteByte(TM1640_ADDR_MASK | addr);
    while (len--)
    {
        TM1640_WriteByte(*data++);
    }
    TM1640_EndCommand();
}

void TM1640_ResetAll(uint8_t data)
{
    uint8_t i;
    TM1640_WriteCommand(TM1640_ADDR_INCR);
    TM1640_StartCommand();
    TM1640_WriteByte(TM1640_ADDR_MASK | 0x00);
    for (i = 0; i < 16; i++)
    {
        TM1640_WriteByte(data);
    }
    TM1640_EndCommand();
}
