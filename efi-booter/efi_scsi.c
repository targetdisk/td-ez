#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <fx2lib.h>
#include <fx2uf2.h>
#include <scsi.h>

bool efi_scsi_data_out( uint8_t lun, __xdata const uint8_t *buffer, uint16_t length ) __reentrant
{
  lun;

  if(current_op == SCSI_OPERATION_WRITE_10) {
    if(blocks_left == 0)
      return false;
    if(length != 512)
      return false;
    if(!efi_spi_write(block_index, buffer))
      return false;

    block_index++;
    blocks_left--;
    if(blocks_left > 0)
      return true;

    goto done;
  }

  return false;

done:
  current_op = 0;
  return true;
}

bool efi_scsi_data_in (uint8_t lun, __xdata uint8_t *data, uint16_t length) __reentrant;
