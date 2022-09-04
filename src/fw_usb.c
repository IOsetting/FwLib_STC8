#include "fw_usb.h"
#include "fw_sys.h"

#if (__CONF_MCU_TYPE == 3)
uint8_t USB_ReadReg(uint8_t addr)
{
  while (USB_IsBusy());
  USB_SetAddrForRead(addr);

  while (USB_IsBusy());
  return USBDAT;
}

void USB_WriteReg(uint8_t addr, uint8_t dat)
{
  while (USB_IsBusy());
  USB_SetAddrForWrite(addr);
  USBDAT = dat;
}

uint8_t USB_ReadFIFO(uint8_t fifo, uint8_t *pdat)
{
  uint8_t cnt, ret;
  ret = cnt = USB_ReadReg(COUNT0);
  while (cnt--)
  {
    *pdat++ = USB_ReadReg(fifo);
  }
  return ret;
}

void USB_WriteFIFO(uint8_t fifo, uint8_t *pdat, uint8_t cnt)
{
  while (cnt--)
  {
    USB_WriteReg(fifo, *pdat++);
  }
}
#endif