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
void menu(void);

int main() {
ptr radice=NULL;
int scelta;

  radice=(ptr)malloc(sizeof(nodo));
   do {
   	menu();
      scanf("%d",&scelta);

      switch(scelta) {
      	case 1: { crea(&radice); break;}
      	case 2: { if(radice!=NULL) inorderSVD(radice);
                   else
                   	printf("\nAlbero vuoto");
                   break;
                 }
      	case 3: {
         			 if(radice!=NULL) preorderVSD(radice);
                   else
                   	printf("\nAlbero vuoto");
                   break;
         			}
      	case 4: { if(radice!=NULL) postorderSDV(radice);
                   else
                   	printf("\nAlbero vuoto");
                   break;
         		  }
         case 0: break;
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

   printf("\n %d ha un figlio sinistro? (s/n)\n:", (*radice)->key);
   fflush(stdin);
   risp=getchar();

   if(risp=='n') (*radice)->sx=NULL;
   else {
   	sin=(ptr)malloc(sizeof(nodo));
      (*radice)->sx=sin;
      crea(&sin);
   }
   printf("\n %d ha un figlio destro? (s/n)\n:",(*radice)->key);
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


void menu(void) {
   printf("\n^^^^^^^^^^^^^^^^^^^^^^^ ALBERI BINARI ^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("\n\n");
   printf("\n\t\t\t1- Crea Albero");
   printf("\n\t\t\t2- Visita Inorder");
   printf("\n\t\t\t3- Visita Preorder");
   printf("\n\t\t\t4- Visita Postorder");
	printf("\n\t\t\t0- Esci");

   printf("\n\n\t\tScelta: ");
}
