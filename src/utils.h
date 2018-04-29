#ifndef __UTILS_CSP__
#define __UTILS_CSP__
#include "CSP.h"



int max (int a, int b);
void init_contraintes(Contraintes * c, int max_var, int max_val);
int ** malloc2D(int l, int c);
int ** create_relation();
void free_relation(int ** r);
void init_domains (int domaine[NB_VAR+1][SIZE_DOM+1]);
int init_relations (int ** relations) ;
void free_Contraintes(Contraintes * contraintes);
int get_max (int domaine [NB_VAR+1][SIZE_DOM+1], int nb_var) ;

Node * makeNode(int var,int val);
void free_Node(Node * n);
Stack makeStack();
Stack push(Stack s,int var, int val);
Node * top(Stack s);
Node * pop(Stack s);
Stack removeTop(Stack s);
void printStack(Stack stack);

#endif
