
/* <<<<<<<<<<<<<<<< Cammino orientato tra nodi di un grafo >>>>>>>>>>>>>>>>>  */

/* -	Scrivere un algoritmo per il seguente problema:
		Dato un grafo orientato G=(V,L) rappresentato mediante liste di adiacenza,
      calcolare per ogni nodo v appartenente a V il numero dei nodi Omega
      raggiungibili da v, ovvero il numero dei nodi Omega appartenenti a V per
      i quali esiste un cammino orientato da V a Omega.							 - */
//
//
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_VERTICI 10		/* Numero massimo di vertici del GRAFO */

/* STRUTTURA GRAFO
	Implementato attraverso liste di adiacenza */
typedef struct t_nodo
{
	int vertice;
	struct t_nodo *link;
} nodo;
typedef nodo *nodo_ptr;

nodo_ptr grafo[MAX_VERTICI];		/* GRAFO */
int visitato[MAX_VERTICI];			/* vettore dei vertici già visitati */

/* PROTOTIPI FUNZIONI */
int menu(void);
int insert(void);
int getv(int);
void rpr(int);
void ram(int v);
void azzera(int *, int);
int n_connessi(int);

/* DEFINIZIONE CODA */
typedef struct t_coda
{
	int vertice;
   struct t_coda *link;
} coda;

typedef coda *coda_ptr;

void addc(coda_ptr *, coda_ptr *, int);
int deletec(coda_ptr  *);

void main()
{
		int i, scelta,
      	 n=0;				/* numero di vertici del grafo, inizialmente = 0 */
      int v_start;		/* vertice di partenza utilizzato nelle visite   */

   do
   {
   	clrscr();
   	scelta=menu();
   	switch(scelta)
   	{
      	case 1: { n=insert(); break; }
         case 2: if(n>0)
         		  { azzera(visitato,n);
                   v_start=getv(n);
                   printf("\nRPR: ");
                   rpr(v_start);
                 }
                 else printf("GRAFO VUOTO!!");
                 break;
         case 3: if(n>0)
         		  { azzera(visitato,n);
                   v_start=getv(n);
                 	 printf("\nRAM: ");
                   ram(v_start);
                 }
                 else printf("GRAFO VUOTO!!");
                 break;
         case 4: if(n>0)
         		  { for(i=0; i<n; i++)
                 	 { azzera(visitato,n); printf("\nVertice %d: %d",i,n_connessi(i)); }
                 }
                 else printf("GRAFO VUOTO!!");
                 break;
         case 0: { printf("\nPremere un tasto per uscire..."); break; }
         default:{ printf("\nScelta errata"); break; }
  	 	}
     	fflush(stdin);
	   getchar();
   }
   while(scelta != 0);
}

int menu(void)
{
		int buf;

	printf("\n****************************** GRAFI ******************************\n\n");
	printf("1) CREA IL GRAFO\n");
	printf("2) VISITA IN PROFONDITA'\n");
	printf("3) VISITA IN AMPIEZZA\n");
   printf("4) VERTICI CONNESSI\n");
	printf("0) TERMINA\n");
   printf("\nScelta: ");
  	scanf("%d",&buf);
	return buf;
}

int insert(void)
{
		nodo_ptr temp, current;
		int i, buf, n;

	printf("\nInserisci il numero di vertici: ");
	scanf("%d",&n);
	for (i = 0; i < n; i++)
   {
		grafo[i] = (nodo_ptr) malloc(sizeof(nodo));
		grafo[i]->vertice = i;	grafo[i]->link = NULL;
		current = grafo[i];
		while(1)
      {
			printf("\nInserisci i vertici connessi a %3d \n",i);
			printf("(valori tra 0 e %3d escluso %3d; -1 termina): ", n-1,i);
			scanf("%d",&buf);
			if (buf == -1)	break;
			else if (buf <=-1 || buf > n-1 || buf==i)	continue;
			temp = (nodo_ptr) malloc(sizeof(nodo));
			temp->link = NULL;		temp->vertice = buf;
			current->link = temp;	current = current->link;
		}
	}
   return(n);
}

int getv(int n)
{
		int v;

   printf("\nSpecificare il vertice di partenza [ 0 <= n < %d ]\n",n);
	do
   {
   	printf(": ");
		scanf("%d",&v);
   }
   while(v<0 || v>n);
   return(v);
}

void azzera(int *v, int n)
{
		int i;

	for(i=0; i<n; i++) v[i]=0;
}

void rpr(int v)
{	/*ricerca in profondità di un grafo*/

		nodo_ptr w;

	printf("%5d  ",v);
   visitato[v]=true;
	for(w = grafo[v]; w; w = w->link)
		if(!visitato[w->vertice]) rpr(w->vertice);
}

void ram(int v)
{	/*ricerca in ampiezza di un grafo */

		coda_ptr davanti, dietro;
		nodo_ptr w;

	davanti=dietro=NULL;			/*inizializza la coda*/
	printf("%5d",v);	visitato[v] = true;
	addc(&davanti,&dietro, v);
	while(davanti)
   {
		v = deletec(&davanti);
		for(w = grafo[v]; w; w = w->link)
		if (!visitato[w->vertice])
      {
			printf("%5d", w->vertice);
			addc(&davanti, &dietro, w->vertice);
			visitato[w->vertice] = true;
		}
	}
}

void addc(coda_ptr *davanti, coda_ptr *dietro , int item)
{				/*aggiunge un elemento alla coda*/

		coda_ptr temp;

	temp=(coda_ptr) malloc(sizeof(coda));
	if(temp == NULL)
   {  printf("\nla memoria è piena");	exit(1);	}

   temp->vertice = item;
   temp->link = NULL;
	if (*davanti) (*dietro)->link = temp;
	else *davanti = temp;
	*dietro = temp;
}

int deletec(coda_ptr  *davanti)
{				/*cancella il primo elemento di una coda*/

		coda_ptr temp = *davanti;
		int item;

	if (!*davanti)  { printf("\nla coda è vuota\n");	exit(1);	}
	item = temp->vertice;		*davanti = temp->link;
	free(temp);
	return item;
}

int n_connessi(int v)
{
		nodo_ptr w;

   visitato[v]=true;
	for(w = grafo[v]; w; w = w->link)
   	if(!visitato[w->vertice]) return(1+n_connessi(w->vertice));
   return(0);
}
