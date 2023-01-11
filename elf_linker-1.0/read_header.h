#ifndef __READ_HEADER_H__
#define __READ_HEADER_H__

#include <elf.h>

/*******************************************************************************
 * read_header
 * parametres : FILE * f
 * resultat : Elf32_Ehdr
 * description : Lit le header du fichier ELF donne en parametre
 * effet de bord : aucun
 *******************************************************************************/
Elf32_Ehdr read_header (FILE * f);

/*******************************************************************************
 * show_header
 * parametres : Elf32_Ehdr h
 * resultat : void
 * description : Affiche le header donne en parametre
 * effet de bord : aucun
 *******************************************************************************/
void show_header (Elf32_Ehdr h);

#endif
