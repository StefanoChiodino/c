#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


#define MAX_VERTICI 20

typedef struct t_nodo {
	int vertice;
		struct t_nodo *link;
}nodo;

typedef nodo *nodo_ptr;
nodo_ptr grafo[MAX_VERTICI];


typedef struct t_coda {
	int vertice;
   struct t_coda *link;
} coda;

typedef coda *coda_ptr;



int visitato[MAX_VERTICI];

int insert(void);
void rpr(int);
void ram(int);
void azzera(int *, int);
void visita(int, int);
void cancellazione(int);
int delete_lato(int, int);
void connesse(int);

int deletec(coda_ptr  *);
void addc(coda_ptr *, coda_ptr * , int);

int menu(void);



int main() {
int scelta,n=0;

	do {
   	scelta=menu();

      switch(scelta) {
			case 1: { n=insert(); break; }
			case 2: { visita(n,scelta);  break; }
			case 3: { visita(n,scelta); break; }
         case 4: { cancellazione(n); break; }
         case 5: { azzera(visitato,n); connesse(n); break; }
         case 0: { printf("\n\n\tPREMERE UN TASTO PER USCIRE"); fflush(stdin); break; }
         default:{ printf("\n\n\tSCELTA ERRATA!"); break; }
      }
      fflush(stdin);
      getchar();

   }
	while(scelta!=0);

}


int menu(void) {
	int buf;
	printf("\n\t\t^^^^^^^^^^^^^^ GRAFI ^^^^^^^^^^^^^^\n\n");
	printf("\n\t\t1- CREA GRAFO");
	printf("\n\t\t2- VISITA IN PROFONDITA'");
	printf("\n\t\t3- VISITA IN AMPIEZZA ");
   printf("\n\t\t4- CANCELLA LATO");
   printf("\n\t\t5- COMPONENTI CONNESSE");
	printf("\n\t\t0- ESCI");
   printf("\n\n\tScelta: ");
     	scanf("%d",&buf);
	return buf;
}


int insert(void) {
	nodo_ptr temp, current;
	int i, buf, n;
   printf("\n\t\t\tCREAZIONE GRAFO\n");
	printf("\nDai il numero di vertici: ");
	scanf("%d",&n);
	for (i = 0; i < n; i++) {
		grafo[i] = (nodo_ptr) malloc(sizeof(nodo));
		grafo[i]->vertice = i;	grafo[i]->link = NULL;
		current = grafo[i];
		while(1) {
			printf("\nDai i vertici connessi a %3d \n",i);
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

void rpr(int v) {
/*ricerca in profondità di un grafo*/
nodo_ptr w;

	printf("%5d  ",v); 	visitato[v]=true;
	for(w = grafo[v]; w; w = w->link)
		if(!visitato[w->vertice]) rpr(w->vertice);
}

void azzera(int *v, int n) {
int i;
	for(i=0; i<n; i++) v[i]=0;
}

void visita(int n, int s) {
int v;

	do {
		printf("\nSpecificare il vertice di partenza (0 <= v < %d )",n);
	   printf("\nVertice: ");
	   scanf("%d",&v);
   }
   while(v > n || v < 0);

	azzera(visitato,n);
   if(s==2) { printf("\nVISITA PER PROFONDITA: "); rpr(v);}
   else 	  { printf("\nVISITA PER AMPIEZZA: "); ram(v);}
}

void ram(int v) {
/*ricerca in ampiezza di un grafo */

coda_ptr davanti, dietro;
nodo_ptr w;

	davanti=dietro=NULL;			/*inizializza la coda*/
	printf("%5d",v);	visitato[v] = true;
	addc(&davanti,&dietro, v);
	while (davanti) {
		v = deletec(&davanti);
		for(w = grafo[v]; w; w = w->link)
			if (!visitato[w->vertice]) {
				printf("%5d", w->vertice);
				addc(&davanti, &dietro, w->vertice);
				visitato[w->vertice] = true;
			}
	}
}


void addc(coda_ptr *davanti, coda_ptr *dietro , int item) {
/*aggiunge un elemento alla coda*/
	coda_ptr temp;
	temp=(coda_ptr) malloc(sizeof(coda));
	if(temp == NULL) {
		printf("\nla memoria è piena");	exit(1);
   }
	temp->vertice = item;		temp->link = NULL;
	if (*davanti)	(*dietro)->link = temp;
	else		*davanti = temp;
	*dietro = temp;
}


int deletec(coda_ptr  *davanti) {
/*cancella il primo elemento di una coda*/
coda_ptr temp = *davanti;
int item;

	if (!*davanti)  { printf("\nla coda è vuota\n");	exit(1);	}
	item = temp->vertice;		*davanti = temp->link;
	free(temp);
	return item;
}



void cancellazione(int n) {
int v1,v2;
   printf("\n\t\t\t   CANCELLAZIONE LATO\n\t\t\t(Inserire -1 per annullare)\n\n");

   do {
		printf("\nInserire il primo vertice del lato.\nVertice 1: ");
	   scanf("%d",&v1);

	  	printf("\nInserire il secondo vertice del lato.\nVertice 2: ");
	   scanf("%d",&v2);

      if(v1==-1 || v2==-1) return;
   }
   while(v1<0 || v1>n || v2<0 || v2>n);

   if(delete_lato(v1,v2)!=-1)   {delete_lato(v2,v1); printf("\nLato cancellato correttamente.\nPremere un tasto per tornare al menu principale"); }
   else printf("\n\nI DUE VERTICI NON SONO CONNESSI");

}



int delete_lato(int v1, int v2) {
nodo_ptr p=grafo[v1], kill;

	if(p) {
   	if(p->vertice==v2) {kill=p; grafo[v1]=p->link; free(kill); return(1); }
      else {
      	while(p->link && p->link->vertice!=v2) p=p->link;
         if(p->link==NULL)  return(-1);
         else {
            kill=p->link;
            p->link=kill->link;
            free(kill);
				return(1);
         }
      }
   } return(-1);
}


void connesse(int n) {
int i;

	for(i=0; i<n; i++)
   	if(!visitato[i]) {
      	rpr(i);
         printf("\n");
      }
}
