ACLOCAL_AMFLAGS = -I m4

AM_CFLAGS=-Wall -Werror -g
AM_CFLAGS+=-D DEBUG
AM_CFLAGS+=-D WARNING
# Uncomment if performance when running with -DDEBUG is an issue
# Warning, if uncommented, issuing calls to debug functions during options
# parsing might result in debug flag incorrectly set to 0 for some files
#AM_CFLAGS+=-D CACHE_DEBUG_FLAG



SUBDIRS=
SUBDIRS+=. Examples_fusion

bin_PROGRAMS=
bin_PROGRAMS+=Options_and_debug_example
bin_PROGRAMS+=readelf


COMMON=debug.h debug.c util.h util.c

EXTRA_DIST=filtre.pl
Options_and_debug_example_SOURCES=$(COMMON) Options_and_debug_example.c
readelf_SOURCES=$(COMMON) readelf.c read_header.c read_header.h read_sect_table.c read_sect_table.h read_section.c read_section.h

EXTRA_DIST+=

