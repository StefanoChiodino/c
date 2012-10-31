#include <stdio.h>
#include <stdlib.h>
#include <conio.h>



typedef struct t_alb {
	struct t_alb *sx;
	struct t_alb *dx;
	int key;
} nodo;

typedef struct t_alb *ptr;



void crea(ptr *);
void inorderSVD(ptr);
void preorderVSD(ptr);
void postorderSDV(ptr);
void peso(ptr);
void calcolo(ptr);

int altezza(ptr);

void menu(void);


int somma=0;


int main() {
ptr radice=NULL;
int scelta;

  radice=(ptr)malloc(sizeof(nodo));
  radice->sx=radice->dx=NULL;
   do {
   	menu();
      scanf("%d",&scelta);

      switch(scelta) {
      	case 1: { crea(&radice);		  break; }
      	case 2: { inorderSVD(radice);   break; }
      	case 3: { preorderVSD(radice);  break; }
      	case 4: { postorderSDV(radice); break; }
      	case 5: { peso(radice);
         			 printf("\nPeso Albero : %d",somma);
                   break;
         		  }
      	case 6: { printf("\nAltezza Albero: %d",altezza(radice)); break; }
         case 0: {printf("\n\n\n\t\t\tPREMERE UN TASTO PER USCIRE"); break; }
         default: printf("\nScelta Errata");
      }
      fflush(stdin);
      getchar();


   }
   while(scelta!=0);
}



void crea(ptr *radice) {
ptr sin,des;
int item;
char risp;

	printf("\nInserisci il dato: ");
   scanf("%d",&item);

   (*radice)->sx=NULL;
   (*radice)->dx=NULL;
   (*radice)->key=item;

   printf("\n %d ha un figlio sinistro? (s/n) :", (*radice)->key);
   fflush(stdin);
   risp=getchar();

   if(risp=='n') (*radice)->sx=NULL;
   else {
   	sin=(ptr)malloc(sizeof(nodo));
      (*radice)->sx=sin;
      crea(&sin);
   }
   printf("\n %d ha un figlio destro? (s/n) :",(*radice)->key);
   fflush(stdin);
   risp=getchar();
   if(risp=='n') (*radice)->dx=NULL;
   else {
   	des=(ptr)malloc(sizeof(nodo));
      (*radice)->dx=des;
      crea(&des);
   }
}


void inorderSVD(ptr radice) {

	if(radice) {
   	inorderSVD(radice->sx);
      printf("%d ",radice->key);
   	inorderSVD(radice->dx);
   }
}

void preorderVSD(ptr radice) {

  	if(radice) {
      printf("%d ",radice->key);
   	preorderVSD(radice->sx);
   	preorderVSD(radice->dx);
   }
}


void postorderSDV(ptr radice) {

	if(radice) {
   	postorderSDV(radice->sx);
   	postorderSDV(radice->dx);
      printf("%d ",radice->key);
   }
}


void peso(ptr radice) {

   if(!radice) return;
   	peso(radice->sx);
      peso(radice->dx);
      calcolo(radice);
}



void calcolo(ptr radice) {

 if(radice->sx)
 {
  somma++;
  calcolo(radice->sx);
 }
 if(radice->dx)
 {
  somma++;
  calcolo(radice->dx);
 }
}


int altezza(ptr radice) {
 int s,d;
 if(!radice) return(0);
 s=altezza(radice->sx);
 d=altezza(radice->dx);
 if(s > d)	return(1+s);
 else 		return(1+d);


}




void menu(void) {
   printf("\n^^^^^^^^^^^^^^^^^^^^^^^ ALBERI BINARI ^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("\n\n");
   printf("\n\t\t\t1- Crea Albero");
   printf("\n\t\t\t2- Visita Inorder");
   printf("\n\t\t\t3- Visita Preorder");
   printf("\n\t\t\t4- Visita Postorder");
	printf("\n\t\t\t5- Calcola Peso");
	printf("\n\t\t\t6- Calcola Altezza");
	printf("\n\t\t\t0- Esci");

   printf("\n\n\t\tScelta: ");
}
