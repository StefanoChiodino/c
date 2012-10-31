#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"
#define MAX_CIFRE 4
#define RADICE_SIZE 10

typedef struct ele
{
    int key[MAX_CIFRE];
    struct ele *next;
} *lista;

lista push(lista testa, int key)
{
      lista tmp;
      int i;
      tmp=(lista)malloc(sizeof(struct ele));
      for(i=MAX_CIFRE-1; i>=0; i--, key/=10)
          tmp->key[i]=key%10;
      tmp->next=testa;
      return tmp;
}

lista add(lista testa, int *elementi)
{
    int max_num=pow(10,MAX_CIFRE)-1,key;
    printf("\nInserisci gli elementi ( 0 - %d)\n"
           "Inserisci una chiave fuori misura per uscire\n\n",max_num);
    do
    {
        printf("Chiave num %d: ",*elementi);
        scanf("%d",&key);
        if(key < max_num && key > 0)
        {
            testa=push(testa,key);
            (*elementi)++;
        }
    }while(key < max_num && key > 0);
    return testa;
}

void stampa(lista scroll)
{
     int i;
     while(scroll)
     {
         for(i=0; i<MAX_CIFRE; i++)
             if(scroll->key[i])
                 printf("%d",scroll->key[i]);
         printf(" -> ");
         scroll=scroll->next;
     }
}

lista radix(lista scroll) {
    lista davanti[RADICE_SIZE], dietro[RADICE_SIZE];
    int i,j,cifra;
	for(i=MAX_CIFRE-1; i>=0; i--)//LSD
    {
		for(j=0; j<RADICE_SIZE; j++)
			davanti[j]=dietro[j]=NULL;

        for(; scroll; scroll=scroll->next)
        {
			cifra=scroll->key[i];
			if(!davanti[cifra])
		   	    davanti[cifra]=scroll;
			else
				dietro[cifra]->next=scroll;
		   dietro[cifra]=scroll;
		}

		scroll=NULL;
		for(j=RADICE_SIZE-1; j>=0; j--)//ristabilisce la lista concatenata per il passo successivo
			if(davanti[j])
			{
				dietro[j]->next=scroll;
				scroll=davanti[j];
			}
	}
	printf("Elementi ordinati!");
	return scroll;
}

lista empty(lista scroll)
{
    lista padre;
    while(scroll)
    {
        padre=scroll;
        scroll=scroll->next;
        free(padre);
    }
    return NULL;
}

int main()
{
    lista testa=NULL;
    int scelta,elementi=0;
    do
    {
        pulisci;
        printf("Ordinamento per radice\n\n"
               "1)Inserisci elementi\n"
               "2)Stampa gli elementi\n"
               "3)ordina gli elementi\n"
               "4)cancella tutti gli elementi\n"
               "0)esci\n");
        scanf("%d",&scelta);
        pulisci;
        switch(scelta)
        {
            case 1:
                 testa=add(testa,&elementi);
                 break;
            case 2:
                 stampa(testa);
                 break;
            case 3:
                 testa=radix(testa);
                 break;
            case 4:
                 testa=empty(testa);
                 break;
            case 0:
                 return 0;
            default:
                 printf("\n\nScelta sbagliata!");
        }
        pause();
    }while(1);
}
