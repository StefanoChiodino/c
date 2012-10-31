#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MLL 10			// Max List Length
#define MLV 50			// Max List Value

typedef struct elemento
					{
               	int info;
                  struct elemento *next;
               } ele;

void printlist(ele *);
ele *creadopo(ele *, int, int);
ele *crealista(ele *);


int main()
{
		ele *x, *y, *z;

	x=y=z=NULL;

   x=crealista(x);
   y=crealista(y);

   printlist(x);
   printlist(y);


	fflush(stdin);
   getchar();
}

void printlist(ele *p)
{
	for(; p; p=p->next)
   	printf("%2d ",p->info);
  	printf("\n");
}

ele *creadopo(ele *inizio, ele *dove, int info)
{
		ele *app;

  	app=(ele *)malloc(sizeof(ele));
   app->info=info;
   if(inizio==NULL || inizio==dove)
	{
	   app->next=dove;
   	dove=app;
   	return(dove);
   }
   app->next=dove->next;
 	dove->next=app;
  	return(inizio);
}


ele *crealista(ele *inizio)
{
		int i, info;
      ele *app, *p;

	for(i=0; i<MLL; i++)
   {
   	p=inizio;
      app=p;
      info=rand()%MLV;
      for(; p && (p->info < info); p=p->next);
      	inizio=creadopo(inizio,p,info);
   }
   return(inizio);
}
