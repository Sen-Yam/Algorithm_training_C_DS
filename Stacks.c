#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Pile{  
	int X;
	struct Pile *suivant;
}Pile,*plistP;
	
// insertion(Empiler) + suppression (Depiler)
void EMPILER(plistP *teteP , int Val) {
	plistP P;  // pointeur sur Pile(entier + pointeur)
	P=malloc(sizeof(Pile));// (Val + pointeur)
	P->X=Val;
	P->suivant=(*teteP);
	(*teteP)=P;
}

int DEPILER(plistP*teteP) {
	int Val;
	plistP Q;
	Val = (*teteP)->X;
	Q=(*teteP);
	(*teteP)=(*teteP)->suivant;
	free(Q);
	return Val;
	
}

int SOMMET_PILE(plistP*teteP) {
	int Val;
	Val = (*teteP)->X;
	return Val;
	
}

void AFFICHER_PILE(plistP*tete) {
    plistP P=NULL;
    int Val;
	printf("\nLes elements de la pile sont : \n");
	while(*tete!=NULL) {
        Val = DEPILER(tete);
        EMPILER(&P , Val);
		printf("%d\n",Val);
	}	
    while(P!=NULL) {
        Val = DEPILER(&P);
        EMPILER(tete , Val);
    }
}


int main(int argc, char *argv[]) {
	plistP teteP;
	int N,i,Val;
	printf("Donnez le nombre d'elements de la pile : \t");
	scanf("%d",&N);
	teteP=NULL;
	for(i=1;i<=N;i++) {
		printf("\n Donnez un element\t");
		scanf("%d",&Val);
		EMPILER(&teteP ,Val);
	}
	AFFICHER_PILE(&teteP);
	return 0;
}