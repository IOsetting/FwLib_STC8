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

#ifndef __FW_DS18B20__
#define __FW_DS18B20__

#include "fw_hal.h"

/**
 * DS18B20 - Programmable Resolution 1-Wire Digital Thermometer
 * 
 * To-92 Pins: 
 *   With the flat side facing you and with the leads pointing down, they are GND, DQ and Vdd
 * 
*/

#define DS18B20_DQ           P35
#define DS18B20_DQ_PULLUP()  GPIO_SetPullUp(GPIO_Port_3, GPIO_Pin_5, HAL_State_ON)
#define DS18B20_DQ_INPUT()   GPIO_P3_SetMode(GPIO_Pin_5, GPIO_Mode_Input_HIP)
#define DS18B20_DQ_OUTPUT()  GPIO_P3_SetMode(GPIO_Pin_5, GPIO_Mode_InOut_OD)
#define DS18B20_DQ_LOW()     DS18B20_DQ=RESET
#define DS18B20_DQ_HIGH()    DS18B20_DQ=SET

/* OneWire commands */
#define ONEWIRE_CMD_RSCRATCHPAD             0xBE
#define ONEWIRE_CMD_WSCRATCHPAD             0x4E
#define ONEWIRE_CMD_CPYSCRATCHPAD           0x48
#define ONEWIRE_CMD_RECEEPROM               0xB8
#define ONEWIRE_CMD_RPWRSUPPLY              0xB4
#define ONEWIRE_CMD_SEARCHROM               0xF0
#define ONEWIRE_CMD_READROM                 0x33
#define ONEWIRE_CMD_MATCHROM                0x55
#define ONEWIRE_CMD_SKIPROM                 0xCC

#define DS18B20_FAMILY_CODE                 0x28
#define DS18B20_CMD_ALARMSEARCH             0xEC

/* DS18B20 read temperature command */
#define DS18B20_CMD_CONVERTTEMP             0x44     /* Convert temperature */
#define DS18B20_DECIMAL_STEPS_12BIT         0.0625
#define DS18B20_DECIMAL_STEPS_11BIT         0.125
#define DS18B20_DECIMAL_STEPS_10BIT         0.25
#define DS18B20_DECIMAL_STEPS_9BIT          0.5

/* Bits locations for resolution */
#define DS18B20_RESOLUTION_R1               6
#define DS18B20_RESOLUTION_R0               5

typedef enum {
	DS18B20_Resolution_9bits = 9,   /*!< DS18B20 9 bits resolution */
	DS18B20_Resolution_10bits = 10, /*!< DS18B20 10 bits resolution */
	DS18B20_Resolution_11bits = 11, /*!< DS18B20 11 bits resolution */
	DS18B20_Resolution_12bits = 12  /*!< DS18B20 12 bits resolution */
} DS18B20_Resolution_t;

/**
 * @brief Initialize DS18B20
 */
void DS18B20_Init(void);

/**
 * @brief Reset DS18B20
 * @return bit value 
 */
__BIT DS18B20_Reset(void);

/**
 * @brief Read one bit from DS18B20
 * @return bit value 
 */
__BIT DS18B20_ReadBit(void);

/**
 * @brief Read one byte from DS18B20
 * @return byte value 
 */
uint8_t DS18B20_ReadByte(void);

/**
 * @brief Write one bit to DS18B20
 * @param b bit value
 */
void DS18B20_WriteBit(__BIT b);

/**
 * @brief Write one byte to DS18B20
 * @param byte byte value
 */
void DS18B20_WriteByte(uint8_t byte);

/**
 * @brief 8-bit CRC calculation
 * 
 * @param addr 
 * @param len 
 * @return crc result 
 */
uint8_t DS18B20_Crc(uint8_t *addr, uint8_t len);

/**
 * @brief Read SRAM scratchpad
 * @param buf a 9-byte buffer, Byte 8 contains the CRC code for bytes 0 through 7
 */
void DS18B20_ReadScratchpad(uint8_t *buf);

/**
 * @brief Start conversion on all slaves
 */
void DS18B20_StartAll(void);

/**
 * @brief If read bit is low, then device is not finished yet with calculation temperature
 * @return bit value
 */
__BIT DS18B20_AllDone(void);

/**
 * @brief Read 64-bit ROM: 8-bit family code "0x28", unique 48-bit serial number, 8-bit CRC
 * @note  This command can only be used if there is a single DS18B20 on the bus. 
 *        If multiple slaves are present, a data collision will occur(a wired AND result).
 * @param buf a 8-byte buffer
 */
void DS18B20_ReadRom(uint8_t *buf);

/**
 * @brief Select a slave on the bus
 * @note  Only the slave that exactly matches the 64-bit ROM code sequence will respond to 
 *        the function command issued by the master; all other slaves on the bus will wait 
 *        for a reset pulse.
 * @param addr 64-bit ROM code
 */
void DS18B20_Select(const uint8_t* addr);

/**
 * @brief Start conversion on selected slave
 * @param addr 64-bit ROM code
 */
void DS18B20_Start(const uint8_t *addr);

/**
 * @brief Read SRAM scratchpad from selected slave
 * 
 * @param addr 64-bit ROM code
 * @param buf a 9-byte buffer, Byte 8 contains the CRC code for bytes 0 through 7
 */
void DS18B20_ReadScratchpadFromAddr(const uint8_t *addr, uint8_t *buf);

/**
 * @brief Perform one ROM search 
 * @param buff 8-byte array for ROM bytes
 * @param stack 8-byte array for search stack
 * @param split_point deepest split point of last search
 * @return new split point
 */
uint8_t DS18B20_Search(uint8_t *buff, uint8_t *stack, uint8_t split_point);

#endif // __DS18B20_H_
