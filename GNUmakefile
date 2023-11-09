CC ?= sdcc

modules/sdcc:
	svn checkout svn://svn.code.sf.net/p/sdcc/code/trunk/sdcc modules/sdcc

sdcc:
	command -v $(CC) || $(MAKE) modules/sdcc

.PHONY: sdcc
