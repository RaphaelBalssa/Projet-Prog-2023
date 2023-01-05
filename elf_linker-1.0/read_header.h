#ifndef __READ_HEADER_H__
#define __READ_HEADER_H__

#include <elf.h>

uint16_t Swap16(uint16_t value);

uint32_t Swap32(uint32_t value);

Elf32_Ehdr read_header (FILE * f);

void show_header (Elf32_Ehdr h);

#endif
