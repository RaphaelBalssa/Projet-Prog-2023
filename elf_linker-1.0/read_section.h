#ifndef __READ_SECTION_H__
#define __READ_SECTION_H__

uint8_t * get_section (SectionsTable sections, char * section, Elf32_Ehdr header, FILE * elf);

void dumpSection (uint8_t * section, int section_size, int sectionNb);

#endif
