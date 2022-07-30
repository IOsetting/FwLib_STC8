#ifndef __FW_REG_STC8H_H__
#define __FW_REG_STC8H_H__

#include "fw_reg_base.h"

SFR(VRTRIM,             0xA6);

SFR(USBCLK,             0xDC);

SFR(ADCCFG,             0xDE);
SFR(IP3,                0xDF);

SFR(P7M1,               0xE1);
SFR(P7M0,               0xE2);
SFR(DPS,                0xE3);
SFR(DPL1,               0xE4);
SFR(DPH1,               0xE5);
SFR(CMPCR1,             0xE6);
SFR(CMPCR2,             0xE7);

SFR(USBDAT,             0xEC);
SFR(IP3H,               0xEE);
SFR(AUXINTIF,           0xEF);

SFR(USBCON,             0xF4);

SFR(IAP_TPS,            0xF5);

SFR(USBADR,             0xFC);

SFR(RSTCFG,             0xFF);


/**
 * Set B7 of P_SW2 before read/write the following registers
*/

/////////////////////////////////////////////////
//FF00H-FFFFH
/////////////////////////////////////////////////



/////////////////////////////////////////////////
//FE00H-FEFFH
/////////////////////////////////////////////////

#define CKSEL             (*(unsigned char volatile __XDATA *)0xfe00)
#define CLKDIV            (*(unsigned char volatile __XDATA *)0xfe01)
#define HIRCCR            (*(unsigned char volatile __XDATA *)0xfe02)
#define XOSCCR            (*(unsigned char volatile __XDATA *)0xfe03)
#define IRC32KCR          (*(unsigned char volatile __XDATA *)0xfe04)
#define MCLKOCR           (*(unsigned char volatile __XDATA *)0xfe05)
#define IRCDB             (*(unsigned char volatile __XDATA *)0xfe06)
#define IRC48MCR          (*(unsigned char volatile __XDATA *)0xfe07)
#define X32KCR            (*(unsigned char volatile __XDATA *)0xfe08)
#define RSTFLAG           (*(unsigned char volatile __XDATA *)0xfe09)
#define PxPU                                                  0xfe10
#define P0PU                                           SFRX(PxPU + 0)
#define P1PU                                           SFRX(PxPU + 1)
#define P2PU              (*(unsigned char volatile __XDATA *)0xfe12)
#define P3PU              (*(unsigned char volatile __XDATA *)0xfe13)
#define P4PU              (*(unsigned char volatile __XDATA *)0xfe14)
#define P5PU              (*(unsigned char volatile __XDATA *)0xfe15)
#define P6PU              (*(unsigned char volatile __XDATA *)0xfe16)
#define P7PU              (*(unsigned char volatile __XDATA *)0xfe17)
#define PxNCS                                                 0xfe18
#define P0NCS             (*(unsigned char volatile __XDATA *)0xfe18)
#define P1NCS             (*(unsigned char volatile __XDATA *)0xfe19)
#define P2NCS             (*(unsigned char volatile __XDATA *)0xfe1a)
#define P3NCS             (*(unsigned char volatile __XDATA *)0xfe1b)
#define P4NCS             (*(unsigned char volatile __XDATA *)0xfe1c)
#define P5NCS             (*(unsigned char volatile __XDATA *)0xfe1d)
#define P6NCS             (*(unsigned char volatile __XDATA *)0xfe1e)
#define P7NCS             (*(unsigned char volatile __XDATA *)0xfe1f)
#define PxSR                                                  0xfe20
#define P0SR              (*(unsigned char volatile __XDATA *)0xfe20)
#define P1SR              (*(unsigned char volatile __XDATA *)0xfe21)
#define P2SR              (*(unsigned char volatile __XDATA *)0xfe22)
#define P3SR              (*(unsigned char volatile __XDATA *)0xfe23)
#define P4SR              (*(unsigned char volatile __XDATA *)0xfe24)
#define P5SR              (*(unsigned char volatile __XDATA *)0xfe25)
#define P6SR              (*(unsigned char volatile __XDATA *)0xfe26)
#define P7SR              (*(unsigned char volatile __XDATA *)0xfe27)
#define PxDR                                                  0xfe28
#define P0DR              (*(unsigned char volatile __XDATA *)0xfe28)
#define P1DR              (*(unsigned char volatile __XDATA *)0xfe29)
#define P2DR              (*(unsigned char volatile __XDATA *)0xfe2a)
#define P3DR              (*(unsigned char volatile __XDATA *)0xfe2b)
#define P4DR              (*(unsigned char volatile __XDATA *)0xfe2c)
#define P5DR              (*(unsigned char volatile __XDATA *)0xfe2d)
#define P6DR              (*(unsigned char volatile __XDATA *)0xfe2e)
#define P7DR              (*(unsigned char volatile __XDATA *)0xfe2f)
#define PxIE                                                  0xfe30
#define P0IE              (*(unsigned char volatile __XDATA *)0xfe30)
#define P1IE              (*(unsigned char volatile __XDATA *)0xfe31)
#define P2IE              (*(unsigned char volatile __XDATA *)0xfe32)
#define P3IE              (*(unsigned char volatile __XDATA *)0xfe33)
#define P4IE              (*(unsigned char volatile __XDATA *)0xfe34)
#define P5IE              (*(unsigned char volatile __XDATA *)0xfe35)
#define P6IE              (*(unsigned char volatile __XDATA *)0xfe36)
#define P7IE              (*(unsigned char volatile __XDATA *)0xfe37)
#define LCMIFCFG          (*(unsigned char volatile __XDATA *)0xfe50)
#define RTCCR             (*(unsigned char volatile __XDATA *)0xfe60)
#define RTCCFG            (*(unsigned char volatile __XDATA *)0xfe61)
#define RTCIEN            (*(unsigned char volatile __XDATA *)0xfe62)
#define RTCIF             (*(unsigned char volatile __XDATA *)0xfe63)
#define ALAHOUR           (*(unsigned char volatile __XDATA *)0xfe64)
#define ALAMIN            (*(unsigned char volatile __XDATA *)0xfe65)
#define ALASEC            (*(unsigned char volatile __XDATA *)0xfe66)
#define ALASSEC           (*(unsigned char volatile __XDATA *)0xfe67)
#define INIYEAR           (*(unsigned char volatile __XDATA *)0xfe68)
#define INIMONTH          (*(unsigned char volatile __XDATA *)0xfe69)
#define INIDAY            (*(unsigned char volatile __XDATA *)0xfe6a)
#define INIHOUR           (*(unsigned char volatile __XDATA *)0xfe6b)
#define INIMIN            (*(unsigned char volatile __XDATA *)0xfe6c)
#define INISEC            (*(unsigned char volatile __XDATA *)0xfe6d)
#define INISSEC           (*(unsigned char volatile __XDATA *)0xfe6e)
#define YEAR              (*(unsigned char volatile __XDATA *)0xfe70)
#define MONTH             (*(unsigned char volatile __XDATA *)0xfe71)
#define DAY               (*(unsigned char volatile __XDATA *)0xfe72)
#define HOUR              (*(unsigned char volatile __XDATA *)0xfe73)
#define MIN               (*(unsigned char volatile __XDATA *)0xfe74)
#define SEC               (*(unsigned char volatile __XDATA *)0xfe75)
#define SSEC              (*(unsigned char volatile __XDATA *)0xfe76)

