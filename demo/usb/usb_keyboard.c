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

/**
 * USB Keyboard Demo
 * 
 * P0:   8 bits for 4x4 Key matrix
 * P6.0: NumLock
 * P6.1: CapsLock
*/

#include "fw_hal.h"
#include <string.h>

#define KeyIO P0

__BIT B_1ms;         // 1ms flag
__BIT KeyChangeTemp;
__BIT KeyChangeFlag;
uint16_t cnt50ms;
uint16_t KeyCode;       // code of key pressed
uint16_t OldKeyCode;    // for key status changing check
uint16_t NewKeyCode;    // new key status
uint16_t KeyHoldTime;

__CODE uint8_t DEVICEDESC[18];
__CODE uint8_t CONFIGDESC[41];
__CODE uint8_t HIDREPORTDESC[63];
__CODE uint8_t LANGIDDESC[4];
__CODE uint8_t MANUFACTDESC[8];
__CODE uint8_t PRODUCTDESC[30];
__CODE uint8_t KeyMap[16];
__XDATA uint8_t HidFreature[64];
__XDATA uint8_t HidInput[64];
__XDATA uint8_t HidOutput[64];
USB_Request_t usb_request;
USB_EP0_Stage_t usb_ep0_stage;

void USB_Init(void);
void KeyScan(void);
void SendKeyStatus(void);

void main()
{
    uint8_t i;

    GPIO_P1_SetMode(GPIO_Pin_All, GPIO_Mode_InOut_QBD);
    GPIO_P3_SetMode(GPIO_Pin_0 | GPIO_Pin_1, GPIO_Mode_Input_HIP);
    GPIO_P6_SetMode(GPIO_Pin_All, GPIO_Mode_Output_PP);

    USB_Init();

    TIM_Timer0_Config(HAL_State_ON, TIM_TimerMode_16BitAuto, 1000);
    EXTI_Timer0_SetIntState(HAL_State_ON);
    EXTI_Timer0_SetIntPriority(EXTI_IntPriority_High);
    TIM_Timer0_SetRunState(HAL_State_ON);
    EXTI_Global_SetIntState(HAL_State_ON);

    for (i = 0; i < 8; i++)
    {
        HidInput[i] = 0;
    }

    while (1)
    {
        if (B_1ms) // every 1 ms
        {
            B_1ms = 0;
            if (++cnt50ms >= 50) // scan every 50 ms
            {
                cnt50ms = 0;
                KeyScan();
            }
            if (KeyChangeFlag) // if key status changed
            {
                KeyChangeFlag = 0;
                SendKeyStatus();
            }
        }
    }
}

void USB_Init()
{
    SYS_EnableOscillator48M();
    USB_SetClockSource(USB_ClockSource_6M);
    USB_SetEnabled(HAL_State_ON);
    USB_SetDpDmPullUp(HAL_State_ON);
    EXTI_USB_SetIntPriority(EXTI_IntPriority_Highest);

    USB_WriteReg(FADDR, 0x00);
    USB_WriteReg(POWER, 0x08);
    USB_WriteReg(INTRIN1E, 0x3f);
    USB_WriteReg(INTROUT1E, 0x3f);
    USB_WriteReg(INTRUSBE, 0x00);
    USB_WriteReg(POWER, 0x01);
    usb_ep0_stage.bStage = USB_CtrlState_Idle;

    EXTI_USB_SetIntState(HAL_State_ON);
}

