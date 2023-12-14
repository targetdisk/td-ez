export PATH := var/bin:$(PATH)
PYTHON ?= python3

efi-booter/efi-booter.ihex: libfx2 $(wildcard efi-booter/*.c efi-booter/*.h)
	$(MAKE) -C efi-booter

efi-booter: efi-booter/efi-booter.ihex

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

var/efi/targetdisk.efi:
	git submodule update --init --recursive -- modules/efi
	$(MAKE) -Cmodules/efi
	cp modules/efi/targetdisk.efi $@

var/bin/fx2tool:
	$(MAKE) sdcc
	git submodule update --init --recursive -- $@
	PATH=$(PATH) $(MAKE) -j$(shell nproc) -C$@/firmware/library
	. var/bin/activate && $(PYTHON) -m pip install $@/software

libfx2: var/bin/fx2tool

sdcc:
	command -v $@ || $(MAKE) var/bin/$@

.PHONY: tags sdcc libfx2 efi-booter
