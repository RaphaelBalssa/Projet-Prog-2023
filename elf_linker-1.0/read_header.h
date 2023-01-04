#ifndef __READ_HEADER_H__
#define __READ_HEADER_H__

#include <elf.h>

Elf32_Ehdr read_header (FILE * f);

void show_header (Elf32_Ehdr h);

#endif
