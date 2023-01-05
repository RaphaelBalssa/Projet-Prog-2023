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
	
	int i = fread(&h, sizeof(h), 1, elf);
	if (is_big_endian(h.e_ident[EI_DATA]))
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
	
	if(i == 1){
        	return h;
    	} else {
        	printf("irrelevant test to avoid warning");
    	}
    
    	return h;
}

void show_header (Elf32_Ehdr h)
{
	printf ("ELF Header:\n");
	
	//Magic Number
	printf("Magic Number: ");
	for (int i = 0; i <= 14; i++)
	{
		printf("%02X ", h.e_ident[i]);
	}
	printf("%02X\n", h.e_ident[15]);
	
	
	//File Class
	switch(h.e_ident[EI_CLASS])
	{
		case 0:
			printf("  Class:                             Invalid\n");
			break;
		case 1:
			printf("  Class:                             ELF32\n");
			break;
		case 2:
			printf("  Class:                             ELF64\n");
			break;
	}
	    
	//File Data:
	switch(h.e_ident[EI_DATA])
	{
		case 0:
			printf("  Data:                              Invalid\n");
			break;
		case 1:
			printf("  Data:                              2's complement, Little Endian\n");
			break;
		case 2:
			printf("  Data:                              2's complement, Big Endian\n");
			break;
	}
	
	//ELF Version
	if (h.e_ident[EI_VERSION] == 1)
	{
		printf("  Version:                           1\n");
	}
	else
	{
		printf("  Version:                           Invalid\n");
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
	printf("  ABI Version:                       %d\n", h.e_ident[EI_ABIVERSION]);
	
	//File Type
	printf("  Type:                              ");
	switch (h.e_type)
	{
		case 0:
			printf("Unknown)\n");
			break;
		case 1:
			printf("REL (Relocatable file)\n");
			break;
		case 2:
			printf("EXEC (Executable file)\n");
			break;
		case 3:
			printf("DYN (Shared Object)\n");
			break;
		case 4:
			printf("CORE (Core file)\n");
			break;
		case 65024:
			printf("LOOS (Operating System Specific File)\n");
			break;
		case 65279:
			printf("HIOS (Operating System Specific File)\n");
			break;
		case 65280:
			printf("LOPROC (PRocessor Specific File)\n");
			break;
		case 65535:
			printf("HIPROC (Processor Specific File)\n");
			break;
	}

	//Target Instruction Set Architecture
	printf("  Machine:                           ARM\n");
    
	//e_version
	printf("  Version:                           0x%X\n", h.e_version);

	//Entry Point Address
    	printf("  Entry point address:               0x%X\n", h.e_entry);

	//Start of program headers
    	printf("  Start of program headers:          %d (bytes into file)\n", h.e_phoff);
    	
    	//Start of section headers
    	printf("  Start of section headers:          %d (bytes into file)\n", h.e_shoff);
    	
    	//Flags
    	printf("  Flags:                             0x%x\n", h.e_flags);
    	
    	//Size of header
    	printf("  Size of this header:               %d (bytes)\n", h.e_ehsize);
    	
    	//Size of program headers
    	printf("  Size of program headers:           %d (bytes)\n", h.e_phentsize);
    
    	//Number of program headers
    	printf("  Number of program headers:         %d\n", h.e_phnum);
 	
 	//Size of section headers   
 	printf("  Size of section headers:           %d (bytes)\n", h.e_shentsize);
    
    	//Number of section headers
   	printf("  Number of section headers:         %d\n", h.e_shnum);
    
    	printf("  Section header string table index: %d\n", h.e_shstrndx);
}
