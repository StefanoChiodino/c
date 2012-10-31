#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAX 50
#define MLL 10							//Max List Length


typedef struct elemento {
	int info;
   struct elemento *next;
} ele;




ele *crealista(ele *);
void printlist(ele *);
ele *mergeandsort(ele *, ele *);


int main() {
ele *x,*y,*z;

	x=y=z=NULL;
   x=crealista(x);
   y=crealista(y);




   printf("\nLista x: ");
   printlist(x);
   printf("\nLista y: ");
   printlist(y);

   z=mergeandsort(x,y);
   printf("\nLista z:");
   printlist(z);




	fflush(stdin);
   getchar();
}



void printlist(ele *p) {

	for(;p;p=p->next)
   	printf("%2d - ",p->info);
}





ele *crealista(ele *inizio) {
int dato=0,i,f;
ele *p,*app;

	for(i=0; i<MLL; i++) {
   	p=inizio; f=1;
   	app=(ele *)malloc(sizeof(ele));
      app->next=NULL;
      app->info=rand()%MAX;
      if(inizio==NULL)
      	inizio=app;
      else {
			if(p->info > app->info) {
         	app->next=inizio;
            inizio=app;
         }
         else {
         	while(p->next && f)
            {
        			if(p->next->info < app->info)
         			p=p->next;
         		else
         			f=0;
            }
            app->next=p->next;
            p->next=app;
         }

      }

   }
   return(inizio);
}


ele *mergeandsort(ele *x, ele *y) {
ele *inizio=NULL;
ele *p=inizio;

	while(x && y) {
   	if(x->info <= y->info) {
   		if (p==NULL) {inizio=p=x;}
         	else 		 {p->next=x; p=p->next;}
         x=x->next;
      }
      else {
   		if (p==NULL) {inizio=p=y;}
         	else 		 {p->next=y; p=p->next;}
         y=y->next;
      }
   }

   if(x!=NULL)
   	for(; x; p->next=x, x=x->next, p=p->next);
   if(y!=NULL)
		for(; y; p->next=y, y=y->next, p=p->next);

   return(inizio);
}
