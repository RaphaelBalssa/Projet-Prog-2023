#ifndef SYMB_TABLE
#define SYMB_TABLE

#include <stdint.h>
#include <elf.h>
#include "read_sect_table.h"

#define ELF32_ST_BIND(i) ((i) >> 4)
#define ELF32_ST_TYPE(i) ((i)&0xf)
#define ELF32_ST_INFO(b, t) (((b) << 4) + ((t)&0xf))
#define ELF32_ST_VISIBILITY(o) ((o)&0x3)


// Structure pour stocker un symbole. Documentation chapitre 1-18 Figure 1-15
/*typedef struct
{
	uint32_t st_name;
	uint32_t st_value;
	uint32_t st_size;
	unsigned char st_info;
	unsigned char st_other;
	uint16_t st_shndx;
} Elf32_Sym; */

// Structure pour stocker deux listes de symboles
typedef struct
{
	int nb_symb;
	Elf32_Sym *symbTab;
	int nb_symbDyn;
	Elf32_Sym *symbDynTab;
} SymboleTable;


/*******************************************************************************
 * lire_symbole
 * parametres : Section sumSect, Section strSect, int i
 * resultat : Symbole
 * description : Lit dans les structures symSect et strSect les donnees du
 *               symbole i et les renvoie sous la forme d'une structure dediee.
 * effet de bord : aucun
 *******************************************************************************/
Symbole lire_symbole(Section symSect, Section strSect, int i);


/*******************************************************************************
 * lire_symboles_table
 * parametres : SectionsList liste
 * resultat : Symboleslist
 * description : Lit dans la structure liste les donnees des symboles et les
 *               renvoie sous la forme d'une structure dediee.
 * effet de bord : aucun
 *******************************************************************************/
SymbolesList lire_symboles_table(SectionsList liste);


/*******************************************************************************
 * afficher_symboles
 * parametres : char *nom, Symbole *symboles, int nb_symb
 * resultat : aucun
 * description : Affiche de facon lisible les informations d'une des listes de
 *               la table des symboles.
 * effet de bord : aucun
 *******************************************************************************/
void afficher_symboles(char *nom, Symbole *symboles, int nb_symb);


/*******************************************************************************
 * afficher_symboles_table
 * parametres : SymbolesList liste
 * resultat : aucun
 * description : Affiche de facon lisible les informations de la table des
 *               symboles donnee.
 * effet de bord : aucun
 *******************************************************************************/
void afficher_symboles_table(SymbolesList liste);

#endif
