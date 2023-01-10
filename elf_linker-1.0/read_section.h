#ifndef __READ_SECTION_H__
#define __READ_SECTION_H__

uint8_t *get_section_data (SectionsTable sections, char * section, Elf32_Ehdr header, FILE * elf);
Section get_section (SectionsTable sections, char * section, Elf32_Ehdr header, FILE * elf);
void dumpSection (uint8_t *contenuSection, Section section, int section_size, int sectionNb);

#endif
