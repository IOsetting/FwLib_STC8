#include "fw_hal.h"

#define BUF_SIZE    256

__BIT waitDeviceAddress;
__BIT waitMemoryAddress;
__XDATA uint8_t buffer[BUF_SIZE], addr;

INTERRUPT(I2C_Routine, EXTI_VectI2C)
{
    SFRX_ON();

    if (I2C_IsSlaveStartInterrupt())
    {
        I2C_ClearSlaveStartInterrupt();
    }
    else if (I2C_IsSlaveRecvInterrupt())
    {
        I2C_ClearSlaveRecvInterrupt();
        if (waitDeviceAddress)          // Received device address
        {
            waitDeviceAddress = 0;
        }
        else if (waitMemoryAddress)     // Received memory address
        {
            waitMemoryAddress = 0;
            addr = I2CRXD;
            I2CTXD = buffer[addr];
        }
        else                            // Received data
        {
            buffer[addr++] = I2CRXD;
            addr = addr % BUF_SIZE;
        }
    }
    else if (I2C_IsSlaveSendInterrupt())
    {
        I2C_ClearSlaveSendInterrupt();
        if (I2C_ReadSlaveAckIn())       // Stop when received NAK
        {
            I2CTXD = 0xFF;
        }
        else                            // Continue sending
        {
            I2CTXD = buffer[addr++];
            addr = addr % BUF_SIZE;
        }
    }
    else if (I2C_IsSlaveStopInterrupt())
    {
        I2C_ClearSlaveStopInterrupt();
        waitDeviceAddress = 1;
        waitMemoryAddress = 1;
    }
    SFRX_OFF();
}

void main()
{
    I2C_SetWorkMode(I2C_WorkMode_Slave);
    // P15:SCL, P14:SDA
    I2C_SetPort(I2C_AlterPort_P15_P14);

    I2CSLADR = 0x5A;

    I2C_ClearAllSlaveInterrupts();
    EXTI_I2C_SetSlvStartIntState(HAL_State_ON);
    EXTI_I2C_SetSlvRecvIntState(HAL_State_ON);
    EXTI_I2C_SetSlvSendIntState(HAL_State_ON);
    EXTI_I2C_SetSlvStopIntState(HAL_State_ON);
    EXTI_Global_SetIntState(HAL_State_ON);

    waitDeviceAddress = 1;
    waitMemoryAddress = 1;
    addr = 0;
    I2CTXD = buffer[addr];

    I2C_SetEnabled(HAL_State_ON);

    while (1);
}