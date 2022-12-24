# 关于

FwLib_STC8 是面向 STC8G/STC8H 系列 MCU 的C语言封装库

## 芯片用户手册

* STC8A/8F: [中文](http://www.stcmcudata.com/STC8F-DATASHEET/STC8A-STC8F.pdf), [英文](http://www.stcmcudata.com/STC8F-DATASHEET/STC8-english-20180320.pdf)
* STC8G: [中文](http://www.stcmcudata.com/STC8F-DATASHEET/STC8G.pdf), [英文](https://www.stcmcudata.com/STC8F-DATASHEET/STC8G-EN.pdf)
* STC8H: [中文](http://www.stcmcudata.com/STC8F-DATASHEET/STC8H.pdf), [英文](https://www.stcmcudata.com/STC8F-DATASHEET/STC8H-EN.pdf)


# 特性

* 与 SDCC 和 Keil C51 兼容
* 为8位MCU的受限资源优化
* 以易读的代码形式提供片上资源的操作
* 丰富的演示例程用于快速上手

# PlatformIO 快速上手

1. 将代码仓库克隆到本地目录
```bash
# GitHub
git clone https://github.com/IOsetting/FwLib_STC8.git FwLib_STC8
# or Giteee (内网用户)
git clone https://gitee.com/iosetting/fw-lib_-stc8.git FwLib_STC8
```
2. 复制(或移动)到 PlatformIO 项目的lib目录下
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
3. 在 platformio.ini 中添加编译参数
```
build_flags =
    -D__CONF_FOSC=36864000UL                       ;MCU的运行频率
    -D__CONF_MCU_MODEL=MCU_MODEL_STC8H3K32S2       ;MCU型号
    -D__CONF_CLKDIV=0x02                           ;以下参数均用于频率修剪
    -D__CONF_IRCBAND=0x03
    -D__CONF_VRTRIM=0x19
    -D__CONF_IRTRIM=0x28
    -D__CONF_LIRTRIM=0x00
```
4. 在代码中引用 `fw_hal.h`后, 就可以开始使用了
```c
#include "fw_hal.h"
```

## VS Code 代码高亮错误

VS Code 并不完全支持 SDCC 的 Intel 8051 语法 ([issue 7146](https://github.com/microsoft/vscode-cpptools/issues/7146)), 如果您需要在代码编辑中消除错误提示, 需要增加一个env, 并在 build_flags 中添加 `__SDCC_SYNTAX_FIX`:
```
build_flags =
    -D__SDCC_SYNTAX_FIX
    -D__CONF_FOSC=36864000UL
    -D__CONF_MCU_MODEL=MCU_MODEL_STC8H3K32S2
    ...
```
这个特殊的env仅用于代码编辑, 编译和上载依然需要使用正常的env.


# Keil C51 快速上手

1. 将代码仓库克隆到本地目录
```bash
# GitHub
git clone https://github.com/IOsetting/FwLib_STC8.git FwLib_STC8
# or Giteee (for Chinese users)
git clone https://gitee.com/iosetting/fw-lib_-stc8.git FwLib_STC8
```
2. 复制(或移动)到 Keil C51 项目目录下
3. 将其通过 Project -> Manage -> Project Items, 添加到项目文件中
4. 通过菜单 Project -> Options for Target ... 打开项目选项, 切换到 C51 标签页, 在 Preprocessor Symbols -> Define 内输入以下内容
```
__CX51__, __CONF_MCU_MODEL=MCU_MODEL_STC8H3K32S2,__CONF_FOSC=36864000UL
```
关于以上的参数
``` 
   __CX51__ 将使宏定义切换为 Keil C51 关键字
   __CONF_MCU_MODEL, 修改为你的MCU型号, 在 include/fw_conf.h 下可以查看所有的可用型号.
   __CONF_FOSC The osc/irc MCU的运行频率, 可以使用STC-ISP下载时对MCU设定的频率.
```
5. 在代码中引用 `fw_hal.h`后, 就可以开始使用了
```c
#include "fw_hal.h"
```

# 宏定义

封装库中引入了一些宏定义, 用于保证对 Keil C51 和 SDCC 的兼容性.

命名和形式来源于 [sdcc compiler.h](https://sourceforge.net/p/sdcc/code/HEAD/tree/trunk/sdcc/device/include/mcs51/compiler.h). 
如果你希望代码在 Keil C51 和 SDCC 下都能编译, 在编码时就应当使用这些宏, 而不是编译器对应的关键词.

以下是相关的宏定义列表

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

这些宏定义可以在 include/fw_reg_base.h 中查看


# 授权

Copyright (c) 2021-present IOsetting <iosetting@outlook.com>

FwLib_STC8 使用 Apache 2.0 协议授权, 可以使用于个人及商业项目.