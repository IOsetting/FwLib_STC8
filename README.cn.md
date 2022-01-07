# 关于

FwLib_STC8 是面向 STC8G/STC8H 系列 MCU 的C语言封装库

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
# or Giteee (for Chinese users)
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
3. 在代码中引用 `fw_hal.h`后, 就可以开始使用了
```c
#include "fw_hal.h"
```

4. 更多的使用细节, 请查看demo中的例程代码.


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
4. 在代码中引用 `fw_hal.h`后, 就可以开始使用了
```c
#include "fw_hal.h"
```


# 授权

Copyright (c) 2021-present IOsetting <iosetting@outlook.com>

FwLib_STC8 使用 Apache 2.0 协议授权, 可以使用于个人及商业项目.