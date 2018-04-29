#include <stdio.h>
#include <stdlib.h>
#define abs(A) (A>0?A:-A)




void generateurDame(int nb_queens){
	//nombre de reines
	printf("%d\n",nb_queens);
	//Domaine
	for(int x = 1 ; x <= nb_queens ; x++){
		printf("%d: ",x);
		for(int y = 1 ; y <= nb_queens ; y++){
			printf("%d ",y);
		}
		printf("\n");
	}
    //n*k
	printf("%d\n",nb_queens*(nb_queens-1));
	for(int l = 1 ; l <= nb_queens ; l++){
		for(int k = 1 ; k <= nb_queens ; k++){
			if(l != k){//pas la meme ligne
                //Couple de contrainte
				printf("%d %d: ",l,k);
                //Relations
				for(int i = 1 ; i <= nb_queens ; i++){
					for(int j = 1 ; j <= nb_queens ; j++){
                        if(i != j){//pas la meme colonne
                            if(abs((l-k))!=abs((i-j)))//pas la me diagonale
                                printf("(%d,%d) ",i,j);
                        }
					}
				}
				printf("\n");
			}
		}
	}
}

int main(int argc, char ** argv){
	if(argc <2){
		printf("Usage: nb dames");
		return 0;
	}
	generateurDame(atoi(argv[1]));
	return 0;
}
