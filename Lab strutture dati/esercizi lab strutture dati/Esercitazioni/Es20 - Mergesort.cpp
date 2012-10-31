#include <stdio.h>
#include <string.h>
#include <conio.h>

#define MAX 20

typedef struct {
 		 char cognome[MAX];
       char nome[MAX];
       char indirizzo[MAX];
       float telefono;
       int link;
} ele;

int inserimento(ele lista[]);
void lettura(ele lista[],int);
void mergesort(ele lista[],int,int);
void merge(ele lista[],int,int,int);
void menu(void);

main() {
	ele agenda[MAX];
	int scelta,n=0;

   do {
   	menu();
		scanf("%d", &scelta);
		switch(scelta) {
			case 0:  { printf("\n\t\tF i n e !"); break; }
			case 1:  { n=inserimento(agenda); break; }
			case 2:  { lettura(agenda,n); break; }
			case 3:  { mergesort(agenda,0,n-1);
	         			puts("\nAgenda ordinata!");
							fflush(stdin);
							getchar();
							break;
      	}
			default: { printf("\tScelta errata!"); break; }
		}
   }
   while(scelta);

}

int inserimento(ele agenda[]) {
int i=-1;
	printf("\n\t I N S E R I M E N T O ");
	printf("\n\t-inserire 0 nel telefono per terminare-\n");

	do {
		printf("\n\tAgenda[%d]\n",++i);
		printf("\tTelefono: ");
		scanf("%f", &agenda[i].telefono);
		if(agenda[i].telefono) {
			printf("\tNome: ");
			scanf("%s", &agenda[i].nome);
			printf("\tCognome: ");
			scanf("%s", &agenda[i].cognome);
			printf("\tIndirizzo: ");
			scanf("%s", &agenda[i].indirizzo);
      }
	}
	while(agenda[i].telefono);

	return i;
}


void lettura(ele lista[],int n) {
int i;

	printf("\n\t**** L E T T U R A  *****\n");
	for(i=0;i<n;i++) {
		printf("\n\tAgenda[%2d]", i);
		printf("\n\tCognome: %s", lista[i].cognome);
		printf("\n\tNome: %s", lista[i].nome);
		printf("\n\tIndirizzo: %s", lista[i].indirizzo);
		printf("\n\t%.0f\n", lista[i].telefono);
	}

	fflush(stdin);
	getchar();
}


void mergesort(ele lista[],int lower,int upper) {
int medium;

	if(lower<upper) {
		medium=(lower+upper)/2;
		mergesort(lista,lower,medium);
		mergesort(lista,medium+1,upper);
		merge(lista,lower,medium,upper);
	}
}


void merge(ele lista[],int i,int m,int n) {
ele ordinata[MAX];
int j,k,t,inizio=i;

	j=m+1;
	k=i;

	while(i<=m && j<=n) {
		if(strcmp(lista[i].cognome,lista[j].cognome)<=0)
	  		ordinata[k++]=lista[i++];
		else
	  		ordinata[k++]=lista[j++];
	}

	if(i>m)
		for(t=j;t<=n;t++) ordinata[k+t-j]=lista[t];
	else
		for(t=i;t<=m;t++) ordinata[k+t-i]=lista[t];

	for(t=inizio;t<=n;t++) lista[t]=ordinata[t];
}

void menu(void) {

		printf("\n\n\t ^^^^^^^^^^^^^^^^^^^^^ MERGESORT ^^^^^^^^^^^^^^^^^^^^^");
		printf("\n\n\t\t1 - Inserimento Dati");
		printf("\n\t\t2 - Lettura");
		printf("\n\t\t3 - Ordinamento");
		printf("\n\t\t0 - Uscita");
		printf("\n\tScelta: ");

}
