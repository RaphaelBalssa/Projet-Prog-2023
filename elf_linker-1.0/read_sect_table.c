#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "read_header.h"
#include "read_sect_table.h"
#include "elf.h"
#include "read_header.h"


// Fonction de comparaison entre deux noms pour trier les sections
int cmpfunc (const void * a, const void * b){
	const Section * v1 = (Section *) a;
	const Section * v2 = (Section *) b;
   return ( v1 -> SectionHeader.sh_name >= v2 -> SectionHeader.sh_name);
}

/*	lire_type(long num, char *sh_type)
		Lit la valeur donnee dans le premier parametre afin de definir la valeur du second
*/
void lire_type(long num, char *sh_type)
{
	// Documentation chapitre 1-11 Figure 1-9
	switch (num)
	{
	case 0:
		strcpy(sh_type, "NULL");
		break;
	case 1:
		strcpy(sh_type, "PROGBITS");
		break;
	case 2:
		strcpy(sh_type, "SYMTAB");
		break;
	case 3:
		strcpy(sh_type, "STRTAB");
		break;
	case 4:
		strcpy(sh_type, "RELA");
		break;
	case 5:
		strcpy(sh_type, "HASH");
		break;
	case 6:
		strcpy(sh_type, "DYNAMIC");
		break;
	case 7:
		strcpy(sh_type, "NOTE");
		break;
	case 8:
		strcpy(sh_type, "NOBITS");
		break;
	case 9:
		strcpy(sh_type, "REL");
		break;
	case 10:
		strcpy(sh_type, "SHLIB");
		break;
	case 11:
		strcpy(sh_type, "DYNSYM");
		break;
	case 14:
		strcpy(sh_type, "INIT_ARRAY");
		break;
	case 15:
		strcpy(sh_type, "FINI_ARRAY");
		break;
	case 16:
		strcpy(sh_type, "PREINIT_ARRAY");
		break;
	case 17:
		strcpy(sh_type, "GROUP");
		break;
	case 18:
		strcpy(sh_type, "SYMTAB_SHNDX");
		break;
	case 0x6ffffff6:
		strcpy(sh_type, "GNU_HASH");
		break;
	case 0x6ffffffd:
		strcpy(sh_type, "VERDEF");
		break;
	case 0x6ffffffe:
		strcpy(sh_type, "VERNEED");
		break;
	case 0x6fffffff:
		strcpy(sh_type, "VERSYM");
		break;
	case 0x70000000:
		strcpy(sh_type, "LOPROC");
		break;
	case 0x7fffffff:
		strcpy(sh_type, "HIPROC");
		break;
	case 0x80000000:
		strcpy(sh_type, "LOUSER");
		break;
	case 0xffffffff:
		strcpy(sh_type, "HIUSER");
		break;
	default:
		strcpy(sh_type, "UNKOWN");
		break;
	}
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

/*
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
	*/
	
 
 
  //TODO : Faire une fonction pour switch sur les types et sur les flags
  //       Trier les sections
  //       Espoir sur les noms
   
	printf("There are %d section headers, starting at offset 0x%x:\n\n", tab.nb_sect, header.e_shoff);
	printf("Section Headers:\n  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al\n");

	for (int i = 0; i < tab.nb_sect; i++)
	{
    //printf("  [%2d] %-17s %X %08x %06x ", i,
		printf("  [%2d] %X %08x %06x ", i,
			   //Swap32(tab.sectTab[i].SectionHeader.sh_name),
			   Swap32(tab.sectTab[i].SectionHeader.sh_type),
			   Swap32(tab.sectTab[i].SectionHeader.sh_addr),
			   Swap32(tab.sectTab[i].SectionHeader.sh_offset));
		printf("%06x %02x %X %2d  %2d %2d\n",
			   Swap32(tab.sectTab[i].SectionHeader.sh_size),
			   Swap32(tab.sectTab[i].SectionHeader.sh_entsize),
			   Swap32(tab.sectTab[i].SectionHeader.sh_flags),
			   Swap32(tab.sectTab[i].SectionHeader.sh_link),
			   Swap32(tab.sectTab[i].SectionHeader.sh_info),
			   Swap32(tab.sectTab[i].SectionHeader.sh_addralign));
	}

	/* En termes de flags, certains n'étaient pas présents dans la documentation.
	   W, A, X sont dans la documentation chapitre 1-13 et 1-14 Figure 1-11.
	   Les autres flags sont dans la fonction reference readelf -S <nomFichier> */
	printf("Key to Flags:\n");
	printf("  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),\n");
	printf("  L (link order), O (extra OS processing required), G (group), T (TLS),\n");
	printf("  C (compressed), x (unknown), o (OS specific), E (exclude),\n");
	printf("  p (processor specific)\n");
 
 	return 0;
}

	
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