INTERRUPT(USB_Routine, EXTI_VectUSB)
{
    uint8_t intrusb;
    uint8_t intrin;
    uint8_t introut;
    uint8_t csr;
    uint8_t cnt;
    uint16_t len = 0;
    intrusb = USB_ReadReg(INTRUSB);
    intrin = USB_ReadReg(INTRIN1);
    introut = USB_ReadReg(INTROUT1);
    if (intrusb & RSTIF)
    {
        USB_SelectEndPoint(1);
        USB_WriteReg(INCSR1, INCLRDT);
        USB_SelectEndPoint(1);
        USB_WriteReg(OUTCSR1, OUTCLRDT);
        usb_ep0_stage.bStage = USB_CtrlState_Idle;
    }
    if (intrin & EP0IF)
    {
        USB_SelectEndPoint(0);
        csr = USB_ReadReg(CSR0);
        if (csr & STSTL)
        {
            USB_WriteReg(CSR0, csr & ~STSTL);
            usb_ep0_stage.bStage = USB_CtrlState_Idle;
        }
        if (csr & SUEND)
        {
            USB_WriteReg(CSR0, csr | SSUEND);
        }
        switch (usb_ep0_stage.bStage)
        {
            case USB_CtrlState_Idle:
            if (csr & OPRDY)
            {
                usb_ep0_stage.bStage = USB_CtrlState_SettingUp;
                USB_ReadFIFO(FIFO0, (uint8_t *)&usb_request);
                ((uint8_t *)&usb_ep0_stage.wResidue)[0] = usb_request.wLength.bb.bh;
                ((uint8_t *)&usb_ep0_stage.wResidue)[1] = usb_request.wLength.bb.bl;
                switch (usb_request.bmRequestType & REQUEST_TYPE_MASK)
                {
                    case USB_RequestType_Standard:
                        switch (usb_request.bRequest)
                        {
                            case USB_StdReq_SetAddress:
                                USB_WriteReg(FADDR, usb_request.wValue.bb.bl);
                                break;

                            case USB_StdReq_SetConfiguration:
                                USB_SelectEndPoint(1);
                                USB_WriteReg(INCSR2, INMODEIN);
                                USB_WriteReg(INMAXP, 8);
                                USB_SelectEndPoint(1);
                                USB_WriteReg(INCSR2, INMODEOUT);
                                USB_WriteReg(OUTMAXP, 8);
                                USB_SelectEndPoint(0);
                                break;

                            case USB_StdReq_GetDescriptor:
                                usb_ep0_stage.bStage = USB_CtrlState_DataIn;
                                switch (usb_request.wValue.bb.bh)
                                {
                                    case USB_DescriptorType_Device:
                                        usb_ep0_stage.pData = (uint8_t *)DEVICEDESC;
                                        len = sizeof(DEVICEDESC);
                                        break;

                                    case USB_DescriptorType_Configuration:
                                        usb_ep0_stage.pData = (uint8_t *)CONFIGDESC;
                                        len = sizeof(CONFIGDESC);
                                        break;

                                    case USB_DescriptorType_String:
                                        switch (usb_request.wValue.bb.bl)
                                        {
                                            case 0:
                                                usb_ep0_stage.pData = (uint8_t *)LANGIDDESC;
                                                len = sizeof(LANGIDDESC);
                                                break;

                                            case 1:
                                                usb_ep0_stage.pData = (uint8_t *)MANUFACTDESC;
                                                len = sizeof(MANUFACTDESC);
                                                break;

                                            case 2:
                                                usb_ep0_stage.pData = (uint8_t *)PRODUCTDESC;
                                                len = sizeof(PRODUCTDESC);
                                                break;

                                            default:
                                                usb_ep0_stage.bStage = USB_CtrlState_Stalled;
                                                break;
                                        }
                                        break;

                                    case USB_DescriptorType_Report:
                                        usb_ep0_stage.pData = (uint8_t *)HIDREPORTDESC;
                                        len = sizeof(HIDREPORTDESC);
                                        break;

                                    default:
                                        usb_ep0_stage.bStage = USB_CtrlState_Stalled;
                                        break;
                                }
                                if (len < usb_ep0_stage.wResidue)
                                {
                                    usb_ep0_stage.wResidue = len;
                                }
                                break;

                            default:
                                usb_ep0_stage.bStage = USB_CtrlState_Stalled;
                                break;
                        }
                        break;

                    case USB_RequestType_Class:
                        switch (usb_request.bRequest)
                        {
                            case USB_HidReq_GetReport:
                                usb_ep0_stage.pData = HidFreature;
                                usb_ep0_stage.bStage = USB_CtrlState_DataIn;
                                break;

                            case USB_HidReq_SetReport:
                                usb_ep0_stage.pData = HidFreature;
                                usb_ep0_stage.bStage = USB_CtrlState_DataOut;
                                break;

                            case USB_HidReq_SetIdle:
                                break;

                            // case USB_HidReq_GetIdle:
                            // case USB_HidReq_GetProtocol:
                            // case USB_HidReq_SetProtocol:
                            default:
                                usb_ep0_stage.bStage = USB_CtrlState_Stalled;
                                break;
                        }
                        break;

                    default:
                        usb_ep0_stage.bStage = USB_CtrlState_Stalled;
                        break;
                }

                switch (usb_ep0_stage.bStage)
                {
                    case USB_CtrlState_DataIn:
                        USB_WriteReg(CSR0, SOPRDY);
                        goto L_Ep0SendData;
                        break;

                    case USB_CtrlState_DataOut:
                        USB_WriteReg(CSR0, SOPRDY);
                        break;

                    case USB_CtrlState_SettingUp:
                        USB_WriteReg(CSR0, SOPRDY | DATEND);
                        usb_ep0_stage.bStage = USB_CtrlState_Idle;
                        break;

                    case USB_CtrlState_Stalled:
                        USB_WriteReg(CSR0, SOPRDY | SDSTL);
                        usb_ep0_stage.bStage = USB_CtrlState_Idle;
                        break;
                }
            }
            break;
            
            case USB_CtrlState_DataIn:
                if (!(csr & IPRDY))
                {
                    L_Ep0SendData:
                    cnt = usb_ep0_stage.wResidue > 64 ? 64 : usb_ep0_stage.wResidue;
                    USB_WriteFIFO(FIFO0, usb_ep0_stage.pData, cnt);
                    usb_ep0_stage.wResidue -= cnt;
                    usb_ep0_stage.pData += cnt;
                    if (usb_ep0_stage.wResidue == 0)
                    {
                        USB_WriteReg(CSR0, IPRDY | DATEND);
                        usb_ep0_stage.bStage = USB_CtrlState_Idle;
                    }
                    else
                    {
                        USB_WriteReg(CSR0, IPRDY);
                    }
                }
                break;

            case USB_CtrlState_DataOut:
                if (csr & OPRDY)
                {
                    cnt = USB_ReadFIFO(FIFO0, usb_ep0_stage.pData);
                    usb_ep0_stage.wResidue -= cnt;
                    usb_ep0_stage.pData += cnt;
                    if (usb_ep0_stage.wResidue == 0)
                    {
                        USB_WriteReg(CSR0, SOPRDY | DATEND);
                        usb_ep0_stage.bStage = USB_CtrlState_Idle;
                    }
                    else
                    {
                        USB_WriteReg(CSR0, SOPRDY);
                    }
                }
                break;
        }
    }

    if (intrin & EP1INIF)
    {
        USB_SelectEndPoint(1);
        csr = USB_ReadReg(INCSR1);
        if (csr & INSTSTL)
        {
            USB_WriteReg(INCSR1, INCLRDT);
        }
        if (csr & INUNDRUN)
        {
            USB_WriteReg(INCSR1, 0);
        }
    }

    if (introut & EP1OUTIF)
    {
        USB_SelectEndPoint(1);
        csr = USB_ReadReg(OUTCSR1);
        if (csr & OUTSTSTL)
        {
            USB_WriteReg(OUTCSR1, OUTCLRDT);
        }
        if (csr & OUTOPRDY)
        {
            USB_ReadFIFO(FIFO1, HidOutput);
            USB_WriteReg(OUTCSR1, 0);
            
            P6 = ~HidOutput[0];    // update LED status
        }
    }
}

