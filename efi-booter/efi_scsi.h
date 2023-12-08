#ifndef EFI_SCSI_H
#define EFI_SCSI_H

#include <stdbool.h>
#include <stdint.h>

#define BYTES_PER_SECTOR  512
#define TOTAL_SECTORS  32768

/* Our SPI flash code is assumed to be the only thing on Port A. */
#define CS_PIN  PA3
#define SCK_PIN  PA2
#define MOSI_PIN  PA1
#define MISO_PIN  PA0
#define OEA_SPI  ( 1 << 3 ) | ( 1 << 2 ) | ( 1 << 1 )

void efi_spi_init( void );

bool efi_scsi_command(uint8_t lun, __xdata uint8_t *buffer, uint8_t length) __reentrant;
bool efi_scsi_data_out(uint8_t lun, __xdata const uint8_t *data, uint16_t length) __reentrant;
bool efi_scsi_data_in (uint8_t lun, __xdata uint8_t *data, uint16_t length) __reentrant;
#endif  /* EFI_SCSI_H */
