#ifndef __FW_REG_STC8G_H__
#define __FW_REG_STC8G_H__

#include "fw_reg_base.h"

SFR(VRTRIM,             0xA6);

#define  _CCON          0xD8
SFR(CCON,               _CCON);
SBIT(CF,                _CCON, 7);
SBIT(CR,                _CCON, 6);
SBIT(CCF3,              _CCON, 3);
SBIT(CCF2,              _CCON, 2);
SBIT(CCF1,              _CCON, 1);
SBIT(CCF0,              _CCON, 0);
SFR(CMOD,               0xD9);
SFR(CCAPM0,             0xDA);
SFR(CCAPM1,             0xDB);
SFR(CCAPM2,             0xDC);
SFR(ADCCFG,             0xDE);
SFR(IP3,                0xDF);

SFR(P7M1,               0xE1);
SFR(P7M0,               0xE2);
SFR(DPS,                0xE3);
SFR(DPL1,               0xE4);
SFR(DPH1,               0xE5);
SFR(CMPCR1,             0xE6);
SFR(CMPCR2,             0xE7);

SFR(CL,                 0xE9);
SFR(CCAP0L,             0xEA);
SFR(CCAP1L,             0xEB);
SFR(CCAP2L,             0xEC);
SFR(IP3H,               0xEE);
SFR(AUXINTIF,           0xEF);

SFR(PWMSET,             0xF1);
SFR(PCA_PWM0,           0xF2);
SFR(PCA_PWM1,           0xF3);
SFR(PCA_PWM2,           0xF4);
SFR(IAP_TPS,            0xF5);
SFR(PWMCFG01,           0xF6);
SFR(PWMCFG23,           0xF7);

SFR(CH,                 0xF9);
SFR(CCAP0H,             0xFA);
SFR(CCAP1H,             0xFB);
SFR(CCAP2H,             0xFC);
SFR(PWMCFG45,           0xFE);
SFR(RSTCFG,             0xFF);

/**
 * Set B7 of P_SW2 before read/write the following registers
*/

/////////////////////////////////////////////////
//FF00H-FFFFH
/////////////////////////////////////////////////


#define     PWM0CH      (*(unsigned char volatile __XDATA *)0xff00)
#define     PWM0CL      (*(unsigned char volatile __XDATA *)0xff01)
#define     PWM0CKS     (*(unsigned char volatile __XDATA *)0xff02)

#define     PWM0TADCH   (*(unsigned char volatile __XDATA *)0xff03)
#define     PWM0TADCL   (*(unsigned char volatile __XDATA *)0xff04)
#define     PWM0IF      (*(unsigned char volatile __XDATA *)0xff05)
#define     PWM0FDCR    (*(unsigned char volatile __XDATA *)0xff06)

#define     PWM00T1L    (*(unsigned char volatile __XDATA *)0xff11)

#define     PWM00T2H    (*(unsigned char volatile __XDATA *)0xff12)
#define     PWM00T2L    (*(unsigned char volatile __XDATA *)0xff13)
#define     PWM00CR     (*(unsigned char volatile __XDATA *)0xff14)
#define     PWM00HLD    (*(unsigned char volatile __XDATA *)0xff15)

#define     PWM01T1H    (*(unsigned char volatile __XDATA *)0xff18)
#define     PWM01T1L    (*(unsigned char volatile __XDATA *)0xff19)

#define     PWM01T2H    (*(unsigned char volatile __XDATA *)0xff1a)
#define     PWM01T2L    (*(unsigned char volatile __XDATA *)0xff1b)
#define     PWM01CR     (*(unsigned char volatile __XDATA *)0xff1c)
#define     PWM01HLD    (*(unsigned char volatile __XDATA *)0xff1d)

#define     PWM02T1H    (*(unsigned char volatile __XDATA *)0xff20)
#define     PWM02T1L    (*(unsigned char volatile __XDATA *)0xff21)

#define     PWM02T2H    (*(unsigned char volatile __XDATA *)0xff22)
#define     PWM02T2L    (*(unsigned char volatile __XDATA *)0xff23)
#define     PWM02CR     (*(unsigned char volatile __XDATA *)0xff24)
#define     PWM02HLD    (*(unsigned char volatile __XDATA *)0xff25)

#define     PWM03T1H    (*(unsigned char volatile __XDATA *)0xff28)
#define     PWM03T1L    (*(unsigned char volatile __XDATA *)0xff29)

#define     PWM03T2H    (*(unsigned char volatile __XDATA *)0xff2a)
#define     PWM03T2L    (*(unsigned char volatile __XDATA *)0xff2b)
#define     PWM03CR     (*(unsigned char volatile __XDATA *)0xff2c)
#define     PWM03HLD    (*(unsigned char volatile __XDATA *)0xff2d)

#define     PWM04T1H    (*(unsigned char volatile __XDATA *)0xff30)
#define     PWM04T1L    (*(unsigned char volatile __XDATA *)0xff31)

#define     PWM04T2H    (*(unsigned char volatile __XDATA *)0xff32)
#define     PWM04T2L    (*(unsigned char volatile __XDATA *)0xff33)
#define     PWM04CR     (*(unsigned char volatile __XDATA *)0xff34)
#define     PWM04HLD    (*(unsigned char volatile __XDATA *)0xff35)

#define     PWM05T1H    (*(unsigned char volatile __XDATA *)0xff38)
#define     PWM05T1L    (*(unsigned char volatile __XDATA *)0xff39)

#define     PWM05T2H    (*(unsigned char volatile __XDATA *)0xff3a)
#define     PWM05T2L    (*(unsigned char volatile __XDATA *)0xff3b)
#define     PWM05CR     (*(unsigned char volatile __XDATA *)0xff3c)
#define     PWM05HLD    (*(unsigned char volatile __XDATA *)0xff3d)

#define     PWM06T1H    (*(unsigned char volatile __XDATA *)0xff40)
#define     PWM06T1L    (*(unsigned char volatile __XDATA *)0xff41)

#define     PWM06T2H    (*(unsigned char volatile __XDATA *)0xff42)
#define     PWM06T2L    (*(unsigned char volatile __XDATA *)0xff43)
#define     PWM06CR     (*(unsigned char volatile __XDATA *)0xff44)
#define     PWM06HLD    (*(unsigned char volatile __XDATA *)0xff45)

#define     PWM07T1H    (*(unsigned char volatile __XDATA *)0xff48)
#define     PWM07T1L    (*(unsigned char volatile __XDATA *)0xff49)

#define     PWM07T2H    (*(unsigned char volatile __XDATA *)0xff4a)
#define     PWM07T2L    (*(unsigned char volatile __XDATA *)0xff4b)
#define     PWM07CR     (*(unsigned char volatile __XDATA *)0xff4c)
#define     PWM07HLD    (*(unsigned char volatile __XDATA *)0xff4d)

#define     PWM1CH      (*(unsigned char volatile __XDATA *)0xff50)
#define     PWM1CL      (*(unsigned char volatile __XDATA *)0xff51)
#define     PWM1CKS     (*(unsigned char volatile __XDATA *)0xff52)
#define     PWM1IF      (*(unsigned char volatile __XDATA *)0xff55)
#define     PWM1FDCR    (*(unsigned char volatile __XDATA *)0xff56)

#define     PWM10T1H    (*(unsigned char volatile __XDATA *)0xff60)
#define     PWM10T1L    (*(unsigned char volatile __XDATA *)0xff61)

#define     PWM10T2H    (*(unsigned char volatile __XDATA *)0xff62)
#define     PWM10T2L    (*(unsigned char volatile __XDATA *)0xff63)
#define     PWM10CR     (*(unsigned char volatile __XDATA *)0xff64)
#define     PWM10HLD    (*(unsigned char volatile __XDATA *)0xff65)

