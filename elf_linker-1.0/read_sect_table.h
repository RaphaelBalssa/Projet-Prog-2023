#ifndef __SECTION_H__
#define __SECTION_H__

#include <stdio.h>
#include "read_header.h"
#include <elf.h>

// Structure pour stocker les informations d'une section : nom, type, flags, donnees et en-tete
typedef struct
{
	Elf32_Shdr SectionHeader;
	char * SectionName;
	//uint8_t * dataTab;
	
} Section;

// Structure pour stocker une liste de sections
typedef struct
{
	uint32_t nb_sect;
	Section * sectTab;
} SectionsTable;


/*******************************************************************************
 * lire_sections_table
 * parametres : FILE *elfFile, Elf64_Ehdr header
 * resultat : SectionsList
 * description : Lit dans le fichier elfFile les informations sur les sections
 *               et les renvoie sous la forme d'une structure dediee.
 * effet de bord : aucun
 *******************************************************************************/
//SectionsTable 
int get_sections (FILE * elf, Elf32_Ehdr header, int endianess);
void lire_type(long num, char *sh_type);
//SectionsList lire_sections_table(FILE *elfFile, Elf32_Ehdr header);


/*******************************************************************************
 * afficher_sections_table
 * parametres : SectionsList liste, uint32_t offset
 * resultat : aucun
 * description : Affiche de facon lisible les informations contenu dans la
 *               structures liste donnee.
 * effet de bord : aucun
 *******************************************************************************/
//void afficher_sections_table(FILE * elf, SectionsList * tableSection, Elf32_Ehdr header);


#endif
