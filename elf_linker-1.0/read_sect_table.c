#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "read_header.h"
#include "read_sect_table.h"
#include "elf.h"
#include "read_header.h"

int cmpfunc (const void * a, const void * b){
	const Section * v1 = (Section *) a;
	const Section * v2 = (Section *) b;
   return ( v1 -> SectionHeader.sh_name >= v2 -> SectionHeader.sh_name);
}

//SectionsTable 
int get_sections (FILE * elf, Elf32_Ehdr header, int endianess)
{
	SectionsTable tab;
	tab.sectTab = (Section *) malloc (header.e_shnum * sizeof(Section));
	tab.nb_sect = header.e_shnum;
	
	
	printf("\n\n\n\n");


	fseek(elf, header.e_shoff, SEEK_SET);
	
	for (int i = 0; i < header.e_shnum; i++)
	{
		if (!fread(&tab.sectTab[i], 40, 1, elf))
		{
			return -1;
		}
	}

	qsort(tab.sectTab, tab.nb_sect, sizeof(Section), cmpfunc);

	fseek(elf, header.e_shoff, SEEK_SET);

	//uint32_t indexes[tab.nb_sect];


	int string_table_offset = Swap32(tab.sectTab[header.e_shstrndx].SectionHeader.sh_offset);
	int string_table_size = Swap32(tab.sectTab[header.e_shstrndx].SectionHeader.sh_size);

	char * res = NULL;

	for (int i = 0; i < tab.nb_sect; i++)
	{
		if (tab.nb_sect - i == 1)
		{
			res = fgets(tab.sectTab[i].SectionName, (string_table_offset + string_table_size) - (string_table_offset + Swap32(tab.sectTab[i].SectionHeader.sh_name) - 1), elf);
		}
		else
		{
			res = fgets(tab.sectTab[i].SectionName, (string_table_offset + Swap32(tab.sectTab[i + 1].SectionHeader.sh_name)) - (string_table_offset + Swap32(tab.sectTab[i].SectionHeader.sh_name) - 1), elf);			
		}
	}
	if (res!=NULL)
	{
		for (int i = 0; i < tab.nb_sect; i++)
		{
			printf("%s\n", tab.sectTab[i].SectionName);
		}
	}

	





	/*int string_table_offset = Swap32(tab.sectTab[header.e_shstrndx].SectionHeader.sh_offset);
	int string_table_size = Swap32(tab.sectTab[header.e_shstrndx].SectionHeader.sh_size);
	
	
	
	fseek(elf, string_table_offset + 1, SEEK_SET);
	//int j = 0;
	//int section_index = 0;
	//char table[20];
	for (int i = 0;  i < string_table_size; i++)
	{
		tab.sectTab[i].SectionName = (char *) malloc (20 * sizeof(char));
		if (fread(tab.sectTab[i].SectionName, sizeof(char), 20, elf))
		{
			printf("%s\n", tab.sectTab[i].SectionName);
		}
		char c = fgetc(elf);
		table[j] = c;
		if (c == 0)
		{
			//printf("%s\n", table);
			tab.sectTab[section_index].SectionName = (char *) malloc ((strlen(table)+1)*sizeof(char));
			strcpy(tab.sectTab[section_index].SectionName, table);
			tab.sectTab[section_index].SectionName[0] = '.';
			tab.sectTab[section_index].SectionName[strlen(table)] = '\0';
			for (int r = 0; r < strlen(table) + 1; r++)
			{

				printf("%c", tab.sectTab[section_index].SectionName[r]);
			}
			printf("%-17s", tab.sectTab[section_index].SectionName);
			printf("\n");
			section_index++;
			j = 0;
		}
		else
		{
			j++;
		}
	}*/
	
	
	
	for (int i = 0; i < tab.nb_sect; i++)
	{
		printf ("Section %d: \n", i);
			printf ("Name: %d\n",Swap32(tab.sectTab[i].SectionHeader.sh_name));
			printf ("Type %X\n",Swap32(tab.sectTab[i].SectionHeader.sh_type));
			printf ("Flags: %X\n",Swap32(tab.sectTab[i].SectionHeader.sh_flags));
			printf ("Address: %X\n",Swap32(tab.sectTab[i].SectionHeader.sh_addr));
			printf ("Offset: %X\n",Swap32(tab.sectTab[i].SectionHeader.sh_offset));
			printf ("Size: %X\n",Swap32(tab.sectTab[i].SectionHeader.sh_size));
			printf ("Link: %X\n",Swap32(tab.sectTab[i].SectionHeader.sh_link));
			printf ("Info: %X\n",Swap32(tab.sectTab[i].SectionHeader.sh_info));
			printf ("Addralign: : %X\n",Swap32(tab.sectTab[i].SectionHeader.sh_addralign));
			printf ("Entsize: %X\n",Swap32(tab.sectTab[i].SectionHeader.sh_entsize));
			printf ("\n\n\n\n");
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	printf("\n");
	
	
	
	
	
	printf ("\n\n\n\n");
	
	/*printf("String table index: %X\n", header.e_shstrndx);
	printf("String table offset: %X\n", Swap32(tab.sectTab[header.e_shstrndx].SectionHeader.sh_offset));
	printf("String table size (bytes): %d\n", Swap32(tab.sectTab[header.e_shstrndx].SectionHeader.sh_size));
	
	int string_table_offset = Swap32(tab.sectTab[header.e_shstrndx].SectionHeader.sh_offset);
	int string_table_size = Swap32(tab.sectTab[header.e_shstrndx].SectionHeader.sh_size);
	
	
	
	fseek(elf, string_table_offset + 1, SEEK_SET);
	int j = 0;
	char table[20];
	for (int i = 0;  i < string_table_size; i++)
	{
		char c = fgetc(elf);
		table[j] = c;
		if (c == 0)
		{
			printf("%s\n", table);
			j = 0;
		}
		else
		{
			j++;
			
		}
	}*/
	
	//printf("String table entry size (bytes): %d\n", Swap32(tab.sectTab[header.e_shstrndx].SectionHeader.sh_entsize));
	/*fseek(elf, header.e_shoff + (header.e_shstrndx * header.e_shentsize), SEEK_SET);
	
	for (int i = 0; i < tab.sectTab[header.e_shoff].SectionHeader.sh_size; i++)
	{
		//fseek(elf, header.e_shstrndx + (tab.sectTab[i].SectionHeader.sh_name * 40), SEEK_SET);
		char * name = (char *) malloc ((tab.sectTab[i].SectionHeader.sh_size + 1) * sizeof(char));
		if (fread(name, 1, tab.sectTab[header.e_shoff].SectionHeader.sh_entsize + 1, elf))
		{
			name[strlen(name)] = '\0';
			printf("Section %d, Name: %s\n", i, name);
		}
		
	}*/
	printf("\n\n\n\n");
	//return tab;




















/*	lire_sections_table(FILE *elfFile, Elf64_Ehdr header)
		Lit la table des sections dans le fichier elfFile
*/
/*SectionsList lire_sections_table(FILE * elfFile, Elf32_Ehdr header)
{
	// Placement du curseur au debut de la premiere section
	fseek(elfFile, header.e_shoff, SEEK_SET);

	// Lecture de l'en-tete de la premiere section
	for (int i = 0; i < header.e_shnum; i++)
	{
		// Lecture de l'en-tete de la section courante
		//fseek(elfFile, header.e_shoff + i * , SEEK_SET);
		int j = fread(&tableSection.sectTab[i], sizeof(header.e_shentsize), 1, elfFile);
		if (j)
		{
			j =0;
		}

		// Allocation memoire des donnees de la taille de la section definie par tab[i]
		//tableSection[i] = malloc(tableSection[i].sh_size);
	}
	
	
	//fread(&sectHdr, 1, sizeof(sectHdr), elfFile);

	// Allocation dans sectNames du nom de la premiere section
	sectNames = malloc(sectHdr.sh_size);
	fseek(elfFile, sectHdr.sh_offset, SEEK_SET);
	fread(sectNames, 1, sectHdr.sh_size, elfFile);

	// Preparation de la table de sections
	tableSection = malloc(sizeof(Elf32_Shdr) * header.e_shnum);

	// Parcours de toutes les sections
	for (int i = 0; i < header.e_shnum; i++)
	{
		// Lecture de l'en-tete de la section courante
		fseek(elfFile, header.e_shoff + i * sizeof(tableSection[i]), SEEK_SET);
		fread(&tableSection[i], 1, sizeof(tableSection[i]), elfFile);

		// Allocation memoire des donnees de la taille de la section definie par tab[i]
		tableSection[i] = malloc(tableSection[i].sh_size);
	}
	free(sectNames);*/
	//return tableSection;
	return 0;
}


/*	afficher_sections_table(SectionsList liste, uint32_t offset)
		Affichage de la table des sections et des informations pour chaque section
*/
/*void afficher_sections_table(FILE * elf, SectionsList * tableSection, Elf32_Ehdr header)
{
	printf("There are %d section headers, starting at offset 0x%x:\n\n", header.e_shnum, header.e_shoff);
	printf("Section Headers:\n  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al\n");
	
	
	
	for (int i = 0; i < header.e_shnum; i++)
	{
		char name[30] = "";
		fseek(elf, header.e_shstrndx + tableSection->sectTab[i].header.sh_name, SEEK_SET);
		int j = fread(&name, 30, 1, elf);
		if (j)
		{
			j = 0;
		}
		//strcpy(name, header.shstrndx);
		if (strlen(name) > 17)
		{
			name[17] = '\0';
		}*/
		
		/*printf("  [%2d] %-17s %X %08x %06x ", i,
			   name,
			   tableSection -> sectTab[i].header.sh_type,
			   tableSection -> sectTab[i].header.sh_addr,
			   tableSection -> sectTab[i].header.sh_offset);
		printf("%06x %02x %X %2d  %2d %2d\n",
			   tableSection -> sectTab[i].header.sh_size,
			   tableSection -> sectTab[i].header.sh_entsize,
			   tableSection -> sectTab[i].header.sh_flags,
			   tableSection -> sectTab[i].header.sh_link,
			   tableSection -> sectTab[i].header.sh_info,
			   tableSection -> sectTab[i].header.sh_addralign);
	}*/

	/* En termes de flags, certains n'étaient pas présents dans la documentation.
	   W, A, X sont dans la documentation chapitre 1-13 et 1-14 Figure 1-11.
	   Les autres flags sont dans la fonction reference readelf -S <nomFichier> */
	/*printf("Key to Flags:\n");
	printf("  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),\n");
	printf("  L (link order), O (extra OS processing required), G (group), T (TLS),\n");
	printf("  C (compressed), x (unknown), o (OS specific), E (exclude),\n");
	printf("  p (processor specific)\n");
}*/
