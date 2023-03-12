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

#ifndef __FW_REG_BASE_H__
#define __FW_REG_BASE_H__

#if defined (__SDCC_SYNTAX_FIX)
    #include <stdbool.h>
    #include <lint.h>
    # warning unrecognized compiler
    #define __BIT   bool
    #define __DATA
    #define __IDATA
    #define __PDATA 
    #define __XDATA 
    #define __CODE 
    #define __REENTRANT  
    #define SBIT(name, addr, bit)    volatile bool           name
    #define SFR(name, addr)          volatile unsigned char  name
    #define SFRX(addr)               (*(unsigned char volatile *)(addr))
    #define SFR16X(addr)             (*(unsigned char volatile *)(addr))
    #define INTERRUPT(name, vector)  void name (void) 
    #define INTERRUPT_USING(name, vector, regnum) void name (void)
    #define NOP() 

#elif defined (SDCC) || defined (__SDCC)
    #define __BIT   __bit
    #define __DATA  __data
    #define __IDATA __idata
    #define __PDATA __pdata
    #define __XDATA __xdata
    #define __CODE  __code
    #define __REENTRANT  __reentrant
    #define SBIT(name, addr, bit)  __sbit  __at(addr+bit)                    name
    #define SFR(name, addr)        __sfr   __at(addr)                        name
    #define SFRX(addr)              (*(unsigned char volatile __xdata *)(addr))
    #define SFR16X(addr)            (*(unsigned int  volatile __xdata *)(addr))

    #define INTERRUPT(name, vector) void name (void) __interrupt (vector)
    #define INTERRUPT_USING(name, vector, regnum) void name (void) __interrupt (vector) __using (regnum)
    #define NOP() __asm NOP __endasm

#elif defined __CX51__ || defined __C51__
    #define __BIT   bit
    #define __DATA  data
    #define __IDATA idata
    #define __PDATA pdata
    #define __XDATA xdata
    #define __CODE  code
    #define __REENTRANT  reentrant
    #define SBIT(name, addr, bit)  sbit  name = addr^bit
    #define SFR(name, addr)        sfr   name = addr
    #define SFRX(addr)              (*(unsigned char volatile xdata *)(addr))
    #define SFR16X(addr)            (*(unsigned int  volatile xdata *)(addr))

    #define INTERRUPT(name, vector) void name (void) interrupt vector
    #define INTERRUPT_USING(name, vector, regnum) void name (void) interrupt vector using regnum
    extern void _nop_ (void);
    #define NOP() _nop_()

#endif

#define  _P0            0x80
SFR(P0,                 _P0);
SBIT(P00,               _P0, 0);
SBIT(P01,               _P0, 1);
SBIT(P02,               _P0, 2);
SBIT(P03,               _P0, 3);
SBIT(P04,               _P0, 4);
SBIT(P05,               _P0, 5);
SBIT(P06,               _P0, 6);
SBIT(P07,               _P0, 7);
SFR(SP,                 0x81);
SFR(DPL,                0x82);
SFR(DPH,                0x83);
SFR(S4CON,              0x84);
SFR(S4BUF,              0x85);
SFR(PCON,               0x87);

#define  _TCON          0x88
SFR(TCON,               _TCON);
SBIT(TF1,               _TCON, 7);
SBIT(TR1,               _TCON, 6);
SBIT(TF0,               _TCON, 5);
SBIT(TR0,               _TCON, 4);
SBIT(IE1,               _TCON, 3);
SBIT(IT1,               _TCON, 2);
SBIT(IE0,               _TCON, 1);
SBIT(IT0,               _TCON, 0);
SFR(TMOD,               0x89);

SFR(TL0,                0x8A);
SFR(TL1,                0x8B);
SFR(TH0,                0x8C);
SFR(TH1,                0x8D);
SFR(AUXR,               0x8E);
SFR(INTCLKO,            0x8F);

#define  _P1            0x90
SFR(P1,                 _P1);
SBIT(P10,               _P1, 0);
SBIT(P11,               _P1, 1);
SBIT(P12,               _P1, 2);
SBIT(P13,               _P1, 3);
SBIT(P14,               _P1, 4);
SBIT(P15,               _P1, 5);
SBIT(P16,               _P1, 6);
SBIT(P17,               _P1, 7);
SFR(P1M1,               0x91);
SFR(P1M0,               0x92);
SFR(P0M1,               0x93);
SFR(P0M0,               0x94);
SFR(P2M1,               0x95);
SFR(P2M0,               0x96);

#define  _SCON          0x98
SFR(SCON,               _SCON);
SBIT(SM0,               _SCON, 7);
SBIT(SM1,               _SCON, 6);
SBIT(SM2,               _SCON, 5);
SBIT(REN,               _SCON, 4);
SBIT(TB8,               _SCON, 3);
SBIT(RB8,               _SCON, 2);
SBIT(TI,                _SCON, 1);
SBIT(RI,                _SCON, 0);
SFR(SBUF,               0x99);
SFR(S2CON,              0x9A);
SFR(S2BUF,              0x9B);
SFR(IRCBAND,            0x9D);
SFR(LIRTRIM,            0x9E);
SFR(IRTRIM,             0x9F);

