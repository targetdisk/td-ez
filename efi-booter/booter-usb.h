#ifndef BOOTER_USB_H
#define BOOTER_USB_H

#include <fx2regs.h>
#include <fx2usb.h>
#include <fx2usbmassstor.h>

#include "efi_scsi.h"

usb_desc_device_c usb_device = {
  .bLength = sizeof(struct usb_desc_device),
  .bDescriptorType = USB_DESC_DEVICE,
  .bcdUSB = 0x0200,
  .bDeviceClass = USB_DEV_CLASS_PER_INTERFACE,
  .bDeviceSubClass = USB_DEV_SUBCLASS_PER_INTERFACE,
  .bDeviceProtocol = USB_DEV_PROTOCOL_PER_INTERFACE,
  .bMaxPacketSize0 = 64,
  .idVendor = 0xcafe,
  .idProduct = 0xbabe,
  .bcdDevice = 0x0000,
  .iManufacturer = 1,
  .iProduct = 2,
  .iSerialNumber = 0,
  .bNumConfigurations = 1,
};

usb_desc_interface_c usb_interface_mass_storage = {
  .bLength              = sizeof(struct usb_desc_interface),
  .bDescriptorType      = USB_DESC_INTERFACE,
  .bInterfaceNumber     = 0,
  .bAlternateSetting    = 0,
  .bNumEndpoints        = 2,
  .bInterfaceClass      = USB_IFACE_CLASS_MASS_STORAGE,
  .bInterfaceSubClass   = USB_IFACE_SUBCLASS_MASS_STORAGE_SCSI,
  .bInterfaceProtocol   = USB_IFACE_PROTOCOL_MASS_STORAGE_BBB,
  .iInterface           = 0,
};

usb_desc_endpoint_c usb_endpoint_ep2_out = {
  .bLength              = sizeof(struct usb_desc_endpoint),
  .bDescriptorType      = USB_DESC_ENDPOINT,
  .bEndpointAddress     = 2,
  .bmAttributes         = USB_XFER_BULK,
  .wMaxPacketSize       = 512,
  .bInterval            = 0,
};

usb_desc_endpoint_c usb_endpoint_ep6_in = {
  .bLength              = sizeof(struct usb_desc_endpoint),
  .bDescriptorType      = USB_DESC_ENDPOINT,
  .bEndpointAddress     = 6|USB_DIR_IN,
  .bmAttributes         = USB_XFER_BULK,
  .wMaxPacketSize       = 512,
  .bInterval            = 0,
};

usb_mass_storage_bbb_state_t usb_mass_storage_state = {
  .interface    = 0,
  .max_in_size  = 512,

  .command      = efi_scsi_command,
  .data_out     = efi_scsi_data_out,  /* SPI flash I/O */
  .data_in      = efi_scsi_data_in,   /* SPI flash I/O */
};

#endif  /* BOOTER_USB_H */
