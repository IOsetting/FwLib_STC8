#ifndef __FW_REG_STC8A8K64D4_H__
#define __FW_REG_STC8A8K64D4_H__

#include "fw_reg_base.h"

SFR(VOCTRL,             0xBB);

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
SFR(PWMCFG,             0xF6);


SFR(CH,                 0xF9);
SFR(CCAP0H,             0xFA);
SFR(CCAP1H,             0xFB);
SFR(CCAP2H,             0xFC);

SFR(RSTCFG,             0xFF);

/**
 * Set B7 of P_SW2 before read/write the following registers
*/

/////////////////////////////////////////////////
//FF00H-FFFFH
/////////////////////////////////////////////////


#define     PWMCH       (*(unsigned char volatile __XDATA *)0xff00)
#define     PWMCL       (*(unsigned char volatile __XDATA *)0xff01)
#define     PWMCKS      (*(unsigned char volatile __XDATA *)0xff02)

#define     PWMTADCH    (*(unsigned char volatile __XDATA *)0xff03)
#define     PWMTADCL    (*(unsigned char volatile __XDATA *)0xff04)
#define     PWMIF       (*(unsigned char volatile __XDATA *)0xff05)
#define     PWMFDCR     (*(unsigned char volatile __XDATA *)0xff06)
#define     PWMDELSEL   (*(unsigned char volatile __XDATA *)0xff07)

#define     PWM0T1H     (*(unsigned char volatile __XDATA *)0xff10)
#define     PWM0T1L     (*(unsigned char volatile __XDATA *)0xff11)

#define     PWM0T2H     (*(unsigned char volatile __XDATA *)0xff12)
#define     PWM0T2L     (*(unsigned char volatile __XDATA *)0xff13)
#define     PWM0CR      (*(unsigned char volatile __XDATA *)0xff14)
#define     PWM0HLD     (*(unsigned char volatile __XDATA *)0xff15)

#define     PWM1T1H     (*(unsigned char volatile __XDATA *)0xff18)
#define     PWM1T1L     (*(unsigned char volatile __XDATA *)0xff19)

#define     PWM1T2H     (*(unsigned char volatile __XDATA *)0xff1a)
#define     PWM1T2L     (*(unsigned char volatile __XDATA *)0xff1b)
#define     PWM1CR      (*(unsigned char volatile __XDATA *)0xff1c)
#define     PWM1HLD     (*(unsigned char volatile __XDATA *)0xff1d)

#define     PWM2T1H     (*(unsigned char volatile __XDATA *)0xff20)
#define     PWM2T1L     (*(unsigned char volatile __XDATA *)0xff21)

#define     PWM2T2H     (*(unsigned char volatile __XDATA *)0xff22)
#define     PWM2T2L     (*(unsigned char volatile __XDATA *)0xff23)
#define     PWM2CR      (*(unsigned char volatile __XDATA *)0xff24)
#define     PWM2HLD     (*(unsigned char volatile __XDATA *)0xff25)

#define     PWM3T1H     (*(unsigned char volatile __XDATA *)0xff28)
#define     PWM3T1L     (*(unsigned char volatile __XDATA *)0xff29)

#define     PWM3T2H     (*(unsigned char volatile __XDATA *)0xff2a)
#define     PWM3T2L     (*(unsigned char volatile __XDATA *)0xff2b)
#define     PWM3CR      (*(unsigned char volatile __XDATA *)0xff2c)
#define     PWM3HLD     (*(unsigned char volatile __XDATA *)0xff2d)

#define     PWM4T1H     (*(unsigned char volatile __XDATA *)0xff30)
#define     PWM4T1L     (*(unsigned char volatile __XDATA *)0xff31)

#define     PWM4T2H     (*(unsigned char volatile __XDATA *)0xff32)
#define     PWM4T2L     (*(unsigned char volatile __XDATA *)0xff33)
#define     PWM4CR      (*(unsigned char volatile __XDATA *)0xff34)
#define     PWM4HLD     (*(unsigned char volatile __XDATA *)0xff35)

