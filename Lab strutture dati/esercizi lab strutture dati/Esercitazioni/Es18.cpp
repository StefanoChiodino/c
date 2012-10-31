#include <stdio.h>
#include <stdlib.h>
#define max_vertice 50

typedef struct nodo *nodo_p;
typedef struct nodo	{
	int vertice;
   nodo_p link;
} Nodo;

typedef struct coda *coda_p;
typedef struct coda	{
	int vertice;
   coda_p link;
} Coda;

nodo_p grafo[max_vertice];
int n=0, visitato[max_vertice], distanza[max_vertice];
coda_p davanti[max_vertice], dietro[max_vertice];

void insert(void);
void rpr(int);
void ram(int);
void addc(coda_p *, coda_p *, int);
int deletec(coda_p *);
void trovad(int);

main() {
int i, j;
	for(i=0; i<max_vertice; i++)
	grafo[i]=NULL;
	printf("\nDISTANZA TRA NODI DI UN GRAFO\n");
	printf("\nInserimanto dati\n");
	insert();
	printf("\nDati acquisiti\n");
	printf("\nVisita in profondita':\n");

	for(i=0; i<n; i++)
		visitato[i]=0;

	rpr(0);
	printf("\nVisita in ampiezza:\n");
	for(i=0; i<n; i++)
		visitato[i]=0;
	ram(0);

   for(i=0; i<n; i++) {
	   for(j=0; j<n; j++)
			visitato[j]=distanza[j]=0;
		trovad(0);
	   for(j=0; j<n; j++)
			printf("\nDistanza di %d da %d: %5d\n", j, i, distanza[j]);
   }
	fflush(stdin);
	getchar();
}


void insert(void) {
nodo_p temp, current;
int i, buf;

	printf("\nDai il numero di vertici: ");
	scanf("%d", &n);
	for(i=0; i<n; i++) {
	   grafo[i]=(nodo_p)malloc(sizeof(Nodo));
	   grafo[i]->vertice=i;
	   grafo[i]->link=NULL;
	   current=grafo[i];
	   while(1)	{
	      printf("\nDai i vertici i cui lati entranti escono da %d (valori tra 0 e %d escluso %d;\n -1 per terminare)\n", i, n-1, i);
	      scanf("%d", &buf);
	      if(buf==-1)	break;
	      else
   	   	if(buf<=-1 || buf>n-1 || buf==i)	continue;
	      temp=(nodo_p)malloc(sizeof(Nodo));
	      temp->link=NULL;
	      temp->vertice=buf;
	      current->link=temp;
	      current=current->link;
      }
   }
}


void rpr(int v) {
nodo_p w;
	printf("%5d", v);
	visitato[v]=1;
	for(w=grafo[v]; w; w=w->link)
		if(!visitato[w->vertice])
	   	rpr(w->vertice);
}

void ram(int v) {
nodo_p w;
coda_p davanti, dietro;
davanti=dietro=NULL;

	printf("%5d", v);
	visitato[v]=1;
	addc(&davanti, &dietro, v);
	while(davanti)	{
	   v=deletec(&davanti);
	   for(w=grafo[v]; w; w=w->link)
   		if(!visitato[w->vertice]) {
	         printf("%5d", w->vertice);
	         addc(&davanti, &dietro, w->vertice);
	         visitato[w->vertice]=1;
         }
   }
}


void addc(coda_p *davanti, coda_p *dietro, int item) {
coda_p temp=(coda_p)malloc(sizeof(Coda));

	if(!(temp))	{
	   printf("\nMemoria piena!\n");
	   exit(1);
	}

   temp->vertice=item;
   temp->link=NULL;
	if(*davanti)
		(*dietro)->link=temp;
	else
		*davanti=temp;
	*dietro=temp;
}


int deletec(coda_p *davanti) {
coda_p temp=*davanti;
int item;
	if(!(davanti))	{
	   printf("\nLa coda e' vuota!\n");
	   exit(1);
   }

	item=temp->vertice;
	*davanti=temp->link;
	free(temp);
	return item;
}

void trovad(int v) {
nodo_p w;
coda_p davanti, dietro;
davanti=dietro=NULL;

	visitato[v]=1;
	addc(&davanti, &dietro, v);
	while(davanti)	{
	   v=deletec(&davanti);
	   for(w=grafo[v]; w; w=w->link)
	   	if(!visitato[w->vertice]) {
	         distanza[w->vertice]=distanza[v]+1;
	         addc(&davanti, &dietro, w->vertice);
	         visitato[w->vertice]=1;
         }
   }
}
