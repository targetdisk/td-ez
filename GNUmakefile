CC ?= sdcc

var:
	mkdir $@

modules:
	mkdir $@

modules/sdcc: modules var
	svn checkout svn://svn.code.sf.net/p/sdcc/code/trunk/sdcc $@
	scripts/build-sdcc

modules/fxload:
	git submodule update --init --recursive -- $@

var/bin/fxload: modules/fxload
	$(MAKE) -C$< -j$(shell nproc)
	PREFIX=$(CURDIR)/var SBINDIR=$(CURDIR)/var/bin $(MAKE) -C$< install

fxload: var/bin/fxload

sdcc:
	command -v $(CC) || $(MAKE) modules/sdcc

.PHONY: sdcc fxload
