#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct noeud {
	int x;
	struct noeud * FilsG;
	struct noeud * FilsD;
}noeud,*arbre;

typedef struct listeF {
	arbre x;
	struct listeF*suivant;
}listeF,*plistF;

typedef struct file {
	plistF tete;
	plistF queue ;
}file;
void Enfiler(file*F,arbre X) {
	plistF P;
	P=malloc(sizeof(listeF));
	P->x=X;
	if((*F).tete==NULL) {
		P->suivant=NULL;
		(*F).tete=P;
		(*F).queue=P;
	}
	else {
		((*F).queue)->suivant=P;
		((*F).queue)=((*F).queue)->suivant;
		P->suivant=NULL;
	}
}

void Defiler(file*F,arbre*X) {
	plistF P=(*F).tete;
	*X=((*F).tete)->x;
	if(((*F).tete)->suivant!=NULL) {
		(*F).tete=((*F).tete)->suivant;
			
	}
	else {
		(*F).tete=NULL;
		(*F).queue=NULL;
	}
	free(P);
}

arbre TeteFile(file F) {
	return (F.tete)->x;
}

bool FileVide(file F) {
	if(F.tete==NULL)  {
		return true;
	}
	else {
		return false;
	}
}

void InitFile(file*F) {
	(*F).tete=NULL;
	(*F).queue=NULL;
}

arbre NOUVEAU_NOEUD(int Val) {
	arbre A;
	A=malloc(sizeof(noeud));
	A->x=Val;
	A->FilsG=NULL;
	A->FilsD=NULL;
	return A;
}

bool ArbreVide(arbre A) {
	if(A==NULL) {
		return true;
	}
	else {
		return false;
	}
}

arbre FilsGauche(arbre A) {
	return A->FilsG;
}

arbre FilsDroit(arbre A) {
	return A->FilsD;
}

bool FEUILLE(arbre A) {
	if(FilsDroit(A)==NULL && FilsGauche(A)==NULL) {
		return true;
	}
	else {
		return false;
	}
}

void INSERER_ABR(arbre* A,int Val) {
	arbre C;
	if(ArbreVide(*A)==true) {
		*A=NOUVEAU_NOEUD(Val);
	}
	else {
		C=*A;
		if((*A)->x < Val){
			
			INSERER_ABR(&(C->FilsD),Val);
		}
		else {
			
			INSERER_ABR(&(C->FilsG),Val);
			
		}
	}
}

void CREATION_ABR(arbre* A,int N) {
	int X,i;
	arbre B,C;
	*A=NULL;
	for(i=1;i<=N;i++) {
		printf("element %d \t",i);
		scanf("%d",&X);
	     INSERER_ABR(&(*A),X);
		printf("\n");
		
	}
	
	
}


int MAX_ABR(arbre A) {
	int max;
	if(FilsGauche(A)==NULL) {
		max=A->x;
	}
	else {
		max=MAX_ABR(FilsDroit(A));
	}
	return max;
}

int MIN_ABR(arbre A) {
	int min;
	if(FilsGauche(A)==NULL) {
		min=A->x;
	}
	else {
		min=MIN_ABR(FilsGauche(A));
	}
	return min;
}

void LARGEUR(arbre A) {
	file F;
	int X;
	InitFile(&F);
	if(ArbreVide(A)==false) {
		Enfiler(&F,A);
		while(FileVide(F)==false) {
			Defiler(&F,&A);
			printf("%d\t",A->x);
			if(A->FilsG!=NULL) {
				Enfiler(&F,A->FilsG);	
			}
			if(A->FilsD!=NULL) {
				Enfiler(&F,A->FilsD);	
			}
		}
		
	}
}

int Max(int A,int B) {
	if(A>B) {
		return A;
	}
	else {
		return B;
	}
}

int HAUTEUR(arbre A) {
	int H;
	if(ArbreVide(A)==true) {
		H=0;
	}
	else {
	
		
			H=1+Max(HAUTEUR(A->FilsG),HAUTEUR(A->FilsD));
		
	}
	return H;
}

bool COMPLET(arbre A) {
	bool C;
	C=true;
	if(ArbreVide(A)==true) {
		C=false;
	}
	else {
		if(FEUILLE(A)==false) {
			if(A->FilsG==NULL || A->FilsD==NULL) {
				C=false;
			}
			else {
				C=COMPLET(A->FilsG);
				C=COMPLET(A->FilsD);
			}
		}
	}
	return C;
}


int ABS(int X) {
	if(X<0) {
		return -X;
	}
	else {
		return X;
	}
}


bool EQUILIBRE(arbre A) {
	bool E;
	E=true;
	if(ArbreVide(A)==false) {
		if(ABS(HAUTEUR(A->FilsG)-HAUTEUR(A->FilsD))>1) {
			E=false;
		}
		else {
			E=EQUILIBRE(A->FilsG);
			E=EQUILIBRE(A->FilsD);
		}
	}
	return E;
}

bool PARFAIT(arbre A) {
	bool P;
	P=true;
	if(COMPLET(A)==false) {
		P=false;
	}
	else {
		if(HAUTEUR(A->FilsG)!=HAUTEUR(A->FilsD)) {
			P=false;
		}
		else {
			P=HAUTEUR(A->FilsG)&&HAUTEUR(A->FilsD);
		}
	}
	return P;
}

void AFFICHERFEUILLE(arbre A) {
	if(ArbreVide(A)==false) {
		if(FEUILLE(A)==true) {
			printf("%d\t",A->x);
		}
		else {
			if(ArbreVide(A->FilsG)==false) {
				AFFICHERFEUILLE(A->FilsG);
			}
			if(ArbreVide(A->FilsD)==false) {
				AFFICHERFEUILLE(A->FilsD);
			}
		}
	}
}

