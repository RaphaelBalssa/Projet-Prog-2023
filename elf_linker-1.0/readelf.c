#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "util.h"
#include "read_header.h"
#include "read_sect_table.h"

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
	
	//Retrieval of the file header and display of said header on the standard output (the screen)
	Elf32_Ehdr header = read_header(elf);
	
	show_header (header);
	
	SectionsTable tabSections;
	tabSections = get_sections(elf, header, big_endian);
	afficher_sections(elf, header, big_endian, tabSections);
	
	fclose(elf);
}