#define     PWM11T1H    (*(unsigned char volatile __XDATA *)0xff68)
#define     PWM11T1L    (*(unsigned char volatile __XDATA *)0xff69)

#define     PWM11T2H    (*(unsigned char volatile __XDATA *)0xff6a)
#define     PWM11T2L    (*(unsigned char volatile __XDATA *)0xff6b)
#define     PWM11CR     (*(unsigned char volatile __XDATA *)0xff6c)
#define     PWM11HLD    (*(unsigned char volatile __XDATA *)0xff6d)

#define     PWM12T1H    (*(unsigned char volatile __XDATA *)0xff70)
#define     PWM12T1L    (*(unsigned char volatile __XDATA *)0xff71)

#define     PWM12T2H    (*(unsigned char volatile __XDATA *)0xff72)
#define     PWM12T2L    (*(unsigned char volatile __XDATA *)0xff73)
#define     PWM12CR     (*(unsigned char volatile __XDATA *)0xff74)
#define     PWM12HLD    (*(unsigned char volatile __XDATA *)0xff75)

#define     PWM13T1H    (*(unsigned char volatile __XDATA *)0xff78)
#define     PWM13T1L    (*(unsigned char volatile __XDATA *)0xff79)

#define     PWM13T2H    (*(unsigned char volatile __XDATA *)0xff7a)
#define     PWM13T2L    (*(unsigned char volatile __XDATA *)0xff7b)
#define     PWM13CR     (*(unsigned char volatile __XDATA *)0xff7c)
#define     PWM13HLD    (*(unsigned char volatile __XDATA *)0xff7d)

#define     PWM14T1H    (*(unsigned char volatile __XDATA *)0xff80)
#define     PWM14T1L    (*(unsigned char volatile __XDATA *)0xff81)

#define     PWM14T2H    (*(unsigned char volatile __XDATA *)0xff82)
#define     PWM14T2L    (*(unsigned char volatile __XDATA *)0xff83)
#define     PWM14CR     (*(unsigned char volatile __XDATA *)0xff84)
#define     PWM14HLD    (*(unsigned char volatile __XDATA *)0xff85)

#define     PWM15T1H    (*(unsigned char volatile __XDATA *)0xff88)
#define     PWM15T1L    (*(unsigned char volatile __XDATA *)0xff89)

#define     PWM15T2H    (*(unsigned char volatile __XDATA *)0xff8a)
#define     PWM15T2L    (*(unsigned char volatile __XDATA *)0xff8b)
#define     PWM15CR     (*(unsigned char volatile __XDATA *)0xff8c)
#define     PWM15HLD    (*(unsigned char volatile __XDATA *)0xff8d)

#define     PWM16T1H    (*(unsigned char volatile __XDATA *)0xff90)
#define     PWM16T1L    (*(unsigned char volatile __XDATA *)0xff91)

#define     PWM16T2H    (*(unsigned char volatile __XDATA *)0xff92)
#define     PWM16T2L    (*(unsigned char volatile __XDATA *)0xff93)
#define     PWM16CR     (*(unsigned char volatile __XDATA *)0xff94)
#define     PWM16HLD    (*(unsigned char volatile __XDATA *)0xff95)

#define     PWM17T1H    (*(unsigned char volatile __XDATA *)0xff98)
#define     PWM17T1L    (*(unsigned char volatile __XDATA *)0xff99)

#define     PWM17T2H    (*(unsigned char volatile __XDATA *)0xff9a)
#define     PWM17T2L    (*(unsigned char volatile __XDATA *)0xff9b)
#define     PWM17CR     (*(unsigned char volatile __XDATA *)0xff9c)
#define     PWM17HLD    (*(unsigned char volatile __XDATA *)0xff9d)

#define     PWM2CH      (*(unsigned char volatile __XDATA *)0xffa0)
#define     PWM2CL      (*(unsigned char volatile __XDATA *)0xffa1)
#define     PWM2CKS     (*(unsigned char volatile __XDATA *)0xffa2)

#define     PWM2TADCH   (*(unsigned char volatile __XDATA *)0xffa3)
#define     PWM2TADCL   (*(unsigned char volatile __XDATA *)0xffa4)
#define     PWM2IF      (*(unsigned char volatile __XDATA *)0xffa5)
#define     PWM2FDCR    (*(unsigned char volatile __XDATA *)0xffa6)

#define     PWM20T1H    (*(unsigned char volatile __XDATA *)0xffb0)
#define     PWM20T1L    (*(unsigned char volatile __XDATA *)0xffb1)

#define     PWM20T2H    (*(unsigned char volatile __XDATA *)0xffb2)
#define     PWM20T2L    (*(unsigned char volatile __XDATA *)0xffb3)
#define     PWM20CR     (*(unsigned char volatile __XDATA *)0xffb4)
#define     PWM20HLD    (*(unsigned char volatile __XDATA *)0xffb5)

#define     PWM21T1H    (*(unsigned char volatile __XDATA *)0xffb8)
#define     PWM21T1L    (*(unsigned char volatile __XDATA *)0xffb9)

#define     PWM21T2H    (*(unsigned char volatile __XDATA *)0xffba)
#define     PWM21T2L    (*(unsigned char volatile __XDATA *)0xffbb)
#define     PWM21CR     (*(unsigned char volatile __XDATA *)0xffbc)
#define     PWM21HLD    (*(unsigned char volatile __XDATA *)0xffbd)

#define     PWM22T1H    (*(unsigned char volatile __XDATA *)0xffc0)
#define     PWM22T1L    (*(unsigned char volatile __XDATA *)0xffc1)

#define     PWM22T2H    (*(unsigned char volatile __XDATA *)0xffc2)
#define     PWM22T2L    (*(unsigned char volatile __XDATA *)0xffc3)
#define     PWM22CR     (*(unsigned char volatile __XDATA *)0xffc4)
#define     PWM22HLD    (*(unsigned char volatile __XDATA *)0xffc5)

#define     PWM23T1H    (*(unsigned char volatile __XDATA *)0xffc8)
#define     PWM23T1L    (*(unsigned char volatile __XDATA *)0xffc9)

#define     PWM23T2H    (*(unsigned char volatile __XDATA *)0xffca)
#define     PWM23T2L    (*(unsigned char volatile __XDATA *)0xffcb)
#define     PWM23CR     (*(unsigned char volatile __XDATA *)0xffcc)
#define     PWM23HLD    (*(unsigned char volatile __XDATA *)0xffcd)

#define     PWM24T1H    (*(unsigned char volatile __XDATA *)0xffd0)
#define     PWM24T1L    (*(unsigned char volatile __XDATA *)0xffd1)

#define     PWM24T2H    (*(unsigned char volatile __XDATA *)0xffd2)
#define     PWM24T2L    (*(unsigned char volatile __XDATA *)0xffd3)
#define     PWM24CR     (*(unsigned char volatile __XDATA *)0xffd4)
#define     PWM24HLD    (*(unsigned char volatile __XDATA *)0xffd5)

#define     PWM25T1H    (*(unsigned char volatile __XDATA *)0xffd8)
#define     PWM25T1L    (*(unsigned char volatile __XDATA *)0xffd9)

#define     PWM25T2H    (*(unsigned char volatile __XDATA *)0xffda)
#define     PWM25T2L    (*(unsigned char volatile __XDATA *)0xffdb)
#define     PWM25CR     (*(unsigned char volatile __XDATA *)0xffdc)
#define     PWM25HLD    (*(unsigned char volatile __XDATA *)0xffdd)

