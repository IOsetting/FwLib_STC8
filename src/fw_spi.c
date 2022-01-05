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

#include "fw_spi.h"
#include "fw_tim.h"
#include "fw_sys.h"


uint8_t SPI_TxRx(uint8_t dat)
{
	SPDAT = dat;
    while (!SPI_RxTxFinished());
    SPI_ClearInterrupts();
	return SPDAT;
}

void SPI_TxRxBytes(uint8_t *pBuf, uint8_t len)
{
    while(len--)
    {
        *pBuf++ = SPI_TxRx(*pBuf);
    }
}