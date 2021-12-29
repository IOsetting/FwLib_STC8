#ifndef ___FW_UART_H___
#define ___FW_UART_H___

#include "fw_conf.h"
#include "fw_types.h"
#include "fw_exti.h"

#define UART_RX_BUFF_SIZE 0x20

/***************************** /
 * UART1
*/
typedef enum
{
    UART1_BaudSource_Timer1 = 0x00,
    UART1_BaudSource_Timer2 = 0x01,
} UART1_BaudSource_t;

#define UART1_SetRxState(__STATE__)         SBIT_ASSIGN(REN, __STATE__)
#define UART1_ClearTxInterrupt              SBIT_RESET(TI)
#define UART1_ClearRxInterrupt              SBIT_RESET(RI)
#define UART1_WriteBuffer(__DATA__)         (SBUF = (__DATA__))
#define UART1_SetFrameErrDetect(__STATE__)  SFR_ASSIGN(PCON, 6, __STATE__)
#define UART1_SetBaudSource(__BAUD_SRC__)   SFR_ASSIGN(AUXR, 0, __BAUD_SRC__)
/**
 * Mode0: Synchronous shift serial mode, baudrate is fixed, provided by SYSCLK
 * Baud = (UART_M0x6 = 0)? (SYSCLK/12) : (SYSCLK/2)
*/
#define UART1_ConfigMode0FixedSyncSerial(__STATE__)        do{ SM0=0; SM1=0; SFR_ASSIGN(AUXR, 5, __STATE__);}while(0)
#define UART1_SetMode0Baudx6(__STATE__)     SFR_ASSIGN(AUXR, 5, __STATE__)
/**
 * Mode2: 9-bit UART mode, baudrate is fixed, provided by SYSCLK
 * Baud = (SMOD = 0)? (SYSCLK/64) : (SYSCLK/32)
*/
#define UART1_ConfigMode2Fixed9bitUart(__STATE__)            do{ SM0=1; SM1=0; SFR_ASSIGN(PCON, 7, __STATE__);}while(0)
#define UART1_SetTimer1Mode2Baudx2(__STATE__)   SFR_ASSIGN(PCON, 7, __STATE__)
/**
 * Mode1: 8-bit UART, dynamic baud-rate, provided by Timer1 or Timer2
*/
void UART1_ConfigMode1Dyn8bitUart(
    UART1_BaudSource_t baudSource, HAL_State_t freq1t, uint32_t baudrate, HAL_State_t enableInterrupt);
/**
 * Mode3: 9-bit UART, dynamic baud-rate, provided by Timer1 or Timer2
*/
void UART1_ConfigMode3Dyn9bitUart(
    UART1_BaudSource_t baudSource, HAL_State_t freq1t, uint32_t baudrate, HAL_State_t enableInterrupt);

void UART1_InterruptHandler(void);

void UART1_IntTxChar(char dat);
void UART1_IntTxHex(uint8_t hex);
void UART1_IntTxString(uint8_t *str);

/**
 * FIXME: If place this in first with following TXString(), sending may not work. didn't find the reason
*/
void UART1_TxChar(char dat);
void UART1_TxHex(uint8_t hex);
void UART1_TxString(uint8_t *str);


/***************************** /
 * UART2
*/
#define UART2_SetRxState(__STATE__)         SFR_ASSIGN(S2CON, 4, __STATE__)
#define UART2_ClearTxInterrupt              SFR_RESET(S2CON, 1)
#define UART2_ClearRxInterrupt              SFR_RESET(S2CON, 0)
#define UART2_WriteBuffer(__DATA__)         (S2BUF = (__DATA__))

/**
 * Mode0: 8-bit UART, dynamic baud-rate, provided by Timer2
*/
void UART2_ConfigMode0Dyn8bitUart(
    HAL_State_t freq1t, uint32_t baudrate, HAL_State_t enableInterrupt);
/**
 * Mode1: 9-bit UART, dynamic baud-rate, provided by Timer2
*/
void UART2_ConfigMode1Dyn9bitUart(
    HAL_State_t freq1t, uint32_t baudrate, HAL_State_t enableInterrupt);

void UART2_TxChar(char dat);
void UART2_TxHex(uint8_t hex);
void UART2_TxString(uint8_t *str);

#endif