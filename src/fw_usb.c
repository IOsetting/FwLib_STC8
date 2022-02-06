#include "fw_usb.h"
#include "fw_sys.h"

uint8_t USB_ReadReg(uint8_t addr)
{
  uint8_t dat;
  while (USBADR & 0x80);
  USBADR = addr | 0x80;
  while (USBADR & 0x80);
  dat = USBDAT;
  return dat;
}

void USB_WriteReg(uint8_t addr, uint8_t dat)
{
  while (USBADR & 0x80);
  USBADR = addr & 0x7f;
  USBDAT = dat;
}

uint8_t USB_ReadFIFO(uint8_t fifo, uint8_t *pdat)
{
  uint8_t cnt;
  uint8_t ret;
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