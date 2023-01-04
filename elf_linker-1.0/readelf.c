#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "read_header.h"

int main (int argc, char * argv[])
{
	if (argc != 2)
	{
		printf ("Usage: ./readelf <name of file>");
		return -1;
	}
	
	//Opening the file in binary form for reading
	FILE * elf = fopen(argv[1], "rb");
	
	if (elf == NULL)
	{
		printf ("Error opening %s. Program terminated", argv[1]);
		return -1;
	}
	
	//Retrieval of the file header and display of said header on the standard output (the screen)
	Elf32_Ehdr header = read_header(elf);
	
	/*for (int i = 0; i < 16; i++)
	{
		printf("%02X ", header.e_ident[i]);
	}*/
	
	show_header (header);
	
	fclose(elf);
}