#define I2CCFG            (*(unsigned char volatile __XDATA *)0xfe80)
#define I2CMSCR           (*(unsigned char volatile __XDATA *)0xfe81)
#define I2CMSST           (*(unsigned char volatile __XDATA *)0xfe82)
#define I2CSLCR           (*(unsigned char volatile __XDATA *)0xfe83)
#define I2CSLST           (*(unsigned char volatile __XDATA *)0xfe84)
#define I2CSLADR          (*(unsigned char volatile __XDATA *)0xfe85)
#define I2CTXD            (*(unsigned char volatile __XDATA *)0xfe86)
#define I2CRXD            (*(unsigned char volatile __XDATA *)0xfe87)
#define I2CMSAUX          (*(unsigned char volatile __XDATA *)0xfe88)

#define TM2PS             (*(unsigned char volatile __XDATA *)0xfea2)
#define TM3PS             (*(unsigned char volatile __XDATA *)0xfea3)
#define TM4PS             (*(unsigned char volatile __XDATA *)0xfea4)
#define ADCTIM            (*(unsigned char volatile __XDATA *)0xfea8)

/**
 * suppress xdata space memory overlap
 */
/*
#define PWM1_ETRPS        (*(unsigned char volatile __XDATA *)0xfeb0)
#define PWM1_ENO          (*(unsigned char volatile __XDATA *)0xfeb1)
#define PWM1_PS           (*(unsigned char volatile __XDATA *)0xfeb2)
#define PWM1_IOAUX        (*(unsigned char volatile __XDATA *)0xfeb3)
#define PWM2_ETRPS        (*(unsigned char volatile __XDATA *)0xfeb4)
#define PWM2_ENO          (*(unsigned char volatile __XDATA *)0xfeb5)
#define PWM2_PS           (*(unsigned char volatile __XDATA *)0xfeb6)
#define PWM2_IOAUX        (*(unsigned char volatile __XDATA *)0xfeb7)
#define PWM1_CR1          (*(unsigned char volatile __XDATA *)0xfec0)
#define PWM1_CR2          (*(unsigned char volatile __XDATA *)0xfec1)
#define PWM1_SMCR         (*(unsigned char volatile __XDATA *)0xfec2)
#define PWM1_ETR          (*(unsigned char volatile __XDATA *)0xfec3)
#define PWM1_IER          (*(unsigned char volatile __XDATA *)0xfec4)
#define PWM1_SR1          (*(unsigned char volatile __XDATA *)0xfec5)
#define PWM1_SR2          (*(unsigned char volatile __XDATA *)0xfec6)
#define PWM1_EGR          (*(unsigned char volatile __XDATA *)0xfec7)
#define PWM1_CCMR1        (*(unsigned char volatile __XDATA *)0xfec8)
#define PWM1_CCMR2        (*(unsigned char volatile __XDATA *)0xfec9)
#define PWM1_CCMR3        (*(unsigned char volatile __XDATA *)0xfeca)
#define PWM1_CCMR4        (*(unsigned char volatile __XDATA *)0xfecb)
#define PWM1_CCER1        (*(unsigned char volatile __XDATA *)0xfecc)
#define PWM1_CCER2        (*(unsigned char volatile __XDATA *)0xfecd)

#define PWM1_CNTRH        (*(unsigned char volatile __XDATA *)0xfece)
#define PWM1_CNTRL        (*(unsigned char volatile __XDATA *)0xfecf)

#define PWM1_PSCRH        (*(unsigned char volatile __XDATA *)0xfed0)
#define PWM1_PSCRL        (*(unsigned char volatile __XDATA *)0xfed1)

#define PWM1_ARRH         (*(unsigned char volatile __XDATA *)0xfed2)
#define PWM1_ARRL         (*(unsigned char volatile __XDATA *)0xfed3)
#define PWM1_RCR          (*(unsigned char volatile __XDATA *)0xfed4)

#define PWM1_CCR1H        (*(unsigned char volatile __XDATA *)0xfed5)
#define PWM1_CCR1L        (*(unsigned char volatile __XDATA *)0xfed6)

#define PWM1_CCR2H        (*(unsigned char volatile __XDATA *)0xfed7)
#define PWM1_CCR2L        (*(unsigned char volatile __XDATA *)0xfed8)

#define PWM1_CCR3H        (*(unsigned char volatile __XDATA *)0xfed9)
#define PWM1_CCR3L        (*(unsigned char volatile __XDATA *)0xfeda)

#define PWM1_CCR4H        (*(unsigned char volatile __XDATA *)0xfedb)
#define PWM1_CCR4L        (*(unsigned char volatile __XDATA *)0xfedc)
#define PWM1_BKR          (*(unsigned char volatile __XDATA *)0xfedd)
#define PWM1_DTR          (*(unsigned char volatile __XDATA *)0xfede)
#define PWM1_OISR         (*(unsigned char volatile __XDATA *)0xfedf)
#define PWM2_CR1          (*(unsigned char volatile __XDATA *)0xfee0)
#define PWM2_CR2          (*(unsigned char volatile __XDATA *)0xfee1)
#define PWM2_SMCR         (*(unsigned char volatile __XDATA *)0xfee2)
#define PWM2_ETR          (*(unsigned char volatile __XDATA *)0xfee3)
#define PWM2_IER          (*(unsigned char volatile __XDATA *)0xfee4)
#define PWM2_SR1          (*(unsigned char volatile __XDATA *)0xfee5)
#define PWM2_SR2          (*(unsigned char volatile __XDATA *)0xfee6)
#define PWM2_EGR          (*(unsigned char volatile __XDATA *)0xfee7)
#define PWM2_CCMR1        (*(unsigned char volatile __XDATA *)0xfee8)
#define PWM2_CCMR2        (*(unsigned char volatile __XDATA *)0xfee9)
#define PWM2_CCMR3        (*(unsigned char volatile __XDATA *)0xfeea)
#define PWM2_CCMR4        (*(unsigned char volatile __XDATA *)0xfeeb)
#define PWM2_CCER1        (*(unsigned char volatile __XDATA *)0xfeec)
#define PWM2_CCER2        (*(unsigned char volatile __XDATA *)0xfeed)

#define PWM2_CNTRH        (*(unsigned char volatile __XDATA *)0xfeee)
#define PWM2_CNTRL        (*(unsigned char volatile __XDATA *)0xfeef)

#define PWM2_PSCRH        (*(unsigned char volatile __XDATA *)0xfef0)
#define PWM2_PSCRL        (*(unsigned char volatile __XDATA *)0xfef1)

#define PWM2_ARRH         (*(unsigned char volatile __XDATA *)0xfef2)
#define PWM2_ARRL         (*(unsigned char volatile __XDATA *)0xfef3)
#define PWM2_RCR          (*(unsigned char volatile __XDATA *)0xfef4)

#define PWM2_CCR1H        (*(unsigned char volatile __XDATA *)0xfef5)
#define PWM2_CCR1L        (*(unsigned char volatile __XDATA *)0xfef6)

#define PWM2_CCR2H        (*(unsigned char volatile __XDATA *)0xfef7)
#define PWM2_CCR2L        (*(unsigned char volatile __XDATA *)0xfef8)

#define PWM2_CCR3H        (*(unsigned char volatile __XDATA *)0xfef9)
#define PWM2_CCR3L        (*(unsigned char volatile __XDATA *)0xfefa)

#define PWM2_CCR4H        (*(unsigned char volatile __XDATA *)0xfefb)
#define PWM2_CCR4L        (*(unsigned char volatile __XDATA *)0xfefc)
#define PWM2_BKR          (*(unsigned char volatile __XDATA *)0xfefd)
#define PWM2_DTR          (*(unsigned char volatile __XDATA *)0xfefe)
#define PWM2_OISR         (*(unsigned char volatile __XDATA *)0xfeff)

#if defined __CX51__
#define PWM1_CNTR         (*(unsigned int  volatile __XDATA *)0xfece)
#define PWM1_PSCR         (*(unsigned int  volatile __XDATA *)0xfed0)
#define PWM1_ARR          (*(unsigned int  volatile __XDATA *)0xfed2)
#define PWM1_CCR1         (*(unsigned int  volatile __XDATA *)0xfed5)
#define PWM1_CCR2         (*(unsigned int  volatile __XDATA *)0xfed7)
#define PWM1_CCR3         (*(unsigned int  volatile __XDATA *)0xfed9)
#define PWM1_CCR4         (*(unsigned int  volatile __XDATA *)0xfedb)
#define PWM2_CNTR         (*(unsigned int  volatile __XDATA *)0xfeee)
#define PWM2_PSCR         (*(unsigned int  volatile __XDATA *)0xfef0)
#define PWM2_ARR          (*(unsigned int  volatile __XDATA *)0xfef2)
#define PWM2_CCR1         (*(unsigned int  volatile __XDATA *)0xfef5)
#define PWM2_CCR2         (*(unsigned int  volatile __XDATA *)0xfef7)
#define PWM2_CCR3         (*(unsigned int  volatile __XDATA *)0xfef9)
#define PWM2_CCR4         (*(unsigned int  volatile __XDATA *)0xfefb)
#endif

*/

