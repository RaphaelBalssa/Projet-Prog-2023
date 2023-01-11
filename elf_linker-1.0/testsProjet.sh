#!/bin/bash

# Test l'affichage de l'en-tete
function test_header()
{	./readelf $1 -H > res_temp.txt
	readelf -h $1 > res_fourni_temp.txt
	
	# Mise en forme pour retirer la ligne indiquant la machine
	grep -v "Machine:" res_temp.txt > resultat_projet.txt
	grep -v "Machine:" res_fourni_temp.txt > resultat_fourni.txt

	diff resultat_projet.txt resultat_fourni.txt > /dev/null
	if [[ $? -eq 0 ]]
	then
		echo "TEST AFFICHAGE HEADER : IDENTIQUE"
	else
		echo "TEST AFFICHAGE HEADER : DIFFERENT"
		diff --suppress-common-lines resultat_projet.txt resultat_fourni.txt
	fi
	echo ""
	
	rm  res_temp.txt res_fourni_temp.txt resultat_projet.txt resultat_fourni.txt
}

# Test l'affichage de la table des sections
function test_sect_table()
{	./readelf $1 -S > res_temp.txt
	readelf -S $1 > res_fourni_temp.txt
	
	
	
	diff res_temp.txt res_fourni_temp.txt > /dev/null
	if [[ $? -eq 0 ]]
	then
		echo "TEST AFFICHAGE TABLE DES SECTIONS : IDENTIQUE"
	else
		echo "TEST AFFICHAGE TABLE DES SECTIONS : DIFFERENT"
		diff --suppress-common-lines res_temp.txt res_fourni_temp.txt
	fi
	echo ""
	
	rm  res_temp.txt res_fourni_temp.txt 
	
}

test_header $1
test_sect_table $1
