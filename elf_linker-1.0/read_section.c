#include <stdio.h>
#include <string.h>
#include <ctype.h>

char * get_section (SectionsList sections, Elf32_Ehdr header, char * section_dump, char * section)
{
	int sectionNb = -1, section_size = 0, is_section_number = 1, section_address;
	int i = 0;
	
	//Determine if we're searching a section by name or number
	while (i != strlen(section))
	{
		if (!isdigit(section[i])
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
		
		if (sectionNb
		
		//The offset saved inside the section header table, is the offset we need to add
		//from the start of the file to reach the section
	}
}

void dumpSection (SectionsList sections, char * section, FILE * elf)
{
	if (is_section_number)
	{
		//Find the offset of the start of the section inside the file and set the cursor to the
		//	first byte of that section
		int section_address = sections -> sectTab[sectionNb] -> header.sh_offset;
		
		fseek(elf, section_address, SEEK_SET);
		
		section_size = sections -> sectTab[sectionNb] -> header.sh_size;
		section_dump = (char *) malloc (section_size * sizeof(char));
		
		//Read the whole section inside our buffer
		fread(section_dump, 1, section_size, elf);
		
		//Print the section, byte by byte. Every 16 bytes, we change line
		int line = 1;
		char * ligne = (char *) malloc (17 * sizeof(char));
		ligne[0] = '\0';
		for (int i = 0; i < strlen(section_dump); i++)
		{
			printf("%X ", section_dump[i]);
			strncat(ligne, section_dump[i], 1);
			if ((line * 16 % i) == 1)
			{
				line++;
				printf("%s\n",ligne);
				ligne[0] = '\0';
			}
		}
	}
	/*else
	{
		char * name;
		utoa(sections.sectTab -> header.sh_name, name, 
		for (int i = 0; i < sections.nb_sect; i++)
		{
			if (strcmp(section, sections
		}
	}*/
}