#define PWMA_ETRPS        (*(unsigned char volatile __XDATA *)0xfeb0)
#define PWMA_ENO          (*(unsigned char volatile __XDATA *)0xfeb1)
#define PWMA_PS           (*(unsigned char volatile __XDATA *)0xfeb2)
#define PWMA_IOAUX        (*(unsigned char volatile __XDATA *)0xfeb3)
#define PWMB_ETRPS        (*(unsigned char volatile __XDATA *)0xfeb4)
#define PWMB_ENO          (*(unsigned char volatile __XDATA *)0xfeb5)
#define PWMB_PS           (*(unsigned char volatile __XDATA *)0xfeb6)
#define PWMB_IOAUX        (*(unsigned char volatile __XDATA *)0xfeb7)
#define PWMA_CR1          (*(unsigned char volatile __XDATA *)0xfec0)
#define PWMA_CR2          (*(unsigned char volatile __XDATA *)0xfec1)
#define PWMA_SMCR         (*(unsigned char volatile __XDATA *)0xfec2)
#define PWMA_ETR          (*(unsigned char volatile __XDATA *)0xfec3)
#define PWMA_IER          (*(unsigned char volatile __XDATA *)0xfec4)
#define PWMA_SR1          (*(unsigned char volatile __XDATA *)0xfec5)
#define PWMA_SR2          (*(unsigned char volatile __XDATA *)0xfec6)
#define PWMA_EGR          (*(unsigned char volatile __XDATA *)0xfec7)
#define PWMA_CCMRx                                            0xfec8
#define PWMA_CCMR1        (*(unsigned char volatile __XDATA *)0xfec8)
#define PWMA_CCMR2        (*(unsigned char volatile __XDATA *)0xfec9)
#define PWMA_CCMR3        (*(unsigned char volatile __XDATA *)0xfeca)
#define PWMA_CCMR4        (*(unsigned char volatile __XDATA *)0xfecb)
#define PWMA_CCER1        (*(unsigned char volatile __XDATA *)0xfecc)
#define PWMA_CCER2        (*(unsigned char volatile __XDATA *)0xfecd)

