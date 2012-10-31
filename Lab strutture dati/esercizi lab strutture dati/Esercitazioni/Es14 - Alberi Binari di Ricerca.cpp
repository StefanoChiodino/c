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
void postorderSDV(tree_ptr);
void preorderVSD(tree_ptr);
void inorderSVD(tree_ptr);
void deletecpy(tree_ptr *root, char *item);
void deletefusion(tree_ptr *root, char *item);
tree_ptr ric_ric(tree_ptr, char *);
tree_ptr ric_iter(tree_ptr, char *);

void menu(void);


int main() {
int scelta;
char key[MAX_STRING_SIZE];
tree_ptr radice=NULL;

	do {
   	fflush(stdin);
		menu();
      scanf("%d",&scelta);
      switch(scelta) {
      	case 1: {
         	fflush(stdin);
         	printf("INSERIMENTO NUOVO NODO\n\nInserisci il dato: ");
            gets(key);
            insert_nodo(&radice,key);
            break;
         }
         case 2: {
         	fflush(stdin);
         	printf("RICERCA ELEMENTO (ric)\n\nCerca: ");
            gets(key);
            if(ric_ric(radice,key)) printf("\nELEMENTO PRESENTE");
            else printf("\nELEMENTO NON PRESENTE");
         	break;
         }
         case 3: {
         	fflush(stdin);
         	printf("RICERCA ELEMENTO (iter)\n\nCerca: ");
            gets(key);
            if(ric_iter(radice,key)) printf("\nELEMENTO PRESENTE");
            else printf("\nELEMENTO NON PRESENTE");
         	break;
         }
         case 4: {
         	fflush(stdin);
         	printf("CANCELLAZIONE PER FUSIONE\n\nElemento da cancellare: ");
            gets(key);
         	deletefusion(&radice,key);
	        	break;
         }
         case 5: {
         	fflush(stdin);
         	printf("CANCELLAZIONE PER COPIATURA\n\nElemento da cancellare: ");
            gets(key);
         	deletecpy(&radice,key);
            break;
         }
         case 6: { inorderSVD(radice); break; }
         case 7: { preorderVSD(radice); break; }
         case 8: { postorderSDV(radice); break; }
         case 0: { printf("\nPREMERE UN TASTO PER USCIRE..."); break;}

      	default: { printf("\nATTENZIONE! SCELTA ERRATA!"); }
      }
      fflush(stdin);
      getchar();
   }
   while(scelta != 0);

}



void menu(void) {
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


void insert_nodo(tree_ptr *radice, char *item) {

		tree_ptr app, tmp;

	tmp=findpos(*radice,item);
   if(tmp || !(*radice))
   {
   	app=(tree_ptr)malloc(sizeof(nodo));
      if(!app)
      {
      	printf("\nMEMORIA PIENA");
         exit(1);
      }
      strcpy(app->key,item);
      app->sx=app->dx=NULL;
      if(*radice)
      	if(strcmp(item,tmp->key)<0)
         	tmp->sx=app;
         else
         	tmp->dx=app;
      else *radice=app;
   }
   else
   	if ((tmp==NULL) && *radice!=NULL) printf("\nATTENZIONE! ELEMENTO GIA PRESENTE!");
}


tree_ptr findpos(tree_ptr radice, char *key) {
tree_ptr temp=NULL;

	while(radice)
 	{
		temp=radice;
	   if(strcmp(key,radice->key)==0)  /*se il nome é presente rende null*/
 		return(NULL);
  		if(strcmp(key,radice->key)<0)
 			radice=radice->sx;
  		else
   		radice=radice->dx;
 	}
 	return(temp);
}

void inorderSVD(tree_ptr radice) {

	if(radice) {
   	inorderSVD(radice->sx);
      printf("%s ",radice->key);
   	inorderSVD(radice->dx);
   }
}

void preorderVSD(tree_ptr radice) {

  	if(radice) {
      printf("%s ",radice->key);
   	preorderVSD(radice->sx);
   	preorderVSD(radice->dx);
   }
}


void postorderSDV(tree_ptr radice) {

	if(radice) {
   	postorderSDV(radice->sx);
   	postorderSDV(radice->dx);
      printf("%s ",radice->key);
   }
}


void deletecpy(tree_ptr *root, char *item) {
tree_ptr tmp, node, prev=NULL, p=*root, previous;

	while(p!=NULL && strcmp(item,p->key)!=0) {
   	prev=p;
      if(strcmp(item,p->key) >0) p=p->dx;
      else p=p->sx;
   }

   node=p;
   if(p!=NULL && strcmp(item,p->key)==0) {
   	if(node->dx==NULL) node=node->sx;
      else if(node->sx==NULL) node=node->dx;
     		  else {
           		tmp=node->sx;
               previous=node;

               while(tmp->dx!=NULL) {
               	previous=tmp;
                  tmp=tmp->dx;
               }

               strcpy(node->key, tmp->key);
               if(previous==node) previous->sx=tmp->sx;
               else previous->dx=tmp->sx;
           }
           if(p==*root) *root=node;
           else if(prev->sx==p) prev->sx=node;
           		 else prev->dx=node;
   }
   else if(*root!=NULL) printf("\nSTRINGA NON TROVATA!");
   	  else printf("\nL'ALBERO E' VUOTO!");
   return;
}

void deletefusion(tree_ptr *radice, char *item) {
tree_ptr tmp, node, prev=NULL, ptr=*radice;

	while(ptr!=NULL && strcmp(item,ptr->key)!=0) {
   	prev=ptr;
      if(strcmp(item,ptr->key)>0) ptr=ptr->dx;
      else ptr=ptr->sx;
   }

   node=ptr;

   if(ptr!=NULL && strcmp(item,ptr->key)==0) {
   	if(node->dx==NULL) node=node->sx;
      else if(node->sx==NULL) node=node->dx;
      	  else {
           		tmp=node->sx;
            	while(tmp->dx!=NULL) tmp=tmp->dx;
            	tmp->dx=node->dx;
            	node=node->sx;
           }
      if(ptr==*radice) *radice=node;
      else if(prev->sx==ptr)	prev->sx=node;
      	  else prev->dx=node;
   }
   else if(*radice!=NULL) printf("\n%s non è presente nell'albero", item);
   	  else printf("L'ALBERO E' VUOTO!");
   return;
}






tree_ptr ric_ric(tree_ptr tree, char *key) {

	if(!tree) return(NULL);
	if(strcmp(key,tree->key)==0) return(tree);
	if(strcmp(key,tree->key)<0) return(ric_ric(tree->sx,key));
	return(ric_ric(tree->dx,key));

}


tree_ptr ric_iter(tree_ptr tree, char *key) {

	while(tree) {
	  	if(strcmp(key,tree->key)==0) return(tree);
		if(strcmp(key,tree->key)<0) tree=tree->sx;
		tree=tree->dx;
   }
   return(NULL);
}
