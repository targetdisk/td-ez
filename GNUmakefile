CC ?= sdcc

var:
	mkdir $@

modules:
	mkdir $@

modules/sdcc: modules var
	svn checkout svn://svn.code.sf.net/p/sdcc/code/trunk/sdcc $@
	scripts/build-sdcc

sdcc:
	command -v $(CC) || $(MAKE) modules/sdcc

.PHONY: sdcc