#define     PWM5T1H     (*(unsigned char volatile __XDATA *)0xff38)
#define     PWM5T1L     (*(unsigned char volatile __XDATA *)0xff39)

#define     PWM5T2H     (*(unsigned char volatile __XDATA *)0xff3a)
#define     PWM5T2L     (*(unsigned char volatile __XDATA *)0xff3b)
#define     PWM5CR      (*(unsigned char volatile __XDATA *)0xff3c)
#define     PWM5HLD     (*(unsigned char volatile __XDATA *)0xff3d)

#define     PWM6T1H     (*(unsigned char volatile __XDATA *)0xff40)
#define     PWM6T1L     (*(unsigned char volatile __XDATA *)0xff41)

#define     PWM6T2H     (*(unsigned char volatile __XDATA *)0xff42)
#define     PWM6T2L     (*(unsigned char volatile __XDATA *)0xff43)
#define     PWM6CR      (*(unsigned char volatile __XDATA *)0xff44)
#define     PWM6HLD     (*(unsigned char volatile __XDATA *)0xff45)

#define     PWM7T1H     (*(unsigned char volatile __XDATA *)0xff48)
#define     PWM7T1L     (*(unsigned char volatile __XDATA *)0xff49)

#define     PWM7T2H     (*(unsigned char volatile __XDATA *)0xff4a)
#define     PWM7T2L     (*(unsigned char volatile __XDATA *)0xff4b)
#define     PWM7CR      (*(unsigned char volatile __XDATA *)0xff4c)
#define     PWM7HLD     (*(unsigned char volatile __XDATA *)0xff4d)

/////////////////////////////////////////////////
//FE00H-FEFFH
/////////////////////////////////////////////////

#define     CKSEL       (*(unsigned char volatile __XDATA *)0xfe00)
#define     CLKDIV      (*(unsigned char volatile __XDATA *)0xfe01)
#define     IRC24MCR    (*(unsigned char volatile __XDATA *)0xfe02)
#define     XOSCCR      (*(unsigned char volatile __XDATA *)0xfe03)
#define     IRC32KCR    (*(unsigned char volatile __XDATA *)0xfe04)
#define     MCLKOCR     (*(unsigned char volatile __XDATA *)0xfe05)
#define     IRCDB       (*(unsigned char volatile __XDATA *)0xfe06)
                         
#define     P0PU        (*(unsigned char volatile __XDATA *)0xfe10)
#define     P1PU        (*(unsigned char volatile __XDATA *)0xfe11)
#define     P2PU        (*(unsigned char volatile __XDATA *)0xfe12)
#define     P3PU        (*(unsigned char volatile __XDATA *)0xfe13)
#define     P4PU        (*(unsigned char volatile __XDATA *)0xfe14)
#define     P5PU        (*(unsigned char volatile __XDATA *)0xfe15)
#define     P6PU        (*(unsigned char volatile __XDATA *)0xfe16)
#define     P7PU        (*(unsigned char volatile __XDATA *)0xfe17)
#define     P0NCS       (*(unsigned char volatile __XDATA *)0xfe18)
#define     P1NCS       (*(unsigned char volatile __XDATA *)0xfe19)
#define     P2NCS       (*(unsigned char volatile __XDATA *)0xfe1a)
#define     P3NCS       (*(unsigned char volatile __XDATA *)0xfe1b)
#define     P4NCS       (*(unsigned char volatile __XDATA *)0xfe1c)
#define     P5NCS       (*(unsigned char volatile __XDATA *)0xfe1d)
#define     P6NCS       (*(unsigned char volatile __XDATA *)0xfe1e)
#define     P7NCS       (*(unsigned char volatile __XDATA *)0xfe1f)
#define     P0SR        (*(unsigned char volatile __XDATA *)0xfe20)
#define     P1SR        (*(unsigned char volatile __XDATA *)0xfe21)
#define     P2SR        (*(unsigned char volatile __XDATA *)0xfe22)
#define     P3SR        (*(unsigned char volatile __XDATA *)0xfe23)
#define     P4SR        (*(unsigned char volatile __XDATA *)0xfe24)
#define     P5SR        (*(unsigned char volatile __XDATA *)0xfe25)
#define     P6SR        (*(unsigned char volatile __XDATA *)0xfe26)
#define     P7SR        (*(unsigned char volatile __XDATA *)0xfe27)
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
                        
