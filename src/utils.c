#include <stdio.h>
#include "CSP.h"
/**
*Retourne le max de deux valeurs
*@param premiere valeur
*@param deuxieme valeur
*/
int max (int a, int b) {
	if (a<b) return b;
	return a;
}

/**
*Initialise la matrice des contraintes
*@param la reference vers la contrainte
*@param le nombre de variables
*@param la valeur la plus grande possible
*/
void init_contraintes(Contraintes * c, int max_var, int max_val){
	c->max_var = max_var;
	c->max_val = max_val;
	for(int i = 0; i < NB_VAR ; i++)
		for(int j = 0; j < NB_VAR ; j++)
			c->relations[i][j] = NULL;
}

/**
*Allocation dynamique d'une matrice
*@param le nombre de lignes
*@param le nombre de colonnes
*@return la matrice creee
*/
int ** malloc2D(int l, int c){
	int ** r = malloc(sizeof(int *)*l);
	for(int i = 0; i < SIZE_DOM; i++)
	{
		r[i] = malloc(sizeof(int)*c);
	}
	return r;
}

/**
*Cree une table de relation de taille SIZE_DOM+1*SIZE_DOM+1
*@return retourne une table de relation
*/
int ** create_relation(){
	return malloc2D(SIZE_DOM+1,SIZE_DOM+1);
}

/**
*Desaloue une table de relation
*@param une table de relation
*/
void free_relation(int ** r){
	for(int i = 0; i < SIZE_DOM; i++)
	{
		free(r[i]);
	}
	free(r);
}

/***
*Initialise le domaine passe en argument
*@param la reference du domaine a initialiser
*/
void init_domains (int domaine[NB_VAR+1][SIZE_DOM+1]) {
	for (int i = 0; i< NB_VAR; i++)
	 	for (int j = 0; j < SIZE_DOM; j++)
			domaine[i][j] = 0;
}

/***
*Initialise la matrice de relations passee en argument
*@param la reference de la matrice a initialiser
*/
int init_relations (int ** relations) {
	if(relations == NULL){
		perror("relations==NULL");
		return -1;//on retourne -1 pour desalouer et quitter proprement le programme
	}
	//Parcours de la matrice
	for (int i = 0; i< SIZE_DOM ; i++)
	 	for (int j = 0; j < SIZE_DOM; j++){
			relations[i][j] = 0;//on initialise à 0
		}
	return 0;
}

/***
*Libere le table de contraintes
*@param la contrainte à liberer
*/
void free_Contraintes(Contraintes * contraintes){
	free(contraintes);
}


/**
*Retourne la valeur maximale de tous les domaine ayant été attribués aux vars
*@param le domaine
*@param le nombre de variables
*@return valeur max de tous les domaines
*/
int get_max (int domaine [NB_VAR+1][SIZE_DOM+1], int nb_var) {
	int maximum = 0;
	for (int i = 0; i < nb_var; i++) {
		for (int j = 0; j < SIZE_DOM+1; j++) {
			if (domaine[i][j])
				maximum = max(maximum, j);
		}
	}
	return maximum;
}

/** Gestion de la pile **/

/**
*Constructeur de noeud
*@param une variable
*@param une valeur
*@return un noeud
*/
Node * makeNode(int var,int val){
	Node * n = malloc(sizeof(Node));
	n->var = var;
	n->val = val;
	return n;
}

/**
*Desaloue un noeud
*@param un noeud a liberer
*/
void free_Node(Node * n){
	free(n);
}

/**
*Constructeur de pile
*@return une pile vide
*/
Stack makeStack(){
	return NULL;
}

/**
*Empille le couple variable valeur
*@param la pile
*@param une variable a empiler
*@param la valeur de la variable
*@return la pile avec la nouvelle valeur
*/
Stack push(Stack s,int var, int val){
	Stack newStack = makeNode(var,val);
	newStack->next = s;
	return newStack;

}

/**
*Retourne une copie du noeud du haut de la pile
*@param la pile
*@return le noeud en haut de la pile
*/
Node * top(Stack s){
	return makeNode(s->var,s->val);
}
/**
*Depile
*@param la pile
*@return le noeud du haut
*/
Node * pop(Stack s){
    Node * n = s;
	s = s -> next;
	return n;
}

/**
*Desaloue le sommet de la pile
*@param la pile
*@return la nouvelle pile
*/
Stack removeTop(Stack s){
	Node * n = s;
	s = s -> next;
	free_Node(n);
	return s;
}

/**
*affiche le contenu de la pile
*@param la pile a afficher
*/
void printStack(Stack stack){
    Node * actual = stack;
    while(actual != NULL){
		printf("(%d: %d)",actual->var,actual->val);
		actual = actual -> next;
    }
	printf("\n");
}
