#ifndef BOOTER_USB_H
#define BOOTER_USB_H

#include <fx2lib.h>
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

usb_configuration_c usb_config_efi = {
  {
    .bLength              = sizeof(struct usb_desc_configuration),
    .bDescriptorType      = USB_DESC_CONFIGURATION,
    .bNumInterfaces       = 1,
    .bConfigurationValue  = 1,
    .iConfiguration       = 0,
    .bmAttributes         = USB_ATTR_RESERVED_1,
    .bMaxPower            = 50,
  },
  {
    { .interface  = &usb_interface_mass_storage },
    { .endpoint   = &usb_endpoint_ep2_out },
    { .endpoint   = &usb_endpoint_ep6_in  },
    { 0 }
  }
};

usb_configuration_set_c usb_configs_efi[] = {
  &usb_config_efi,
};

usb_ascii_string_c usb_strings_efi[] = {
  [0] = "targetdisk1394@gmail.com",
  [1] = "Target Disk EFI Flash Media (SPI flash)",
  [2] = "000000000000",
};

__xdata struct usb_descriptor_set usb_descriptor_set = {
  .device           = &usb_device,
  .config_count     = ARRAYSIZE(usb_configs_efi),
  .configs          = usb_configs_efi,
  .string_count     = ARRAYSIZE(usb_strings_efi),
  .strings          = usb_strings_efi,
};

usb_mass_storage_bbb_state_t usb_mass_storage_state = {
  .interface    = 0,
  .max_in_size  = 512,

  .command      = efi_scsi_command,
  .data_out     = efi_scsi_data_out,  /* SPI flash I/O */
  .data_in      = efi_scsi_data_in,   /* SPI flash I/O */
};

#endif  /* BOOTER_USB_H */