#define     PWM26T1H    (*(unsigned char volatile __XDATA *)0xffe0)
#define     PWM26T1L    (*(unsigned char volatile __XDATA *)0xffe1)

#define     PWM26T2H    (*(unsigned char volatile __XDATA *)0xffe2)
#define     PWM26T2L    (*(unsigned char volatile __XDATA *)0xffe3)
#define     PWM26CR     (*(unsigned char volatile __XDATA *)0xffe4)
#define     PWM26HLD    (*(unsigned char volatile __XDATA *)0xffe5)

#define     PWM27T1H    (*(unsigned char volatile __XDATA *)0xffe8)
#define     PWM27T1L    (*(unsigned char volatile __XDATA *)0xffe9)

#define     PWM27T2H    (*(unsigned char volatile __XDATA *)0xffea)
#define     PWM27T2L    (*(unsigned char volatile __XDATA *)0xffeb)
#define     PWM27CR     (*(unsigned char volatile __XDATA *)0xffec)
#define     PWM27HLD    (*(unsigned char volatile __XDATA *)0xffed)

/////////////////////////////////////////////////
//FE00H-FEFFH
/////////////////////////////////////////////////

#define     CKSEL       (*(unsigned char volatile __XDATA *)0xfe00)
#define     CLKDIV      (*(unsigned char volatile __XDATA *)0xfe01)
#define     HIRCCR      (*(unsigned char volatile __XDATA *)0xfe02)
#define     XOSCCR      (*(unsigned char volatile __XDATA *)0xfe03)
#define     IRC32KCR    (*(unsigned char volatile __XDATA *)0xfe04)
#define     MCLKOCR     (*(unsigned char volatile __XDATA *)0xfe05)
#define     IRCDB       (*(unsigned char volatile __XDATA *)0xfe06)
#define     X32KCR      (*(unsigned char volatile __XDATA *)0xfe08)
#define     PxPU                                            0xfe10
#define     P0PU        (*(unsigned char volatile __XDATA *)0xfe10)
#define     P1PU        (*(unsigned char volatile __XDATA *)0xfe11)
#define     P2PU        (*(unsigned char volatile __XDATA *)0xfe12)
#define     P3PU        (*(unsigned char volatile __XDATA *)0xfe13)
#define     P4PU        (*(unsigned char volatile __XDATA *)0xfe14)
#define     P5PU        (*(unsigned char volatile __XDATA *)0xfe15)
#define     P6PU        (*(unsigned char volatile __XDATA *)0xfe16)
#define     P7PU        (*(unsigned char volatile __XDATA *)0xfe17)
#define     PxNCS                                           0xfe18
#define     P0NCS       (*(unsigned char volatile __XDATA *)0xfe18)
#define     P1NCS       (*(unsigned char volatile __XDATA *)0xfe19)
#define     P2NCS       (*(unsigned char volatile __XDATA *)0xfe1a)
#define     P3NCS       (*(unsigned char volatile __XDATA *)0xfe1b)
#define     P4NCS       (*(unsigned char volatile __XDATA *)0xfe1c)
#define     P5NCS       (*(unsigned char volatile __XDATA *)0xfe1d)
#define     P6NCS       (*(unsigned char volatile __XDATA *)0xfe1e)
#define     P7NCS       (*(unsigned char volatile __XDATA *)0xfe1f)
#define     PxSR                                            0xfe20
#define     P0SR        (*(unsigned char volatile __XDATA *)0xfe20)
#define     P1SR        (*(unsigned char volatile __XDATA *)0xfe21)
#define     P2SR        (*(unsigned char volatile __XDATA *)0xfe22)
#define     P3SR        (*(unsigned char volatile __XDATA *)0xfe23)
#define     P4SR        (*(unsigned char volatile __XDATA *)0xfe24)
#define     P5SR        (*(unsigned char volatile __XDATA *)0xfe25)
#define     P6SR        (*(unsigned char volatile __XDATA *)0xfe26)
#define     P7SR        (*(unsigned char volatile __XDATA *)0xfe27)
#define     PxDR                                            0xfe28
#define     P0DR        (*(unsigned char volatile __XDATA *)0xfe28)
#define     P1DR        (*(unsigned char volatile __XDATA *)0xfe29)
#define     P2DR        (*(unsigned char volatile __XDATA *)0xfe2a)
#define     P3DR        (*(unsigned char volatile __XDATA *)0xfe2b)
#define     P4DR        (*(unsigned char volatile __XDATA *)0xfe2c)
#define     P5DR        (*(unsigned char volatile __XDATA *)0xfe2d)
#define     P6DR        (*(unsigned char volatile __XDATA *)0xfe2e)
#define     P7DR        (*(unsigned char volatile __XDATA *)0xfe2f)
#define     PxIE                                            0xfe30
#define     P0IE        (*(unsigned char volatile __XDATA *)0xfe30)
#define     P1IE        (*(unsigned char volatile __XDATA *)0xfe31)
#define     P2IE        (*(unsigned char volatile __XDATA *)0xfe32)
#define     P3IE        (*(unsigned char volatile __XDATA *)0xfe33)
#define     P4IE        (*(unsigned char volatile __XDATA *)0xfe34)
#define     P5IE        (*(unsigned char volatile __XDATA *)0xfe35)
#define     P6IE        (*(unsigned char volatile __XDATA *)0xfe36)
#define     P7IE        (*(unsigned char volatile __XDATA *)0xfe37)

#define     RTCCR       (*(unsigned char volatile __XDATA *)0xfe60)
#define     RTCCFG      (*(unsigned char volatile __XDATA *)0xfe61)
#define     RTCIEN      (*(unsigned char volatile __XDATA *)0xfe62)
#define     RTCIF       (*(unsigned char volatile __XDATA *)0xfe63)
#define     ALAHOUR     (*(unsigned char volatile __XDATA *)0xfe64)
#define     ALAMIN      (*(unsigned char volatile __XDATA *)0xfe65)
#define     ALASEC      (*(unsigned char volatile __XDATA *)0xfe66)
#define     ALASSEC     (*(unsigned char volatile __XDATA *)0xfe67)
#define     INIYEAR     (*(unsigned char volatile __XDATA *)0xfe68)
#define     INIMONTH    (*(unsigned char volatile __XDATA *)0xfe69)
#define     INIDAY      (*(unsigned char volatile __XDATA *)0xfe6a)
#define     INIHOUR     (*(unsigned char volatile __XDATA *)0xfe6b)
#define     INIMIN      (*(unsigned char volatile __XDATA *)0xfe6c)
#define     INISEC      (*(unsigned char volatile __XDATA *)0xfe6d)
#define     INISSEC     (*(unsigned char volatile __XDATA *)0xfe6e)
#define     YEAR        (*(unsigned char volatile __XDATA *)0xfe70)
#define     MONTH       (*(unsigned char volatile __XDATA *)0xfe71)
#define     DAY         (*(unsigned char volatile __XDATA *)0xfe72)
#define     HOUR        (*(unsigned char volatile __XDATA *)0xfe73)
#define     MIN         (*(unsigned char volatile __XDATA *)0xfe74)
#define     SEC         (*(unsigned char volatile __XDATA *)0xfe75)
#define     SSEC        (*(unsigned char volatile __XDATA *)0xfe76)

