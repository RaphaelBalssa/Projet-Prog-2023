#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "read_sect_table.h"
#include "util.h"

uint8_t * get_section (SectionsTable sections, char * section, Elf32_Ehdr header, FILE * elf)
{
	int sectionNb = -1, is_section_number = 1;
	uint32_t section_address, section_size;
	int i = 0;
	
	//Determine if we're searching a section by name or number
	while (i != strlen(section))
	{
		if (!isdigit(section[i]))
		{
			is_section_number = 0;
			i = strlen(section);
		}
		else
		{
			i++;
		}
	}
	
	//Steps to follow if we're searching with section number
	if (is_section_number)
	{
		//Convert section number string into integer
		sectionNb = atoi(section);
		
		if (!(sectionNb >=0 && sectionNb <= header.e_shnum))
		{
			printf("The specified section does not exist\n");
			return NULL;
		}
		
		section_address = Swap32(sections.sectTab[sectionNb].SectionHeader.sh_offset);
		printf("\n\n\n\n");
		printf("%X",section_address);
		printf("\n\n\n\n");
		section_size = sections.sectTab[sectionNb].SectionHeader.sh_size;
		
		uint8_t * section_dump = (uint8_t *) malloc (section_size*sizeof(uint8_t));
				
		fseek(elf, section_address, SEEK_SET);
		
		
		
		return section_dump;
	}
	return NULL;
}

void dumpSection (uint8_t * section, int section_size, int sectionNb)
{
	printf("Affichage de la section %d\n", sectionNb);
	//Print the section, byte by byte.
	for (int i = 0; i < section_size; i++)
	{
		printf("%X ", section[i]);
	}
}