#define  _P2            0xA0
SFR(P2,                 _P2);
SBIT(P20,               _P2, 0);
SBIT(P21,               _P2, 1);
SBIT(P22,               _P2, 2);
SBIT(P23,               _P2, 3);
SBIT(P24,               _P2, 4);
SBIT(P25,               _P2, 5);
SBIT(P26,               _P2, 6);
SBIT(P27,               _P2, 7);
SFR(BUS_SPEED,          0xA1);
SFR(P_SW1,              0xA2);

#define  _IE            0xA8
SFR(IE,                 _IE);
SBIT(EA,                _IE, 7);
SBIT(ELVD,              _IE, 6);
SBIT(EADC,              _IE, 5);
SBIT(ES,                _IE, 4);
SBIT(ET1,               _IE, 3);
SBIT(EX1,               _IE, 2);
SBIT(ET0,               _IE, 1);
SBIT(EX0,               _IE, 0);
SFR(SADDR,              0xA9);
SFR(WKTCL,              0xAA);
SFR(WKTCH,              0xAB);
SFR(S3CON,              0xAC);
SFR(S3BUF,              0xAD);
SFR(TA,                 0xAE);
SFR(IE2,                0xAF);

#define  _P3            0xB0
SFR(P3,                 _P3);
SBIT(P30,               _P3, 0);
SBIT(P31,               _P3, 1);
SBIT(P32,               _P3, 2);
SBIT(P33,               _P3, 3);
SBIT(P34,               _P3, 4);
SBIT(P35,               _P3, 5);
SBIT(P36,               _P3, 6);
SBIT(P37,               _P3, 7);
SFR(P3M1,               0xB1);
SFR(P3M0,               0xB2);
SFR(P4M1,               0xB3);
SFR(P4M0,               0xB4);
SFR(IP2,                0xB5);
SFR(IP2H,               0xB6);
SFR(IPH,                0xB7);

#define  _IP            0xB8
SFR(IP,                 _IP);
SBIT(PPCA,              _IP, 7);
SBIT(PLVD,              _IP, 6);
SBIT(PADC,              _IP, 5);
SBIT(PS,                _IP, 4);
SBIT(PT1,               _IP, 3);
SBIT(PX1,               _IP, 2);
SBIT(PT0,               _IP, 1);
SBIT(PX0,               _IP, 0);
SFR(SADEN,              0xB9);
SFR(P_SW2,              0xBA);
SFR(ADC_CONTR,          0xBC);
SFR(ADC_RES,            0xBD);
SFR(ADC_RESL,           0xBE);

#define  _P4            0xC0
SFR(P4,                 _P4);
SBIT(P40,               _P4, 0);
SBIT(P41,               _P4, 1);
SBIT(P42,               _P4, 2);
SBIT(P43,               _P4, 3);
SBIT(P44,               _P4, 4);
SBIT(P45,               _P4, 5);
SBIT(P46,               _P4, 6);
SBIT(P47,               _P4, 7);
SFR(WDT_CONTR,          0xC1);
SFR(IAP_DATA,           0xC2);
SFR(IAP_ADDRH,          0xC3);
SFR(IAP_ADDRL,          0xC4);
SFR(IAP_CMD,            0xC5);
SFR(IAP_TRIG,           0xC6);
SFR(IAP_CONTR,          0xC7);

#define  _P5            0xC8
SFR(P5,                 _P5);
SBIT(P50,               _P5, 0);
SBIT(P51,               _P5, 1);
SBIT(P52,               _P5, 2);
SBIT(P53,               _P5, 3);
SBIT(P54,               _P5, 4);
SBIT(P55,               _P5, 5);
SBIT(P56,               _P5, 6);
SBIT(P57,               _P5, 7);
SFR(P5M1,               0xC9);
SFR(P5M0,               0xCA);
SFR(P6M1,               0xCB);
SFR(P6M0,               0xCC);
SFR(SPSTAT,             0xCD);
SFR(SPCTL,              0xCE);
SFR(SPDAT,              0xCF);

#define  _PSW           0xD0
SFR(PSW,                _PSW);
SBIT(CY,                _PSW, 7);
SBIT(AC,                _PSW, 6);
SBIT(F0,                _PSW, 5);
SBIT(RS1,               _PSW, 4);
SBIT(RS0,               _PSW, 3);
SBIT(OV,                _PSW, 2);
SBIT(F1,                _PSW, 1);
SBIT(P,                 _PSW, 0);
SFR(T4T3M,              0xD1);
SFR(T4H,                0xD2);
SFR(T4L,                0xD3);
SFR(T3H,                0xD4);
SFR(T3L,                0xD5);
SFR(T2H,                0xD6);
SFR(T2L,                0xD7);

SFR(ACC,                0xE0);

#define  _P6            0xE8
SFR(P6,                 _P6);
SBIT(P60,               _P6, 0);
SBIT(P61,               _P6, 1);
SBIT(P62,               _P6, 2);
SBIT(P63,               _P6, 3);
SBIT(P64,               _P6, 4);
SBIT(P65,               _P6, 5);
SBIT(P66,               _P6, 6);
SBIT(P67,               _P6, 7);

SFR(B,                  0xF0);

#define  _P7            0xF8
SFR(P7,                 _P7);
SBIT(P70,               _P7, 0);
SBIT(P71,               _P7, 1);
SBIT(P72,               _P7, 2);
SBIT(P73,               _P7, 3);
SBIT(P74,               _P7, 4);
SBIT(P75,               _P7, 5);
SBIT(P76,               _P7, 6);
SBIT(P77,               _P7, 7);

#endif