#define     I2CCFG      (*(unsigned char volatile __XDATA *)0xfe80)
#define     I2CMSCR     (*(unsigned char volatile __XDATA *)0xfe81)
#define     I2CMSST     (*(unsigned char volatile __XDATA *)0xfe82)
#define     I2CSLCR     (*(unsigned char volatile __XDATA *)0xfe83)
#define     I2CSLST     (*(unsigned char volatile __XDATA *)0xfe84)
#define     I2CSLADR    (*(unsigned char volatile __XDATA *)0xfe85)
#define     I2CTXD      (*(unsigned char volatile __XDATA *)0xfe86)
#define     I2CRXD      (*(unsigned char volatile __XDATA *)0xfe87)
#define     I2CMSAUX    (*(unsigned char volatile __XDATA *)0xfe88)

#define     TM2PS       (*(unsigned char volatile __XDATA *)0xfea2)
#define     TM3PS       (*(unsigned char volatile __XDATA *)0xfea3)
#define     TM4PS       (*(unsigned char volatile __XDATA *)0xfea4)
#define     ADCTIM      (*(unsigned char volatile __XDATA *)0xfea8)
#define     T3T4PS      (*(unsigned char volatile __XDATA *)0xfeac)














































































































































































/////////////////////////////////////////////////
//FD00H-FDFFH
/////////////////////////////////////////////////

#define     PxINTE                                          0xfd00
#define     P0INTE      (*(unsigned char volatile __XDATA *)0xfd00)
#define     P1INTE      (*(unsigned char volatile __XDATA *)0xfd01)
#define     P2INTE      (*(unsigned char volatile __XDATA *)0xfd02)
#define     P3INTE      (*(unsigned char volatile __XDATA *)0xfd03)
#define     P4INTE      (*(unsigned char volatile __XDATA *)0xfd04)
#define     P5INTE      (*(unsigned char volatile __XDATA *)0xfd05)
#define     P6INTE      (*(unsigned char volatile __XDATA *)0xfd06)
#define     P7INTE      (*(unsigned char volatile __XDATA *)0xfd07)
#define     P0INTF      (*(unsigned char volatile __XDATA *)0xfd10)
#define     P1INTF      (*(unsigned char volatile __XDATA *)0xfd11)
#define     P2INTF      (*(unsigned char volatile __XDATA *)0xfd12)
#define     P3INTF      (*(unsigned char volatile __XDATA *)0xfd13)
#define     P4INTF      (*(unsigned char volatile __XDATA *)0xfd14)
#define     P5INTF      (*(unsigned char volatile __XDATA *)0xfd15)
#define     P6INTF      (*(unsigned char volatile __XDATA *)0xfd16)
#define     P7INTF      (*(unsigned char volatile __XDATA *)0xfd17)
#define     PxIM0                                           0xfd20
#define     P0IM0       (*(unsigned char volatile __XDATA *)0xfd20)
#define     P1IM0       (*(unsigned char volatile __XDATA *)0xfd21)
#define     P2IM0       (*(unsigned char volatile __XDATA *)0xfd22)
#define     P3IM0       (*(unsigned char volatile __XDATA *)0xfd23)
#define     P4IM0       (*(unsigned char volatile __XDATA *)0xfd24)
#define     P5IM0       (*(unsigned char volatile __XDATA *)0xfd25)
#define     P6IM0       (*(unsigned char volatile __XDATA *)0xfd26)
#define     P7IM0       (*(unsigned char volatile __XDATA *)0xfd27)
#define     PxIM1                                           0xfd30
#define     P0IM1       (*(unsigned char volatile __XDATA *)0xfd30)
#define     P1IM1       (*(unsigned char volatile __XDATA *)0xfd31)
#define     P2IM1       (*(unsigned char volatile __XDATA *)0xfd32)
#define     P3IM1       (*(unsigned char volatile __XDATA *)0xfd33)
#define     P4IM1       (*(unsigned char volatile __XDATA *)0xfd34)
#define     P5IM1       (*(unsigned char volatile __XDATA *)0xfd35)
#define     P6IM1       (*(unsigned char volatile __XDATA *)0xfd36)
#define     P7IM1       (*(unsigned char volatile __XDATA *)0xfd37)
#define     P0WKUE      (*(unsigned char volatile __XDATA *)0xfd40)
#define     P1WKUE      (*(unsigned char volatile __XDATA *)0xfd41)
#define     P2WKUE      (*(unsigned char volatile __XDATA *)0xfd42)
#define     P3WKUE      (*(unsigned char volatile __XDATA *)0xfd43)
#define     P4WKUE      (*(unsigned char volatile __XDATA *)0xfd44)
#define     P5WKUE      (*(unsigned char volatile __XDATA *)0xfd45)
#define     P6WKUE      (*(unsigned char volatile __XDATA *)0xfd46)
#define     P7WKUE      (*(unsigned char volatile __XDATA *)0xfd47)
#define     PIN_IP      (*(unsigned char volatile __XDATA *)0xfd60)
#define     PIN_IPH     (*(unsigned char volatile __XDATA *)0xfd61)

/////////////////////////////////////////////////
//FC00H-FCFFH
/////////////////////////////////////////////////


#define     PWM3CH      (*(unsigned char volatile __XDATA *)0xfc00)
#define     PWM3CL      (*(unsigned char volatile __XDATA *)0xfc01)
#define     PWM3CKS     (*(unsigned char volatile __XDATA *)0xfc02)
#define     PWM3IF      (*(unsigned char volatile __XDATA *)0xfc05)
#define     PWM3FDCR    (*(unsigned char volatile __XDATA *)0xfc06)

#define     PWM30T1H    (*(unsigned char volatile __XDATA *)0xfc10)
#define     PWM30T1L    (*(unsigned char volatile __XDATA *)0xfc11)

#define     PWM30T2H    (*(unsigned char volatile __XDATA *)0xfc12)
#define     PWM30T2L    (*(unsigned char volatile __XDATA *)0xfc13)
#define     PWM30CR     (*(unsigned char volatile __XDATA *)0xfc14)
#define     PWM30HLD    (*(unsigned char volatile __XDATA *)0xfc15)

#define     PWM31T1H    (*(unsigned char volatile __XDATA *)0xfc18)
#define     PWM31T1L    (*(unsigned char volatile __XDATA *)0xfc19)

#define     PWM31T2H    (*(unsigned char volatile __XDATA *)0xfc1a)
#define     PWM31T2L    (*(unsigned char volatile __XDATA *)0xfc1b)
#define     PWM31CR     (*(unsigned char volatile __XDATA *)0xfc1c)
#define     PWM31HLD    (*(unsigned char volatile __XDATA *)0xfc1d)

#define     PWM32T1H    (*(unsigned char volatile __XDATA *)0xfc20)
#define     PWM32T1L    (*(unsigned char volatile __XDATA *)0xfc21)

#define     PWM32T2H    (*(unsigned char volatile __XDATA *)0xfc22)
#define     PWM32T2L    (*(unsigned char volatile __XDATA *)0xfc23)
#define     PWM32CR     (*(unsigned char volatile __XDATA *)0xfc24)
#define     PWM32HLD    (*(unsigned char volatile __XDATA *)0xfc25)

#define     PWM33T1H    (*(unsigned char volatile __XDATA *)0xfc28)
#define     PWM33T1L    (*(unsigned char volatile __XDATA *)0xfc29)

#define     PWM33T2H    (*(unsigned char volatile __XDATA *)0xfc2a)
#define     PWM33T2L    (*(unsigned char volatile __XDATA *)0xfc2b)
#define     PWM33CR     (*(unsigned char volatile __XDATA *)0xfc2c)
#define     PWM33HLD    (*(unsigned char volatile __XDATA *)0xfc2d)

#define     PWM34T1H    (*(unsigned char volatile __XDATA *)0xfc30)
#define     PWM34T1L    (*(unsigned char volatile __XDATA *)0xfc31)

