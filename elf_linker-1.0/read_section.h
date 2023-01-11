#ifndef __READ_SECTION_H__
#define __READ_SECTION_H__


/*******************************************************************************
 * get_section_data
 * parametres : SectionsTable sections, char * section, Elf32_Ehdr header, FILE * elf
 * resultat : uint8_t *
 * description : Recupere le contenu d'une section dans un tableau d'octet
 * effet de bord : aucun
 *******************************************************************************/
uint8_t *get_section_data (SectionsTable sections, char * section, Elf32_Ehdr header, FILE * elf);

/*******************************************************************************
 * get_section
 * parametres : SectionsTable sections, char * section, Elf32_Ehdr header, FILE * elf
 * resultat : Section
 * description : Récupere une section entiere dans une structure et la renvoie
 * effet de bord : aucun
 *******************************************************************************/
Section get_section (SectionsTable sections, char * section, Elf32_Ehdr header, FILE * elf);

/*******************************************************************************
 * dumpSection
 * parametres : uint8_t *contenuSection, Section section, int section_size, int sectionNb
 * resultat : void
 * description : Recupère les informations d'une section et son contenu pour l'afficher
 * effet de bord : aucun
 *******************************************************************************/
void dumpSection (uint8_t *contenuSection, Section section, int section_size, int sectionNb);

#endif