#define     LCMIFCFG    (*(unsigned char volatile __XDATA *)0xfe50)
#define     LCMIFCFG2   (*(unsigned char volatile __XDATA *)0xfe51)
#define     LCMIFCR     (*(unsigned char volatile __XDATA *)0xfe52)
#define     LCMIFSTA    (*(unsigned char volatile __XDATA *)0xfe53)
#define     LCMIFDATL   (*(unsigned char volatile __XDATA *)0xfe54)
#define     LCMIFDATH   (*(unsigned char volatile __XDATA *)0xfe55)
                        
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
#define     ADCEXCFG    (*(unsigned char volatile __XDATA *)0xfead)
#define     CMPEXCFG    (*(unsigned char volatile __XDATA *)0xfeae)

/////////////////////////////////////////////////
//FD00H-FDFFH
/////////////////////////////////////////////////

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
#define     P0IM0       (*(unsigned char volatile __XDATA *)0xfd20)
#define     P1IM0       (*(unsigned char volatile __XDATA *)0xfd21)
#define     P2IM0       (*(unsigned char volatile __XDATA *)0xfd22)
#define     P3IM0       (*(unsigned char volatile __XDATA *)0xfd23)
#define     P4IM0       (*(unsigned char volatile __XDATA *)0xfd24)
#define     P5IM0       (*(unsigned char volatile __XDATA *)0xfd25)
#define     P6IM0       (*(unsigned char volatile __XDATA *)0xfd26)
#define     P7IM0       (*(unsigned char volatile __XDATA *)0xfd27)
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
                        
#define     CCAPM3      (*(unsigned char volatile __XDATA *)0xfd54)
#define     CCAP3L      (*(unsigned char volatile __XDATA *)0xfd55)
#define     CCAP3H      (*(unsigned char volatile __XDATA *)0xfd56)
#define     PCA_PWM3    (*(unsigned char volatile __XDATA *)0xfd57)
                        
#define     PIN_IP      (*(unsigned char volatile __XDATA *)0xfd60)
#define     PIN_IPH     (*(unsigned char volatile __XDATA *)0xfd61)
                        
#define     CHIPID0     (*(unsigned char volatile __XDATA *)0xfde0)
#define     CHIPID1     (*(unsigned char volatile __XDATA *)0xfde1)
#define     CHIPID2     (*(unsigned char volatile __XDATA *)0xfde2)
#define     CHIPID3     (*(unsigned char volatile __XDATA *)0xfde3)
#define     CHIPID4     (*(unsigned char volatile __XDATA *)0xfde4)
#define     CHIPID5     (*(unsigned char volatile __XDATA *)0xfde5)
#define     CHIPID6     (*(unsigned char volatile __XDATA *)0xfde6)
#define     CHIPID7     (*(unsigned char volatile __XDATA *)0xfde7)
#define     CHIPID8     (*(unsigned char volatile __XDATA *)0xfde8)
#define     CHIPID9     (*(unsigned char volatile __XDATA *)0xfde9)
#define     CHIPID10    (*(unsigned char volatile __XDATA *)0xfdea)
#define     CHIPID11    (*(unsigned char volatile __XDATA *)0xfdeb)
#define     CHIPID12    (*(unsigned char volatile __XDATA *)0xfdec)
#define     CHIPID13    (*(unsigned char volatile __XDATA *)0xfded)
#define     CHIPID14    (*(unsigned char volatile __XDATA *)0xfdee)
#define     CHIPID15    (*(unsigned char volatile __XDATA *)0xfdef)
#define     CHIPID16    (*(unsigned char volatile __XDATA *)0xfdf0)
#define     CHIPID17    (*(unsigned char volatile __XDATA *)0xfdf1)
#define     CHIPID18    (*(unsigned char volatile __XDATA *)0xfdf2)
#define     CHIPID19    (*(unsigned char volatile __XDATA *)0xfdf3)
#define     CHIPID20    (*(unsigned char volatile __XDATA *)0xfdf4)
#define     CHIPID21    (*(unsigned char volatile __XDATA *)0xfdf5)
#define     CHIPID22    (*(unsigned char volatile __XDATA *)0xfdf6)
#define     CHIPID23    (*(unsigned char volatile __XDATA *)0xfdf7)
#define     CHIPID24    (*(unsigned char volatile __XDATA *)0xfdf8)
#define     CHIPID25    (*(unsigned char volatile __XDATA *)0xfdf9)
#define     CHIPID26    (*(unsigned char volatile __XDATA *)0xfdfa)
#define     CHIPID27    (*(unsigned char volatile __XDATA *)0xfdfb)
#define     CHIPID28    (*(unsigned char volatile __XDATA *)0xfdfc)
#define     CHIPID29    (*(unsigned char volatile __XDATA *)0xfdfd)
#define     CHIPID30    (*(unsigned char volatile __XDATA *)0xfdfe)
#define     CHIPID31    (*(unsigned char volatile __XDATA *)0xfdff)