#define     PWM34T2H    (*(unsigned char volatile __XDATA *)0xfc32)
#define     PWM34T2L    (*(unsigned char volatile __XDATA *)0xfc33)
#define     PWM34CR     (*(unsigned char volatile __XDATA *)0xfc34)
#define     PWM34HLD    (*(unsigned char volatile __XDATA *)0xfc35)

#define     PWM35T1H    (*(unsigned char volatile __XDATA *)0xfc38)
#define     PWM35T1L    (*(unsigned char volatile __XDATA *)0xfc39)

#define     PWM35T2H    (*(unsigned char volatile __XDATA *)0xfc3a)
#define     PWM35T2L    (*(unsigned char volatile __XDATA *)0xfc3b)
#define     PWM35CR     (*(unsigned char volatile __XDATA *)0xfc3c)
#define     PWM35HLD    (*(unsigned char volatile __XDATA *)0xfc3d)

#define     PWM36T1H    (*(unsigned char volatile __XDATA *)0xfc40)
#define     PWM36T1L    (*(unsigned char volatile __XDATA *)0xfc41)

#define     PWM36T2H    (*(unsigned char volatile __XDATA *)0xfc42)
#define     PWM36T2L    (*(unsigned char volatile __XDATA *)0xfc43)
#define     PWM36CR     (*(unsigned char volatile __XDATA *)0xfc44)
#define     PWM36HLD    (*(unsigned char volatile __XDATA *)0xfc45)

#define     PWM37T1H    (*(unsigned char volatile __XDATA *)0xfc48)
#define     PWM37T1L    (*(unsigned char volatile __XDATA *)0xfc49)

#define     PWM37T2H    (*(unsigned char volatile __XDATA *)0xfc4a)
#define     PWM37T2L    (*(unsigned char volatile __XDATA *)0xfc4b)
#define     PWM37CR     (*(unsigned char volatile __XDATA *)0xfc4c)
#define     PWM37HLD    (*(unsigned char volatile __XDATA *)0xfc4d)

#define     PWM4CH      (*(unsigned char volatile __XDATA *)0xfc50)
#define     PWM4CL      (*(unsigned char volatile __XDATA *)0xfc51)
#define     PWM4CKS     (*(unsigned char volatile __XDATA *)0xfc52)

#define     PWM4TADCH   (*(unsigned char volatile __XDATA *)0xfc53)
#define     PWM4TADCL   (*(unsigned char volatile __XDATA *)0xfc54)
#define     PWM4IF      (*(unsigned char volatile __XDATA *)0xfc55)
#define     PWM4FDCR    (*(unsigned char volatile __XDATA *)0xfc56)

#define     PWM40T1H    (*(unsigned char volatile __XDATA *)0xfc60)
#define     PWM40T1L    (*(unsigned char volatile __XDATA *)0xfc61)

#define     PWM40T2H    (*(unsigned char volatile __XDATA *)0xfc62)
#define     PWM40T2L    (*(unsigned char volatile __XDATA *)0xfc63)
#define     PWM40CR     (*(unsigned char volatile __XDATA *)0xfc64)
#define     PWM40HLD    (*(unsigned char volatile __XDATA *)0xfc65)

#define     PWM41T1H    (*(unsigned char volatile __XDATA *)0xfc68)
#define     PWM41T1L    (*(unsigned char volatile __XDATA *)0xfc69)

#define     PWM41T2H    (*(unsigned char volatile __XDATA *)0xfc6a)
#define     PWM41T2L    (*(unsigned char volatile __XDATA *)0xfc6b)
#define     PWM41CR     (*(unsigned char volatile __XDATA *)0xfc6c)
#define     PWM41HLD    (*(unsigned char volatile __XDATA *)0xfc6d)

#define     PWM42T1H    (*(unsigned char volatile __XDATA *)0xfc70)
#define     PWM42T1L    (*(unsigned char volatile __XDATA *)0xfc71)

#define     PWM42T2H    (*(unsigned char volatile __XDATA *)0xfc72)
#define     PWM42T2L    (*(unsigned char volatile __XDATA *)0xfc73)
#define     PWM42CR     (*(unsigned char volatile __XDATA *)0xfc74)
#define     PWM42HLD    (*(unsigned char volatile __XDATA *)0xfc75)

#define     PWM43T1H    (*(unsigned char volatile __XDATA *)0xfc78)
#define     PWM43T1L    (*(unsigned char volatile __XDATA *)0xfc79)

#define     PWM43T2H    (*(unsigned char volatile __XDATA *)0xfc7a)
#define     PWM43T2L    (*(unsigned char volatile __XDATA *)0xfc7b)
#define     PWM43CR     (*(unsigned char volatile __XDATA *)0xfc7c)
#define     PWM43HLD    (*(unsigned char volatile __XDATA *)0xfc7d)

#define     PWM44T1H    (*(unsigned char volatile __XDATA *)0xfc80)
#define     PWM44T1L    (*(unsigned char volatile __XDATA *)0xfc81)

#define     PWM44T2H    (*(unsigned char volatile __XDATA *)0xfc82)
#define     PWM44T2L    (*(unsigned char volatile __XDATA *)0xfc83)
#define     PWM44CR     (*(unsigned char volatile __XDATA *)0xfc84)
#define     PWM44HLD    (*(unsigned char volatile __XDATA *)0xfc85)

#define     PWM45T1H    (*(unsigned char volatile __XDATA *)0xfc88)
#define     PWM45T1L    (*(unsigned char volatile __XDATA *)0xfc89)

#define     PWM45T2H    (*(unsigned char volatile __XDATA *)0xfc8a)
#define     PWM45T2L    (*(unsigned char volatile __XDATA *)0xfc8b)
#define     PWM45CR     (*(unsigned char volatile __XDATA *)0xfc8c)
#define     PWM45HLD    (*(unsigned char volatile __XDATA *)0xfc8d)

#define     PWM46T1H    (*(unsigned char volatile __XDATA *)0xfc90)
#define     PWM46T1L    (*(unsigned char volatile __XDATA *)0xfc91)

#define     PWM46T2H    (*(unsigned char volatile __XDATA *)0xfc92)
#define     PWM46T2L    (*(unsigned char volatile __XDATA *)0xfc93)
#define     PWM46CR     (*(unsigned char volatile __XDATA *)0xfc94)
#define     PWM46HLD    (*(unsigned char volatile __XDATA *)0xfc95)

#define     PWM47T1H    (*(unsigned char volatile __XDATA *)0xfc98)
#define     PWM47T1L    (*(unsigned char volatile __XDATA *)0xfc99)

#define     PWM47T2H    (*(unsigned char volatile __XDATA *)0xfc9a)
#define     PWM47T2L    (*(unsigned char volatile __XDATA *)0xfc9b)
#define     PWM47CR     (*(unsigned char volatile __XDATA *)0xfc9c)
#define     PWM47HLD    (*(unsigned char volatile __XDATA *)0xfc9d)

#define     PWM5CH      (*(unsigned char volatile __XDATA *)0xfca0)
#define     PWM5CL      (*(unsigned char volatile __XDATA *)0xfca1)
#define     PWM5CKS     (*(unsigned char volatile __XDATA *)0xfca2)
#define     PWM5IF      (*(unsigned char volatile __XDATA *)0xfca5)
#define     PWM5FDCR    (*(unsigned char volatile __XDATA *)0xfca6)

#define     PWM50T1H    (*(unsigned char volatile __XDATA *)0xfcb0)
#define     PWM50T1L    (*(unsigned char volatile __XDATA *)0xfcb1)

#define     PWM50T2H    (*(unsigned char volatile __XDATA *)0xfcb2)
#define     PWM50T2L    (*(unsigned char volatile __XDATA *)0xfcb3)
#define     PWM50CR     (*(unsigned char volatile __XDATA *)0xfcb4)
#define     PWM50HLD    (*(unsigned char volatile __XDATA *)0xfcb5)