uint8_t KeyCount(uint16_t dat)
{
    uint8_t i;

    i = 0;
    while (dat)
    {
        if (dat & 0x8000) i++;
        dat <<= 1;
    }
    return i;
}

//HidInput first byte for special keys，second byte is reserved，the reset 6 bytes for normal keys
void SendKeyStatus(void)
{
    uint8_t i,n;
    
    if(KeyCode) // if key pressed
    {
        // allow 3 keys pressed simultaneously
        if(KeyCount(KeyCode) > 3) 
        {
            return;  // too many keys
        }
        else
        {
            n = 2;
            for (i = 0; i < 16; i++)
            {
                if (i == 1)
                {
                    if (KeyCode & (1 << i)) // left Ctrl
                    {
                        HidInput[0] |= 1;
                    }
                    else
                    {
                        HidInput[0] &= ~1;
                    }
                }
                else if (i == 2)
                {
                    if (KeyCode & (1 << i)) // left alt
                    {
                        HidInput[0] |= 1 << 2;
                    }
                    else
                    {
                        HidInput[0] &= ~(1 << 2);
                    }
                }
                else
                {
                    if (KeyCode & (1 << i))
                    {
                        HidInput[n++] = KeyMap[i];
                    }
                }
            }

            for(; n<8; n++)
            {
                HidInput[n]=0;  // fill 0 to the rest
            }
        }
    }
    else // if no key pressed, return 0
    {
        for (i = 0; i < 8; i++)
        {
            HidInput[i] = 0;
        }
    }

    // return 8 bytes data
    USB_SelectEndPoint(1);
    for (i = 0; i < 8; i++)
    {
        USB_WriteReg(FIFO1, HidInput[i]);
    }
    USB_WriteReg(INCSR1, INIPRDY);
}

