// Copyright 2021 IOsetting <iosetting(at)outlook.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "fw_hal.h"

#define RING_BUFFER_SIZE 0x20

__IDATA uint8_t ring_buffer[RING_BUFFER_SIZE];
static volatile uint16_t from, to;

void ring_buffer_reset(void);
void ring_buffer_push(uint8_t c);
uint8_t ring_buffer_pop(uint8_t *c);
uint16_t ring_buffer_size(void);
uint16_t ring_buffer_read(uint8_t *buf);


INTERRUPT(UART1_Routine, EXTI_VectUART1)
{
    uint8_t c;

    if (RI)
    {
        UART1_ClearRxInterrupt();
        c = SBUF;
        if (c == '\r' || c == '\n')
        {
            c = '\0';
            ring_buffer_push(c);
        }
        else if (c == 0x7F)
        {
            ring_buffer_pop(&c);
        }
        else
        {
            ring_buffer_push(c);
        }
    }
}

void main(void)
{
    uint8_t msg[RING_BUFFER_SIZE], size;

    SYS_SetClock();
    // UART1, baud 115200, baud source Timer2, 1T mode, interrupt on
    UART1_Config8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200);
    UART1_SetRxState(HAL_State_ON);
    // Enable UART1 interrupt
    EXTI_Global_SetIntState(HAL_State_ON);
    EXTI_UART1_SetIntState(HAL_State_ON);
    // Initialize ring buffer
    ring_buffer_reset();

    while(1)
    {
        size = ring_buffer_read((uint8_t *)msg);
        if (size > 0)
        {
            ring_buffer_reset();
            UART1_TxString(msg);
            UART1_TxString("\r\n");
        }
        SYS_Delay(500);
    }
}

/**
 * Ring buffer methods
*/

void ring_buffer_reset(void)
{
    from = 0;
    to = 0;
}

void ring_buffer_push(uint8_t c)
{
    ring_buffer[to++] = c;
    if (to >= RING_BUFFER_SIZE)
    {
        to = 0;
    }
    if (to == from)
    {
        from++;
        if (from >= RING_BUFFER_SIZE)
        {
            from = 0;
        }
    }
}

uint8_t ring_buffer_pop(uint8_t *c)
{
    if (to != from)
    {
        to = (to > 0)? to - 1 : RING_BUFFER_SIZE - 1;
        *c = ring_buffer[to];
        return 1;
    }
    else
    {
        return 0;
    }
}

uint16_t ring_buffer_size(void)
{
    if (to >= from)
    {
        return to - from;
    }
    else
    {
        return RING_BUFFER_SIZE - from + to;
    }
}

uint16_t ring_buffer_read(uint8_t *buf)
{
    uint16_t pos;
    if (to >= from)
    {
        pos = from;
        while(pos < to)
        {
            *buf++ = ring_buffer[pos++];
        }
        return to - from;
    }
    else
    {
        pos = from;
        while(pos < RING_BUFFER_SIZE)
        {
            *buf++ = ring_buffer[pos++];
        }
        pos = 0;
        while(pos < to)
        {
            *buf++ = ring_buffer[pos++];
        }
        return RING_BUFFER_SIZE - from + to;
    }
}