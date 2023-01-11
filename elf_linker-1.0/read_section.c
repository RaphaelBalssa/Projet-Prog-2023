
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "read_sect_table.h"
#include "util.h"


// This function fills a uint8_t table with the chose section's content
// It's the same as you built earlier 
uint8_t *get_section_data (SectionsTable sections, char * section, Elf32_Ehdr header, FILE * elf)
{
	int sectionNb;
	int use_section_number = 1;
	uint32_t section_address, section_size;
	int i = 0;
	uint8_t *section_data;
	
	// Needed to compile
	section_data = malloc(sizeof(uint8_t));
	
	//Determine if we're searching a section by name or number
	if (!isdigit(section[i]))
	{
		use_section_number = 0;
		i = strlen(section);
	}
	
	//Steps to follow if we're searching with section number
	if (use_section_number)
	{
		//Convert section number string into integer
		sectionNb = atoi(section);
		
		if (sectionNb < 0 || sectionNb > header.e_shnum)
		{
			printf("The specified section does not exist\n");
		}
		
		// The swaps were necessary
		section_address = Swap32(sections.sectTab[sectionNb].SectionHeader.sh_offset);

		section_size = Swap32(sections.sectTab[sectionNb].SectionHeader.sh_size);
		
		
		section_data = malloc(section_size*sizeof(uint8_t));
		fseek(elf, section_address, SEEK_SET);
		// This does not allow us to fill the table with the section's content...
		 
		
		if(!fread(section_data, section_size, 1, elf)){
			printf("Erreur \n");
		}
	}
	
	return section_data;
}


// This function allows us to also get the section in a structure we often use, so that 
// we can get header data, and information we can't access only with the uint8_t table.
Section get_section (SectionsTable sections, char * section, Elf32_Ehdr header, FILE * elf)
{
	int sectionNb;
	int use_section_number = 1;
	uint32_t section_address;
	int i = 0;
	Section section_resultat;
	
	printf("\n");
	
	//Determine if we're searching a section by name or number
	if (!isdigit(section[i]))
	{
		use_section_number = 0;
		i = strlen(section);
	}
	
	//Steps to follow if we're searching with section number
	if (use_section_number)
	{
		//Convert section number string into integer
		sectionNb = atoi(section);
		
		if (sectionNb < 0 || sectionNb > header.e_shnum)
		{
			printf("The specified section does not exist\n");
		}

		section_address = Swap32(sections.sectTab[sectionNb].SectionHeader.sh_offset);
		
		
		fseek(elf, section_address, SEEK_SET);
		if(!fread(&section_resultat, 40, 1, elf)){
			printf("Erreur \n");
		}
		
	}
	
	return section_resultat;
}

// Finally, the display function shows us the result of our functions.
// Then we display and move in the uint8_t tab byte by byte 

void dumpSection (uint8_t *contenuSection, Section section, int section_size, int sectionNb) {
	// Cas ou le contenu de la section est vide
	if (section_size == 0) {
		printf("Section '%d' has no data to dump.\n", sectionNb);
	} else {
		
		printf("Affichage de la section %d\n", sectionNb);		
			
		for(int i = 0; i < section_size; i++){
			printf("%02x", contenuSection[i]);
			
			if((i+1) % 4 == 0) {
				printf(" ");
			}
		}
		
	
		
	}
}
