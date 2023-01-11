#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>

#include "read_relocation_table.h"
#include "read_sect_header.h"
#include "read_symb_table.h"


/*	lire_reimp_table(SectionsList liste_sect, SymbolesList liste_symb)
		Lit une table de reimplantation
*/
RelocTable lire_reimp_table(SectionsTable table_sect, SymboleTable symb_table)
{
	Elf32_Rel rel;
	Elf32_Rela rela;
	
	RelocTable reloc_table = {0, 0, NULL};
	//TODO malloc pour relaTab et relTab 
	
	// Parcours des sections
	for (int i = 0; i < table_sect.nb_sect; i++)
	{
		// Section courante
		Section sect = table_sect.sectTab[i];
		
		// Cas ou la section courante est du type SHT_RELA
		if (sect.sh_type == 4)
		{
			// Lecture de la liste de reimplantation de la section courante
			RelocTable reloc_table = ;
			
			// Reallocation et ajout de cette liste dans la table
			table_reimp.nb_list++;
			table_reimp.tab = realloc(table_reimp.tab, sizeof(RelocList) * table_reimp.nb_list);
			table_reimp.tab[table_reimp.nb_list - 1] = liste_reimp;
		}
		
		// Cas ou la section courante est du type SHT_REL
		else if (sect.header.sh_type == 9){
		
			// Lecture de la liste de reimplantation de la section courante
			RelocList liste_reimp = lire_rel_liste(sect, liste_sect, liste_symb);
			
			// Reallocation et ajout de cette liste dans la table
			table_reimp.nb_list++;
			table_reimp.tab = realloc(table_reimp.tab, sizeof(RelocList) * table_reimp.nb_list);
			table_reimp.tab[table_reimp.nb_list - 1] = liste_reimp;
		}
	}
	
	return table_reimp;
}
