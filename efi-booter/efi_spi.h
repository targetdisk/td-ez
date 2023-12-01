#ifndef EFI_SPI_H
#define EFI_SPI_H

bool efi_spi_read( uint32_t lba, __xdata uint8_t *data );
bool efi_spi_write( uint32_t lba, __xdata const uint8_t *data );

#endif  /* EFI_SPI_H */
