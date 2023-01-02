#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Element{ //(X+pointeur)
	int X;
	struct Element*suivant;
}Element,*Pelement;


typedef struct File { 
	 Pelement tete; // pointeur sur le 1er element
	Pelement queue;  // pointeur sur le 2eme element   
}File , *plistF;



//insertion fin de liste
void ENFILER(File*F , int Val) { 	
	Pelement P = malloc(sizeof(Element));
	P->X=Val;
	P->suivant=NULL;   
	if((*F).tete==NULL){ 
	(*F).tete=P;
	(*F).queue=P;
	  }
	else {  
	
	((*F).queue)->suivant=P; // 1 2 3 queue(4+adresse de 5 = P   5+NULL)
	((*F).queue)=((*F).queue)->suivant;
}	
}

int DEFILER(File*F) { // a expliquer dans la prochaine seance 
    int Val;
    Pelement P;
    P=(*F).tete;
    Val = (*F).tete->X;
    (*F).tete=(*F).tete->suivant;
    free(P);
    return Val;

}

void AFFICHER_FILE(File*F) {
    File Q;
    int Val;
    Q.tete=NULL;
    Q.queue=NULL;
	printf("\nLes elements de la file sont : \n");
	while((*F).tete!=NULL) {
        Val = DEFILER(F);
        ENFILER(&Q , Val);
		printf("%d\n",Val);
	}	
    while(Q.tete!=NULL) {
    Val = DEFILER(&Q);
    ENFILER(F , Val);
    }
}

int main(int argc, char *argv[]) {
	File F;
	int N,i,Val;
	printf("Donnez le nombre d'elements de la file : \t");
	scanf("%d",&N);
	F.queue=NULL;
	F.tete=NULL;
	for(i=1;i<=N;i++) {
		printf("\n Donnez un element\t");
		scanf("%d",&Val);
		ENFILER(&F ,Val);
	}
	AFFICHER_FILE(&F);
	

	return 0;
}