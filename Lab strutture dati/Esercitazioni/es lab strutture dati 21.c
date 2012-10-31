/* Stefano Chiodino 39962 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#define MAX_WORDS 100
#define MAX_CHAR 30

typedef struct parola
{
    char word[MAX_CHAR];
}vocabolo;

int add(vocabolo dizionario[], int size)
{
 	int flag;
    if(size < MAX_WORDS)
    {
        printf("Inserire Q per uscire\n");
        flag=1;
        while(flag)
        {
            printf("%d: ",size);
            scanf("%s",&dizionario[size].word);
            if(!((dizionario[size].word[0]=='q' || dizionario[size].word[0]=='Q') && dizionario[size].word[1]=='\0'))
            {
		  	    size++;
		  	    if(size==MAX_WORDS)
		  	        flag=0;
		  	}
		    else
		  	    flag=0;
        }
    }
    if(size == MAX_WORDS)
        printf("E' stato raggiunto il limite massimo di parole!");
    return size;
}

int empty(int size)
{
 	if(size>1)
 	    return 1;
    printf("Nessun vocabolo presente nel dizionario!");
    return 0;
}

void stampa(vocabolo dizionario[],int size)
{
    if(empty(size))
    {
		int i;
		for(i=1; i<size; i++)
			printf("%d: %s\n",i,dizionario[i].word);
		printf("\n%d parole nel dizionario",size-1);
    }
}

void adatta(vocabolo dizionario[],int radice,int size) {
    int figlio;
    char chiave[MAX_CHAR];
    vocabolo tmp;
	tmp=dizionario[radice];
	strcpy(chiave,dizionario[radice].word);
	figlio=2*radice;//figlio sinistro
	while(figlio<=size) {
		if((figlio<size) && (strcmp(dizionario[figlio].word,dizionario[figlio+1].word)<0) )//si sposta al figlio dx se è più grande
		    figlio++;
		if(strcmp(chiave,dizionario[figlio].word)>=0)//se il padre è più grande del maggiore dei figli
		    break;
		else//se no scambia figlio con padre
		{
			dizionario[figlio/2]=dizionario[figlio];
			figlio*=2;
		}
	}
	dizionario[figlio/2]=tmp;
}

void heap_sort(vocabolo dizionario[],int size)
{
    if(empty(size))
    {
        int i;
    	vocabolo tmp;
    	for(i=size/2;i>0;i--)//adatta tutti i nodi 0<i<n/2 (non foglie)
            adatta(dizionario,i,size);
    	for(i=size; i>0; )//scambia il primo e l'ultimo elemento e riadatta il nuovo vettore escludendo gli elementi messi alla fine (già ordinati)
        {
    		tmp=dizionario[1];
    		dizionario[1]=dizionario[i];
    		dizionario[i]=tmp;
    		adatta(dizionario,1,--i);

    	}
    	printf("Parole ordinate!");
     }
}

int main()
{
    vocabolo dizionario[MAX_WORDS];
    int scelta,size=1;
    do
    {
        pulisci
        printf("Ordinamento di un dizionario mediante heapsort\n\n"
               "1)inserire nuovi vocaboli\n"
               "2)Stampare il dizionario\n"
               "3)Ordinare le parole\n"
               "0)uscire\n");
        scanf("%d",&scelta);
        pulisci
        switch(scelta)
        {
            case 0:
            return 0;
            case 1:
            size=add(dizionario, size);
            break;
            case 2:
            stampa(dizionario, size);
            break;
            case 3:
            heap_sort(dizionario, size);
            break;
            default :
            printf("Scelta errata!");
        }
        pause();
    }while(1);
}
