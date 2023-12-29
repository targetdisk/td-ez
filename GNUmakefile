export PATH := $(CURDIR)/var/bin:$(PATH)
PYTHON ?= python3

# Pulled from the Winbond W25Q128FV dataheet
SPI_PAGE_SIZE ?= 256
SPI_N_PAGES ?= 65536
BLANK_IMG ?= var/spiflash/blank_$(SPI_PAGE_SIZE)x$(SPI_N_PAGES).img
ESP_IMG ?= var/spiflash/ESP_$(SPI_PAGE_SIZE)x$(SPI_N_PAGES).img

efi-booter/efi-booter.ihex: libfx2 $(wildcard efi-booter/*.c efi-booter/*.h)
	$(MAKE) -C efi-booter

efi-booter: efi-booter/efi-booter.ihex

load-booter: efi-booter/efi-booter.ihex
	sudo fx2tool load $<

var/spiflash:
	mkdir -p $@

$(BLANK_IMG): var/spiflash var/.has_sgdisk
	dd if=/dev/zero bs=$(SPI_PAGE_SIZE) count=$(SPI_N_PAGES) of=$@
	sgdisk -a 1 --new=0:0:0 $@
	sgdisk --change-name=1:"Targetdisk (EFI)" $@
	sgdisk --typecode=1:ef00 $@
	sgdisk -A 1:set:0 $@
	sgdisk -A 1:set:60 $@
	scripts/mk-esp $@
	@sgdisk -p $@

blank-img: $(BLANK_IMG)

var/mnt: var
	mkdir -p $@

$(ESP_IMG): $(BLANK_IMG) var/efi/targetdisk.efi var/mnt
	cp $(BLANK_IMG) $@
	scripts/populate-esp $@

esp-img: $(ESP_IMG)

flash-spi: $(ESP_IMG)
	minipro -p W25Q128FV@SOIC8 -w $<

tags: libfx2
	find modules/libfx2/firmware/library -name '*.c' -print0 | xargs -0 ctags -dt
	find modules/libfx2/firmware/library -name '*.h' -print0 | xargs -0 ctags -adt
	find efi-booter -name '*.c' -print0 | xargs -0 ctags -adt
	find efi-booter -name '*.h' -print0 | xargs -0 ctags -adt

var:
	mkdir -p $@
	$(PYTHON) -m venv var

var/bin/sdcc: var
	git submodule update --init --recursive -- modules/sdcc
	scripts/build-sdcc

modules/efi/gfx/img_data.h:
	git submodule update --init --recursive -- modules/efi
	. var/bin/activate && cd modules/efi/gfx && ./configure.py

var/efi: var
	mkdir -p $@

var/efi/targetdisk.efi: modules/efi/gfx/img_data.h var/efi
	$(MAKE) -Cmodules/efi
	cp modules/efi/targetdisk.efi $@

efi: var/efi/targetdisk.efi

efitest: efi
	modules/efi/qemu_test.sh var/efi

var/bin/fx2tool:
	$(MAKE) sdcc
	git submodule update --init --recursive -- modules/libfx2
	PATH=$(PATH) $(MAKE) -j$(shell nproc) -Cmodules/libfx2/firmware/library
	. var/bin/activate && $(PYTHON) -m pip install modules/libfx2/software

libfx2: var/bin/fx2tool

sdcc:
	command -v $@ || $(MAKE) var/bin/$@

var/.has_sgdisk:
	@command -v sgdisk || (echo Please install gptfdisk/gdisk >&2 && exit 1)
	touch var/.has_sgdisk

.PHONY: tags sdcc libfx2 efi-booter blank-img esp-img efi efitest
