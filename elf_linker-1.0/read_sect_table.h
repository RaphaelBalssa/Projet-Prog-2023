#ifndef __SECTION_H__
#define __SECTION_H__

#include <stdio.h>
#include "read_header.h"
#include <elf.h>

// Structure pour stocker les informations d'une section
typedef struct
{
	Elf32_Shdr SectionHeader;
	char * SectionName;	
} Section;

// Structure pour stocker une liste de sections
typedef struct
{
	uint32_t nb_sect;
	Section * sectTab;
} SectionsTable;


/*******************************************************************************
 * revstr
 * parametres : char *str
 * resultat : char *
 * description : Lit un string donne et le renvoie en inversant les lettres
 * effet de bord : aucun
 *******************************************************************************/
void revstr(char *str);

/*******************************************************************************
 * lire_type
 * parametres : long num
 * resultat : char *
 * description : Lit un champ d'une section et le transforme en string en fonction des donnees lues
 * effet de bord : aucun
 *******************************************************************************/
char * lire_type(long num);


/*******************************************************************************
 * lire_flags
 * parametres : char *tab, int n
 * resultat : void
 * description : Lit un champ d'une section et le transforme en string en fonction des donnees lues
 * effet de bord : aucun
 *******************************************************************************/
void lire_flags(char *tab, int n);


/*******************************************************************************
 * get_sections
 * parametres : FILE *elfFile, Elf64_Ehdr header, int endianess
 * resultat : SectionsTable
 * description : Lit dans le fichier elfFile les informations sur les sections
 *               et les renvoie sous la forme d'une structure dediee.
 * effet de bord : aucun
 *******************************************************************************/
SectionsTable get_sections (FILE * elf, Elf32_Ehdr header, int endianess);



/*******************************************************************************
 * afficher_sections
 * parametres : FILE * elf, Elf32_Ehdr header, int endianess, SectionsTable tab
 * resultat : aucun
 * description : Affiche de facon lisible les informations contenu dans la
 *               structures liste donnee.
 * effet de bord : aucun
 *******************************************************************************/
void afficher_sections(FILE * elf, Elf32_Ehdr header, int endianess, SectionsTable tab);


#endif
