#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"
#include "CSP.h"

/**
*Remplit le domaine avec le fichier src et retourne le nombre de variables utilisées
*@param le fichier src
*@param le domaine
*@return le nombre de variables du domaine
*/
int create_domain (FILE * src, int domaine[NB_VAR+1][SIZE_DOM+1]) {
	int nb_var;
	char domain[200];
	fscanf(src, "%d", &nb_var);
	int var, domain_value;
	for (int i = 1; i <= nb_var; i++) {
		fscanf(src, "%d: %[^\n]\n", &var, domain);
		if (var != i){
            printf ("CSP error\n");
            exit(-1);
        }
		int indice = 0;
		while(1){
			int r = sscanf(domain + indice, " %d", &domain_value);
			if( r<=0) break;
			indice += r;
			(domaine)[i][domain_value] = 1;
		}

	}
	return nb_var;
}

/**
*Remplit les contraintes a partir du fichier src
*@param fichier src
*@param reference vers les contraintes
*/
void create_contraintes (FILE * src, Contraintes * csp) {
	int contr_i, contr_j, couple_i, couple_j;
	int nb_contr;
	fscanf(src, "%d", &nb_contr);
	for (int i = 0; i < nb_contr; i++) {
		fscanf(src,"%d %d:", &contr_i, &contr_j);
		csp->relations[contr_i][contr_j] = create_relation();
		if(csp->relations[contr_i][contr_j]==NULL){
			free_Contraintes(csp);
			exit(1);
		}
		if(init_relations(csp->relations[contr_i][contr_j])<0){
			free_Contraintes(csp);
			exit(1);
		}
		while(fscanf(src," (%d,%d)",&couple_i,&couple_j)>1){
			(csp->relations[contr_i][contr_j][couple_i][couple_j]) = 1;
		}
	}
}


/**
*Retourne la CSP donnee par le fichier
*@param fichier src
*@return une CSP
*/
Contraintes read_file (FILE * src) {
	Contraintes csp;
	int nb_var = create_domain(src, (csp.domaine));
	int max_val = get_max(csp.domaine, nb_var);

	init_contraintes(&csp, nb_var, max_val);
	create_contraintes(src, &csp);
	return csp;
}
