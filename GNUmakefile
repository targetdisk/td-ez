export PATH := var/bin:$(PATH)
PYTHON ?= python3

var:
	mkdir -p $@
	$(PYTHON) -m venv var

var/bin/sdcc: var
	git submodule update --init --recursive -- $@
	scripts/build-sdcc

var/bin/fx2tool:
	$(MAKE) sdcc
	git submodule update --init --recursive -- $@
	PATH=$(PATH) $(MAKE) -j$(shell nproc) -C$@/firmware/library
	. var/bin/activate && $(PYTHON) -m pip install $@/software

libfx2: var/bin/fx2tool

sdcc:
	command -v $@ || $(MAKE) var/bin/$@

.PHONY: sdcc libfx2 efi-booter
