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

/***
 * Demo: EEPROM IAP read, write, erase and software reset
 */

#include "fw_hal.h"

#define TEST_ADDR           0x0400
#define TEST_SIZE           32

void TestIAPRead(uint16_t addr, uint8_t size)
{
    uint8_t pos = 0;
    UART1_TxString("IAP_CmdRead: ");
    for (pos = 0; pos < size; pos++)
    {
        IAP_CmdRead(addr + pos);
        if (IAP_IsCmdFailed())
        {
            UART1_TxString("__ ");
            IAP_ClearCmdFailFlag();
        }
        else
        {
            UART1_TxHex(IAP_ReadData());
            UART1_TxChar(' ');
        }
    }
    UART1_TxString("\r\n");
}

void TestIAPWrite(uint16_t addr, uint8_t size)
{
    uint8_t pos = 0;
    UART1_TxString("IAP_CmdWrite: ");
    for (pos = 0; pos < size; pos++)
    {
        IAP_WriteData(pos);
        IAP_CmdWrite(addr + pos);
        if (IAP_IsCmdFailed())
        {
            UART1_TxString("__ ");
            IAP_ClearCmdFailFlag();
        }
        else
        {
            UART1_TxHex(pos);
            UART1_TxChar(' ');
        }
    }
    UART1_TxString("\r\n");
}

void TestIAPErase(uint16_t addr)
{
    uint8_t pos = 0;
    UART1_TxString("IAP_CmdErase: ");
    IAP_CmdErase(addr);
    if (IAP_IsCmdFailed())
    {
        UART1_TxString("failed.\r\n");
        IAP_ClearCmdFailFlag();
    }
    else
    {
        UART1_TxString("succeeded.\r\n");
    }
}

int main(void)
{
    SYS_SetClock();
    UART1_Config8bitUart(UART1_BaudSource_Timer2, HAL_State_ON, 115200);
    UART1_TxString("Test restarted\r\n");
    IAP_SetWaitTime();
    IAP_SetEnabled(HAL_State_ON);

    TestIAPRead(TEST_ADDR, TEST_SIZE);
    SYS_Delay(500);
    TestIAPWrite(TEST_ADDR, TEST_SIZE);
    SYS_Delay(500);
    TestIAPRead(TEST_ADDR, TEST_SIZE);
    SYS_Delay(500);
    TestIAPErase(TEST_ADDR);
    SYS_Delay(500);
    TestIAPRead(TEST_ADDR, TEST_SIZE);
    IAP_SetEnabled(HAL_State_OFF);
    SYS_Delay(2000);

    UART1_TxString("Software reset\r\n");
    SYS_Delay(1000);
    IAP_SoftReset();

    return 0;
}
