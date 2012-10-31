#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#define MAX_CIFRE 4
#define RADICE_SIZE 10

typedef struct list_node *list_pointer;
typedef struct list_node{
 		  int chiave[MAX_CIFRE];
        list_pointer link;
} lista;

list_pointer testa = NULL;

void inserimento(void);
list_pointer radice_sort(list_pointer);
void lettura(list_pointer);
list_pointer crea_lista(list_pointer,int);
void menu(void);

main() {
int scelta;

	do {
	   menu();
		scanf("%d", &scelta);
		switch(scelta) {
			case 0:  { puts("\n\t\tF i n e !"); break; }
			case 1:  { inserimento(); break; }
		   case 2:  { testa=radice_sort(testa); lettura(testa); break; }
			default: { puts("\tScelta errata!"); break; }
	  }
	}
	while(scelta);

 fflush(stdin);
 getchar();
}

void inserimento(void) {
int i,num,max,n;

	max=pow(10,MAX_CIFRE)-1;     // max=9999
	puts("\n\t** I N S E R I M E N T O **");
	printf("\t - massimo %d cifre \n", max);
	printf("\n\tQuanti elementi vuoi inserire? ->");
	scanf("%d",&n);
	for(i=0;i<n;i++) {
		do {
			printf("\tChiave %2d : ",i);
			scanf("%d", &num);
		}
		while(num>max || num<0);
		testa=crea_lista(testa,num);
	}
}

list_pointer crea_lista(list_pointer inizio,int q) {
list_pointer temp,succ;
int j,r;

	succ=inizio;

	if((temp=(list_pointer)malloc(sizeof(lista)))==NULL) {
   	puts("Problemi di allocazione");exit(1);
   }

	temp->link=NULL;
	for(j=MAX_CIFRE-1;j>=0;j--) {
		r=q%10;
		q=q/10;         // divide per il passo successivo
		temp->chiave[j]=r;
	}

   if(!inizio)
		return(temp);     // temp é il primo nodo della lista

	while(succ->link)
	  	succ=succ->link;

	succ->link=temp;
	return(inizio);
}


list_pointer radice_sort(list_pointer ptr) {
list_pointer davanti[RADICE_SIZE],dietro[RADICE_SIZE];
int i,j,cifra;

	for(i=MAX_CIFRE-1;i>=0;i--) {
		for(j=0;j<RADICE_SIZE;j++)
			davanti[j]=dietro[j]=NULL;

      while(ptr) {
			cifra=ptr->chiave[i];
			if(!davanti[cifra])
		   	davanti[cifra]=ptr;
			else
				dietro[cifra]->link=ptr;

		   dietro[cifra]=ptr;
			ptr=ptr->link;
		}                 //ristabilisce la lista concatenata per il passo successivo

		ptr=NULL;
		for(j=RADICE_SIZE-1;j>=0;j--)
			if(davanti[j]) {
				dietro[j]->link=ptr;
				ptr=davanti[j];
			}
	}
	return ptr;
}

void lettura(list_pointer ptr) {
int i,n=0;

	puts("\n\n\t** L E T T U R A  **");

   while(ptr) {
		printf("\n\tchiave %2d: ->",n++);
		for(i=0;i<MAX_CIFRE;i++)
			printf("%d", ptr->chiave[i]);
		ptr=ptr->link;
	}

	fflush(stdin);
	getchar();
}



void menu(void) {
		puts("\n\n\t ^^^^^^^^^^^^^^^^^^^^^^^^^ RADIXSORT ^^^^^^^^^^^^^^^^^^^^^^^^^");
		puts("\n\n\t\t1 - Inserimento");
		puts("\t\t2 - Lettura");
		puts("\t\t0 - Uscita");
		printf("  \tScelta: ");
}
