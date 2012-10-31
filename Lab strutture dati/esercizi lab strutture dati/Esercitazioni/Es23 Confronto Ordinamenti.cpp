
/* <<<<<<<<<<<<<<<<<<<<<<<<< CONFRONTO ORDINAMENTI >>>>>>>>>>>>>>>>>>>>>>>>>  */

/* -	Confrontare i vari tipi di ordinamento contando il numero di confronti e
		di scambi per diversi tipi di dati di input. Valutare anche il tempo di
      esecuzione di ciascun algoritmo, ovviamente influenzato dall'architettura
      su cui il programma viene eseguito.												 - */


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>

#define MAX_CIFRE 5
#define RADICE_SIZE 10
#define MAX 99999

typedef struct nodo *lista_ptr;
typedef struct nodo
{
	int chiave[MAX_CIFRE];
   lista_ptr link;
}	lista;
lista_ptr testa=NULL;

/* PROTOTIPI FUNZIONI */
void copia(int *a, int *l, int);
void analisi(int *a,int n);
void lettura(int *a, int);
void selezione(int *a, int);
void inserzione(int *a, int, int);
void quick_sort(int *a, int, int);
void merge_sort(int *a, int, int);
void heap_sort(int *a, int);
void radix_sort(int *a, int);
void scambia(int *, int *);

/* PROTOTIPI FUNZIONI AUSILIARIE */
int perno(int *a, int, int);
void merge(int *a, int, int, int);
void adatta(int *a, int, int);
lista_ptr crea_lista(lista_ptr,int);
lista_ptr radice_sort(lista_ptr);

void free_list(lista_ptr *p);	/* Dealloca tutti i nodi della lista in ingresso */


int scambio,confronto;

main() {
		int lista[MAX];
 		int n,i,j,scelta=1,temp,b=0,cont=0;

 	puts("\n\n ** CONFRONTO METODI DI ORDINAMENTO **");
 	printf("\nNumero Elementi da Inserire (max %d) - 0 per uscire -: ", MAX);
 	scanf("%d", &n);
 	do {
	  	puts("\n\n ** T I P I  d i  I N S E R I M E N T O **\n");
		puts("1 - Ordinato");
		puts("2 - Quasi Ordinato");
		puts("3 - Inversamante Ordinato");
		puts("4 - Casuale");
		puts("0 - Uscita");
		printf("\nScelta: ");
		scanf("%d", &scelta);
		switch(scelta)	{
   		case 0:  puts("\n\n\tArrivederci!");
		            break;
		   case 1:  for(i=1;i<=n;i++) lista[i]=i;
      		      break;
		   case 2:  temp=n/10;
      		      for(i=0;i<n;i++) {
		            	cont++;
			            if(cont==temp) { b++; cont=0; }
         			   if(b%2) lista[i]=rand()%n;
			            else lista[i]=i;
            		}
		            break;
	   	case 3:  for(i=0,j=n;i<n;i++,j--) lista[i]=j;
         		   break;
		   case 4:  for(i=0;i<n;i++) lista[i]=rand()%n;
      		      break;
		   default: puts("\n\tScelta errata..");
		            break;
	  	}
		if(scelta) analisi(lista,n);
	 }
	 while(scelta);
}

void copia(int *a, int *l, int n) {
int i;
	 for(i=0;i<n;i++) a[i]=l[i];
}


void analisi(int *lista, int n) {
clock_t start,end;
int a[MAX];

	puts("\nAlgoritmo \tScambi\tConfronti\t\tTempo");

	copia(a,lista,n);
	confronto=scambio=0;
	start=clock();
	selezione(a,n);
	end=clock();
	printf("\nSelezione \t%3d\t%3d\t\t%3.3f",scambio,confronto,((double)(end-start))/CLK_TCK);

	copia(a,lista,n);
	start=clock();
	inserzione(a,1,n-1);
	end=clock();
	printf(" ok\nInserzione\t%3d\t%3d\t\t%3.3f",scambio,confronto,((double)(end-start))/CLK_TCK);

	copia(a,lista,n);
	start=clock();
	quick_sort(a,0,n-1);
	end=clock();
	printf(" ok\nQuick Sort\t%3d\t%3d\t\t%3.3f",scambio,confronto,((double)(end-start))/CLK_TCK);

	copia(a,lista,n);
	start=clock();
	merge_sort(a,0,n-1);
	end=clock();
	printf(" ok\nMerge Sort\t%3d\t%3d\t\t%3.3f",scambio,confronto,((double)(end-start))/CLK_TCK);

	copia(a,lista,n);
	start=clock();
	heap_sort(a,n);
	end=clock();
	printf(" ok\nHeap Sort \t%3d\t%3d\t\t%3.3f",scambio,confronto,((double)(end-start))/CLK_TCK);

	copia(a,lista,n);
	start=clock();
	radix_sort(a,n);
	end=clock();
	printf(" ok\nRadix Sort\t%3d\t%3d\t\t%3.3f",scambio,confronto,((double)(end-start))/CLK_TCK);

	puts(" ok\n\nPremere invio per proseguire...");
	fflush(stdin);
	getchar();
}

void lettura(int *a, int n) {
int i;

	puts("\n\t\t\t\t ***L I S T A***");
	for(i=0;i<n;i++)
		printf("%.4d ",a[i]);
	fflush(stdin);
	getchar();
}