INTERRUPT(Timer0_Routine, EXTI_VectTimer0)
{
    B_1ms = 1;
}

/*****************************************************
    Key Matrix Scan

     Y   P04      P05      P06      P07
          |        |        |        |
X         |        |        |        |
P00 ---- K00 ---- K01 ---- K02 ---- K03 ----
          |        |        |        |
P01 ---- K04 ---- K05 ---- K06 ---- K07 ----
          |        |        |        |
P02 ---- K08 ---- K09 ---- K10 ---- K11 ----
          |        |        |        |
P03 ---- K12 ---- K13 ---- K14 ---- K15 ----
          |        |        |        |
******************************************************/

void KeyScan(void)
{
    uint8_t temp;

    KeyIO = 0x0F;
    SYS_DelayUs(1);
    if ((KeyIO & 0x0F) == 0x0F) // no key pressed
    {
        NewKeyCode = 0;
    }
    else // start scan
    {
        // scan first line
        KeyIO = (uint8_t)~0x10;
        SYS_DelayUs(1);
        // save 4 keys status
        temp = KeyIO & 0x0F;

        // second line
        KeyIO = (uint8_t)~0x20;
        SYS_DelayUs(1);
        temp |= KeyIO << 4;

        // save current key status
        NewKeyCode = (~temp) & 0xFF;

        // third line
        KeyIO = (uint8_t)~0x40;
        SYS_DelayUs(1);
        temp = KeyIO & 0x0F;

        // 4th line
        KeyIO = (uint8_t)~0x80;
        SYS_DelayUs(1);
        temp |= KeyIO << 4;

        // save all 16 keys' status in 2 bytes, 1 indicates key pressed
        NewKeyCode |= (((uint16_t)~temp) << 8);
    }

    if (NewKeyCode != OldKeyCode)
    {
        KeyHoldTime = 0;
        OldKeyCode = NewKeyCode;
        KeyChangeTemp = 1;
    }
    else
    {
        KeyHoldTime++;
        if (KeyHoldTime >= 1)
        {
            KeyHoldTime = 1;
            KeyCode = OldKeyCode;
            if (KeyChangeTemp)
            {
                KeyChangeTemp = 0;
                KeyChangeFlag = 1; // Set send flag
            }
        }
    }
}

__CODE uint8_t DEVICEDESC[18] =
{
    0x12, //bLength(18);
    0x01, //bDescriptorType(Device);
    0x00,0x02, //bcdUSB(2.00);
    0x00, //bDeviceClass(0);
    0x00, //bDeviceSubClass0);
    0x00, //bDeviceProtocol(0);
    0x40, //bMaxPacketSize0(64);
    0x54,0x53, //idVendor(5354);
    0x80,0x44, //idProduct(4480);
    0x00,0x01, //bcdDevice(1.00);
    0x01, //iManufacturer(1);
    0x02, //iProduct(2);
    0x03, //iSerialNumber(3);
    0x01, //bNumConfigurations(1);
};