#define PWMA_CNTRH        (*(unsigned char volatile __XDATA *)0xfece)
#define PWMA_CNTRL        (*(unsigned char volatile __XDATA *)0xfecf)

#define PWMA_PSCRH        (*(unsigned char volatile __XDATA *)0xfed0)
#define PWMA_PSCRL        (*(unsigned char volatile __XDATA *)0xfed1)

#define PWMA_ARRH         (*(unsigned char volatile __XDATA *)0xfed2)
#define PWMA_ARRL         (*(unsigned char volatile __XDATA *)0xfed3)
#define PWMA_RCR          (*(unsigned char volatile __XDATA *)0xfed4)

#define PWMA_CCR1H        (*(unsigned char volatile __XDATA *)0xfed5)
#define PWMA_CCR1L        (*(unsigned char volatile __XDATA *)0xfed6)

#define PWMA_CCR2H        (*(unsigned char volatile __XDATA *)0xfed7)
#define PWMA_CCR2L        (*(unsigned char volatile __XDATA *)0xfed8)

#define PWMA_CCR3H        (*(unsigned char volatile __XDATA *)0xfed9)
#define PWMA_CCR3L        (*(unsigned char volatile __XDATA *)0xfeda)

#define PWMA_CCR4H        (*(unsigned char volatile __XDATA *)0xfedb)
#define PWMA_CCR4L        (*(unsigned char volatile __XDATA *)0xfedc)
#define PWMA_BKR          (*(unsigned char volatile __XDATA *)0xfedd)
#define PWMA_DTR          (*(unsigned char volatile __XDATA *)0xfede)
#define PWMA_OISR         (*(unsigned char volatile __XDATA *)0xfedf)
#define PWMB_CR1          (*(unsigned char volatile __XDATA *)0xfee0)
#define PWMB_CR2          (*(unsigned char volatile __XDATA *)0xfee1)
#define PWMB_SMCR         (*(unsigned char volatile __XDATA *)0xfee2)
#define PWMB_ETR          (*(unsigned char volatile __XDATA *)0xfee3)
#define PWMB_IER          (*(unsigned char volatile __XDATA *)0xfee4)
#define PWMB_SR1          (*(unsigned char volatile __XDATA *)0xfee5)
#define PWMB_SR2          (*(unsigned char volatile __XDATA *)0xfee6)
#define PWMB_EGR          (*(unsigned char volatile __XDATA *)0xfee7)
#define PWMB_CCMRx                                            0xfee8
#define PWMB_CCMR1        (*(unsigned char volatile __XDATA *)0xfee8)
#define PWMB_CCMR2        (*(unsigned char volatile __XDATA *)0xfee9)
#define PWMB_CCMR3        (*(unsigned char volatile __XDATA *)0xfeea)
#define PWMB_CCMR4        (*(unsigned char volatile __XDATA *)0xfeeb)
#define PWMB_CCER1        (*(unsigned char volatile __XDATA *)0xfeec)
#define PWMB_CCER2        (*(unsigned char volatile __XDATA *)0xfeed)

#define PWMB_CNTRH        (*(unsigned char volatile __XDATA *)0xfeee)
#define PWMB_CNTRL        (*(unsigned char volatile __XDATA *)0xfeef)

#define PWMB_PSCRH        (*(unsigned char volatile __XDATA *)0xfef0)
#define PWMB_PSCRL        (*(unsigned char volatile __XDATA *)0xfef1)

#define PWMB_ARRH         (*(unsigned char volatile __XDATA *)0xfef2)
#define PWMB_ARRL         (*(unsigned char volatile __XDATA *)0xfef3)
#define PWMB_RCR          (*(unsigned char volatile __XDATA *)0xfef4)

#define PWMB_CCR5H        (*(unsigned char volatile __XDATA *)0xfef5)
#define PWMB_CCR5L        (*(unsigned char volatile __XDATA *)0xfef6)

#define PWMB_CCR6H        (*(unsigned char volatile __XDATA *)0xfef7)
#define PWMB_CCR6L        (*(unsigned char volatile __XDATA *)0xfef8)

#define PWMB_CCR7H        (*(unsigned char volatile __XDATA *)0xfef9)
#define PWMB_CCR7L        (*(unsigned char volatile __XDATA *)0xfefa)

#define PWMB_CCR8H        (*(unsigned char volatile __XDATA *)0xfefb)
#define PWMB_CCR8L        (*(unsigned char volatile __XDATA *)0xfefc)
#define PWMB_BKR          (*(unsigned char volatile __XDATA *)0xfefd)
#define PWMB_DTR          (*(unsigned char volatile __XDATA *)0xfefe)
#define PWMB_OISR         (*(unsigned char volatile __XDATA *)0xfeff)


/////////////////////////////////////////////////
//FD00H-FDFFH
/////////////////////////////////////////////////