/* SELEZIONE */
void selezione(int *a, int n) {
int i,j,min;

	for(i=0;i<n-1;i++) {
   	min=i;
  		for(j=i+1;j<n;j++) {
      	confronto++;
  			if(a[j]<a[min]) min=j;
		}
		scambio++;
		scambia(&a[i],&a[min]);
	}
}

/* INSERZIONE */
void inserzione(int *a, int primo, int ultimo)
{
		int i,j,prossimo;

	for(i=primo;i<ultimo;i++)
	{
		prossimo=a[i];
		for(j=i-1;j>=primo && prossimo<a[j];j--)
		{
   		scambio++;confronto++;
	   	a[j+1]=a[j];
		}
  		scambio++;
		a[j+1]=prossimo;
	}
}

/* QUICK SORT */
void quick_sort(int *a, int u, int v) {
int p;

	confronto++;
	if(v==u)	return;
	p=perno(a,u,v);
	confronto++;
	if(u<p) quick_sort(a,u,p-1);
	confronto++;
	if(p<v) quick_sort(a,p+1,v);
}


int perno(int *a, int primo, int ultimo) {
int i=primo,j=ultimo+1,pivot=a[primo];

	do	{
   	do i++; while(a[i]<pivot && i<j);
		do j--; while(a[j]>pivot && j>primo);
		if(i<j) { scambio++; scambia(&a[i],&a[j]); }
	}
	while(i<j);
	scambio++;
	scambia(&a[primo],&a[j]);

	return j;
}

void scambia(int *a1, int *a2) {
int app;

	app=*a1;
	*a1=*a2;
	*a2=app;
}

/* MERGE SORT */
void merge_sort(int *a, int lower, int upper) {
int medium;

	confronto++;
	if(lower<upper) {
		medium=(lower+upper)/2;
		merge_sort(a,lower,medium);
		merge_sort(a,medium+1,upper);
		merge(a,lower,medium,upper);
	}
}


void merge(int *a, int i, int m, int n) {
int ordinata[MAX],j,k,t,inizio=i;

	j=m+1;
	k=i;
	while(i<=m && j<=n) {
		confronto++;
		if(a[i]<a[j])
	  		ordinata[k++]=a[i++];
		else
  			ordinata[k++]=a[j++];
	}
	if(i>m)
 		for(t=j;t<=n;t++) ordinata[k+t-j]=a[t];
	else
   	for(t=i;t<=m;t++) ordinata[k+t-i]=a[t];

	for(t=inizio;t<=n;t++) { scambio++;a[t]=ordinata[t]; }
}

/* HEAP SORT */
void heap_sort(int *a, int n) {
int i,park;

	for(i=n/2;i>0;i--) adatta(a,i,n);
	for(i=n-1;i>0;i--) {
		scambio++;
		park=a[1];
		a[1]=a[i+1];
		a[i+1]=park;
		adatta(a,1,i);
	}
}

void adatta(int *a, int radice, int n) {
int figlio,temp,chiave;

	temp=a[radice];
	chiave=a[radice];
	figlio=2*radice;
	while(figlio<=n) {
		confronto++;
		if((figlio<n) && a[figlio]<a[figlio+1])
		  	figlio++;
		confronto++;
		if(chiave>a[figlio])
		  	break;
		else {
   		scambio++;
		   a[figlio/2]=a[figlio];
   		figlio*=2;
		}
	}
	scambio++;
	a[figlio/2]=temp;
}

/* RADIX SORT */
void radix_sort(int *a, int n) {
		int i;

   free_list(&testa);
	for(i=0;i<n;i++)
		testa=crea_lista(testa,a[i]);
	testa=radice_sort(testa);
}

lista_ptr crea_lista(lista_ptr inizio, int q) {
		lista_ptr temp,succ;
		int j,r;
		succ=inizio;

	if((temp=(lista_ptr)malloc(sizeof(lista)))==NULL)
	  	{ puts("Problemi di allocazione");exit(1); }

	temp->link=NULL;
	for(j=MAX_CIFRE-1;j>=0;j--) {
   	r=q%10;
	   q=q/10;
   	temp->chiave[j]=r;
	}
	if(!inizio)
  		return(temp);
	while(succ->link)
  		succ=succ->link;
	succ->link=temp;
	return(inizio);
}

lista_ptr radice_sort(lista_ptr ptr) {
		lista_ptr davanti[RADICE_SIZE],dietro[RADICE_SIZE];
		int i,j,cifra;

	for(i=MAX_CIFRE-1;i>=0;i--) {
   	for(j=0;j<RADICE_SIZE;j++) davanti[j]=dietro[j]=NULL;
		while(ptr) {
			cifra=ptr->chiave[i];
		   if(!davanti[cifra]) davanti[cifra]=ptr;
		   else					  dietro[cifra]->link=ptr;
		   dietro[cifra]=ptr;
		   ptr=ptr->link;
		}
		ptr=NULL;
		for(j=RADICE_SIZE-1;j>=0;j--)
		 	if(davanti[j]) {
				dietro[j]->link=ptr;
				ptr=davanti[j];
		   }
	}
	return ptr;
}

void free_list(lista_ptr *p) {
/* Dealloca tutti i nodi della lista in ingresso */
		lista_ptr kill;

	while(*p) {
   	kill=*p;
      *p=(*p)->link;
      free(kill);
   }
}
