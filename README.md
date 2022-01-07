# About

FwLib_STC8 is a lite firmware library for STC8G/STC8H series MCU.

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
3. Include `fw_hal.h` in your code
```c
#include "fw_hal.h"
```
then it's ready to use.

4. For more detailed usage, please check the code in demos


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
4. Include `fw_hal.h` in your code
```c
#include "fw_hal.h"
```
then it's ready to use.


# License

Copyright (c) 2021-present IOsetting <iosetting@outlook.com>

The FwLib_STC8 is licensed under the permissive Apache 2.0 license, you can use it in both commercial and personal projects with confidence.