#define PxINTE                                                0xfd00
#define P0INTE            (*(unsigned char volatile __XDATA *)0xfd00)
#define P1INTE            (*(unsigned char volatile __XDATA *)0xfd01)
#define P2INTE            (*(unsigned char volatile __XDATA *)0xfd02)
#define P3INTE            (*(unsigned char volatile __XDATA *)0xfd03)
#define P4INTE            (*(unsigned char volatile __XDATA *)0xfd04)
#define P5INTE            (*(unsigned char volatile __XDATA *)0xfd05)
#define P6INTE            (*(unsigned char volatile __XDATA *)0xfd06)
#define P7INTE            (*(unsigned char volatile __XDATA *)0xfd07)
#define P0INTF            (*(unsigned char volatile __XDATA *)0xfd10)
#define P1INTF            (*(unsigned char volatile __XDATA *)0xfd11)
#define P2INTF            (*(unsigned char volatile __XDATA *)0xfd12)
#define P3INTF            (*(unsigned char volatile __XDATA *)0xfd13)
#define P4INTF            (*(unsigned char volatile __XDATA *)0xfd14)
#define P5INTF            (*(unsigned char volatile __XDATA *)0xfd15)
#define P6INTF            (*(unsigned char volatile __XDATA *)0xfd16)
#define P7INTF            (*(unsigned char volatile __XDATA *)0xfd17)
#define PxIM0                                                 0xfd20
#define P0IM0             (*(unsigned char volatile __XDATA *)0xfd20)
#define P1IM0             (*(unsigned char volatile __XDATA *)0xfd21)
#define P2IM0             (*(unsigned char volatile __XDATA *)0xfd22)
#define P3IM0             (*(unsigned char volatile __XDATA *)0xfd23)
#define P4IM0             (*(unsigned char volatile __XDATA *)0xfd24)
#define P5IM0             (*(unsigned char volatile __XDATA *)0xfd25)
#define P6IM0             (*(unsigned char volatile __XDATA *)0xfd26)
#define P7IM0             (*(unsigned char volatile __XDATA *)0xfd27)
#define PxIM1                                                 0xfd30
#define P0IM1             (*(unsigned char volatile __XDATA *)0xfd30)
#define P1IM1             (*(unsigned char volatile __XDATA *)0xfd31)
#define P2IM1             (*(unsigned char volatile __XDATA *)0xfd32)
#define P3IM1             (*(unsigned char volatile __XDATA *)0xfd33)
#define P4IM1             (*(unsigned char volatile __XDATA *)0xfd34)
#define P5IM1             (*(unsigned char volatile __XDATA *)0xfd35)
#define P6IM1             (*(unsigned char volatile __XDATA *)0xfd36)
#define P7IM1             (*(unsigned char volatile __XDATA *)0xfd37)
#define P0WKUE            (*(unsigned char volatile __XDATA *)0xfd40)
#define P1WKUE            (*(unsigned char volatile __XDATA *)0xfd41)
#define P2WKUE            (*(unsigned char volatile __XDATA *)0xfd42)
#define P3WKUE            (*(unsigned char volatile __XDATA *)0xfd43)
#define P4WKUE            (*(unsigned char volatile __XDATA *)0xfd44)
#define P5WKUE            (*(unsigned char volatile __XDATA *)0xfd45)
#define P6WKUE            (*(unsigned char volatile __XDATA *)0xfd46)
#define P7WKUE            (*(unsigned char volatile __XDATA *)0xfd47)
#define PIN_IP            (*(unsigned char volatile __XDATA *)0xfd60)
#define PIN_IPH           (*(unsigned char volatile __XDATA *)0xfd61)
#define CHIPIDxx                                              0xfde0
#define CHIPID00          (*(unsigned char volatile __XDATA *)0xfde0)

/////////////////////////////////////////////////
//FC00H-FCFFH
/////////////////////////////////////////////////

#define MD3               (*(unsigned char volatile __XDATA *)0xfcf0)
#define MD2               (*(unsigned char volatile __XDATA *)0xfcf1)
#define MD1               (*(unsigned char volatile __XDATA *)0xfcf2)
#define MD0               (*(unsigned char volatile __XDATA *)0xfcf3)
#define MD5               (*(unsigned char volatile __XDATA *)0xfcf4)
#define MD4               (*(unsigned char volatile __XDATA *)0xfcf5)
#define ARCON             (*(unsigned char volatile __XDATA *)0xfcf6)
#define OPCON             (*(unsigned char volatile __XDATA *)0xfcf7)

/////////////////////////////////////////////////
//FB00H-FBFFH
/////////////////////////////////////////////////

