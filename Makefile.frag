PACKAGE_NAME = flvinfo
PACKAGE_VERSION = 0.0.1
PACKAGE_FILES_STD = CREDITS EXPERIMENTAL config.m4 Makefile.frag package.xml
PACKAGE_FILES_SOURCES = flvinfo.c flvinfo.php php_flvinfo.c php_flvinfo.h
PACKAGE_FILES_TESTS = tests
PACKAGE_FILES = $(PACKAGE_FILES_STD) $(PACKAGE_FILES_SOURCES) $(PACKAGE_FILES_TESTS)

flvinfo: flvinfo.c
	$(LIBTOOL) --mode=link $(CC) -o $@ $< $(FLVINFO_SHARED_LIBADD) $(INCLUDES)

# recreate makefile if this file is modified
Makefile: Makefile.frag
	cp $< $@
	./config.status --recheck

test1: $(all_targets)
	php -dextension_dir=modules flvinfo.php

dist:
	rm -rf $(PACKAGE_NAME)-$(PACKAGE_VERSION)
	mkdir  $(PACKAGE_NAME)-$(PACKAGE_VERSION)
	cp -a $(PACKAGE_FILES) $(PACKAGE_NAME)-$(PACKAGE_VERSION)
	tar cjf $(PACKAGE_NAME)-$(PACKAGE_VERSION).tar.bz2 --exclude=CVS $(PACKAGE_NAME)-$(PACKAGE_VERSION)
	rm -rf $(PACKAGE_NAME)-$(PACKAGE_VERSION)
