#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "util.h"

//Swaps endianess on a 16-bit value
uint16_t Swap16(uint16_t value)
{
    return (((value & 0x00FF) << 8) |
            ((value & 0xFF00) >> 8));
}

//Swaps endianess on a 32-bit value
uint32_t Swap32(uint32_t value) 
{
    return (((value & 0x000000FF) << 24) |
            ((value & 0x0000FF00) <<  8) |
            ((value & 0x00FF0000) >>  8) |
            ((value & 0xFF000000) >> 24));
}

Elf32_Ehdr read_header(FILE * elf)
{
	Elf32_Ehdr h;
	
	if (fread(&h, sizeof(h), 1, elf))
	{
		if (!is_big_endian())
		//if (h.e_ident[EI_DATA] == 2)
		{
			h.e_type = Swap16(h.e_type);
			h.e_version = Swap32(h.e_version);
			h.e_entry = Swap32(h.e_entry);
			h.e_phoff = Swap32(h.e_phoff);
			h.e_shoff = Swap32(h.e_shoff);
			h.e_flags = Swap32(h.e_flags);
			h.e_ehsize = Swap16(h.e_ehsize);
			h.e_phentsize = Swap16(h.e_phentsize);
			h.e_phnum = Swap16(h.e_phnum);
			h.e_shentsize = Swap16(h.e_shentsize);
			h.e_shnum = Swap16(h.e_shnum);
			h.e_shstrndx = Swap16(h.e_shstrndx);
		}
	}
	
	if(i == 1){
        	return h;
    	} else {
        	printf("irrelevant test to avoid warning");
    	}
    
    	return h;
}

void show_header (Elf32_Ehdr h)
{
  printf("En-tête ELF:\n");
	
  //Magic Number
  printf("  Magique:   ");
	for (int i = 0; i < 15; i++)
	{
		printf("%02X ", h.e_ident[i]);
	}
	printf("%02X\n", h.e_ident[15]);
	
	
	//File Class
	switch(h.e_ident[EI_CLASS])
	{
		case 0:
			printf("  Classe:                            Invalide\n");
			break;
		case 1:
			printf("  Classe:                            ELF32\n");
			break;
		case 2:
			printf("  Classe:                            ELF64\n");
			break;
	}
	    
	//File Data:
	switch(h.e_ident[EI_DATA])
	{
		case 0:
			printf("  Données:                           Invalide\n");
			break;
		case 1:
			printf("  Données:                          complément à 2, système à octets de poids fort d'abord (little endian)\n");
			break;
		case 2:
			printf("  Données:                          complément à 2, système à octets de poids fort d'abord (big endian)\n");
			break;
	}
	
	//ELF Version
	if (h.e_ident[EI_VERSION] == 1)
	{
		printf("  Version:                           1 (actuelle)\n");
	}
	else
	{
		printf("  Version:                           Invalide\n");
	}
	
	//OS/ABI
	switch (h.e_ident[EI_OSABI])
	{
    	case 0 :
    		printf("  OS/ABI:                            UNIX - System V\n");
    		break;
 	case 1 :
    		printf("  OS/ABI:                            HP-UX\n");
    		break;
	case 2 :
		printf("  OS/ABI:                            NetBSD\n");
    		break;
	case 3 :
    		printf("  OS/ABI:                            Linux\n");
    		break;
    	case 4:
		printf("  OS/ABI:                            GNU Hurd\n");
    		break;
    	case 6 :
    		printf("  OS/ABI:                            Sun Solaris\n");
    		break;
    	case 7 :
    		printf("  OS/ABI:                            IBM AIX\n");
    		break;
    	case 8 :
    		printf("  OS/ABI:                            SGI Irix\n");
    		break;
    	case 9 :
    		printf("  OS/ABI:                            FreeBSD\n");
    		break;
    	case 10 :
    		printf("  OS/ABI:                            Compaq TRU64\n");
    		break;
    	case 11 :
    		printf("  OS/ABI:                            Novell Modesto\n");
    		break;
    	case 12 :
    		printf("  OS/ABI:                            OpenBSD\n");
    		break;
    	case 13:
    		printf("  OS/ABI:                            OpenVMS\n");
    		break;
    	case 14:
    		printf("  OS/ABI:                            NonStop Kernel\n");
    		break;
    	case 15:
    		printf("  OS/ABI:                            AROS\n");
    		break;
    	case 16:
    		printf("  OS/ABI:                            Fenix OS\n");
    		break;
    	case 17:
    		printf("  OS/ABI:                            CloudABI\n");
    		break;
    	case 18:
    		printf("  OS/ABI:                            Stratus Technologies OpenVOS");
    		break;
    	case 64 :
    		printf("  OS/ABI:                            ARM EABI\n");
    		break;
    	case 97 :
    		printf("  OS/ABI:                            ARM\n");
    		break;
    	case 255 :
    		printf("  OS/ABI:                            Standalone\n");
    		break;
    	}

	//ABI Version
	printf("  Version ABI:                       %d\n", h.e_ident[EI_ABIVERSION]);
	
	//File Type
	printf("  Type:                             ");
	switch (h.e_type)
	{
		case 0:
			printf(" Inconnu\n");
			break;
		case 1:
			printf(" REL (Fichier de réadressage)\n");
			break;
		case 2:
			printf(" EXEC (Fichier exécutable)\n");
			break;
		case 3:
			printf(" DYN (Objet partagé)\n");
			break;
		case 4:
			printf(" CORE (Fichier core)\n");
			break;
		case 65024:
			printf(" LOOS (Operating System Specific File)\n");
			break;
		case 65279:
			printf(" HIOS (Operating System Specific File)\n");
			break;
		case 65280:
			printf(" LOPROC (Processor Specific File)\n");
			break;
		case 65535:
			printf(" HIPROC (Processor Specific File)\n");
			break;
	}

	//Target Instruction Set Architecture
	printf("  Machine:                           ARM\n");
    
	//e_version
	printf("  Version:                           0x%X\n", h.e_version);

	//Entry Point Address
    	printf("  Adresse du point d'entrée:         0x%X\n", h.e_entry);

	//Start of program headers
    	printf("  Début des en-têtes de programme :  %d (octets dans le fichier)\n", h.e_phoff);
    	
    	//Start of section headers
    	printf("  Début des en-têtes de section :    %d (octets dans le fichier)\n", h.e_shoff);
    	
    	//Flags
    	printf("  Fanions:                           0x%x, Version5 EABI\n", h.e_flags); //estce toujours EABI V 5
    	
    	//Size of header
    	printf("  Taille de cet en-tête:             %d (octets)\n", h.e_ehsize);
    	
    	//Size of program headers
    	printf("  Taille de l'en-tête du programme:  %d (octets)\n", h.e_phentsize);
    
    	//Number of program headers
    	printf("  Nombre d'en-tête du programme:     %d\n", h.e_phnum);
 	
 	//Size of section headers   
 	printf("  Taille des en-têtes de section:    %d (octets)\n", h.e_shentsize);
    
    	//Number of section headers
   	printf("  Nombre d'en-têtes de section:      %d\n", h.e_shnum);
    
    	printf("  Table d'index des chaînes d'en-tête de section: %d\n", h.e_shstrndx);
}
