#ifndef __CSP_H__
#define __CSP_H__

#include <stdio.h>
#include <stdlib.h>
#define NB_VAR 50
#define SIZE_DOM 30


typedef struct {
    int domaine[NB_VAR+1][SIZE_DOM+1];
	int ** relations[NB_VAR+1][NB_VAR+1];
	int taille[NB_VAR+1];
	int max_var;
	int max_val;
}Contraintes;

typedef struct Node{
	struct Node * next;
	int var;
	int val;
}Node;

typedef Node * Stack;

Contraintes * makeContraintes(int nb_var,int max_val);
void free_Constraints(Contraintes * csp);

void free_Node(Node * n);
Node * makeNode(int variable,int value);

#endif
