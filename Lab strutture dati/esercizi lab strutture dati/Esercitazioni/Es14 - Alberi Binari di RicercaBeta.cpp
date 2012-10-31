#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_STRING_SIZE 80


typedef struct t_alb {
	struct t_alb *sx;
	struct t_alb *dx;
	char key[MAX_STRING_SIZE];
} nodo;

typedef struct t_alb *tree_ptr;

void insert_nodo(tree_ptr *tree, char *key);
tree_ptr findpos(tree_ptr, char *);



void menu(void);


void main() {
int scelta;
char info[MAX_STRING_SIZE];
tree_ptr radice=NULL;

	do {
		menu();
      scanf("%d",&scelta);
      clrscr();
      switch(scelta) {
      	case 1: {
         	fflush(stdin);
         	printf("\nInserisci il dato: ");
            gets(info);
            insert_nodo(&radice,info);
            break;
         }
      	case 2: { break; }
      	case 3: { break; }
      	case 4: { break; }
      	case 5: { break; }
      	case 6: { break; }
      	case 7: { break; }
      	case 8: { break; }
         default:  { printf("\nATTENZIONE! SCELTA ERRATA"); break; }
      }
     	fflush(stdin);
      getchar();
   }
   while(scelta != '0');

}



void menu(void) {
  	clrscr();
   printf("^^^^^^^^^^^^^^^^^^^^^^^^^^ ALBERI BINARI DI RICERCA ^^^^^^^^^^^^^^^^^^^^^^^^^^");
	printf("\n\n\n\t\t\t1- INSERISCI ELEMENTO");
	printf("\n\t\t\t2- RICERCA ELEMENTO (ric)");
	printf("\n\t\t\t3- RICERCA ELEMENTO (iter)");
	printf("\n\t\t\t4- CANCELLA ELEMENTO PER FUSIONE");
	printf("\n\t\t\t5- CANCELLA ELEMENTO PER COPIATURA");
	printf("\n\t\t\t6- VISITA INORDER");
	printf("\n\t\t\t7- VISITA PREORDER");
	printf("\n\t\t\t8- VISITA POSTORDER");
	printf("\n\t\t\t0- ESCI");
   printf("\n\n\t\tScelta: ");
}


void insert_nodo(tree_ptr *tree, char *key) {

tree_ptr app,tmp;
   fflush(stdin);
	tmp=findpos(*tree, key);
	if(tmp || !(*tree)) {
	   app=(tree_ptr)malloc(sizeof(nodo));
      if(app==NULL) { printf("\nMEMORIA PIENA"); exit(1); }
      strcpy(app->key,key);
      app->sx=NULL; app->dx=NULL;
      if(*tree)
      	if(strcmp(key,app->key)<0) tmp->sx=app;
         else								tmp->dx=app;
      else *tree=app;
   }
   else
   	if(tmp==NULL && (*tree)!=NULL) printf("ELEMENTO %s GIA' PRESENTE!",*key);
}


tree_ptr findpos(tree_ptr tree, char *key) {




}
