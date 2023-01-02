#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// P c'est le pointeur , *P c'est la variable pointee par P // declaration d'un pointeur sur entier : int*P

 /* 
 	declaration d'une liste
 	creation (FIFO+LIFO)
 	insertion (debut - milieu - fin) // indiquer la position K 
 	
 */
typedef struct Liste {   // 1 2 3 4 5 6     tete  (1+pointeur sur 2)   (2+pointeur sur 3) ........ (6+NULL)
   int X; 
   struct Liste*suivant ;   // un element de la liste = (int + pointeur vers liste)
   
}Liste,*plist ;  // struct Liste * = plist

void CREATION_FIFO(plist*tete) {  // Fifo = First In First Out    (1+pointeur vers2) 2 3 4 (5+NULL)          LIFO = Last In First Out  5 4 3 2 1
	int N,i , Val;
	plist P, Q;
	printf("Donnez le nombre des elements de la liste \t");
	scanf("%d",&N);
	printf("\n Donnez les elements de la liste : \n");
	(*tete)=malloc(sizeof(Liste));
	printf("Donnez le 1er element \t");
	scanf("%d",&Val);
	(*tete)->X=Val;
	(*tete)->suivant=NULL;
	P=(*tete);
	for(i=1;i<N;i++) {
		printf("\nDonnez le %d eme element \t",i);
	    scanf("%d",&Val);
	    Q=malloc(sizeof(Liste));
	    Q->X=Val;
	    P->suivant=Q;
	    P=P->suivant;
	    
	}
	P->suivant=NULL;	
}


void CREATION_LIFO(plist*tete) {
	int N,i , Val;
	plist P, Q;  
	printf("Donnez l e nombre des elements de la liste \t");
	scanf("%d",&N);
	printf("\n Donnez les elements de la liste : \n");
	(*tete)=malloc(sizeof(Liste)); 
	printf("Donnez le 1er element \t");
	scanf("%d",&Val);
	(*tete)->X=Val;
	(*tete)->suivant=NULL;
	
	for(i=1;i<N;i++) {
		printf("\nDonnez le %d eme element \t",i);
	    scanf("%d",&Val);
	    Q=malloc(sizeof(Liste));
	    Q->X=Val;
	    Q->suivant=(*tete);
	    (*tete)=Q;	    
	}	
}
void INSERTION(int Val ,plist*tete , int K ){
	plist Q;
	int i;
	plist P = malloc(sizeof(Liste));     
	P->X=Val;   
	if(K==1){
		//insertion au debut 
	P->suivant=(*tete);
	(*tete)=P;	
	}
	else {
		Q=(*tete); 
		i=1;
		while (i<K-1 && Q->suivant!=NULL){      
	        Q=Q->suivant;
			i++;	
		}
		if(Q->suivant==NULL) {  // insertion a la fin
			Q->suivant=P;
			P->suivant=NULL;
		}
		else {  // insertion au milieu
			P->suivant=Q->suivant;
			Q->suivant=P;
		}	
	}
		
}
void AFFICHAGE(plist T) {
	while(T!=NULL)  {
		printf("\n%d",T->X);  
		T=T->suivant; 
	}
}
 

int main(int argc, char *argv[]) {
	plist T; // tete de liste  elle pointe sur le 1er element de la liste 
	T=NULL;
	int N,K;
	// creation FIFO : 
	CREATION_FIFO(&T) ;   //&tete    
	AFFICHAGE(T);
	printf("\n Donnez une valeur a inserer \t"); 
	scanf("%d",&N);
	printf("\n Donnez une position \t");
	scanf("%d",&K);
	INSERTION(N,&T ,K );
	AFFICHAGE(T);
	
	
	return 0;
}