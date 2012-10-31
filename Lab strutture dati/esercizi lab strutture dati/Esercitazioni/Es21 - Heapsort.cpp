#include <stdio.h>
#include <string.h>
#include <conio.h>

#define MAX 20

struct diz {
		 char parola[MAX];
};

typedef struct diz Sd;

Sd dizionario[MAX];

int inserimento(void);
void adatta(Sd d[],int,int);
void heap_sort(Sd d[],int);
void lettura(int);

main() {
	int n;
	n=inserimento();
	lettura(n);
	heap_sort(dizionario,n);
	lettura(n);
}

int inserimento(void) {
int i=0;

	printf("\n\t I N S E R I M E N T O \n");
	printf("\n\tInserisci le parole (Max %d caratteri)\n",MAX);
	printf("\tInserire -end- per terminare\n");

	do {
		printf("\tDizionario[%d]: ",++i);
		scanf("%s", &dizionario[i].parola);
	}
	while (strcmp(dizionario[i].parola,"end"));

   return i-1;
}


void heap_sort(Sd d[],int n) {
int i;

	Sd park;
	for(i=n/2;i>0;i--) adatta(d,i,n);
	for(i=n-1;i>0;i--) {
		park=d[1];
		d[1]=d[i+1];
		d[i+1]=park;
		adatta(d,1,i);
	}
}


void adatta(Sd d[],int radice,int n) {
int figlio;
Sd temp,chiave;

	temp=d[radice];
	chiave=d[radice];
	figlio=2*radice;
	while(figlio<=n) {
		if((figlio<n) && (strcmp(d[figlio].parola,d[figlio+1].parola)<0) )
		figlio++;
		if(strcmp(chiave.parola,d[figlio].parola)>0) break;
		else {
			d[figlio/2]=d[figlio];
			figlio*=2;
		}
	}
	d[figlio/2]=temp;
}


void lettura(int n) {
int i;

	printf("\n\t L E T T U R A \n");
	for(i=1;i<=n;i++)
		printf("\n\tDizionario[%d]: %s",i,dizionario[i].parola);

	fflush(stdin);
	getchar();
}
