# Targetdisk Cable Firmware
### for Cypress EZ-USB FX2

This firmware is for the Cypress CY7C68013 EZ-USB FX2 chip (well for two
FX2 chips, actually).

## What is this?

My USB target disk solution allows any UEFI-compatible motherboard to share all
attached block storage devices with another computer as if they were just regular
USB mass storage devices.

![diagram of how this all works](fx2-sketch.png)

1. The business end of our dongle device attaches to a target computer.  The
   target computer loads and executes the Targetdisk UEFI runtime hosted on
   the business end of our dongle.
2. The UEFI runtime on the target device reflashes the business end of our
   dongle device with FIFO-establishing firmware.
3. After the business end of the dongle reboots, it lets the other FX2 know
   that it's time to wake up and establish our hardware FIFO.  The hardware
   FIFO then begins to proxy SCSI commands from the mass storage interface end
   of our dongle to the target computer's UEFI runtime.

## Flashing
Note that I have only successfully loaded firmware with the Python `fx2tool`
so far.  More details soon!
