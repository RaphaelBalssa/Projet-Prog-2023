#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

int main (int argc, char * argv[])
{
	if (argc != 2)
	{
		printf ("Usage: ./readelf <name of file>");
		return 0;
	}
	
	//Opening the file in binary form for reading
	FILE * elf = fopen(argv[1], "rb");
	
	
	Elf32_Ehdr header = read_header(elf);
}
