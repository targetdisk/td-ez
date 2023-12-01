#ifndef EFI_SCSI_H
#define EFI_SCSI_H

#include <stdbool.h>
#include <stdint.h>

bool efi_scsi_data_out(uint8_t lun, __xdata const uint8_t *data, uint16_t length) __reentrant;
bool efi_scsi_data_in (uint8_t lun, __xdata uint8_t *data, uint16_t length) __reentrant;
#endif  /* EFI_SCSI_H */
