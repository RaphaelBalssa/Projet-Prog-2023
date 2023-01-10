#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "read_header.h"
#include "read_sect_table.h"
#include "elf.h"
#include "read_header.h"
#include "util.h"

// Fonction de renversement de string pour afficher les flags de la bonne maniere
void revstr(char *str)
{
	int len, temp;
	len = strlen(str);
	
	for (int i = 0; i < len / 2; i++)
	{
		temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
	}
}

// Fonction de comparaison entre deux noms pour trier les sections (inutile dans la phase finale)
int cmpfunc (const void * a, const void * b){
	const Section * v1 = (Section *) a;
	const Section * v2 = (Section *) b;
   return ( v1 -> SectionHeader.sh_name >= v2 -> SectionHeader.sh_name);
}


// Renvoie une chaine de caracteres correspondant au type et a la specification donnee
char * lire_type(long num)
{
	char *sh_type;
	// Documentation chapitre 1-11 Figure 1-9
	switch (num)
	{
	case 0:
		sh_type = "NULL";
		break;
	case 1:
		sh_type = "PROGBITS";
		break;
	case 2:
		sh_type = "SYMTAB";
		break;
	case 3:
		sh_type = "STRTAB";
		break;
	case 4:
		sh_type = "RELA";
		break;
	case 5:
		sh_type = "HASH";
		break;
	case 6:
		sh_type = "DYNAMIC";
		break;
	case 7:
		sh_type = "NOTE";
		break;
	case 8:
		sh_type = "NOBITS";
		break;
	case 9:
		sh_type = "REL";
		break;
	case 10:
		sh_type = "SHLIB";
		break;
	case 11:
		sh_type = "DYNSYM";
		break;
	case 14:
		sh_type = "INIT_ARRAY";
		break;
	case 15:
		sh_type = "FINI_ARRAY";
		break;
	case 16:
		sh_type = "PREINIT_ARRAY";
		break;
	case 17:
		sh_type = "GROUP";
		break;
	case 18:
		sh_type = "SYMTAB_SHNDX";
		break;
	case 0x6ffffff6:
		sh_type = "GNU_HASH";
		break;
	case 0x6ffffffd:
		sh_type = "VERDEF";
		break;
	case 0x6ffffffe:
		sh_type = "VERNEED";
		break;
	case 0x6fffffff:
		sh_type = "VERSYM";
		break;
	case 0x70000000:
		sh_type = "LOPROC";
		break;
	case 0x7fffffff:
		sh_type = "HIPROC";
		break;
	case 0x80000000:
		sh_type = "LOUSER";
		break;
	case 0xffffffff:
		sh_type = "HIUSER";
		break;
	default:
		sh_type = "UNKOWN";
		break;
	}
	
	return sh_type;
}


// Permet de lire la valeur decimale des fanions et de les transformer en texte d'apres la documentation
void lire_flags(char *tab, int n)
{
	int j = 0;
	// Les valeurs des deux tableaux proviennent de la documentation 
	// (et des informations decrites sous la fonction readelf -S <fichier> )
	int tabVal[12] = {2048, 1024, 512, 256, 128, 64, 32, 16, 4, 2, 1, 0};
	char tabChar[12] = {'C','T','G','O','L','I','S','M','X','A','W',' '};
	
	// Tant que n > 0 alors
	for (int i = 0; n > 0; i++)
	{
		// Si n est plus grand que la valeur courate de tabval
		if (n >= tabVal[i])
		{
			tab[j] = tabChar[i];
			n -= tabVal[i];
			j++;
		}
	}
	// Fin de chaine, dernier caractere
	tab[j] = '\0';
}


// Permet de recuperer le contenu de tous les headers des sections, pour l'afficher ensuite
SectionsTable get_sections(FILE * elf, Elf32_Ehdr header, int endianess)
{
	// Declaration et allouement memoire de la table des sections
	SectionsTable tab;
	tab.sectTab = (Section *) malloc (header.e_shnum * sizeof(Section));
	tab.nb_sect = header.e_shnum;
	
	printf("\n\n");

	// Deplacement du curseur jusqu'a la table des sections
	fseek(elf, header.e_shoff, SEEK_SET);
	
	// Pour toutes les sections, lire leur contenu et le stocker dans tab
	for (int i = 0; i < header.e_shnum; i++)
	{
		if (!fread(&tab.sectTab[i], 40, 1, elf))
		{
			printf("Erreur \n");
		}
	}

	// Tentative de tri pour recuperer les noms des sections en string
	//qsort(tab.sectTab, tab.nb_sect, sizeof(Section), cmpfunc);

	// Replacement du curseur au debut de la table des sections
	fseek(elf, header.e_shoff, SEEK_SET);
 	return tab;
}
 
// Permet d'afficher le contenu des sections selon l'affichage de readelf
void afficher_sections(FILE * elf, Elf32_Ehdr header, int endianess, SectionsTable tab) {
  

  	char *type = "";
  	char flags[3] = "";
  
 	// Debut de la table des sections
	printf("There are %d section headers, starting at offset 0x%x:\n\n", tab.nb_sect, header.e_shoff);
	printf("Section Headers:\n  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al\n");

	for (int i = 0; i < tab.nb_sect; i++)
	{
		// Lecture du type et des flags, modification des donnees lues
		type = lire_type(Swap32(tab.sectTab[i].SectionHeader.sh_type));
		lire_flags(flags, Swap32(tab.sectTab[i].SectionHeader.sh_flags));
		revstr(flags);
		
		// Affichage
		printf("  [%2d] %-17x %-15s %08x %06x ", i,
			   Swap32(tab.sectTab[i].SectionHeader.sh_name),
			   type,
			   Swap32(tab.sectTab[i].SectionHeader.sh_addr),
			   Swap32(tab.sectTab[i].SectionHeader.sh_offset));
		printf("%06x %02x %3s %2d  %2d %2d\n",
			   Swap32(tab.sectTab[i].SectionHeader.sh_size),
			   Swap32(tab.sectTab[i].SectionHeader.sh_entsize),
			   flags,
			   Swap32(tab.sectTab[i].SectionHeader.sh_link),
			   Swap32(tab.sectTab[i].SectionHeader.sh_info),
			   Swap32(tab.sectTab[i].SectionHeader.sh_addralign));
	}
	
	printf("Key to Flags:\n");
	printf("  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),\n");
	printf("  L (link order), O (extra OS processing required), G (group), T (TLS),\n");
	printf("  C (compressed), x (unknown), o (OS specific), E (exclude),\n");
	printf("  p (processor specific)\n");


}


