__CODE uint8_t CONFIGDESC[41] =
{
    0x09, //bLength(9);
    0x02, //bDescriptorType(Configuration);
    0x29,0x00, //wTotalLength(41);
    0x01, //bNumInterfaces(1);
    0x01, //bConfigurationValue(1);
    0x00, //iConfiguration(0);
    0xa0, //bmAttributes(BUSPower);
    0xc8, //MaxPower(400mA);
    
    0x09, //bLength(9);
    0x04, //bDescriptorType(Interface);
    0x00, //bInterfaceNumber(0);
    0x00, //bAlternateSetting(0);
    0x02, //bNumEndpoints(2);
    0x03, //bInterfaceClass(HID);
    0x01, //bInterfaceSubClass(1);
    0x01, //bInterfaceProtocol(1);
    0x00, //iInterface(0);
    
    0x09, //bLength(9);
    0x21, //bDescriptorType(HID);
    0x01,0x10, //bcdHID(1.01);
    0x00, //bCountryCode(0);
    0x01, //bNumDescriptors(1);
    0x22, //bDescriptorType(HID Report);
    0x3f,0x00, //wDescriptorLength(63);
    0x07, //bLength(7);
    0x05, //bDescriptorType(Endpoint);
    0x81, //bEndpointAddress(EndPoint1 as IN);
    0x03, //bmAttributes(Interrupt);
    0x40,0x00, //wMaxPacketSize(64);
    0x0a, //bInterval(10ms);
    0x07, //bLength(7);
    0x05, //bDescriptorType(Endpoint);
    0x01, //bEndpointAddress(EndPoint1 as OUT);
    0x03, //bmAttributes(Interrupt);
    0x40,0x00, //wMaxPacketSize(64);
    0x0a, //bInterval(10ms);
};

__CODE uint8_t HIDREPORTDESC[63] =
{
    0x05, 0x01,    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,    // USAGE (Keyboard)
    0xa1, 0x01,    // COLLECTION (Application)
    0x05, 0x07,    //   USAGE_PAGE (Keyboard)
    0x19, 0xe0,    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,    //   REPORT_SIZE (1)
    0x95, 0x08,    //   REPORT_COUNT (8)
    0x81, 0x02,    //   INPUT (Data,Var,Abs)
    0x95, 0x01,    //   REPORT_COUNT (1)
    0x75, 0x08,    //   REPORT_SIZE (8)
    0x81, 0x03,    //   INPUT (Cnst,Var,Abs)
    0x95, 0x05,    //   REPORT_COUNT (5)
    0x75, 0x01,    //   REPORT_SIZE (1)
    0x05, 0x08,    //   USAGE_PAGE (LEDs)
    0x19, 0x01,    //   USAGE_MINIMUM (Num Lock)
    0x29, 0x05,    //   USAGE_MAXIMUM (Kana)
    0x91, 0x02,    //   OUTPUT (Data,Var,Abs)
    0x95, 0x01,    //   REPORT_COUNT (1)
    0x75, 0x03,    //   REPORT_SIZE (3)
    0x91, 0x03,    //   OUTPUT (Cnst,Var,Abs)
    0x95, 0x06,    //   REPORT_COUNT (6)
    0x75, 0x08,    //   REPORT_SIZE (8)
    0x15, 0x00,    //   LOGICAL_MINIMUM (0)
    0x25, 0xFF,    //   LOGICAL_MAXIMUM (255)
    0x05, 0x07,    //   USAGE_PAGE (Keyboard)
    0x19, 0x00,    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,    //   INPUT (Data,Ary,Abs)
    0xc0           // END_COLLECTION
};

__CODE uint8_t LANGIDDESC[4] =
{
    0x04,0x03,
    0x09,0x04,
};

__CODE uint8_t MANUFACTDESC[8] =
{
    0x08,0x03,
    'S',0,
    'T',0,
    'C',0,
};

__CODE uint8_t PRODUCTDESC[30] =
{
    0x1e,0x03,
    'S',0,
    'T',0,
    'C',0,
    ' ',0,
    'U',0,
    'S',0,
    'B',0,
    ' ',0,
    'D',0,
    'e',0,
    'v',0,
    'i',0,
    'c',0,
    'e',0,
};

__CODE uint8_t KeyMap[16] = {
    0x53,    //0: Num Lock
    0xFF,    //1: NULL - Left Ctrl
    0xFF,    //2: NULL - Left ALT
    0x2A,    //3: BackSpace

    0x5F,    //4: 7
    0x60,    //5: 8
    0x61,    //6: 9
    0x62,    //7: 0

    0x5C,    //8: 4
    0x5D,    //9: 5
    0x5E,    //A: 6
    0x63,    //B: DEL

    0x59,    //C: 1
    0x5A,    //D: 2
    0x5B,    //E: 3
    0x58,    //F: Return
};