bool DEGENERE(arbre A) {
	bool D=true;
	if(ArbreVide(A)==false) {
		if(ArbreVide(A->FilsG)==false && ArbreVide(A->FilsD)==false) {
			D=false;
		}
		else {
			if(ArbreVide(A->FilsG)==false) {
				D=DEGENERE(A->FilsG);
			}
			else {
				D=DEGENERE(A->FilsD);
			}
		}
	}
	return D;
}

arbre RECHERCHER(arbre A,int Val) {
	arbre P=NULL;
	if(ArbreVide(A)==false) {
		if(A->x==Val) {
			P=A;
		}
		else {
			if(Val > A->x) {
				P=RECHERCHER(A->FilsD,Val);
			}
			else {
				P=RECHERCHER(A->FilsG,Val);
			}
			
		}
	}
	return P;
}

int TAILLE(arbre A,int*N) {
	int T;
	if(ArbreVide(A)==false) {
		*N=*N+1;
		T=TAILLE(A->FilsG,&(*N));
		T=TAILLE(A->FilsD,&(*N));
		T=*N;
	}
	return T;
}

void MIRROIR(arbre A) {
	arbre X;
	if(ArbreVide(A)==false) {
		X=A->FilsG;
		A->FilsG=A->FilsD;
		A->FilsD=X;
		MIRROIR(A->FilsG);
		MIRROIR(A->FilsD);
	}
}

arbre ADRESSE_NODE(arbre A, int*K) {
	arbre D;

	D=NULL ;
	if(ArbreVide(A)==false) {
		D=ADRESSE_NODE(A->FilsG,&(*K));
		if(*K==1) {
			D=A;
		}
		else {
			*K=*K-1;
			D=ADRESSE_NODE(A->FilsD,&(*K));
		}
	}
	return D;
}

arbre ADRESSE_K(arbre A,int*K) {
	arbre D;
	D=NULL;
	if(ArbreVide(A)==false && *K!=0) {
		D=ADRESSE_K(A->FilsG,&(*K));
		if(*K==1) {
			D=A;	
		}
		else {
			*K=*K-1;
			D=ADRESSE_K(A->FilsD,&(*K));
		}	
	}
	return D;
}

void AFFICHE(arbre B) {
	file F;
	int X,Y;
	InitFile(&F);
	if(ArbreVide(B)==false) {
		Enfiler(&F,B);
		while(FileVide(F)==false) {
			Defiler(&F,&B);
			if(ArbreVide(B->FilsG)==false) {
				Enfiler(&F,B->FilsG);
				X=(B->FilsG)->x;	
			}
			else {
				X=000;
			}
			if(ArbreVide(B->FilsD)==false) {
				Enfiler(&F,B->FilsD);
				Y=(B->FilsD)->x;	
			}
			else {
				Y=000;
			}
			printf("(%d , %d , %d )\n",B->x,X,Y);
		}
	}
}

int MinTree(arbre A) {
	int min;
	file F;
	InitFile(&F);
	if(ArbreVide(A)==false) {
		min=A->x;
		if(ArbreVide(A->FilsG)==false) {
			Enfiler(&F,A->FilsG);
		}
		if(ArbreVide(A->FilsD)==false) {
			Enfiler(&F,A->FilsD);
		}
		while(FileVide(F)==false) {
			Defiler(&F,&A);
			if(A->x < min) {
				min=A->x;
			}
			if(ArbreVide(A->FilsG)==false) {
				Enfiler(&F,A->FilsG);
			}
			if(ArbreVide(A->FilsD)==false) {
				Enfiler(&F,A->FilsD);
			}
		}
	}

	return min;
}

int MaxTree(arbre A) {
	int max;
	file F;
	InitFile(&F);
	if(ArbreVide(A)==false) {
		max=A->x;
		if(ArbreVide(A->FilsG)==false) {
			Enfiler(&F,A->FilsG);
		}
		if(ArbreVide(A->FilsD)==false) {
			Enfiler(&F,A->FilsD);
		}
		while(FileVide(F)==false) {
			Defiler(&F,&A);
			if(A->x > max) {
				max=A->x;
			}
			if(ArbreVide(A->FilsG)==false) {
				Enfiler(&F,A->FilsG);
			}
			if(ArbreVide(A->FilsD)==false) {
				Enfiler(&F,A->FilsD);
			}
		}
	}

	return max;
}

int Minimum(int A,int B) {
	if(A < B) {
		return A;
	}
	else {
		return B;
	}
}

int MinHauteur(arbre A) {
	int H;
	if(ArbreVide(A)==false) {
		H=1+Minimum(HAUTEUR(A->FilsG),HAUTEUR(A->FilsD));
	}
	
	return H;
}

int MaxHauteur(arbre A) {
	int H;
	if(ArbreVide(A)==false) {
		H=1+Max(HAUTEUR(A->FilsG),HAUTEUR(A->FilsD));
	}
	
	return H;
}

int main(int argc, char *argv[]) {
	arbre A,B;
	int*T;
	int N,i,X;
	printf("donnez la taille de l arbre :\t");
	scanf("%d",&N);
	printf("\n");
	printf("donnez les elements de l arbre :\n");
	A=NULL;
	CREATION_ABR(&A, N);
	printf("\n \n l'affichage :\n\n");
	printf("\n min = %d\n",MinTree(A));
	printf("\n max = %d\n",MaxTree(A));
	printf("\n hauteur minimale  = %d\n",MinHauteur(A));
	printf("\n hauteur maximale  = %d\n",MaxHauteur(A));
	return 0;
}
