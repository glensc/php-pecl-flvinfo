flvinfo: flvinfo.c
	$(LIBTOOL) --mode=link $(CC) -o $@ $< $(FLVINFO_SHARED_LIBADD) $(INCLUDES)

# recreate makefile if this file is modified
Makefile: Makefile.frag
	cp $< $@
	./config.status --recheck

test1: $(all_targets)
	php -dextension_dir=modules flvinfo.php
