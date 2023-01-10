#ifndef __REL_H__
#define __REL_H__

#include <stdint.h>
#include <elf.h>

#include "read_header.h"
#include "read_sect_table.h"
#include "read_symb_table.h"

#define ELF32_R_SYM(i)     ((i) >> 8)
#define ELF32_R_TYPE(i)    ((unsigned char)(i))
#define ELF32_R_INFO(s, t) (((s) << 8) + (unsigned char)(t))

// Structures pour stocker les informations d'une reimplantation : type, nom
typedef struct
{
	uint32_t value;
	char type[30];
	char name[50];
	Elf32_Rel rel;
} Rel;

// Structure pour stocker une liste de reimplantation
typedef struct
{
	char name[30];
	uint32_t offset;
	int nb_reloc;
	int type; // 0=rel - 1=rela
	Rel *relTab;
	Rela *relaTab;
} RelocList;

// Structure pour stocker une liste (table) de liste de reimplantation reimplantation
typedef struct
{
	int nb_list;
	RelocList *tab;
} RelocTable;

/*******************************************************************************
 * lire_reimp_table
 * parametres : SectionsList liste_sect, SymbolesList liste_symb
 * resultat : RelocTable
 * description : Lit depuis le contenu des sections une table de reimplantation
 *               et la renvoie sous la forme d'une structure dediee.
 * effet de bord : aucun
 *******************************************************************************/
RelocTable lire_reimp_table(SectionsList liste_sect, SymbolesList liste_symb);


/*******************************************************************************
 * afficher_reimp_table
 * parametres : RelocTable table_reimp
 * resultat : aucun
 * description : Affiche de facon lisible les informations de la table de
 *               reimplantation donnee.
 * effet de bord : aucun
 *******************************************************************************/
void afficher_reimp_table(RelocTable table_reimp);

#endif