#define     PWM51T1H    (*(unsigned char volatile __XDATA *)0xfcb8)
#define     PWM51T1L    (*(unsigned char volatile __XDATA *)0xfcb9)

#define     PWM51T2H    (*(unsigned char volatile __XDATA *)0xfcba)
#define     PWM51T2L    (*(unsigned char volatile __XDATA *)0xfcbb)
#define     PWM51CR     (*(unsigned char volatile __XDATA *)0xfcbc)
#define     PWM51HLD    (*(unsigned char volatile __XDATA *)0xfcbd)

#define     PWM52T1H    (*(unsigned char volatile __XDATA *)0xfcc0)
#define     PWM52T1L    (*(unsigned char volatile __XDATA *)0xfcc1)

#define     PWM52T2H    (*(unsigned char volatile __XDATA *)0xfcc2)
#define     PWM52T2L    (*(unsigned char volatile __XDATA *)0xfcc3)
#define     PWM52CR     (*(unsigned char volatile __XDATA *)0xfcc4)
#define     PWM52HLD    (*(unsigned char volatile __XDATA *)0xfcc5)

#define     PWM53T1H    (*(unsigned char volatile __XDATA *)0xfcc8)
#define     PWM53T1L    (*(unsigned char volatile __XDATA *)0xfcc9)

#define     PWM53T2H    (*(unsigned char volatile __XDATA *)0xfcca)
#define     PWM53T2L    (*(unsigned char volatile __XDATA *)0xfccb)
#define     PWM53CR     (*(unsigned char volatile __XDATA *)0xfccc)
#define     PWM53HLD    (*(unsigned char volatile __XDATA *)0xfccd)

#define     PWM54T1H    (*(unsigned char volatile __XDATA *)0xfcd0)
#define     PWM54T1L    (*(unsigned char volatile __XDATA *)0xfcd1)

#define     PWM54T2H    (*(unsigned char volatile __XDATA *)0xfcd2)
#define     PWM54T2L    (*(unsigned char volatile __XDATA *)0xfcd3)
#define     PWM54CR     (*(unsigned char volatile __XDATA *)0xfcd4)
#define     PWM54HLD    (*(unsigned char volatile __XDATA *)0xfcd5)

#define     PWM55T1H    (*(unsigned char volatile __XDATA *)0xfcd8)
#define     PWM55T1L    (*(unsigned char volatile __XDATA *)0xfcd9)

#define     PWM55T2H    (*(unsigned char volatile __XDATA *)0xfcda)
#define     PWM55T2L    (*(unsigned char volatile __XDATA *)0xfcdb)
#define     PWM55CR     (*(unsigned char volatile __XDATA *)0xfcdc)
#define     PWM55HLD    (*(unsigned char volatile __XDATA *)0xfcdd)

#define     PWM56T1H    (*(unsigned char volatile __XDATA *)0xfce0)
#define     PWM56T1L    (*(unsigned char volatile __XDATA *)0xfce1)

#define     PWM56T2H    (*(unsigned char volatile __XDATA *)0xfce2)
#define     PWM56T2L    (*(unsigned char volatile __XDATA *)0xfce3)
#define     PWM56CR     (*(unsigned char volatile __XDATA *)0xfce4)
#define     PWM56HLD    (*(unsigned char volatile __XDATA *)0xfce5)

#define     PWM57T1H    (*(unsigned char volatile __XDATA *)0xfce8)
#define     PWM57T1L    (*(unsigned char volatile __XDATA *)0xfce9)

#define     PWM57T2H    (*(unsigned char volatile __XDATA *)0xfcea)
#define     PWM57T2L    (*(unsigned char volatile __XDATA *)0xfceb)
#define     PWM57CR     (*(unsigned char volatile __XDATA *)0xfcec)
#define     PWM57HLD    (*(unsigned char volatile __XDATA *)0xfced)

#define     MD3         (*(unsigned char volatile __XDATA *)0xfcf0)
#define     MD2         (*(unsigned char volatile __XDATA *)0xfcf1)
#define     MD1         (*(unsigned char volatile __XDATA *)0xfcf2)
#define     MD0         (*(unsigned char volatile __XDATA *)0xfcf3)
#define     MD5         (*(unsigned char volatile __XDATA *)0xfcf4)
#define     MD4         (*(unsigned char volatile __XDATA *)0xfcf5)
#define     ARCON       (*(unsigned char volatile __XDATA *)0xfcf6)
#define     OPCON       (*(unsigned char volatile __XDATA *)0xfcf7)

/////////////////////////////////////////////////
//FB00H-FBFFH
/////////////////////////////////////////////////

#define     COMEN       (*(unsigned char volatile __XDATA *)0xfb00)
#define     SEGENL      (*(unsigned char volatile __XDATA *)0xfb01)
#define     SEGENH      (*(unsigned char volatile __XDATA *)0xfb02)
#define     LEDCTRL     (*(unsigned char volatile __XDATA *)0xfb03)
#define     LEDCKS      (*(unsigned char volatile __XDATA *)0xfb04)
#define     COM0_DA_L   (*(unsigned char volatile __XDATA *)0xfb10)
#define     COM1_DA_L   (*(unsigned char volatile __XDATA *)0xfb11)
#define     COM2_DA_L   (*(unsigned char volatile __XDATA *)0xfb12)
#define     COM3_DA_L   (*(unsigned char volatile __XDATA *)0xfb13)
#define     COM4_DA_L   (*(unsigned char volatile __XDATA *)0xfb14)
#define     COM5_DA_L   (*(unsigned char volatile __XDATA *)0xfb15)
#define     COM6_DA_L   (*(unsigned char volatile __XDATA *)0xfb16)
#define     COM7_DA_L   (*(unsigned char volatile __XDATA *)0xfb17)
#define     COM0_DA_H   (*(unsigned char volatile __XDATA *)0xfb18)
#define     COM1_DA_H   (*(unsigned char volatile __XDATA *)0xfb19)
#define     COM2_DA_H   (*(unsigned char volatile __XDATA *)0xfb1a)
#define     COM3_DA_H   (*(unsigned char volatile __XDATA *)0xfb1b)
#define     COM4_DA_H   (*(unsigned char volatile __XDATA *)0xfb1c)
#define     COM5_DA_H   (*(unsigned char volatile __XDATA *)0xfb1d)
#define     COM6_DA_H   (*(unsigned char volatile __XDATA *)0xfb1e)
#define     COM7_DA_H   (*(unsigned char volatile __XDATA *)0xfb1f)
#define     COM0_DC_L   (*(unsigned char volatile __XDATA *)0xfb20)
#define     COM1_DC_L   (*(unsigned char volatile __XDATA *)0xfb21)
#define     COM2_DC_L   (*(unsigned char volatile __XDATA *)0xfb22)
#define     COM3_DC_L   (*(unsigned char volatile __XDATA *)0xfb23)
#define     COM4_DC_L   (*(unsigned char volatile __XDATA *)0xfb24)
#define     COM5_DC_L   (*(unsigned char volatile __XDATA *)0xfb25)
#define     COM6_DC_L   (*(unsigned char volatile __XDATA *)0xfb26)
#define     COM7_DC_L   (*(unsigned char volatile __XDATA *)0xfb27)
#define     COM0_DC_H   (*(unsigned char volatile __XDATA *)0xfb28)
#define     COM1_DC_H   (*(unsigned char volatile __XDATA *)0xfb29)
#define     COM2_DC_H   (*(unsigned char volatile __XDATA *)0xfb2a)
#define     COM3_DC_H   (*(unsigned char volatile __XDATA *)0xfb2b)
#define     COM4_DC_H   (*(unsigned char volatile __XDATA *)0xfb2c)
#define     COM5_DC_H   (*(unsigned char volatile __XDATA *)0xfb2d)
#define     COM6_DC_H   (*(unsigned char volatile __XDATA *)0xfb2e)
#define     COM7_DC_H   (*(unsigned char volatile __XDATA *)0xfb2f)

