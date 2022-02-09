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

#ifndef ___FW_USB_H___
#define ___FW_USB_H___

#include "fw_conf.h"
#include "fw_types.h"

/**
 * STC8H8K64U USB SFR
*/

#define FADDR           0x00
#define POWER           0x01
#define INTRIN1         0x02
#define  EP5INIF         0x20
#define  EP4INIF         0x10
#define  EP3INIF         0x08
#define  EP2INIF         0x04
#define  EP1INIF         0x02
#define  EP0IF           0x01
#define INTROUT1        0x04
#define  EP5OUTIF        0x20
#define  EP4OUTIF        0x10
#define  EP3OUTIF        0x08
#define  EP2OUTIF        0x04
#define  EP1OUTIF        0x02
#define INTRUSB         0x06
#define  SOFIF           0x08
#define  RSTIF           0x04
#define  RSUIF           0x02
#define  SUSIF           0x01
#define INTRIN1E        0x07
#define  EP5INIE         0x20
#define  EP4INIE         0x10
#define  EP3INIE         0x08
#define  EP2INIE         0x04
#define  EP1INIE         0x02
#define  EP0IE           0x01
#define INTROUT1E       0x09
#define  EP5OUTIE        0x20
#define  EP4OUTIE        0x10
#define  EP3OUTIE        0x08
#define  EP2OUTIE        0x04
#define  EP1OUTIE        0x02
#define INTRUSBE        0x0B
#define  SOFIE           0x08
#define  RSTIE           0x04
#define  RSUIE           0x02
#define  SUSIE           0x01
#define FRAME1          0x0C
#define FRAME2          0x0D
#define INDEX           0x0E
#define INMAXP          0x10
#define CSR0            0x11
#define  SSUEND          0x80 // Serviced Setup End
#define  SOPRDY          0x40 // Serviced OPRDY(Out Packet Ready)
#define  SDSTL           0x20 // Send Stall
#define  SUEND           0x10 // Setup End
#define  DATEND          0x08 // Data End
#define  STSTL           0x04 // Sent Stall
#define  IPRDY           0x02 // In Packet Ready
#define  OPRDY           0x01 // Out Packet Ready
#define INCSR1          0x11
#define  INCLRDT         0x40
#define  INSTSTL         0x20
#define  INSDSTL         0x10
#define  INFLUSH         0x08
#define  INUNDRUN        0x04
#define  INFIFONE        0x02
#define  INIPRDY         0x01
#define INCSR2          0x12
#define  INAUTOSET       0x80
#define  INISO           0x40
#define  INMODEIN        0x20
#define  INMODEOUT       0x00
#define  INENDMA         0x10
#define  INFCDT          0x08
#define OUTMAXP         0x13
#define OUTCSR1         0x14
#define  OUTCLRDT        0x80
#define  OUTSTSTL        0x40
#define  OUTSDSTL        0x20
#define  OUTFLUSH        0x10
#define  OUTDATERR       0x08
#define  OUTOVRRUN       0x04
#define  OUTFIFOFUL      0x02
#define  OUTOPRDY        0x01
#define OUTCSR2         0x15
#define  OUTAUTOCLR      0x80
#define  OUTISO          0x40
#define  OUTENDMA        0x20
#define  OUTDMAMD        0x10
#define COUNT0          0x16
#define OUTCOUNT1       0x16
#define OUTCOUNT2       0x17
#define FIFO0           0x20
#define FIFO1           0x21
#define FIFO2           0x22
#define FIFO3           0x23
#define FIFO4           0x24
#define FIFO5           0x25
#define UTRKCTL         0x30
#define UTRKSTS         0x31

typedef enum _CONTROL_STATE
{
    USB_CtrlState_Idle      = 0x00,
    USB_CtrlState_SettingUp = 0x01,
    USB_CtrlState_DataIn    = 0x02,
    USB_CtrlState_DataOut   = 0x03,
    USB_CtrlState_Stalled   = 0x04,
} USB_CtrlState_t;  /* The state machine states of a control pipe */

typedef enum
{
    USB_StdReq_GetStatus        = 0x00,
    USB_StdReq_ClearFeature     = 0x01,
    USB_StdReq_SetFeature       = 0x03,
    USB_StdReq_SetAddress       = 0x05,
    USB_StdReq_GetDescriptor    = 0x06,
    USB_StdReq_SetDescriptor    = 0x07,
    USB_StdReq_GetConfiguration = 0x08,
    USB_StdReq_SetConfiguration = 0x09,
    USB_StdReq_GetInterface     = 0x0A,
    USB_StdReq_SetInterface     = 0x0B,
    USB_StdReq_SynchFrame       = 0x0C,
} USB_StdReq_t;

typedef enum
{
    USB_HidReq_GetReport        = 0x01,
    USB_HidReq_GetIdle          = 0x02,
    USB_HidReq_GetProtocol      = 0x03,
    USB_HidReq_SetReport        = 0x09,
    USB_HidReq_SetIdle          = 0x0A,
    USB_HidReq_SetProtocol      = 0x0B,
} USB_HidReq_t;