#define COMEN             (*(unsigned char volatile __XDATA *)0xfb00)
#define SEGENL            (*(unsigned char volatile __XDATA *)0xfb01)
#define SEGENH            (*(unsigned char volatile __XDATA *)0xfb02)
#define LEDCTRL           (*(unsigned char volatile __XDATA *)0xfb03)
#define LEDCKS            (*(unsigned char volatile __XDATA *)0xfb04)
#define COM0_DA_L         (*(unsigned char volatile __XDATA *)0xfb10)
#define COM1_DA_L         (*(unsigned char volatile __XDATA *)0xfb11)
#define COM2_DA_L         (*(unsigned char volatile __XDATA *)0xfb12)
#define COM3_DA_L         (*(unsigned char volatile __XDATA *)0xfb13)
#define COM4_DA_L         (*(unsigned char volatile __XDATA *)0xfb14)
#define COM5_DA_L         (*(unsigned char volatile __XDATA *)0xfb15)
#define COM6_DA_L         (*(unsigned char volatile __XDATA *)0xfb16)
#define COM7_DA_L         (*(unsigned char volatile __XDATA *)0xfb17)
#define COM0_DA_H         (*(unsigned char volatile __XDATA *)0xfb18)
#define COM1_DA_H         (*(unsigned char volatile __XDATA *)0xfb19)
#define COM2_DA_H         (*(unsigned char volatile __XDATA *)0xfb1a)
#define COM3_DA_H         (*(unsigned char volatile __XDATA *)0xfb1b)
#define COM4_DA_H         (*(unsigned char volatile __XDATA *)0xfb1c)
#define COM5_DA_H         (*(unsigned char volatile __XDATA *)0xfb1d)
#define COM6_DA_H         (*(unsigned char volatile __XDATA *)0xfb1e)
#define COM7_DA_H         (*(unsigned char volatile __XDATA *)0xfb1f)
#define COM0_DC_L         (*(unsigned char volatile __XDATA *)0xfb20)
#define COM1_DC_L         (*(unsigned char volatile __XDATA *)0xfb21)
#define COM2_DC_L         (*(unsigned char volatile __XDATA *)0xfb22)
#define COM3_DC_L         (*(unsigned char volatile __XDATA *)0xfb23)
#define COM4_DC_L         (*(unsigned char volatile __XDATA *)0xfb24)
#define COM5_DC_L         (*(unsigned char volatile __XDATA *)0xfb25)
#define COM6_DC_L         (*(unsigned char volatile __XDATA *)0xfb26)
#define COM7_DC_L         (*(unsigned char volatile __XDATA *)0xfb27)
#define COM0_DC_H         (*(unsigned char volatile __XDATA *)0xfb28)
#define COM1_DC_H         (*(unsigned char volatile __XDATA *)0xfb29)
#define COM2_DC_H         (*(unsigned char volatile __XDATA *)0xfb2a)
#define COM3_DC_H         (*(unsigned char volatile __XDATA *)0xfb2b)
#define COM4_DC_H         (*(unsigned char volatile __XDATA *)0xfb2c)
#define COM5_DC_H         (*(unsigned char volatile __XDATA *)0xfb2d)
#define COM6_DC_H         (*(unsigned char volatile __XDATA *)0xfb2e)
#define COM7_DC_H         (*(unsigned char volatile __XDATA *)0xfb2f)

#define TSCHEN1           (*(unsigned char volatile __XDATA *)0xfb40)
#define TSCHEN2           (*(unsigned char volatile __XDATA *)0xfb41)
#define TSCFG1            (*(unsigned char volatile __XDATA *)0xfb42)
#define TSCFG2            (*(unsigned char volatile __XDATA *)0xfb43)
#define TSWUTC            (*(unsigned char volatile __XDATA *)0xfb44)
#define TSCTRL            (*(unsigned char volatile __XDATA *)0xfb45)
#define TSSTA1            (*(unsigned char volatile __XDATA *)0xfb46)
#define TSSTA2            (*(unsigned char volatile __XDATA *)0xfb47)
#define TSRT              (*(unsigned char volatile __XDATA *)0xfb48)

#define TSDATH            (*(unsigned char volatile __XDATA *)0xfb49)
#define TSDATL            (*(unsigned char volatile __XDATA *)0xfb4A)

#define TSTH00H           (*(unsigned char volatile __XDATA *)0xfb50)
#define TSTH00L           (*(unsigned char volatile __XDATA *)0xfb51)

#define TSTH01H           (*(unsigned char volatile __XDATA *)0xfb52)
#define TSTH01L           (*(unsigned char volatile __XDATA *)0xfb53)

#define TSTH02H           (*(unsigned char volatile __XDATA *)0xfb54)
#define TSTH02L           (*(unsigned char volatile __XDATA *)0xfb55)

#define TSTH03H           (*(unsigned char volatile __XDATA *)0xfb56)
#define TSTH03L           (*(unsigned char volatile __XDATA *)0xfb57)

#define TSTH04H           (*(unsigned char volatile __XDATA *)0xfb58)
#define TSTH04L           (*(unsigned char volatile __XDATA *)0xfb59)

#define TSTH05H           (*(unsigned char volatile __XDATA *)0xfb5a)
#define TSTH05L           (*(unsigned char volatile __XDATA *)0xfb5b)

#define TSTH06H           (*(unsigned char volatile __XDATA *)0xfb5c)
#define TSTH06L           (*(unsigned char volatile __XDATA *)0xfb5d)

#define TSTH07H           (*(unsigned char volatile __XDATA *)0xfb5e)
#define TSTH07L           (*(unsigned char volatile __XDATA *)0xfb5f)

#define TSTH08H           (*(unsigned char volatile __XDATA *)0xfb60)
#define TSTH08L           (*(unsigned char volatile __XDATA *)0xfb61)

#define TSTH09H           (*(unsigned char volatile __XDATA *)0xfb62)
#define TSTH09L           (*(unsigned char volatile __XDATA *)0xfb63)

#define TSTH10H           (*(unsigned char volatile __XDATA *)0xfb64)
#define TSTH10L           (*(unsigned char volatile __XDATA *)0xfb65)

#define TSTH11H           (*(unsigned char volatile __XDATA *)0xfb66)
#define TSTH11L           (*(unsigned char volatile __XDATA *)0xfb67)

#define TSTH12H           (*(unsigned char volatile __XDATA *)0xfb68)
#define TSTH12L           (*(unsigned char volatile __XDATA *)0xfb69)

#define TSTH13H           (*(unsigned char volatile __XDATA *)0xfb6a)
#define TSTH13L           (*(unsigned char volatile __XDATA *)0xfb6b)

#define TSTH14H           (*(unsigned char volatile __XDATA *)0xfb6c)
#define TSTH14L           (*(unsigned char volatile __XDATA *)0xfb6d)

#define TSTH15H           (*(unsigned char volatile __XDATA *)0xfb6e)
#define TSTH15L           (*(unsigned char volatile __XDATA *)0xfb6f)

/////////////////////////////////////////////////
//FA00H-FAFFH
/////////////////////////////////////////////////