#define     TSCHEN1     (*(unsigned char volatile __XDATA *)0xfb40)
#define     TSCHEN2     (*(unsigned char volatile __XDATA *)0xfb41)
#define     TSCFG1      (*(unsigned char volatile __XDATA *)0xfb42)
#define     TSCFG2      (*(unsigned char volatile __XDATA *)0xfb43)
#define     TSWUTC      (*(unsigned char volatile __XDATA *)0xfb44)
#define     TSCTRL      (*(unsigned char volatile __XDATA *)0xfb45)
#define     TSSTA1      (*(unsigned char volatile __XDATA *)0xfb46)
#define     TSSTA2      (*(unsigned char volatile __XDATA *)0xfb47)
#define     TSRT        (*(unsigned char volatile __XDATA *)0xfb48)

#define     TSDATH      (*(unsigned char volatile __XDATA *)0xfb49)
#define     TSDATL      (*(unsigned char volatile __XDATA *)0xfb4a)

#define     TSTH00H     (*(unsigned char volatile __XDATA *)0xfb50)
#define     TSTH00L     (*(unsigned char volatile __XDATA *)0xfb51)

#define     TSTH01H     (*(unsigned char volatile __XDATA *)0xfb52)
#define     TSTH01L     (*(unsigned char volatile __XDATA *)0xfb53)

#define     TSTH02H     (*(unsigned char volatile __XDATA *)0xfb54)
#define     TSTH02L     (*(unsigned char volatile __XDATA *)0xfb55)

#define     TSTH03H     (*(unsigned char volatile __XDATA *)0xfb56)
#define     TSTH03L     (*(unsigned char volatile __XDATA *)0xfb57)

#define     TSTH04H     (*(unsigned char volatile __XDATA *)0xfb58)
#define     TSTH04L     (*(unsigned char volatile __XDATA *)0xfb59)

#define     TSTH05H     (*(unsigned char volatile __XDATA *)0xfb5a)
#define     TSTH05L     (*(unsigned char volatile __XDATA *)0xfb5b)

#define     TSTH06H     (*(unsigned char volatile __XDATA *)0xfb5c)
#define     TSTH06L     (*(unsigned char volatile __XDATA *)0xfb5d)

#define     TSTH07H     (*(unsigned char volatile __XDATA *)0xfb5e)
#define     TSTH07L     (*(unsigned char volatile __XDATA *)0xfb5f)

#define     TSTH08H     (*(unsigned char volatile __XDATA *)0xfb60)
#define     TSTH08L     (*(unsigned char volatile __XDATA *)0xfb61)

#define     TSTH09H     (*(unsigned char volatile __XDATA *)0xfb62)
#define     TSTH09L     (*(unsigned char volatile __XDATA *)0xfb63)

#define     TSTH10H     (*(unsigned char volatile __XDATA *)0xfb64)
#define     TSTH10L     (*(unsigned char volatile __XDATA *)0xfb65)

#define     TSTH11H     (*(unsigned char volatile __XDATA *)0xfb66)
#define     TSTH11L     (*(unsigned char volatile __XDATA *)0xfb67)

#define     TSTH12H     (*(unsigned char volatile __XDATA *)0xfb68)
#define     TSTH12L     (*(unsigned char volatile __XDATA *)0xfb69)

#define     TSTH13H     (*(unsigned char volatile __XDATA *)0xfb6a)
#define     TSTH13L     (*(unsigned char volatile __XDATA *)0xfb6b)

#define     TSTH14H     (*(unsigned char volatile __XDATA *)0xfb6c)
#define     TSTH14L     (*(unsigned char volatile __XDATA *)0xfb6d)

#define     TSTH15H     (*(unsigned char volatile __XDATA *)0xfb6e)
#define     TSTH15L     (*(unsigned char volatile __XDATA *)0xfb6f)

/////////////////////////////////////////////////
//FA00H-FAFFH
/////////////////////////////////////////////////


#if defined __CX51__

