#include <stdio.h>
#include <stdlib.h>

void generateurPigeon(int nb_pigeons){
	int nb_trous = nb_pigeons -1;
	//nombre de pigeons
	printf("%d\n",nb_pigeons);
	//Domaine
	for(int x = 1 ; x <= nb_pigeons ; x++){
		printf("%d: ",x);
		for(int y = 1 ; y <= nb_trous ; y++){
			printf("%d ",y);
		}
		printf("\n");
	}
	//n*k
	printf("%d\n",(nb_pigeons) * (nb_pigeons -1));
	for(int l = 1 ; l <= nb_pigeons ; l++){
		for(int k = 1 ; k <= nb_pigeons ; k++){
			if(l == k)continue;
			//Contraintes
			printf("%d %d: ",l,k);
			//Relation
			for(int i = 1 ; i <= nb_trous ; i++){
				for(int j = 1 ; j <= nb_trous ; j++){
					if(i!=j)
						printf("(%d,%d) ",i,j);
				}
			}
		printf("\n");
		}
	}
}

int main(int argc, char ** argv){
	if(argc <2){
		printf("Usage: nb pigeons");
		return 0;
	}
	generateurPigeon(atoi(argv[1]));
	return 0;
}
