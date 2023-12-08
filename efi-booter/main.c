#include <fx2delay.h>
#include <fx2regs.h>
#include <fx2usb.h>

#include "booter-usb.h"
#include "efi_scsi.h"

volatile bool pending_ep6_in;

void isr_IBN(void) __interrupt {
  pending_ep6_in = true;
  CLEAR_USB_IRQ();
  NAKIRQ = _IBN;
  IBNIRQ = _IBNI_EP6;
}

int main() {
  CPUCS = _CLKSPD1;

  REVCTL = _ENH_PKT | _DYN_OUT;

  /* According to the technical reference manual, this macro is magic.  Trust.  */
  SYNCDELAY;

  FIFORESET = _NAKALL;

  /* Enable endpoint |  BULK TYPE | OUT direction | double-buffered */
  EP2CFG = _VALID | _TYPE1 | _BUF1;
  EP2CS = 0;  /* Reset Endpoint control and status bit field register */

  EP6CFG = _VALID | _TYPE1 | _DIR | _BUF1;
  EP6CS = 0;

  /* Disable endpoints 4 and 8 */
  EP4CFG &= ~_VALID;
  EP8CFG &= ~_VALID;

  /* Enable IN-BULK-NAK interrupts for EP6 */
  IBNIE = _IBNI_EP6;
  NAKIE = _IBN;

  /* Reset the hardware FIFOs */
  SYNCDELAY;
  FIFORESET = _NAKALL|2;
  SYNCDELAY;
  OUTPKTEND = _SKIP|2;
  SYNCDELAY;
  OUTPKTEND = _SKIP|2;
  SYNCDELAY;
  FIFORESET = _NAKALL|6;
  SYNCDELAY;
  FIFORESET = 0;

  efi_spi_init();

  // Re-enumerate, to make sure our descriptors are picked up correctly.
  usb_init( true );

  for ( ;; )
  {
    /* Handle OUT requests from host */
    if ( !( EP2CS & _EMPTY ) )
    {
      uint16_t length = ( EP2BCH << 8 ) | EP2BCL;
      if ( usb_mass_storage_bbb_bulk_out( &usb_mass_storage_state, EP2FIFOBUF, length ) )
      {
        EP2BCL = 0;
      }
      else
      {
        EP2CS  = _STALL;
        EP6CS  = _STALL;
      }
    }

    if ( pending_ep6_in )
    {
      __xdata uint16_t length;
      if ( usb_mass_storage_bbb_bulk_in( &usb_mass_storage_state, EP6FIFOBUF, &length ) )
      {
        if ( length > 0 )
        {
          EP6BCH = length >> 8;
          SYNCDELAY;
          EP6BCL = length;
        }
      }
      else
      {
        EP6CS  = _STALL;
      }

      pending_ep6_in = false;
    }
  }
}
