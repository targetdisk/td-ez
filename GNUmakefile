CC ?= sdcc

modules:
	mkdir $@

modules/sdcc: modules
	svn checkout svn://svn.code.sf.net/p/sdcc/code/trunk/sdcc $@

sdcc:
	command -v $(CC) || $(MAKE) modules/sdcc

.PHONY: sdcc
