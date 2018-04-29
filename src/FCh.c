#include <string.h>
#include "FC.h"
#include "utils.h"
#include "CSP.h"
#include "CSP_reader.h"

int min_domaine_var = 1;
int all=0;

/**
*Retourne la taille du domaine
*@param la variable dont on cherche la taille de domaine
*@param la CSP
*@return taille de domaine
*/
int getDomainSize(int var,Contraintes * c){
	return c->taille[var];
}

/**
*Retourne la variable dont le domaine est de taille minimale (heuristique)
*@param la CSP
*@param liste des variables instanciees
*@return variable avec le plus petit domaine
*/
int getMinDomain(Contraintes * c, int* est_instanciee){
	int min = 0;
	for(int v = 1; v <=  c->max_var ; v++){
		if(!est_instanciee[v]){
			if(getDomainSize(min,c)> getDomainSize(v,c) || min == 0)
				min = v;
		}
	}
	return min;
}

/**
*Affiche les domaines
*@param la CSP
*@param la taille de chaque domaine
*/
void printDomains(Contraintes * c,int * domain_size){
	for(int var = 1; var <=  c->max_var ; var++){
		printf("%d) ",domain_size[var]);
		printf("%d :",var);
        for(int val = 1; val <= c->max_val; val ++)
            printf("%d ",c->domaine[var][val]);
        printf("\n");
	}
}
/**
*Instancie la variable
*@param la csp
*@param la pile
*@param la variable a instancier
*@param le tableau d'instanciation
*@return la nouvelle pile
*/
Stack instancier(Contraintes * c, Stack s, int k, int * est_instanciee){
  if(getDomainSize(k,c) == 0){
		perror("domaine vide\n");
		exit(0);
	}
	if(est_instanciee[min_domaine_var]){
		k = getMinDomain(c, est_instanciee);//heuristique ici
	}
	int val_k = 0;
	for(int val = 1; val <=  c->max_val; val ++)
		if( c->domaine[k][val]==1){
			val_k = val;
			break;
		}
	if(val_k == 0){
		perror("domaine vide\n");
		exit(0);
	}
	est_instanciee[k] = 1;
	for(int f = 1; f <=  c->max_var ; f++)
		if(!est_instanciee[f]){
			if( c->relations[k][f] != NULL){
				for(int val_f = 1; val_f <=  c->max_val; val_f ++)
					if( c->relations[k][f][val_k][val_f]==0)
						if( c->domaine[f][val_f]== 1){
						 	c->domaine[f][val_f]=-k;
		 					c->taille[f] --;
							if(c->taille[min_domaine_var] >= c->taille[f])
							{
								min_domaine_var = f;
							}
					 	}
			}
		}
	s = push(s,k,val_k);
	return s;
}


/**
*Desanstancie la valeur du sommet de pile et la retire de son domaine
*@param la csp
*@param la pile
*@param le tableau d'instanciation
*@return la nouvelle pile
*/
Stack desinstancier(Contraintes * c,Stack s,int * est_instanciee){
			int k = top(s)->var;
		int val_k = top(s)->val;
		s = removeTop(s);
		if(s == NULL){
			c->domaine[k][val_k] = 0;
			c->taille[k] --;
		}
		else{
		 c->domaine[k][val_k] = - (top(s)->var);// pour qu'au prochain BT la valeur revienne dans son domaine
		 c->taille[k] --;
	 	}
		est_instanciee[k] = 0;
		for(int f = 1; f <=  c->max_var ; f++)
			if(!est_instanciee[f]){
				for(int val_f = 1; val_f <=  c->max_val; val_f ++)
				{
					if( c->domaine[f][val_f] == -k ){
						c->domaine[f][val_f] = 1;//on retablit le domaine
						c->taille[f] ++;
					}
				}
			}
	if(c->taille[k]  < c->taille[min_domaine_var] || est_instanciee[min_domaine_var])
		min_domaine_var = k;
	return s;
}
/**
*Forward checking avec heuristique
*@param csp
*@return nombre de solutions
*/
int FC(Contraintes * c){
	Stack rs = makeStack();
	int nb_solutions= 0;
	int var = 1;
	int est_instanciee[c->max_var+1];

	for(int i = 1; i <= c->max_var ; i++){
    est_instanciee[i] = 0;
		c->taille[i] = c->max_val;
  }

  int stack_size = 0;

  while(1){
    rs = instancier(c,rs,var,est_instanciee);
    stack_size ++;
    var = min_domaine_var;
    for(int f = var+1; f <=  c->max_var; f++)
			if(c->taille[f] <= 0)
                {
                    if(rs == NULL)
                    {
        //on a epuise la pile, toutes les affectations possibles ont ete teste
          printf("Fin : %d solutions\n",nb_solutions);
          return nb_solutions;
        }
        rs = desinstancier(c,rs,est_instanciee);
        stack_size --;
        var = top(rs)->var;
    }
		if(stack_size == c->max_var)
		{
      var = top(rs)->var;
			rs = desinstancier(c,rs,est_instanciee);
      stack_size --;
			nb_solutions ++;
			if(!all){
                printf("sol trouvee");

                return 1;
			}
		}
		while(c->taille[var] <= 0){
      if(rs ==NULL){
        printf("FIN : %d solutions\n",nb_solutions);
        return nb_solutions;
      }
      var = top(rs)->var;
      rs = desinstancier(c,rs,est_instanciee);
      stack_size --;
    }
  }
}
//Gestion de l'argument -a
int main (int argc, char ** argv) {
	if (argc < 2) {
		printf("Usage : [-a] file");
		exit(-1);
	}
	all = 0;
	char * path = argv[1];
	if(argc == 3){
		if(!strcmp(argv[1],"-a")){
            printf("toute sol demande\n");
			all =1;
			path = argv[2];
		}
		else
			printf("Usage : [-a] file");
	}
	FILE * src = fopen (path, "r");
	if(src == NULL) {perror("open");exit(1);}
	Contraintes c = read_file (src);



        FC(&c);


	return 0;
}
