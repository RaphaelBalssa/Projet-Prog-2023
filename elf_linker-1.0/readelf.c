#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "util.h"
#include "read_header.h"
#include "read_sect_table.h"
#include "read_section.h"

int main (int argc, char * argv[])
{	
	if (argc != 2)
	{
		printf ("Usage: ./readelf <name of file>");
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
	char opt;
	SectionsTable tabSections;
	tabSections = get_sections(elf, header, big_endian);
	char s[10];
  	while (opt != 'q')
  	{
  		printf("\n\n\ndisplay header (H) | Display sections(S) | display selcted section (x)| quit (q)\n");
  		int y=scanf(" %c", &opt);
  		if(y==1)
  		{
			switch (opt)
			{
				case 'H':
					show_header (header);
					break;
				case 'S':
					afficher_sections(elf, header, big_endian, tabSections);
				 	break;
				case 'x':
					printf("\n\n\n enter the section you want to display :");
					y=scanf(" %s", s);
  					if(y==1)
  					{
  						int n_sec = atoi(s);
  						uint8_t *sectionLue;
						Section sect;
						sectionLue = get_section_data(tabSections,s, header, elf);
						sect = get_section(tabSections, s, header, elf);
						dumpSection(sectionLue, sect, Swap32(tabSections.sectTab[n_sec].SectionHeader.sh_size), n_sec);

  					}
					break;
				default:
					break;
			}
		}
	}
	/*show_header (header);
	
	SectionsTable tabSections;
	tabSections = get_sections(elf, header, big_endian);
	afficher_sections(elf, header, big_endian, tabSections);*/
	
	//uint8_t *sectionLue;
	//Section sect;
	//sectionLue = get_section_data(tabSections,"13", header, elf);
	//sect = get_section(tabSections,s, header, elf);
	//int n_sec = atoi(s);
	//dumpSection(sectionLue, sect, Swap32(tabSections.sectTab[13].SectionHeader.sh_size), 13);
	
	
	fclose(elf);
}


