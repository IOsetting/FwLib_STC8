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

#ifndef ___FW_INC_H___
#define ___FW_INC_H___

#include "fw_conf.h"
#include "fw_sys.h"
#include "fw_rcc.h"
#include "fw_mem.h"
#include "fw_exti.h"
#include "fw_gpio.h"
#include "fw_tim.h"
#include "fw_uart.h"
#include "fw_adc.h"
#include "fw_i2c.h"
#include "fw_spi.h"
#include "fw_iap.h"
#include "fw_util.h"
#include "fw_wdt.h"

#if (__CONF_MCU_TYPE == 2  )
#include "fw_pca.h"
#endif
#if (__CONF_MCU_TYPE == 3  )
#include "fw_pwm.h"
#include "fw_rtc.h"
#include "fw_dma.h"
#include "fw_usb.h"
#endif

#endif