#define DMA_M2M_CFG       (*(unsigned char volatile __XDATA *)0xfa00)
#define DMA_M2M_CR        (*(unsigned char volatile __XDATA *)0xfa01)
#define DMA_M2M_STA       (*(unsigned char volatile __XDATA *)0xfa02)
#define DMA_M2M_AMT       (*(unsigned char volatile __XDATA *)0xfa03)
#define DMA_M2M_DONE      (*(unsigned char volatile __XDATA *)0xfa04)
#define DMA_M2M_TXAH      (*(unsigned char volatile __XDATA *)0xfa05)
#define DMA_M2M_TXAL      (*(unsigned char volatile __XDATA *)0xfa06)
#define DMA_M2M_RXAH      (*(unsigned char volatile __XDATA *)0xfa07)
#define DMA_M2M_RXAL      (*(unsigned char volatile __XDATA *)0xfa08)

#define DMA_ADC_CFG       (*(unsigned char volatile __XDATA *)0xfa10)
#define DMA_ADC_CR        (*(unsigned char volatile __XDATA *)0xfa11)
#define DMA_ADC_STA       (*(unsigned char volatile __XDATA *)0xfa12)
#define DMA_ADC_RXAH      (*(unsigned char volatile __XDATA *)0xfa17)
#define DMA_ADC_RXAL      (*(unsigned char volatile __XDATA *)0xfa18)
#define DMA_ADC_CFG2      (*(unsigned char volatile __XDATA *)0xfa19)
#define DMA_ADC_CHSW0     (*(unsigned char volatile __XDATA *)0xfa1a)
#define DMA_ADC_CHSW1     (*(unsigned char volatile __XDATA *)0xfa1b)

#define DMA_SPI_CFG       (*(unsigned char volatile __XDATA *)0xfa20)
#define DMA_SPI_CR        (*(unsigned char volatile __XDATA *)0xfa21)
#define DMA_SPI_STA       (*(unsigned char volatile __XDATA *)0xfa22)
#define DMA_SPI_AMT       (*(unsigned char volatile __XDATA *)0xfa23)
#define DMA_SPI_DONE      (*(unsigned char volatile __XDATA *)0xfa24)
#define DMA_SPI_TXAH      (*(unsigned char volatile __XDATA *)0xfa25)
#define DMA_SPI_TXAL      (*(unsigned char volatile __XDATA *)0xfa26)
#define DMA_SPI_RXAH      (*(unsigned char volatile __XDATA *)0xfa27)
#define DMA_SPI_RXAL      (*(unsigned char volatile __XDATA *)0xfa28)
#define DMA_SPI_CFG2      (*(unsigned char volatile __XDATA *)0xfa29)

#define DMA_UR1T_CFG      (*(unsigned char volatile __XDATA *)0xfa30)
#define DMA_UR1T_CR       (*(unsigned char volatile __XDATA *)0xfa31)
#define DMA_UR1T_STA      (*(unsigned char volatile __XDATA *)0xfa32)
#define DMA_UR1T_AMT      (*(unsigned char volatile __XDATA *)0xfa33)
#define DMA_UR1T_DONE     (*(unsigned char volatile __XDATA *)0xfa34)
#define DMA_UR1T_TXAH     (*(unsigned char volatile __XDATA *)0xfa35)
#define DMA_UR1T_TXAL     (*(unsigned char volatile __XDATA *)0xfa36)
#define DMA_UR1R_CFG      (*(unsigned char volatile __XDATA *)0xfa38)
#define DMA_UR1R_CR       (*(unsigned char volatile __XDATA *)0xfa39)
#define DMA_UR1R_STA      (*(unsigned char volatile __XDATA *)0xfa3a)
#define DMA_UR1R_AMT      (*(unsigned char volatile __XDATA *)0xfa3b)
#define DMA_UR1R_DONE     (*(unsigned char volatile __XDATA *)0xfa3c)
#define DMA_UR1R_RXAH     (*(unsigned char volatile __XDATA *)0xfa3d)
#define DMA_UR1R_RXAL     (*(unsigned char volatile __XDATA *)0xfa3e)

#define DMA_UR2T_CFG      (*(unsigned char volatile __XDATA *)0xfa40)
#define DMA_UR2T_CR       (*(unsigned char volatile __XDATA *)0xfa41)
#define DMA_UR2T_STA      (*(unsigned char volatile __XDATA *)0xfa42)
#define DMA_UR2T_AMT      (*(unsigned char volatile __XDATA *)0xfa43)
#define DMA_UR2T_DONE     (*(unsigned char volatile __XDATA *)0xfa44)
#define DMA_UR2T_TXAH     (*(unsigned char volatile __XDATA *)0xfa45)
#define DMA_UR2T_TXAL     (*(unsigned char volatile __XDATA *)0xfa46)
#define DMA_UR2R_CFG      (*(unsigned char volatile __XDATA *)0xfa48)
#define DMA_UR2R_CR       (*(unsigned char volatile __XDATA *)0xfa49)
#define DMA_UR2R_STA      (*(unsigned char volatile __XDATA *)0xfa4a)
#define DMA_UR2R_AMT      (*(unsigned char volatile __XDATA *)0xfa4b)
#define DMA_UR2R_DONE     (*(unsigned char volatile __XDATA *)0xfa4c)
#define DMA_UR2R_RXAH     (*(unsigned char volatile __XDATA *)0xfa4d)
#define DMA_UR2R_RXAL     (*(unsigned char volatile __XDATA *)0xfa4e)