typedef enum
{
    USB_DescriptorType_Device           = 0x01,
    USB_DescriptorType_Configuration    = 0x02,
    USB_DescriptorType_String           = 0x03,
    USB_DescriptorType_Interface        = 0x04,
    USB_DescriptorType_Endpoint         = 0x05,
    USB_DescriptorType_HID              = 0x21,
    USB_DescriptorType_Report           = 0x22,
    USB_DescriptorType_Physical         = 0x23,
} USB_DescriptorType_t;

#define REQUEST_TYPE_MASK   0x60

typedef enum
{
    USB_RequestType_Standard    = 0x00,
    USB_RequestType_Class       = 0x20,
    USB_RequestType_Vendor      = 0x40,
} USB_RequestType_t;

typedef enum
{
    USB_ClockSource_6M      = 0x00,
    USB_ClockSource_12M     = 0x01, // default value
    USB_ClockSource_24M     = 0x02,
    USB_ClockSource_IRCDiv2 = 0x03,
} USB_ClockSource_t;

typedef enum
{
    USB_PHYTest_Method_Normal      = 0x00,
    USB_PHYTest_Method_Force1      = 0x01,
    USB_PHYTest_Method_Force0      = 0x02,
    USB_PHYTest_Method_ForceOneEnd0 = 0x03,
} USB_PHYTest_Method_t;

#define USB_SetClockPPL(__STATE__)          SFR_ASSIGN(USBCLK, 7, __STATE__)
#define USB_SetClockSource(__SOURCE__)      SFR_ASSIGN2BIT(USBCLK, 5, __SOURCE__)
#define USB_SetClockCRE(__STATE__)          SFR_ASSIGN(USBCLK, 4, __STATE__)
#define USB_SetUSBTestMode(__STATE__)       SFR_ASSIGN(USBCLK, 3, __STATE__)
#define USB_SetPHYTestMode(__STATE__)       SFR_ASSIGN(USBCLK, 2, __STATE__)
#define USB_SetPHYTestMethod(__TEST_METHOD__) SFR_ASSIGN2BIT(USBCLK, 0, __TEST_METHOD__)

#define USB_SetEnabled(__STATE__)           SFR_ASSIGN(USBCON, 7, __STATE__)
#define USB_TurnOnReset()                   SFR_SET(USBCON, 6)
#define USB_TurnOffReset()                  SFR_RESET(USBCON, 6)
#define USB_SetPS2Mode(__STATE__)           SFR_ASSIGN(USBCON, 5, __STATE__)
/**
 * Enable/Disable 1.5KR pull up resistance on D+ and D-
*/
#define USB_SetDpDmPullUp(__STATE__)        SFR_ASSIGN(USBCON, 4, __STATE__)
/**
 * Enable/Disable 500KR pull down resistance on D+ and D-
*/
#define USB_SetDpDmPullDown(__STATE__)      SFR_ASSIGN(USBCON, 3, __STATE__)
#define USB_GetDiffRecvMode()               (USBCON & 0x04)
/**
 * Read D+ level
*/
#define USB_GetDp()                         (USBCON & 0x02)
/**
 * Write D+ level, writable when PS2 mode is 1
*/
#define USB_SetDp(__STATE__)                SFR_ASSIGN(USBCON, 1, __STATE__)
/**
 * Read D- level
*/
#define USB_GetDm()                         (USBCON & 0x01)
/**
 * Write D- level, writable when PS2 mode is 1
*/
#define USB_SetDm(__STATE__)                SFR_ASSIGN(USBCON, 0, __STATE__)

#define USB_IsBusy()                        (USBADR & 0x80)
#define USB_SetAddrForRead(__ADDR__)        (USBADR = (__ADDR__) | 0x80)
#define USB_SetAddrForWrite(__ADDR__)       (USBADR = (__ADDR__) & 0x7F)

#define USB_SelectEndPoint(__INDEX__)       USB_WriteReg(INDEX, __INDEX__)


typedef union
{
  uint16_t w;
  struct _bb
  {
    uint8_t bl;
    uint8_t bh;
  } bb;
} uint16_2uint8_t;

typedef struct
{
    uint8_t bmRequestType;
    uint8_t bRequest;
    uint16_2uint8_t wValue;
    uint16_2uint8_t wIndex;
    uint16_2uint8_t wLength;
} USB_Request_t;

typedef struct
{
    uint8_t bStage;
    uint16_t wResidue;
    uint8_t *pData;
} USB_EP0_Stage_t;


uint8_t USB_ReadReg(uint8_t addr);
void USB_WriteReg(uint8_t addr, uint8_t dat);
uint8_t USB_ReadFIFO(uint8_t fifo, uint8_t *pdat);
void USB_WriteFIFO(uint8_t fifo, uint8_t *pdat, uint8_t cnt);

#endif
