#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

Elf32_Ehdr read_header(FILE * elf)
{
	Elf32_Ehdr h;
	char test[65];
	for (int i = 0; i < 64; i++)
	{
		char c = fgetc(elf);
		test[i] = c;
	}
	test[64] = '\0';
	printf("\n\n\n\n");
	for (int i = 32; i < 40; i++)
	{
		printf("%d", test[i]);
	}
	printf("\n\n\n\n");
	fread(&h, 1, sizeof(h), elf);
	
	return h;
}

void show_header (Elf32_Ehdr h)
{
	printf ("ELF Header:\n");
	
	//Magic Number
	printf("Magic Number: ");
	for (int i = 0; i < 14; i++)
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
		printf("  Version:                           %X\n", h.e_version);
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
		case ET_NONE:
			printf("Unknown\n");
			break;
		case ET_REL:
			printf("REL (Relocatable file\n");
			break;
		case ET_EXEC:
			printf("EXEC (Executable file)\n");
			break;
		case ET_DYN:
			printf("DYN (Shared Object)\n");
			break;
		case ET_CORE:
			printf("CORE (Core file)\n");
			break;
		case ET_LOOS:
			printf("LOOS (Operating System Specific File)\n");
			break;
		case ET_HIOS:
			printf("HIOS (Operating System Specific File)\n");
			break;
		case ET_LOPROC:
			printf("LOPROC (PRocessor Specific File)\n");
			break;
		case ET_HIPROC:
			printf("HIPROC (Processor Specific File)\n");
			break;
	}

	//Target Instruction Set Architecture
	printf("  Machine:                           Advanced Micro Devices X86-64\n");
    
	//e_version
	printf("  Version:                           0x%X\n", h.e_version);

	//Entry Point Address
    printf("  Entry point address:               0x%X\n", h.e_entry);

	//Start of program headers
    printf("  Start of program headers:          %X (bytes into file)\n", h.e_phoff);
    printf("  Start of section headers:          %d (bytes into file)\n", h.e_shoff);
    printf("  Flags:                             0x%x\n", h.e_flags);
    printf("  Size of this header:               %d (bytes)\n", h.e_ehsize);
    printf("  Size of program headers:           %d (bytes)\n", h.e_phentsize);
    printf("  Number of program headers:         %d\n", h.e_phnum);
    printf("  Size of section headers:           %d (bytes)\n", h.e_shentsize);
    printf("  Number of section headers:         %d\n", h.e_shnum);
    printf("  Section header string table index: %d\n", h.e_shstrndx);
}
