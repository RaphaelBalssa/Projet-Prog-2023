#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include "read_sect_table.h"
#include "read_symb_tab.h"

/*	lire_symbole(Section symSect, Section strSect, int i)
	Lit dans a section dediee les informations du symbole i
*/
Symbole read_symbole(Section symSect, Section strSect, int i)
{
	Elf32_Sym symbole;
	
	// Lecture de symbole.symb dans la section symSect entree
	symbole.st_name  = *((uint32_t *) &(symSect.dataTab[i*16   ]));
	symbole.st_value = *(&(symSect.dataTab[i*16+4 ])); 
	symbole.st_size  = *((uint32_t *) &(symSect.dataTab[i*16+8 ])); 
	symbole.st_info  = *((uint8_t  *) &(symSect.dataTab[i*16+12])); 
	symbole.st_other = *((uint8_t  *) &(symSect.dataTab[i*16+13])); 
	symbole.st_shndx = *((uint16_t *) &(symSect.dataTab[i*16+14]));

	return symbole;
}


/*	lire_symboles_table(SectionsList liste_sect)
		Lit la table des symboles
*/
SymbolesList read_symb_tab(SectionTable table_sect)
{
	Section strtab, symtab, dynsym, dynstr;
	SymTable table_symb;
	
	// Recherche des sections contenant la table des symboles
	bool dyna = false;
	int nb = 0;
	for (int i = 0; i < table_sect.nb_sect; i++)
	{
		Section sect = table_sect.sectTab[i];
		if (sect.sh_type == 11)
		{
			dynsym = sect;
			dyna=true;
		}
		else if (sect.sh_type == 2)
		{
			symtab = sect;
			nb++;
		}
		else if (strcmp(sect.SectionName, ".strtab") == 0)
		{
			strtab = sect;
		}
		else if (strcmp(sect.SectionName, ".dynstr") == 0)
		{
			dynstr = sect;
		}
	}
	
	// Cas ou il existe une section de symboles dynamiques
	if (dyna)
	{
		// Calcul du nombre de symbole et allocation memoire de la liste des symboles
		table_symb.nb_symbDyn = dynsym.sh_size / dynsym.sh_entsize;
		table_symb.symbDynTab = malloc(sizeof(Elf32_Sym) * liste_symb.nb_symbDyn);

		// Parcours des symboles
		for (int i = 0; i < liste_symb.nb_symbDyn; i++)
		{
			table_symb.symbDynTab[i] = lire_symbole(dynsym, dynstr, i);
		}
	}

	// Cas ou il existe une section de symboles non dynamiques
	if (nb > 0)
	{
		// Calcul du nombre de symbole et allocation memoire de la liste des symboles
		table_symb.nb_symb = symtab.SectionHeader.sh_size / symtab.SectionHeader.sh_entsize;
		table_symb.symbTab = malloc(sizeof(Symbole) * liste_symb.nb_symb);
		
		// Parcours des symboles
		for (int i = 0; i < liste_symb.nb_symb; i++)
		{
			liste_symb.symbTab[i] = lire_symbole(symtab, strtab, i);
		}
	}

	return liste_symb;
}


/*	afficher_symboles(char *nom, Symbole *symboles, int nb_symb)
		Affiche les informations d'une liste de symboles
*/
void afficher_symboles(char *nom, Elf32_Sym *symboles, int nb_symb)
{
	printf("\nSymbol table '%s' contains %d entries:\n", nom, nb_symb);
	printf("   Num:    Value  Size Type    Bind   Vis      Ndx Name\n");
	
	// Parcours des symboles	
	for (int i = 0; i < nb_symb; i++)
	{
		/*
		printf("   %3d: %08x %x %x %x %x\n",
			   i, symboles[i].st_value, symboles[i].st_size,
			   symboles[i].st_info, symboles[i].st_other, symboles[i].st_shndx);*/
	}
}


/*	afficher_symboles_table(SymbolesList liste)
		Affiche les informations de la table des symboles
*/
void afficher_symboles_table(SymboleTable table)
{
	// Cas des symboles dynamiques
	if (table.nb_symbDyn > 0)
	{
		afficher_symboles(".dynsym", table.symbDynTab, liste.nb_symbDyn);
	}
	
	// Cas des autres symboles
	if (table.nb_symb > 0)
	{
		afficher_symboles(".symtab", table.symbTab, liste.nb_symb);
	}	
}
