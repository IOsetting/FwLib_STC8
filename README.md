# About

FwLib_STC8 is a lite firmware library for STC8G/STC8H series MCU.

## Official Datasheets, User Manuals

* STC8A/8F: [Chinese](http://www.stcmcudata.com/STC8F-DATASHEET/STC8A-STC8F.pdf), [English](http://www.stcmcudata.com/STC8F-DATASHEET/STC8A-STC8F-EN.pdf)
* STC8G: [Chinese](http://www.stcmcudata.com/STC8F-DATASHEET/STC8G.pdf), [English](https://www.stcmcudata.com/STC8F-DATASHEET/STC8G-EN.pdf)
* STC8H: [Chinese](http://www.stcmcudata.com/STC8F-DATASHEET/STC8H.pdf), [English](https://www.stcmcudata.com/STC8F-DATASHEET/STC8H-EN.pdf)

# Features

* Compatible with SDCC and Keil C51
* Optimized for constrained 8-bit MCU resources
* Readable code for on-chip resources operation
* Demos for quick start

# PlatformIO Quick Start

1. Clone this repository to local file system
```bash
# GitHub
git clone https://github.com/IOsetting/FwLib_STC8.git FwLib_STC8
# or Giteee (for Chinese users)
git clone https://gitee.com/iosetting/fw-lib_-stc8.git FwLib_STC8
```
2. Copy(or move) it to your PlatformIO project library, the file structure
```
├── include
├── lib
│   └── FwLib_STC8
│       ├── demo
│       ├── include
│       └── src
├── src
└── test
```
3. Add compile arguments in platformio.ini
```
build_flags =
    -D__CONF_FOSC=36864000UL                       ;The osc/irc frequency you MCU will be running on
    -D__CONF_MCU_MODEL=MCU_MODEL_STC8H3K32S2       ;change this to your MCU type
    -D__CONF_CLKDIV=0x02                           ;frequency trimming
    -D__CONF_IRCBAND=0x03
    -D__CONF_VRTRIM=0x19
    -D__CONF_IRTRIM=0x28
    -D__CONF_LIRTRIM=0x00
```
4. Include `fw_hal.h` in your code
```c
#include "fw_hal.h"
```
then it's ready to go.

## VS Code Syntax Problem

VS Code doesn't support some of SDCC syntax for Intel 8051 ([issue 7146](https://github.com/microsoft/vscode-cpptools/issues/7146)), if you want to eliminate syntax errors in code editor, add a separate env for code editing and add `__SDCC_SYNTAX_FIX` in build_flags:
```
build_flags =
    -D__SDCC_SYNTAX_FIX
    -D__CONF_FOSC=36864000UL
    -D__CONF_MCU_MODEL=MCU_MODEL_STC8H3K32S2
    ...
```
This special env is for code editing only, building and uploading should use the normal env. 


# Keil C51 Quick Start

1. Clone this repository to local file system
```bash
# GitHub
git clone https://github.com/IOsetting/FwLib_STC8.git FwLib_STC8
# or Giteee (for Chinese users)
git clone https://gitee.com/iosetting/fw-lib_-stc8.git FwLib_STC8
```
2. Copy(or move) it to your Keil C51 project directory, 
3. Add it to project through Project -> Manage -> Project Items,
4. Open project option dialog by clicking Project -> Options for Target ... , switch to C51 tab, and input following content in Preprocessor Symbols -> Define:
```
__CX51__, __CONF_MCU_MODEL=MCU_MODEL_STC8H3K32S2,__CONF_FOSC=36864000UL
```
The explanation of these arguments
``` 
   __CX51__ This will tell the macros to switch to Keil C51 keywords
   __CONF_MCU_MODEL, change this to your MCU type, please look into FwLib_STC8/include/fw_conf.h for all available types.
   __CONF_FOSC The osc/irc frequency you MCU will be running on. It equals to the frequency this MCU will be trimmed to in STC-ISP.
```
5. Include `fw_hal.h` in your code
```c
#include "fw_hal.h"
```
then it's ready to go.

# Macros

Some macros were introduced for code compatibility with Keil C51 and SDCC. 

The naming is from [sdcc compiler.h](https://sourceforge.net/p/sdcc/code/HEAD/tree/trunk/sdcc/device/include/mcs51/compiler.h). If you want your code to work with both compilers, you need to stick to these macros instead of the compiler specific keywords:

Here is a list of the macros:

| Macro | Keil C51 | SDCC |
| ----------- | ---------------- | ----------------- |
| __BIT | bit | __bit |
| __DATA  | data  | __data  |
| __IDATA | idata | __idata |
| __PDATA | pdata | __pdata |
| __XDATA | xdata | __xdata |
| __CODE | code | __code |
| SBIT(name, addr, bit) | sbit name = addr^bit | __sbit __at(addr+bit) name |
| SFR(name, addr) | sfr name = addr | __sfr __at(addr) name |
| SFRX(addr) | (*(unsigned char volatile xdata *)(addr)) | (*(unsigned char volatile __xdata *)(addr)) |
| SFR16X(addr) | (*(unsigned int  volatile xdata *)(addr)) | (*(unsigned int  volatile __xdata *)(addr)) |
| INTERRUPT(name, vector) | void name (void) interrupt vector | void name (void) __interrupt (vector) |
| INTERRUPT_USING(name, vector, regnum) | void name (void) interrupt vector using regnum | void name (void) __interrupt (vector) __using (regnum) |
| NOP() | _nop_() | __asm NOP __endasm |

The definition of these macros can be found in include/fw_reg_base.h


# License

Copyright (c) 2021-present IOsetting <iosetting@outlook.com>

The FwLib_STC8 is licensed under the permissive Apache 2.0 license, you can use it in both commercial and personal projects with confidence.