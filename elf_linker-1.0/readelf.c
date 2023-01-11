#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "util.h"
#include "read_header.h"
#include "read_sect_table.h"
#include "read_section.h"

int main (int argc, char * argv[])
{	
	if (argc < 3)
	{
		printf("Usage: readelf elf-file <option> \n");
		printf(" Display information about the contents of ELF format files\n");
		printf(" Options are : \n");
		printf("  -h : Display the ELF file header\n");
		printf("  -S : Display the sections' header\n");
		printf("  -s : Display the symbol table\n");
		printf("  -r : Display the relocations (if present)\n");
		printf("  -x : Dump the contents of section <number|name> as bytes\n");
		return -1;
	}
	
	int big_endian = is_big_endian();
	
	//Opening the file in binary form for reading
	FILE * elf = fopen(argv[1], "rb");
	
	if (elf == NULL)
	{
		printf ("Error opening %s. Program terminated", argv[1]);
		return -1;
	}
	
	fseek(elf, 0, SEEK_SET);
	
	//Retrieval of the file header and display of said header on the standard output (the screen)
	
	Elf32_Ehdr header = read_header(elf);
	SectionsTable tabSections;
	tabSections = get_sections(elf, header, big_endian);
	
	switch(argv[2][1]){
		case 'H':
		
			show_header (header);
			break;
		case 'S':
		
			afficher_sections(elf, header, big_endian, tabSections);
			break;
		case 'x':
		
			int nb_section = atoi(argv[3]);
			if(nb_section < 0 && nb_section > header.e_shnum){
				printf("Numero de section %d incorrect \n", nb_section);
			} else {
			
				uint8_t *sectionLue;
				Section sect;
				sectionLue = get_section_data(tabSections,argv[3], header, elf);
				sect = get_section(tabSections,argv[3], header, elf);
				dumpSection(sectionLue, sect, Swap32(tabSections.sectTab[nb_section].SectionHeader.sh_size), nb_section);
			
			}
			
			break;
				
		default:
		
			printf("Argument incorrect, veuillez recommencer \n");
			break;
	}
	fclose(elf);
}