#define     PWM0C       (*(unsigned int  volatile __XDATA *)0xff00)
#define     PWM0TADC    (*(unsigned int  volatile __XDATA *)0xff03)
#define     PWM00T1     (*(unsigned int  volatile __XDATA *)0xff10)
#define     PWM00T2     (*(unsigned int  volatile __XDATA *)0xff12)
#define     PWM01T1     (*(unsigned int  volatile __XDATA *)0xff18)
#define     PWM01T2     (*(unsigned int  volatile __XDATA *)0xff1a)
#define     PWM02T1     (*(unsigned int  volatile __XDATA *)0xff20)
#define     PWM02T2     (*(unsigned int  volatile __XDATA *)0xff22)
#define     PWM03T1     (*(unsigned int  volatile __XDATA *)0xff28)
#define     PWM03T2     (*(unsigned int  volatile __XDATA *)0xff2a)
#define     PWM04T1     (*(unsigned int  volatile __XDATA *)0xff30)
#define     PWM04T2     (*(unsigned int  volatile __XDATA *)0xff32)
#define     PWM05T1     (*(unsigned int  volatile __XDATA *)0xff38)
#define     PWM05T2     (*(unsigned int  volatile __XDATA *)0xff3a)
#define     PWM06T1     (*(unsigned int  volatile __XDATA *)0xff40)
#define     PWM06T2     (*(unsigned int  volatile __XDATA *)0xff42)
#define     PWM07T1     (*(unsigned int  volatile __XDATA *)0xff48)
#define     PWM07T2     (*(unsigned int  volatile __XDATA *)0xff4a)
#define     PWM1C       (*(unsigned int  volatile __XDATA *)0xff50)
#define     PWM10T1     (*(unsigned int  volatile __XDATA *)0xff60)
#define     PWM10T2     (*(unsigned int  volatile __XDATA *)0xff62)
#define     PWM11T1     (*(unsigned int  volatile __XDATA *)0xff68)
#define     PWM11T2     (*(unsigned int  volatile __XDATA *)0xff6a)
#define     PWM12T1     (*(unsigned int  volatile __XDATA *)0xff70)
#define     PWM12T2     (*(unsigned int  volatile __XDATA *)0xff72)
#define     PWM13T1     (*(unsigned int  volatile __XDATA *)0xff78)
#define     PWM13T2     (*(unsigned int  volatile __XDATA *)0xff7a)
#define     PWM14T1     (*(unsigned int  volatile __XDATA *)0xff80)
#define     PWM14T2     (*(unsigned int  volatile __XDATA *)0xff82)
#define     PWM15T1     (*(unsigned int  volatile __XDATA *)0xff88)
#define     PWM15T2     (*(unsigned int  volatile __XDATA *)0xff8a)
#define     PWM16T1     (*(unsigned int  volatile __XDATA *)0xff90)
#define     PWM16T2     (*(unsigned int  volatile __XDATA *)0xff92)
#define     PWM17T1     (*(unsigned int  volatile __XDATA *)0xff98)
#define     PWM17T2     (*(unsigned int  volatile __XDATA *)0xff9a)
#define     PWM2C       (*(unsigned int  volatile __XDATA *)0xffa0)
#define     PWM2TADC    (*(unsigned int  volatile __XDATA *)0xffa3)
#define     PWM20T1     (*(unsigned int  volatile __XDATA *)0xffb0)
#define     PWM20T2     (*(unsigned int  volatile __XDATA *)0xffb2)
#define     PWM21T1     (*(unsigned int  volatile __XDATA *)0xffb8)
#define     PWM21T2     (*(unsigned int  volatile __XDATA *)0xffba)
#define     PWM22T1     (*(unsigned int  volatile __XDATA *)0xffc0)
#define     PWM22T2     (*(unsigned int  volatile __XDATA *)0xffc2)
#define     PWM23T1     (*(unsigned int  volatile __XDATA *)0xffc8)
#define     PWM23T2     (*(unsigned int  volatile __XDATA *)0xffca)
#define     PWM24T1     (*(unsigned int  volatile __XDATA *)0xffd0)
#define     PWM24T2     (*(unsigned int  volatile __XDATA *)0xffd2)
#define     PWM25T1     (*(unsigned int  volatile __XDATA *)0xffd8)
#define     PWM25T2     (*(unsigned int  volatile __XDATA *)0xffda)
#define     PWM26T1     (*(unsigned int  volatile __XDATA *)0xffe0)
#define     PWM26T2     (*(unsigned int  volatile __XDATA *)0xffe2)
#define     PWM27T1     (*(unsigned int  volatile __XDATA *)0xffe8)
#define     PWM27T2     (*(unsigned int  volatile __XDATA *)0xffea)
#define     PWM3C       (*(unsigned int  volatile __XDATA *)0xfc00)
#define     PWM30T1     (*(unsigned int  volatile __XDATA *)0xfc10)
#define     PWM30T2     (*(unsigned int  volatile __XDATA *)0xfc12)
#define     PWM31T1     (*(unsigned int  volatile __XDATA *)0xfc18)
#define     PWM31T2     (*(unsigned int  volatile __XDATA *)0xfc1a)
#define     PWM32T1     (*(unsigned int  volatile __XDATA *)0xfc20)
#define     PWM32T2     (*(unsigned int  volatile __XDATA *)0xfc22)
#define     PWM33T1     (*(unsigned int  volatile __XDATA *)0xfc28)
#define     PWM33T2     (*(unsigned int  volatile __XDATA *)0xfc2a)
#define     PWM34T1     (*(unsigned int  volatile __XDATA *)0xfc30)
#define     PWM34T2     (*(unsigned int  volatile __XDATA *)0xfc32)
#define     PWM35T1     (*(unsigned int  volatile __XDATA *)0xfc38)
#define     PWM35T2     (*(unsigned int  volatile __XDATA *)0xfc3a)
#define     PWM36T1     (*(unsigned int  volatile __XDATA *)0xfc40)
#define     PWM36T2     (*(unsigned int  volatile __XDATA *)0xfc42)
#define     PWM37T1     (*(unsigned int  volatile __XDATA *)0xfc48)
#define     PWM37T2     (*(unsigned int  volatile __XDATA *)0xfc4a)
#define     PWM4C       (*(unsigned int  volatile __XDATA *)0xfc50)
#define     PWM4TADC    (*(unsigned int  volatile __XDATA *)0xfc53)
#define     PWM40T1     (*(unsigned int  volatile __XDATA *)0xfc60)
#define     PWM40T2     (*(unsigned int  volatile __XDATA *)0xfc62)
#define     PWM41T1     (*(unsigned int  volatile __XDATA *)0xfc68)
#define     PWM41T2     (*(unsigned int  volatile __XDATA *)0xfc6a)
#define     PWM42T1     (*(unsigned int  volatile __XDATA *)0xfc70)
#define     PWM42T2     (*(unsigned int  volatile __XDATA *)0xfc72)
#define     PWM43T1     (*(unsigned int  volatile __XDATA *)0xfc78)
#define     PWM43T2     (*(unsigned int  volatile __XDATA *)0xfc7a)
#define     PWM44T1     (*(unsigned int  volatile __XDATA *)0xfc80)
#define     PWM44T2     (*(unsigned int  volatile __XDATA *)0xfc82)
#define     PWM45T1     (*(unsigned int  volatile __XDATA *)0xfc88)
#define     PWM45T2     (*(unsigned int  volatile __XDATA *)0xfc8a)
#define     PWM46T1     (*(unsigned int  volatile __XDATA *)0xfc90)
#define     PWM46T2     (*(unsigned int  volatile __XDATA *)0xfc92)
#define     PWM47T1     (*(unsigned int  volatile __XDATA *)0xfc98)
#define     PWM47T2     (*(unsigned int  volatile __XDATA *)0xfc9a)
#define     PWM5C       (*(unsigned int  volatile __XDATA *)0xfca0)
#define     PWM50T1     (*(unsigned int  volatile __XDATA *)0xfcb0)
#define     PWM50T2     (*(unsigned int  volatile __XDATA *)0xfcb2)
#define     PWM51T1     (*(unsigned int  volatile __XDATA *)0xfcb8)
#define     PWM51T2     (*(unsigned int  volatile __XDATA *)0xfcba)
#define     PWM52T1     (*(unsigned int  volatile __XDATA *)0xfcc0)
#define     PWM52T2     (*(unsigned int  volatile __XDATA *)0xfcc2)
#define     PWM53T1     (*(unsigned int  volatile __XDATA *)0xfcc8)
#define     PWM53T2     (*(unsigned int  volatile __XDATA *)0xfcca)
#define     PWM54T1     (*(unsigned int  volatile __XDATA *)0xfcd0)
#define     PWM54T2     (*(unsigned int  volatile __XDATA *)0xfcd2)
#define     PWM55T1     (*(unsigned int  volatile __XDATA *)0xfcd8)
#define     PWM55T2     (*(unsigned int  volatile __XDATA *)0xfcda)
#define     PWM56T1     (*(unsigned int  volatile __XDATA *)0xfce0)
#define     PWM56T2     (*(unsigned int  volatile __XDATA *)0xfce2)
#define     PWM57T1     (*(unsigned int  volatile __XDATA *)0xfce8)
#define     PWM57T2     (*(unsigned int  volatile __XDATA *)0xfcea)
#define     TSDAT       (*(unsigned int  volatile __XDATA *)0xfb49)
#define     TSTH00      (*(unsigned int  volatile __XDATA *)0xfb50)
#define     TSTH01      (*(unsigned int  volatile __XDATA *)0xfb52)
#define     TSTH02      (*(unsigned int  volatile __XDATA *)0xfb54)
#define     TSTH03      (*(unsigned int  volatile __XDATA *)0xfb56)
#define     TSTH04      (*(unsigned int  volatile __XDATA *)0xfb58)
#define     TSTH05      (*(unsigned int  volatile __XDATA *)0xfb5a)
#define     TSTH06      (*(unsigned int  volatile __XDATA *)0xfb5c)
#define     TSTH07      (*(unsigned int  volatile __XDATA *)0xfb5e)
#define     TSTH08      (*(unsigned int  volatile __XDATA *)0xfb60)
#define     TSTH09      (*(unsigned int  volatile __XDATA *)0xfb62)
#define     TSTH10      (*(unsigned int  volatile __XDATA *)0xfb64)
#define     TSTH11      (*(unsigned int  volatile __XDATA *)0xfb66)
#define     TSTH12      (*(unsigned int  volatile __XDATA *)0xfb68)
#define     TSTH13      (*(unsigned int  volatile __XDATA *)0xfb6a)
#define     TSTH14      (*(unsigned int  volatile __XDATA *)0xfb6c)
#define     TSTH15      (*(unsigned int  volatile __XDATA *)0xfb6e)

#endif


/////////////////////////////////////////////////

#endif