#define DMA_UR3T_CFG      (*(unsigned char volatile __XDATA *)0xfa50)
#define DMA_UR3T_CR       (*(unsigned char volatile __XDATA *)0xfa51)
#define DMA_UR3T_STA      (*(unsigned char volatile __XDATA *)0xfa52)
#define DMA_UR3T_AMT      (*(unsigned char volatile __XDATA *)0xfa53)
#define DMA_UR3T_DONE     (*(unsigned char volatile __XDATA *)0xfa54)
#define DMA_UR3T_TXAH     (*(unsigned char volatile __XDATA *)0xfa55)
#define DMA_UR3T_TXAL     (*(unsigned char volatile __XDATA *)0xfa56)
#define DMA_UR3R_CFG      (*(unsigned char volatile __XDATA *)0xfa58)
#define DMA_UR3R_CR       (*(unsigned char volatile __XDATA *)0xfa59)
#define DMA_UR3R_STA      (*(unsigned char volatile __XDATA *)0xfa5a)
#define DMA_UR3R_AMT      (*(unsigned char volatile __XDATA *)0xfa5b)
#define DMA_UR3R_DONE     (*(unsigned char volatile __XDATA *)0xfa5c)
#define DMA_UR3R_RXAH     (*(unsigned char volatile __XDATA *)0xfa5d)
#define DMA_UR3R_RXAL     (*(unsigned char volatile __XDATA *)0xfa5e)

#define DMA_UR4T_CFG      (*(unsigned char volatile __XDATA *)0xfa60)
#define DMA_UR4T_CR       (*(unsigned char volatile __XDATA *)0xfa61)
#define DMA_UR4T_STA      (*(unsigned char volatile __XDATA *)0xfa62)
#define DMA_UR4T_AMT      (*(unsigned char volatile __XDATA *)0xfa63)
#define DMA_UR4T_DONE     (*(unsigned char volatile __XDATA *)0xfa64)
#define DMA_UR4T_TXAH     (*(unsigned char volatile __XDATA *)0xfa65)
#define DMA_UR4T_TXAL     (*(unsigned char volatile __XDATA *)0xfa66)
#define DMA_UR4R_CFG      (*(unsigned char volatile __XDATA *)0xfa68)
#define DMA_UR4R_CR       (*(unsigned char volatile __XDATA *)0xfa69)
#define DMA_UR4R_STA      (*(unsigned char volatile __XDATA *)0xfa6a)
#define DMA_UR4R_AMT      (*(unsigned char volatile __XDATA *)0xfa6b)
#define DMA_UR4R_DONE     (*(unsigned char volatile __XDATA *)0xfa6c)
#define DMA_UR4R_RXAH     (*(unsigned char volatile __XDATA *)0xfa6d)
#define DMA_UR4R_RXAL     (*(unsigned char volatile __XDATA *)0xfa6e)

#define DMA_LCM_CFG       (*(unsigned char volatile __XDATA *)0xfa70)
#define DMA_LCM_CR        (*(unsigned char volatile __XDATA *)0xfa71)
#define DMA_LCM_STA       (*(unsigned char volatile __XDATA *)0xfa72)
#define DMA_LCM_AMT       (*(unsigned char volatile __XDATA *)0xfa73)
#define DMA_LCM_DONE      (*(unsigned char volatile __XDATA *)0xfa74)
#define DMA_LCM_TXAH      (*(unsigned char volatile __XDATA *)0xfa75)
#define DMA_LCM_TXAL      (*(unsigned char volatile __XDATA *)0xfa76)
#define DMA_LCM_RXAH      (*(unsigned char volatile __XDATA *)0xfa77)
#define DMA_LCM_RXAL      (*(unsigned char volatile __XDATA *)0xfa78)

#if defined __CX51__

#define PWMA_CNTR         (*(unsigned int  volatile __XDATA *)0xfece)
#define PWMA_PSCR         (*(unsigned int  volatile __XDATA *)0xfed0)
#define PWMA_ARR          (*(unsigned int  volatile __XDATA *)0xfed2)
#define PWMA_CCR1         (*(unsigned int  volatile __XDATA *)0xfed5)
#define PWMA_CCR2         (*(unsigned int  volatile __XDATA *)0xfed7)
#define PWMA_CCR3         (*(unsigned int  volatile __XDATA *)0xfed9)
#define PWMA_CCR4         (*(unsigned int  volatile __XDATA *)0xfedb)
#define PWMB_CNTR         (*(unsigned int  volatile __XDATA *)0xfeee)
#define PWMB_PSCR         (*(unsigned int  volatile __XDATA *)0xfef0)
#define PWMB_ARR          (*(unsigned int  volatile __XDATA *)0xfef2)
#define PWMB_CCR5         (*(unsigned int  volatile __XDATA *)0xfef5)
#define PWMB_CCR6         (*(unsigned int  volatile __XDATA *)0xfef7)
#define PWMB_CCR7         (*(unsigned int  volatile __XDATA *)0xfef9)
#define PWMB_CCR8         (*(unsigned int  volatile __XDATA *)0xfefb)
#define TSDAT             (*(unsigned int  volatile __XDATA *)0xfb49)
#define TSTH00            (*(unsigned int  volatile __XDATA *)0xfb50)
#define TSTH01            (*(unsigned int  volatile __XDATA *)0xfb52)
#define TSTH02            (*(unsigned int  volatile __XDATA *)0xfb54)
#define TSTH03            (*(unsigned int  volatile __XDATA *)0xfb56)
#define TSTH04            (*(unsigned int  volatile __XDATA *)0xfb58)
#define TSTH05            (*(unsigned int  volatile __XDATA *)0xfb5a)
#define TSTH06            (*(unsigned int  volatile __XDATA *)0xfb5c)
#define TSTH07            (*(unsigned int  volatile __XDATA *)0xfb5e)
#define TSTH08            (*(unsigned int  volatile __XDATA *)0xfb60)
#define TSTH09            (*(unsigned int  volatile __XDATA *)0xfb62)
#define TSTH10            (*(unsigned int  volatile __XDATA *)0xfb64)
#define TSTH11            (*(unsigned int  volatile __XDATA *)0xfb66)
#define TSTH12            (*(unsigned int  volatile __XDATA *)0xfb68)
#define TSTH13            (*(unsigned int  volatile __XDATA *)0xfb6a)
#define TSTH14            (*(unsigned int  volatile __XDATA *)0xfb6c)
#define TSTH15            (*(unsigned int  volatile __XDATA *)0xfb6e)

#endif
/////////////////////////////////////////////////

#endif
