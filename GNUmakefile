export PATH := var/bin:$(PATH)

src/td-ez.ihex: modules/libfx2 $(wildcard src/*.c src/*.h)
	$(MAKE) -Csrc

var:
	mkdir $@

modules:
	mkdir $@

modules/sdcc: modules var
	git submodule update --init --recursive -- $@
	scripts/build-sdcc

modules/fxload:
	git submodule update --init --recursive -- $@

modules/libfx2: sdcc
	git submodule update --init --recursive -- $@
	PATH=$(PATH) $(MAKE) -j$(shell nproc) -C$@/firmware/library

var/bin/fxload: modules/fxload
	$(MAKE) -C$< -j$(shell nproc)
	PREFIX=$(CURDIR)/var SBINDIR=$(CURDIR)/var/bin $(MAKE) -C$< install

fxload: var/bin/fxload

sdcc:
	command -v $@ || $(MAKE) modules/sdcc

.PHONY: sdcc fxload
