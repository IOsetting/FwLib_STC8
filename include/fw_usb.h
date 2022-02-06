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
 * STC8H8K64U(LQFP48)   (LQFP64)
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
#define  SSUEND          0x80
#define  SOPRDY          0x40
#define  SDSTL           0x20
#define  SUEND           0x10
#define  DATEND          0x08
#define  STSTL           0x04
#define  IPRDY           0x02
#define  OPRDY           0x01
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

#define EPIDLE          0
#define EPSTATUS        1
#define EPDATAIN        2
#define EPDATAOUT       3
#define EPSTALL         -1

#define GET_STATUS      0x00
#define CLEAR_FEATURE   0x01
#define SET_FEATURE     0x03
#define SET_ADDRESS     0x05
#define GET_DESCRIPTOR  0x06
#define SET_DESCRIPTOR  0x07
#define GET_CONFIG      0x08
#define SET_CONFIG      0x09
#define GET_INTERFACE   0x0A
#define SET_INTERFACE   0x0B
#define SYNCH_FRAME     0x0C
#define GET_REPORT      0x01
#define GET_IDLE        0x02
#define GET_PROTOCOL    0x03
#define SET_REPORT      0x09
#define SET_IDLE        0x0A
#define SET_PROTOCOL    0x0B
#define DESC_DEVICE     0x01
#define DESC_CONFIG     0x02
#define DESC_STRING     0x03
#define DESC_HIDREPORT  0x22
#define STANDARD_REQUEST 0x00
#define CLASS_REQUEST   0x20
#define VENDOR_REQUEST  0x40
#define REQUEST_MASK    0x60

typedef struct
{
    uint8_t bmRequestType;
    uint8_t bRequest;
    uint8_t wValueL;
    uint8_t wValueH;
    uint8_t wIndexL;
    uint8_t wIndexH;
    uint8_t wLengthL;
    uint8_t wLengthH;
} SETUP;

typedef struct
{
    uint8_t bStage;
    uint16_t wResidue;
    uint8_t *pData;
} EP0STAGE;


uint8_t USB_ReadReg(uint8_t addr);
void USB_WriteReg(uint8_t addr, uint8_t dat);
uint8_t USB_ReadFIFO(uint8_t fifo, uint8_t *pdat);
void USB_WriteFIFO(uint8_t fifo, uint8_t *pdat, uint8_t cnt);

#endif