/////////////////////////////////////////////////
//FC00H-FCFFH
/////////////////////////////////////////////////

#define     MD3         (*(unsigned char volatile __XDATA *)0xfcf0)
#define     MD2         (*(unsigned char volatile __XDATA *)0xfcf1)
#define     MD1         (*(unsigned char volatile __XDATA *)0xfcf2)
#define     MD0         (*(unsigned char volatile __XDATA *)0xfcf3)
#define     MD5         (*(unsigned char volatile __XDATA *)0xfcf4)
#define     MD4         (*(unsigned char volatile __XDATA *)0xfcf5)
#define     dwOP1       (*(unsigned long volatile __XDATA *)0xfcf0)


#define     ARCON       (*(unsigned char volatile __XDATA *)0xfcf6)
#define     OPCON       (*(unsigned char volatile __XDATA *)0xfcf7)

/////////////////////////////////////////////////
//FB00H-FBFFH
/////////////////////////////////////////////////


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

#define     PWMC        (*(unsigned int  volatile __XDATA *)0xff00)
#define     PWMTADC     (*(unsigned int  volatile __XDATA *)0xff03)
#define     PWM0T1      (*(unsigned int  volatile __XDATA *)0xff10)
#define     PWM0T2      (*(unsigned int  volatile __XDATA *)0xff12)
#define     PWM1T1      (*(unsigned int  volatile __XDATA *)0xff18)
#define     PWM1T2      (*(unsigned int  volatile __XDATA *)0xff1a)
#define     PWM2T1      (*(unsigned int  volatile __XDATA *)0xff20)
#define     PWM2T2      (*(unsigned int  volatile __XDATA *)0xff22)
#define     PWM3T1      (*(unsigned int  volatile __XDATA *)0xff28)
#define     PWM3T2      (*(unsigned int  volatile __XDATA *)0xff2a)
#define     PWM4T1      (*(unsigned int  volatile __XDATA *)0xff30)
#define     PWM4T2      (*(unsigned int  volatile __XDATA *)0xff32)
#define     PWM5T1      (*(unsigned int  volatile __XDATA *)0xff38)
#define     PWM5T2      (*(unsigned int  volatile __XDATA *)0xff3a)
#define     PWM6T1      (*(unsigned int  volatile __XDATA *)0xff40)
#define     PWM6T2      (*(unsigned int  volatile __XDATA *)0xff42)
#define     PWM7T1      (*(unsigned int  volatile __XDATA *)0xff48)
#define     PWM7T2      (*(unsigned int  volatile __XDATA *)0xff4a)
#define     wOP1        (*(unsigned int  volatile __XDATA *)0xfcf2)
#define     wOP2        (*(unsigned int  volatile __XDATA *)0xfcf4)

#endif

#endif
